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
#include "../inc/main.h"

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
 ** This sample toggle GPIOA.07
 **
 ******************************************************************************/

/**
 * @brief  使用BTIM1作为GTIM的分频器，对PCLK进行48000分频
 * @return int32_t 
 */
int32_t main(void)
{
  GTIM_InitTypeDef GTIM_InitStruct;
  BTIM_TimeBaseInitTypeDef BTIM_InitStruct;

  /* System Clocks Configuration */
  RCC_Configuration();  

  /* GPIO Configuration */
  GPIO_Configuration();

  /* NVIC Configuration */
  NVIC_Configuration();  

  GTIM_InitStruct.Mode = GTIM_MODE_COUNTER;
  GTIM_InitStruct.OneShotMode = GTIM_COUNT_CONTINUE;
  GTIM_InitStruct.Prescaler = GTIM_PRESCALER_DIV1;
  GTIM_InitStruct.ReloadValue = 999;
  GTIM_InitStruct.ToggleOutState = DISABLE;
  GTIM_TimeBaseInit(&GTIM_InitStruct);

  GTIM_ITRConfig(ITR_SOURCE_BTIM1);

  BTIM_InitStruct.BTIM_Mode = BTIM_Mode_TIMER;
  BTIM_InitStruct.BTIM_OPMode = BTIM_OPMode_Repetitive;
  BTIM_InitStruct.BTIM_Period = 47999;
  BTIM_InitStruct.BTIM_Prescaler = BTIM_PRS_DIV1;
  BTIM_TimeBaseInit(CW_BTIM1, &BTIM_InitStruct);

  GTIM_ITConfig(GTIM_IT_OV, ENABLE);

  GTIM_Cmd(ENABLE);
  BTIM_Cmd(CW_BTIM1, ENABLE);

  while (1)
  {
    
  }
}

/**
  * @brief  Configures the different system clocks.
  * @param  None
  * @retval None
  */
void RCC_Configuration(void)
{
  //    CW_SYSCTRL->APBEN1_f.GTIM = 1U;    //
  __RCC_FLASH_CLK_ENABLE();    // 打开FLASH时钟
  FLASH_SetLatency(FLASH_Latency_2);    // 频率大于24M需要配置FlashWait=2
  RCC_HSI_Enable(RCC_HSIOSC_DIV1);
  
  __RCC_BTIM_CLK_ENABLE();
  __RCC_GTIM_CLK_ENABLE();
  __RCC_GPIOA_CLK_ENABLE();
}

/**
  * @brief  Configure the GPIO Pins.
  * @param  None
  * @retval None
  */
void GPIO_Configuration(void)
{
  PA07_DIGTAL_ENABLE();
  PA07_DIR_OUTPUT();
  PA07_PUSHPULL_ENABLE();

}

/**
  * @brief  Configure the nested vectored interrupt controller.
  * @param  None
  * @retval None
  */
void NVIC_Configuration(void)
{
  __disable_irq(); 
  NVIC_EnableIRQ(GTIM_IRQn); 
  __enable_irq();  
}

void GTIM_IRQHandlerCallBack(void)
{
  if (GTIM_GetITStatus(GTIM_IT_OV))
  {
    GTIM_ClearITPendingBit(GTIM_IT_OV);
    PA07_TOG();
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

