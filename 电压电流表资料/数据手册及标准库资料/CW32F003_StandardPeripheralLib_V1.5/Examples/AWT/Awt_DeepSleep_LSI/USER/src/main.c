/**
 * @file main.c
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2021-05-18
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
#include "cw32f003_rcc.h"
/******************************************************************************
 * Local pre-processor symbols/macros ('#define')
 ******************************************************************************/

/******************************************************************************
 * Global variable definitions (declared in header file with 'extern')
 ******************************************************************************/

/******************************************************************************
 * Local type definitions ('typedef')
 ******************************************************************************/

/******************************************************************************
 * Local function prototypes ('static')
 ******************************************************************************/
void RCC_Configuration(void);
void GPIO_Configuration(void);
void NVIC_Configuration(void);

/******************************************************************************
 * Local variable definitions ('static')                                      *
 ******************************************************************************/
 AWT_TimeCntInitTypeDef AWT_TimeCntInitStruct;
 
 uint8_t intflag;
/******************************************************************************
 * Local pre-processor symbols/macros ('#define')
 ******************************************************************************/

/*****************************************************************************
 * Function implementation - global ('extern') and local ('static')
 ******************************************************************************/


/**
 ******************************************************************************
 ** \brief  Main function of project
 **
 ** \return uint32_t return value, if needed
 **
 ** This sample toggle GPIOA.00
 **
 ******************************************************************************/
int32_t main(void)
{ 
	/* CLK Configuration */
	RCC_Configuration();
  
	/* NVIC Configuration */
  NVIC_Configuration();

  /* GPIO Configuration */
  GPIO_Configuration();
	
	//RCC_SystemCoreClockUpdate( RCC_Sysctrl_GetHClkFreq() );
	
	PA06_SETHIGH();
	PA07_SETHIGH();
	FirmwareDelay(2000000);
	
	PA06_SETLOW();
	PA07_SETLOW();
	FirmwareDelay(2000000);
	
	RCC_LSI_Enable();
	
  AWT_TimeCntStructInit( &AWT_TimeCntInitStruct );
  AWT_TimeCntInitStruct.AWT_ClkSource = AWT_CLKSOURCE_LSI;  
  AWT_TimeCntInitStruct.AWT_Prescaler = AWT_PRS_DIV32768;
  AWT_TimeCntInitStruct.AWT_Mode = AWT_MODE_TIMECNT;
  AWT_TimeCntInitStruct.AWT_Period = 4;
  AWT_TimeCntInit(&AWT_TimeCntInitStruct);
  
	intflag = 0;
  //使能AWT下溢出中断
  AWT_ITConfig(AWT_IT_UD, ENABLE); 
	AWT_Cmd(ENABLE);
		
  while(1)
  {		  
		//进入深度睡眠模式前，须降低系统频率到4M以下。当前为HSIOSC时钟，48M，6分频后HCLK为8M。
		RCC_HSI_Enable( RCC_HSIOSC_DIV12);     //48M/12=4M
		
    SCB->SCR = 0X04;
    __WFI();  
		
		//退出深度睡眠模式，恢复原时钟频率。
    RCC_HSI_Enable( RCC_HSIOSC_DIV6);	     //48M/6=8M			
		
		if(intflag ==1)
		{
			intflag = 0;
			for(uint8_t i = 0; i<6; i++)
			{
				PA06_TOG();
				PA07_TOG();
				FirmwareDelay(100000);
			}			
		}
		FirmwareDelay(500000);
  }
	
}

/**
  * @brief  Configure CLK.
  * @param  None
  * @retval None
  */
void RCC_Configuration(void)
{
	__RCC_AWT_CLK_ENABLE();
	__RCC_GPIOA_CLK_ENABLE();
	__RCC_GPIOB_CLK_ENABLE();
	__RCC_GPIOC_CLK_ENABLE();
}

/**
  * @brief  Configure the GPIO Pins.
  * @param  None
  * @retval None
  */
void GPIO_Configuration(void)
{
	PA06_DIGTAL_ENABLE();
	PA07_DIGTAL_ENABLE();
	PA06_DIR_OUTPUT();
	PA07_DIR_OUTPUT();
	PA06_PUSHPULL_ENABLE();
	PA07_PUSHPULL_ENABLE();
	PA06_SETLOW();
	PA07_SETLOW();
}

/**
  * @brief  Configure the nested vectored interrupt controller.
  * @param  None
  * @retval None
  */
void NVIC_Configuration(void)
{
  __disable_irq();
	NVIC_EnableIRQ(AWT_IRQn);
  __enable_irq();
}



#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{ 
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     tex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

