/**
 * @file main.c
 * @author P&S (you@domain.com)
 * @brief
 * @version 0.1
 * @date 2021-09-23
 *
 * @copyright Copyright (c) 2021
 *
 */
/*******************************************************************************
*
* 代码许可和免责信息
* 武汉芯源半导体有限公司授予您使用所有编程代码示例的非专属的版权许可，您可以由此
* 生成根据您的特定需要而定制的相似功能。根据不能被排除的任何法定保证，武汉芯源半
* 导体有限公司及其程序开发商和供应商对程序或技术支持（如果有）不提供任何明示或暗
* 含的保证或条件，包括但不限于暗含的有关适销性、适用于某种特定用途和非侵权的保证
* 或条件。
* 无论何种情形，武汉芯源半导体有限公司及其程序开发商或供应商均不对下列各项负责，
* 即使被告知其发生的可能性时，也是如此：数据的丢失或损坏；直接的、特别的、附带的
* 或间接的损害，或任何后果性经济损害；或利润、业务、收入、商誉或预期可节省金额的
* 损失。
* 某些司法辖区不允许对直接的、附带的或后果性的损害有任何的排除或限制，因此某些或
* 全部上述排除或限制可能并不适用于您。
*
*******************************************************************************/
/******************************************************************************
 * Include files
 ******************************************************************************/
#include "main.h"


/******************************************************************************
 * Local pre-processor symbols/macros ('#define')
 ******************************************************************************/


/******************************************************************************
 * Global variable definitions (declared in header file with 'extern')
 ******************************************************************************/
uint16_t valueAdc;
uint32_t valueAdcAcc;
volatile uint8_t gFlagIrq;
uint16_t gCntEoc = 0;
uint8_t cntSample;
float fTsDegree;
//...
uint32_t valuePeriod;
uint32_t valuePosWidth;
uint32_t valueReload = 0xFFFFu;
/******************************************************************************
 * Local type definitions ('typedef')
 ******************************************************************************/

/******************************************************************************
 * Local function prototypes ('static')
 ******************************************************************************/

/******************************************************************************
 * Local variable definitions ('static')                                      *
 ******************************************************************************/


/******************************************************************************
 * Local pre-processor symbols/macros ('#define')
 ******************************************************************************/

/*****************************************************************************
 * Function implementation - global ('extern') and local ('static')
 ******************************************************************************/
/**
 * @brief PWM I/O初始化
 *
 */
void PWM_PortInit(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;

	/* PA6 PWM 输出 */
	__RCC_GPIOA_CLK_ENABLE();
	
	GPIO_InitStructure.Pins = GPIO_PIN_6;
	GPIO_InitStructure.Mode = GPIO_MODE_OUTPUT_PP;
	
	GPIO_Init(CW_GPIOA, &GPIO_InitStructure);

	PA06_AFx_GTIMCH3();
}

/**
 * @brief ADC I/O初始化
 * 
 */
void ADC_PortInit(void)
{
    //打开GPIO时钟
    REGBITS_SET( CW_SYSCTRL->AHBEN, SYSCTRL_AHBEN_GPIOA_Msk );
    //打开ADC时钟
    REGBITS_SET( CW_SYSCTRL->APBEN2, SYSCTRL_APBEN2_ADC_Msk );

    //set PA01 as AIN1 INPUT
    PA01_ANALOG_ENABLE();
}

/**
 * @brief LED I/O初始化
 * 
 */
void LED_Init(void)
{
	  GPIO_InitTypeDef  GPIO_InitStructure;
 
	  //打开GPIO时钟
	  REGBITS_SET( CW_SYSCTRL->AHBEN, SYSCTRL_AHBEN_GPIOA_Msk);

	  /* Configure the GPIO_LED pin */
	  GPIO_InitStructure.Pins = GPIO_PIN_7;
	  GPIO_InitStructure.Mode = GPIO_MODE_OUTPUT_PP;
	  
	  GPIO_Init(CW_GPIOA, &GPIO_InitStructure);

	  //LEDs are off.	  
	  PA07_SETLOW();
}

void BTIM_Init(void)
{
  BTIM_TimeBaseInitTypeDef BTIM_InitStructure;
  
  __RCC_BTIM_CLK_ENABLE();
  BTIM_InitStructure.BTIM_Mode = BTIM_Mode_TIMER;
  BTIM_InitStructure.BTIM_OPMode = BTIM_OPMode_Repetitive;
  BTIM_InitStructure.BTIM_Prescaler = BTIM_PRS_DIV1024;   // 46875Hz的频率
  BTIM_InitStructure.BTIM_Period = 46874;      // 约1s溢出 

  BTIM_TimeBaseInit(CW_BTIM1, &BTIM_InitStructure);
  BTIM_ITConfig(CW_BTIM1, BTIM_IT_OV, ENABLE);
  NVIC_EnableIRQ(BTIM1_IRQn);
  BTIM_Cmd(CW_BTIM1, ENABLE);
  
}

/**
 * @brief GTIM初始化
 * 
 */
void GTIM_Init(void)
{
	GTIM_InitTypeDef GTIM_InitStruct;

	//打开GTIM时钟
	__RCC_GTIM_CLK_ENABLE();

	GTIM_InitStruct.Mode = GTIM_MODE_TIME;
	GTIM_InitStruct.OneShotMode = GTIM_COUNT_CONTINUE;
	GTIM_InitStruct.Prescaler = GTIM_PRESCALER_DIV1024;
	GTIM_InitStruct.ReloadValue = 0xFFFFu;
	GTIM_InitStruct.ToggleOutState = ENABLE;

	GTIM_TimeBaseInit(&GTIM_InitStruct);

	valuePeriod = GTIM_InitStruct.ReloadValue;
	valuePosWidth = valuePeriod >> 1u;

	GTIM_OCInit(GTIM_CHANNEL3, GTIM_OC_OUTPUT_PWM_HIGH);
	GTIM_SetCompare3(valuePosWidth);

	//GTIM_ITConfig(CW_GTIM2, GTIM_IT_OV, ENABLE);
	GTIM_Cmd(ENABLE);
}

/**
 * @brief Main function of project
 * 
 * @return int 
 */
int main(void)
{	
	ADC_InitTypeDef ADC_InitStructure;
	ADC_WdtTypeDef ADC_WdtStructure;
	ADC_SingleChTypeDef ADC_SingleChStructure;
  
  //打开FLASH时钟
	__RCC_FLASH_CLK_ENABLE();
	FLASH_SetLatency(FLASH_Latency_3);
	RCC_HSI_Enable(RCC_HSIOSC_DIV1);
	

	//配置ADC测试IO口
	ADC_PortInit();

	//LED初始化
	LED_Init();

	PWM_PortInit();
  BTIM_Init();
	GTIM_Init();

	//ADC默认值初始化
	ADC_StructInit(&ADC_InitStructure);
	//ADC模拟看门狗通道初始化
	ADC_WdtInit(&ADC_WdtStructure);

	ADC_InitStructure.ADC_ClkDiv = ADC_Clk_Div128;    //ADCCLK:500KHz.
	ADC_InitStructure.ADC_InBufEn = ADC_BufEnable;
	ADC_InitStructure.ADC_SampleTime = ADC_SampTime10Clk;

	//配置单通道转换模式
	ADC_SingleChStructure.ADC_DiscardEn = ADC_DiscardNull;
	ADC_SingleChStructure.ADC_Chmux = ADC_ExInputCH1; //选择ADC转换通道
	ADC_SingleChStructure.ADC_InitStruct = ADC_InitStructure;
	ADC_SingleChStructure.ADC_WdtStruct = ADC_WdtStructure;

	ADC_SingleChOneModeCfg(&ADC_SingleChStructure);
	ADC_ITConfig(ADC_IT_EOC, ENABLE);

	ADC_EnableIrq(ADC_INT_PRIORITY);
	ADC_ClearITPendingAll();

	//ADC使能
	ADC_Enable();

	//ADC外部中断触发源配置
	ADC_ExtTrigCfg(ADC_TRIG_BTIM1, ENABLE);
	BTIM_Cmd(CW_BTIM1, ENABLE);

	while (1)
	{
		while (!(gFlagIrq & ADC_ISR_EOC_Msk));
		gFlagIrq = 0u;
		PA07_TOG();


		valueAdc = ADC_GetConversionValue();
		//positive slope
        //valueReload =(4095u * 62500ul) / (4999u * valueAdc + 4095u);
        valueReload =((4095u * 125000ul) / (4999u * valueAdc + 4095u) + 1) >> 1;//Rounding.
		valuePosWidth = valueReload >> 1u;
                
		GTIM_SetCounterValue(0u);     //reset.
		GTIM_SetReloadValue(valueReload);
		GTIM_SetCompare3(valuePosWidth);
		//等待ADC外部中断触发源启动下一次ADC转换
	}
}

/******************************************************************************
 * EOF (not truncated)
 ******************************************************************************/
#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @return None
  */
void assert_failed(uint8_t *file, uint32_t line)
{ 
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     tex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

