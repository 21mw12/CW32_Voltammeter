/**
* @file main.c
* @author your name (you@domain.com)
* @brief
* @version 0.1
* @date 2021-06-25
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
uint8_t i = 0;
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
******************************************************************************
** \brief  Main function of project
**
** \return uint32_t return value, if needed
**
** This sample HSI switch to LSI, LSI switch to HSI.
**
******************************************************************************/
int32_t main(void)
{
  uint32_t delay = 240000;          // 在24MHz约 100ms   
  RCC_HSI_Enable(RCC_HSIOSC_DIV2); //24M
  RCC_PCLK_OUT(); //通过PB03观察PCLK频率
  RCC_HCLK_OUT(); //通过PB06观察HCLK频率
  __RCC_GPIOB_CLK_ENABLE();
  __RCC_GPIOA_CLK_ENABLE();

  // LED1 
  CW_GPIOA->ANALOG_f.PIN7 = 0;    // digital
  CW_GPIOA->DIR_f.PIN7 = 0;       // output
  CW_GPIOA->OPENDRAIN_f.PIN7 = 0; // push-pull
  CW_GPIOA->ODR_f.PIN7 = 1;       // ouput high

  // KEY1
  CW_GPIOB->ANALOG_f.PIN5 = 0; // digital
  CW_GPIOB->DIR_f.PIN5 = 1;    // input
  CW_GPIOB->FALLIE_f.PIN5 = 1;  // 低电平触发中断
  CW_GPIOB->ICR_f.PIN5 = 0;    // 清中断标志位

  NVIC_EnableIRQ(GPIOB_IRQn);
  //----------------------------------------------------------------------
  //相关程序在中断服务GPIOB_IRQHandler中进行处理

  while (1)
  {
    CW_GPIOA->TOG_f.PIN7 = 1;
    FirmwareDelay(delay);  
    if (i > 2)
    {
      i = 0;
    }

    switch (i)
    {
    default:
    case 0:
      //============================================================================
      //以下从其他源切换到HSI
      RCC_SysClk_Switch(RCC_SYSCLKSRC_HSI);     //切换系统时钟到HSI
      delay = 240000;
      break;
    case 1:
      //============================================================================
      //以下从HSI切换到LSI
      RCC_LSI_Enable();                           //开启内部低速时钟LSI
      RCC_SysClk_Switch(RCC_SYSCLKSRC_LSI);       //切换系统时钟到LSI
      delay = 3300;
      break;
    case 2:
      //============================================================================
      //以下从LSI切换到HEX
      RCC_HEX_Enable(RCC_HEX_PINMUX_PB00);      // PB00输入外部高速时钟
      RCC_SysClk_Switch(RCC_SYSCLKSRC_HEX);     //切换系统时钟到HEX
      delay = 480000;
      break;
    }
  }    
}

  /******************************************************************************
  * EOF (not truncated)
  ******************************************************************************/
#ifdef USE_FULL_ASSERT
  /**
* @brief  Reports the name of the source file and the source line number
*         where the assert_param error has occurred.
* @param  file: pointer to the source file name
* @param  line: assert_param error line source number
* @retval None
*/
  void assert_failed(uint8_t * file, uint32_t line)
  {
    /* USER CODE BEGIN 6 */
    /* User can add his own implementation to report the file name and line number,
  tex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
  }
#endif /* USE_FULL_ASSERT */
