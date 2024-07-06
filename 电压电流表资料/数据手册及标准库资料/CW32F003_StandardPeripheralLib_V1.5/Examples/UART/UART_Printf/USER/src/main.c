/******************************************************************************/
/** \file main.c
 **
 ** A detailed description is available at
 ** @link Sample Group Some description @endlink
 **
 **   - 2021-03-12  1.0  xiebin First version for Device Driver Library of Module.
 **
 ******************************************************************************/
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
//UARTx
#define  DEBUG_USARTx                   CW_UART1
#define  DEBUG_USART_CLK                RCC_APB2_PERIPH_UART1
#define  DEBUG_USART_APBClkENx          RCC_APBPeriphClk_Enable2
#define  DEBUG_USART_BaudRate           9600
#define  DEBUG_USART_UclkFreq           8000000

//UARTx GPIO
#define  DEBUG_USART_TX_GPIO_CLK        RCC_AHB_PERIPH_GPIOB
#define  DEBUG_USART_RX_GPIO_CLK        RCC_AHB_PERIPH_GPIOA
#define  DEBUG_USART_TX_GPIO_PORT       CW_GPIOB   
#define  DEBUG_USART_TX_GPIO_PIN        GPIO_PIN_2
#define  DEBUG_USART_RX_GPIO_PORT       CW_GPIOA
#define  DEBUG_USART_RX_GPIO_PIN        GPIO_PIN_0

//GPIO AF
#define  DEBUG_USART_AFTX               PB02_AFx_UART1TXD()
#define  DEBUG_USART_AFRX               PA00_AFx_UART1RXD()
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
void UART_Configuration(void);

#ifdef __GNUC__
  /* With GCC/RAISONANCE, small printf (option LD Linker->Libraries->Small printf
     set to 'Yes') calls __io_putchar() */
  #define PUTCHAR_PROTOTYPE int __io_putchar(int ch)
#else
  #define PUTCHAR_PROTOTYPE int fputc(int ch, FILE *f)
#endif /* __GNUC__ */

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
 ******************************************************************************/
int32_t main(void)
{ 
  //配置RCC
  RCC_Configuration();

  //配置GPIO
  GPIO_Configuration();

  //配置UART
  UART_Configuration();

  printf("\r\nCW32F003 UART Printf Example\r\n");

  while(1)
  {  

  }    
}

/**
 * @brief 配置RCC
 * 
 */
void RCC_Configuration(void)
{
  //SYSCLK = HSI = 8MHz = HCLK = PCLK
  RCC_HSI_Enable(RCC_HSIOSC_DIV6);

  //外设时钟使能
  RCC_AHBPeriphClk_Enable(DEBUG_USART_TX_GPIO_CLK | DEBUG_USART_RX_GPIO_CLK, ENABLE);
  DEBUG_USART_APBClkENx(DEBUG_USART_CLK, ENABLE);
}

/**
 * @brief 配置GPIO
 * 
 */
void GPIO_Configuration(void)
{
  GPIO_InitTypeDef GPIO_InitStructure;

  //UART TX RX 复用
  DEBUG_USART_AFTX;                     
  DEBUG_USART_AFRX;                     

  GPIO_InitStructure.Pins = DEBUG_USART_TX_GPIO_PIN;
  GPIO_InitStructure.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_Init(DEBUG_USART_TX_GPIO_PORT, &GPIO_InitStructure);
    
  GPIO_InitStructure.Pins = DEBUG_USART_RX_GPIO_PIN;
  GPIO_InitStructure.Mode = GPIO_MODE_INPUT_PULLUP;
  GPIO_Init(DEBUG_USART_RX_GPIO_PORT, &GPIO_InitStructure);
}

/**
 * @brief 配置UART
 * 
 */
void UART_Configuration(void)
{
  USART_InitTypeDef USART_InitStructure;

  USART_InitStructure.USART_BaudRate = DEBUG_USART_BaudRate;
  USART_InitStructure.USART_Over = USART_Over_16;
  USART_InitStructure.USART_Source = USART_Source_PCLK;
  USART_InitStructure.USART_UclkFreq = DEBUG_USART_UclkFreq;
  USART_InitStructure.USART_StartBit = USART_StartBit_FE;
  USART_InitStructure.USART_StopBits = USART_StopBits_1;
  USART_InitStructure.USART_Parity = USART_Parity_No ;
  USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
  USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
  USART_Init(DEBUG_USARTx, &USART_InitStructure); 	
}

/**
 * @brief Retargets the C library printf function to the USART.
 * 
 */
PUTCHAR_PROTOTYPE
{
  USART_SendData_8bit(DEBUG_USARTx, (uint8_t)ch);

  while (USART_GetFlagStatus(DEBUG_USARTx, USART_FLAG_TXE) == RESET);

  return ch;
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

