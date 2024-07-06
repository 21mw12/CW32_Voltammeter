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
//#define  SPI_HARD_TEST
#define  SPI_SOFT_TEST

//UARTx
#define  DEBUG_USARTx                   CW_UART1
#define  DEBUG_USART_CLK                RCC_APB2_PERIPH_UART1
#define  DEBUG_USART_APBClkENx          RCC_APBPeriphClk_Enable2

//UARTx GPIO
#define  DEBUG_USART_TX_GPIO_CLK        RCC_AHB_PERIPH_GPIOB
#define  DEBUG_USART_RX_GPIO_CLK        RCC_AHB_PERIPH_GPIOA
#define  DEBUG_USART_CS_GPIO_CLK        RCC_AHB_PERIPH_GPIOA
#define  DEBUG_USART_TX_GPIO_PORT       CW_GPIOB   
#define  DEBUG_USART_TX_GPIO_PIN        GPIO_PIN_2
#define  DEBUG_USART_RX_GPIO_PORT       CW_GPIOA
#define  DEBUG_USART_RX_GPIO_PIN        GPIO_PIN_0 
#define  DEBUG_USART_CS_GPIO_PORT       CW_GPIOA
#define  DEBUG_USART_CS_GPIO_PIN        GPIO_PIN_1

//SPI GPIO
#define  DEBUG_SPI_SCK_GPIO_CLK         RCC_AHB_PERIPH_GPIOC
#define  DEBUG_SPI_MISO_GPIO_CLK        RCC_AHB_PERIPH_GPIOC
#define  DEBUG_SPI_CS_GPIO_CLK          RCC_AHB_PERIPH_GPIOB
#define  DEBUG_SPI_SCK_GPIO_PORT        CW_GPIOC
#define  DEBUG_SPI_SCK_GPIO_PIN         GPIO_PIN_0
#define  DEBUG_SPI_MISO_GPIO_PORT       CW_GPIOC
#define  DEBUG_SPI_MISO_GPIO_PIN        GPIO_PIN_1
#define  DEBUG_SPI_CS_GPIO_PORT         CW_GPIOB
#define  DEBUG_SPI_CS_GPIO_PIN          GPIO_PIN_6

//GPIO AF
#define  DEBUG_USART_AFTX               PB02_AFx_UART1TXD()
#define  DEBUG_USART_AFRX               PA00_AFx_UART1RXD()
#define  DEBUG_SPI_AFSCK                PC00_AFx_SPISCK()
#define  DEBUG_SPI_AFMISO               PC01_AFx_SPIMISO()
#define  DEBUG_SPI_AFCS                 PB06_AFx_SPICS()

//CS LOW or HIGH
#define  SPI_CS_LOW()     				PA01_SETLOW()
#define  SPI_CS_HIGH()    				PA01_SETHIGH()

//LED GPIO
#define  LED1_GPIO_PORT                 CW_GPIOA
#define  LED1_GPIO_PIN                  GPIO_PIN_7

#define  LED2_GPIO_PORT                 CW_GPIOA
#define  LED2_GPIO_PIN                  GPIO_PIN_6

#define  TxBufferSize1                  (ARRAY_SZ(TxBuffer1) - 1)
#define  TxBufferSize2                  (ARRAY_SZ(TxBuffer2) - 1)

/******************************************************************************
 * Global variable definitions (declared in header file with 'extern')
 ******************************************************************************/

/******************************************************************************
 * Local type definitions ('typedef')
 ******************************************************************************/
typedef enum {FAILED = 0, PASSED = !FAILED} TestStatus;
/******************************************************************************
 * Local function prototypes ('static')
 ******************************************************************************/
void RCC_Configuration(void);
void GPIO_Configuration(void);
void UART_Configuration(void);
void SPI_Configuration(void);
TestStatus Buffercmp(uint8_t* pBuffer1, uint8_t* pBuffer2, uint16_t BufferLength);

/******************************************************************************
 * Local variable definitions ('static')                                      *
 ******************************************************************************/
uint8_t TxBuffer1[] = "\r\nCW32F003 UART Synchronous: UART -> SPI\r\n";
uint8_t TxBuffer2[] = "\r\nCW32F003 UART Synchronous: SPI  -> UART\r\n";
uint8_t RxBuffer1[TxBufferSize2];
uint8_t RxBuffer2[TxBufferSize1];
uint32_t NbrOfDataToRead1 = TxBufferSize2;
uint32_t NbrOfDataToRead2 = TxBufferSize1;
uint8_t TxCounter1 = 0, RxCounter1 = 0;
uint8_t TxCounter2 = 0, RxCounter2 = 0;
volatile TestStatus TransferStatus1 = FAILED, TransferStatus2 = FAILED; 
LED_InitTypeDef LED1;
LED_InitTypeDef LED2;
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

  //配置UART 同步半双工模式
  UART_Configuration();

  //配置SPI 单线半双工模式
  SPI_Configuration();

  /*************************** UART -> SPI *************************/
  USART_DirectionModeCmd(DEBUG_USARTx, USART_Mode_Tx, ENABLE);
  //SPI 仅接收
  SPI_BiDirectionalLineConfig(SPI_Direction_Rx);
   
  //拉低片选
  #ifdef SPI_SOFT_TEST 
  SPI_NSSInternalSoftwareConfig(SPI_NSSInternalSoft_Reset);
  #endif
  #ifdef SPI_HARD_TEST
  SPI_CS_LOW();
  #endif

  while(NbrOfDataToRead2--)
  {
    //UART发送一个字节数据
    USART_SendData_8bit(DEBUG_USARTx, TxBuffer1[TxCounter1++]);
    while(USART_GetFlagStatus(DEBUG_USARTx, USART_FLAG_TXE) == RESET);

    //SPI 等待RXNE
    while(SPI_GetFlagStatus(SPI_FLAG_RXNE) == RESET);   
    RxBuffer2[RxCounter2++] = SPI_ReceiveData();
  }
  //拉高片选
  #ifdef SPI_SOFT_TEST
  SPI_NSSInternalSoftwareConfig(SPI_NSSInternalSoft_Set);
  #endif
  #ifdef SPI_HARD_TEST
  SPI_CS_HIGH();
  #endif

  /*************************** SPI -> UART **************************/
  //SPI 仅发送
  SPI_BiDirectionalLineConfig(SPI_Direction_Tx);
  //SPI 清空发送缓冲区和移位寄存器
  SPI_FlushSendBuff();
  SPI_SendData(TxBuffer2[TxCounter2++]);
  
  //拉低片选
  #ifdef SPI_SOFT_TEST 
  SPI_NSSInternalSoftwareConfig(SPI_NSSInternalSoft_Reset);
  #endif
  #ifdef SPI_HARD_TEST
  SPI_CS_LOW();
  #endif

  USART_DirectionModeCmd(DEBUG_USARTx, USART_Mode_Tx, DISABLE);
  USART_DirectionModeCmd(DEBUG_USARTx, USART_Mode_Rx, ENABLE);
  while(NbrOfDataToRead1--)
  { 
    //查询TXE，SPI发送一个字节数据
    while(SPI_GetFlagStatus(SPI_FLAG_TXE) == RESET);
    SPI_SendData(TxBuffer2[TxCounter2++]);

    //UART 等待RC
    while(USART_GetFlagStatus(DEBUG_USARTx,USART_FLAG_RC) == RESET);
    RxBuffer1[RxCounter1++] = USART_ReceiveData_8bit(DEBUG_USARTx);
    //清除RC后，立即开始接收下一个字节数据
    USART_ClearFlag(DEBUG_USARTx, USART_FLAG_RC);
  }
  //拉高片选
  #ifdef SPI_SOFT_TEST
  SPI_NSSInternalSoftwareConfig(SPI_NSSInternalSoft_Set);
  #endif
  #ifdef SPI_HARD_TEST
  SPI_CS_HIGH();
  #endif
  
  //检查收发数据一致性
  TransferStatus1 = Buffercmp(TxBuffer1, RxBuffer2, TxBufferSize1);
  TransferStatus2 = Buffercmp(TxBuffer2, RxBuffer1, TxBufferSize2);

  if(TransferStatus1 == PASSED && TransferStatus2 == PASSED) //PASSED
  {
    //LED1亮
    LED1.LED_On(&LED1);
  }
  else //FAILED
  {
    //LED2亮
    LED2.LED_On(&LED2);
  }
  
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
  //SYSCLK = HSI = 24MHz = HCLK = PCLK
  RCC_HSI_Enable(RCC_HSIOSC_DIV2);

  //外设时钟使能
  #ifdef SPI_HARD_TEST
  RCC_AHBPeriphClk_Enable(DEBUG_USART_CS_GPIO_CLK | DEBUG_SPI_CS_GPIO_CLK, ENABLE);
  #endif
  RCC_AHBPeriphClk_Enable(DEBUG_USART_TX_GPIO_CLK | DEBUG_USART_RX_GPIO_CLK |\
                          DEBUG_SPI_SCK_GPIO_CLK | DEBUG_SPI_MISO_GPIO_CLK, ENABLE);
  DEBUG_USART_APBClkENx(DEBUG_USART_CLK, ENABLE);
  RCC_APBPeriphClk_Enable2(RCC_APB2_PERIPH_SPI, ENABLE);
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

  //SPI SCK MISO 复用
  DEBUG_SPI_AFSCK;
  DEBUG_SPI_AFMISO;  

  #ifdef SPI_HARD_TEST
  DEBUG_SPI_AFCS; 
  #endif    

  //UART TX RX CS 推挽输出
  GPIO_InitStructure.Pins = DEBUG_USART_TX_GPIO_PIN;
  GPIO_InitStructure.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_Init(DEBUG_USART_TX_GPIO_PORT, &GPIO_InitStructure);
    
  GPIO_InitStructure.Pins = DEBUG_USART_RX_GPIO_PIN;
  GPIO_Init(DEBUG_USART_RX_GPIO_PORT, &GPIO_InitStructure);

  #ifdef SPI_HARD_TEST
  GPIO_InitStructure.Pins = DEBUG_USART_CS_GPIO_PIN;
  GPIO_Init(DEBUG_USART_CS_GPIO_PORT, &GPIO_InitStructure);
  #endif

  //SPI MISO 推挽输出
  GPIO_InitStructure.Pins = DEBUG_SPI_MISO_GPIO_PIN;
  GPIO_Init(DEBUG_SPI_MISO_GPIO_PORT, &GPIO_InitStructure);

  //SPI SCK 浮空输入
  GPIO_InitStructure.Pins = DEBUG_SPI_SCK_GPIO_PIN;
  GPIO_InitStructure.Mode = GPIO_MODE_INPUT;
  GPIO_Init(DEBUG_SPI_SCK_GPIO_PORT, &GPIO_InitStructure);

  #ifdef SPI_HARD_TEST
  //SPI CS 上拉输入
  GPIO_InitStructure.Pins = DEBUG_SPI_CS_GPIO_PIN;
  GPIO_InitStructure.Mode = GPIO_MODE_INPUT_PULLUP;
  GPIO_Init(DEBUG_SPI_CS_GPIO_PORT, &GPIO_InitStructure);
  #endif

  //LED1 LED2
  LED1.LED_Port = LED1_GPIO_PORT;
  LED1.LED_Pin = LED1_GPIO_PIN;
  LED_Init(&LED1);
  LED2.LED_Port = LED2_GPIO_PORT;
  LED2.LED_Pin = LED2_GPIO_PIN;
  LED_Init(&LED2);

  LED1.LED_Off(&LED1);
  LED2.LED_Off(&LED2);
}

/**
 * @brief 配置UART 同步模式  2Mbps
 * 
 */
void UART_Configuration(void)
{
  USART_ClockInitTypeDef USART_ClockInitStructure;

  USART_ClockInitStructure.USART_Clock = USART_Clock_Enable;
  USART_ClockInitStructure.USART_Source = USART_Source_PCLK;

  USART_ClockInit(DEBUG_USARTx, &USART_ClockInitStructure); 
}

/**
 * @brief 配置SPI 单线半双工 从机
 * 
 */
void SPI_Configuration(void)
{
  SPI_InitTypeDef SPI_InitStructure;

  SPI_InitStructure.SPI_Direction = SPI_Direction_1Lines_HalfDuplex;    // 单线半双工
  SPI_InitStructure.SPI_Mode = SPI_Mode_Slave;                          // 从机模式
  SPI_InitStructure.SPI_DataSize = SPI_DataSize_8b;                     // 帧数据长度为8bit
  SPI_InitStructure.SPI_CPOL = SPI_CPOL_High;                           // 时钟空闲电平为高
  SPI_InitStructure.SPI_CPHA = SPI_CPHA_2Edge;                          // 第二个边沿采样
  SPI_InitStructure.SPI_NSS = SPI_NSS_Soft;                             // SSI寄存器的值决定本机是否被选中
  #ifdef SPI_HARD_TEST
  SPI_InitStructure.SPI_NSS = SPI_NSS_Hard;                             // SPI_CS引脚电平决定本机是否被选中
  #endif
  SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_2;    // 波特率为PCLK的2分频
  SPI_InitStructure.SPI_FirstBit = SPI_FirstBit_LSB;                    // 最低有效位 LSB 收发在前
  SPI_InitStructure.SPI_Speed = SPI_Speed_Low;                          // 低速SPI
  
  SPI_Init(&SPI_InitStructure);
  SPI_Cmd(ENABLE); 
}

/**
 * @brief Compares two buffers
 * 
 * @param pBuffer1 :buffers to be compared
 * @param pBuffer2 :buffers to be compared
 * @param BufferLength :buffer's length
 * @return TestStatus 
 *     @arg PASSED: pBuffer1 identical to pBuffer2
 *     @arg FAILED: pBuffer1 differs from pBuffer2
 */
TestStatus Buffercmp(uint8_t* pBuffer1, uint8_t* pBuffer2, uint16_t BufferLength)
{
  while(BufferLength--)
  {
    if(*pBuffer1 != *pBuffer2)
    {
      return FAILED;
    }
    
    pBuffer1++;
    pBuffer2++;
  }

  return PASSED;  
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

