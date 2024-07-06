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
#include "cw32f003_gpio.h"
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
 ** This sample toggle MCO
 ** PA01: MCO
 ******************************************************************************/
int32_t main(void)
{
  uint8_t i = 0;
  RCC_HSI_Enable(RCC_HSIOSC_DIV2); //24M
  __RCC_GPIOB_CLK_ENABLE();

  CW_GPIOB->ANALOG_f.PIN5 = 0; // digital
  CW_GPIOB->DIR_f.PIN5 = 1;    // input
  while (1)
  {
    while (CW_GPIOB->IDR_f.PIN5 == 1)
      ; // 等按键key1按下

    FirmwareDelay(1000); // 按键去抖
    if (CW_GPIOB->IDR_f.PIN5 == 0)
    {
      i++;
      if (i > 7)
      {
        i = 0;
      }
    }
    while (CW_GPIOB->IDR_f.PIN5 == 0);  // 等按键释放

    switch (i)
    {
    case 0:
      RCC_MCO_OUT(RCC_MCO_SRC_NONE, RCC_MCO_DIV1);
      break;
    default:
    case 1:
      /********************************************************************
         1. MCO toggle HCLK Test. MCO_CLK = HCLK
         *******************************************************************/
      RCC_MCO_OUT(RCC_MCO_SRC_HCLK, RCC_MCO_DIV1);
      break;
    case 2:
      /********************************************************************
         2. MCO toggle PCLK Test. MCO_CLK = PCLK / 2
        *******************************************************************/
      RCC_MCO_OUT(RCC_MCO_SRC_PCLK, RCC_MCO_DIV2);
      break;
    case 3:
      /********************************************************************
	       3. MCO toggle HSI Test.  MCO_CLK = HSIOSC / 8
	      *******************************************************************/
      RCC_MCO_OUT(RCC_MCO_SRC_HSI, RCC_MCO_DIV8);
      break;
    case 4:
      /********************************************************************
	       4. MCO toggle LSI Test.  MCO_CLK = LSI / 64
	      *******************************************************************/
      RCC_LSI_Enable();
      RCC_MCO_OUT(RCC_MCO_SRC_LSI, RCC_MCO_DIV64);
      break;
    case 5:
      /********************************************************************
	       5. MCO toggle HEX Test. MCO_CLK = HEX / 128
	      *******************************************************************/
      //        RCC_HEX_Enable(RCC_HEX_PINMUX_PB00);
      // 	      RCC_MCO_OUT( RCC_MCO_SRC_HEX , RCC_MCO_DIV128 );
      break;
    case 6:
      /********************************************************************
	       6. MCO toggle RC150K Test. MCO_CLK = RC150K
	       需要开启端口RC150K滤波或者VC滤波
	      *******************************************************************/
      RCC_AHBPeriphClk_Enable(RCC_AHB_PERIPH_GPIOA, ENABLE);       //打开GPIOA时钟
      GPIO_ConfigFilter(CW_GPIOA, GPIO_PIN_2, GPIO_FLTCLK_RC150K); //选择GPIOA.02滤波为RC150K
      RCC_MCO_OUT(RCC_MCO_SRC_RC150K, RCC_MCO_DIV1);
      break;
    case 7:
      /********************************************************************
        	7. MCO toggle RC10K Test. MCO_CLK = RC10K
	        需要开启端口RC10K滤波或者VC滤波
	      *******************************************************************/
      RCC_AHBPeriphClk_Enable(RCC_AHB_PERIPH_GPIOA, ENABLE);      //打开GPIOA时钟
      GPIO_ConfigFilter(CW_GPIOA, GPIO_PIN_2, GPIO_FLTCLK_RC10K); //选择GPIOA.02滤波为RC10K
      RCC_MCO_OUT(RCC_MCO_SRC_RC10K, RCC_MCO_DIV1);
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
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     tex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
