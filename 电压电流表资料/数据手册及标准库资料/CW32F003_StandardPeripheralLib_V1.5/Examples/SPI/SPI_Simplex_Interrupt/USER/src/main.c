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
//SPI GPIO
#define  SPI_SCK_GPIO_CLK              RCC_AHB_PERIPH_GPIOA
#define  SPI_SCK_GPIO_PORT             CW_GPIOA 
#define  SPI_SCK_GPIO_PIN              GPIO_PIN_0
#define  SPI_SCK_AF()                  PA00_AFx_SPISCK()

#define  SPI_MOSI_GPIO_CLK             RCC_AHB_PERIPH_GPIOA
#define  SPI_MOSI_GPIO_PORT            CW_GPIOA 
#define  SPI_MOSI_GPIO_PIN             GPIO_PIN_1
#define  SPI_MOSI_AF()                 PA01_AFx_SPIMOSI()

#define  SPI_CS_GPIO_CLK               RCC_AHB_PERIPH_GPIOB
#define  SPI_CS_GPIO_PORT              CW_GPIOB
#define  SPI_CS_GPIO_PIN               GPIO_PIN_2
#define  SPI_CS_AF()                   PB02_AFx_SPICS()

//CS LOW or HIGH
#define  SPI_CS_LOW()     		         PB02_SETLOW()
#define  SPI_CS_HIGH()    		         PB02_SETHIGH()

//LED GPIO
#define  LED1_GPIO_PORT                CW_GPIOA
#define  LED1_GPIO_PIN                 GPIO_PIN_7

#define  LED2_GPIO_PORT                CW_GPIOA
#define  LED2_GPIO_PIN                 GPIO_PIN_6

#define  BufferSize                    ARRAY_SZ(TxBuffer)
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
void NVIC_Configuration(void);
void SPI_Configuration(void);
TestStatus Buffercmp(uint8_t* pBuffer1, uint8_t* pBuffer2, uint16_t BufferLength);

/******************************************************************************
 * Local variable definitions ('static')                                      *
 ******************************************************************************/
uint8_t TxBuffer[] = {0x61, 0x62, 0x63, 0x64, 0x65, 0x66, 0x67,
                      0x68, 0x69, 0x6A, 0x6B, 0x6C, 0x6D, 0x6E,
                      0x6F, 0x70, 0x71, 0x72, 0x73, 0x74, 0x75, 
                      0x76, 0x77, 0x78, 0x79, 0x7A, 0x7B, 0x7C,
                      0x7D, 0x7E, 0x7F, 0x80, 0x81, 0x82, 0x83,
                      0x84, 0x85, 0x86, 0x87, 0x88, 0x89, 0x8A};
uint8_t RxBuffer[BufferSize];
uint8_t TxCounter = 0, RxCounter = 0;
volatile TestStatus TransferStatus = FAILED; 
LED_InitTypeDef LED1;
LED_InitTypeDef LED2;
/******************************************************************************
 * Local pre-processor symbols/macros ('#define')
 ******************************************************************************/

/******************************************************************************
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

  //配置SPI
  SPI_Configuration(); 

  //配置NVIC
  NVIC_Configuration();

  #ifdef SPI_MASTER
  //拉低CS，选中SPI从机
  SPI_CS_LOW();

  //使能 SPI TXE 中断
  SPI_ITConfig(SPI_IT_TXE, ENABLE);

  //等待发送完成
  while(TxCounter < BufferSize);
  while(SPI_GetFlagStatus(SPI_FLAG_BUSY) != RESET);

  //拉高CS，释放SPI从机
  SPI_CS_HIGH();
  #endif

  #ifdef SPI_SLAVE 
  //使能 SPI RXNE 中断
  SPI_ITConfig(SPI_IT_RXNE, ENABLE);

  //等待接收完成
  while(RxCounter < BufferSize);

  //检查收发数据一致性
  TransferStatus = Buffercmp(TxBuffer, RxBuffer, BufferSize);

  if(TransferStatus == PASSED) //PASSED
  {
    //LED1亮
    LED1.LED_On(&LED1);
  }
  else //FAILED
  {
    //LED2亮
    LED2.LED_On(&LED2); 
  }
  #endif
  
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
  RCC_AHBPeriphClk_Enable(SPI_SCK_GPIO_CLK | SPI_MOSI_GPIO_CLK | SPI_CS_GPIO_CLK, ENABLE);
  RCC_APBPeriphClk_Enable2(RCC_APB2_PERIPH_SPI, ENABLE);
}

/**
 * @brief 配置GPIO
 * 
 */
void GPIO_Configuration(void)
{  
  GPIO_InitTypeDef GPIO_InitStructure;
 
  //SPI SCK MOSI 复用
  SPI_SCK_AF();
  SPI_MOSI_AF();       

  #ifdef SPI_MASTER
  //推挽输出 SCK MOSI CS
  GPIO_InitStructure.Pins = SPI_SCK_GPIO_PIN;
  GPIO_InitStructure.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_Init(SPI_SCK_GPIO_PORT, &GPIO_InitStructure);
    
  GPIO_InitStructure.Pins = SPI_MOSI_GPIO_PIN;
  GPIO_Init(SPI_MOSI_GPIO_PORT, &GPIO_InitStructure);
    
  GPIO_InitStructure.Pins = SPI_CS_GPIO_PIN;
  GPIO_Init(SPI_CS_GPIO_PORT, &GPIO_InitStructure);

  //拉高CS
  SPI_CS_HIGH();
  #endif

  #ifdef SPI_SLAVE
  //SPI CS复用
  SPI_CS_AF(); 

  //浮空输入 SCK MOSI CS
  GPIO_InitStructure.Pins = SPI_SCK_GPIO_PIN;
  GPIO_InitStructure.Mode = GPIO_MODE_INPUT;
  GPIO_Init(SPI_SCK_GPIO_PORT, &GPIO_InitStructure);

  GPIO_InitStructure.Pins = SPI_MOSI_GPIO_PIN;
  GPIO_Init(SPI_MOSI_GPIO_PORT, &GPIO_InitStructure);

  GPIO_InitStructure.Pins = SPI_CS_GPIO_PIN;
  GPIO_InitStructure.Mode = GPIO_MODE_INPUT_PULLUP;
  GPIO_Init(SPI_CS_GPIO_PORT, &GPIO_InitStructure);
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
 * @brief 配置RCC 3Mbit/s
 * 
 */
void SPI_Configuration()
{
  SPI_InitTypeDef SPI_InitStructure;

  SPI_InitStructure.SPI_Direction = SPI_Direction_1Line_TxOnly;         // 单工单发
  SPI_InitStructure.SPI_Mode = SPI_Mode_Master;                         // 主机模式
  SPI_InitStructure.SPI_DataSize = SPI_DataSize_8b;                     // 帧数据长度为8bit
  SPI_InitStructure.SPI_CPOL = SPI_CPOL_Low;                            // 时钟空闲电平为低
  SPI_InitStructure.SPI_CPHA = SPI_CPHA_1Edge;                          // 第一个边沿采样
  SPI_InitStructure.SPI_NSS = SPI_NSS_Soft;                             // 片选信号由SSI寄存器控制
  SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_8;    // 波特率为PCLK的8分频
  SPI_InitStructure.SPI_FirstBit = SPI_FirstBit_MSB;                    // 最高有效位 MSB 收发在前
  SPI_InitStructure.SPI_Speed = SPI_Speed_Low;                          // 低速SPI
    
  #ifdef SPI_SLAVE
  SPI_InitStructure.SPI_Direction = SPI_Direction_1Line_RxOnly;         // 单工单收
  SPI_InitStructure.SPI_Mode = SPI_Mode_Slave;                          // 从机模式
  SPI_InitStructure.SPI_NSS = SPI_NSS_Hard;                             // SPI_CS引脚电平决定本机是否被选中
  #endif

  SPI_Init(&SPI_InitStructure);
  SPI_Cmd(ENABLE); 
}

/**
 * @brief 配置NVIC
 * 
 */
void NVIC_Configuration(void)
{
  //优先级，无优先级分组
  NVIC_SetPriority(SPI_IRQn, 0);
  //SPI中断使能
  NVIC_EnableIRQ(SPI_IRQn);
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

