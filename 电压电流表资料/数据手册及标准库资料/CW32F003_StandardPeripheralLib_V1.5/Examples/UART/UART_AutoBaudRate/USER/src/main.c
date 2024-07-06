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
* ������ɺ�������Ϣ
* �人��Դ�뵼�����޹�˾������ʹ�����б�̴���ʾ���ķ�ר���İ�Ȩ��ɣ��������ɴ�
* ���ɸ��������ض���Ҫ�����Ƶ����ƹ��ܡ����ݲ��ܱ��ų����κη�����֤���人��Դ��
* �������޹�˾������򿪷��̺͹�Ӧ�̶Գ������֧�֣�����У����ṩ�κ���ʾ��
* ���ı�֤�������������������ڰ������й������ԡ�������ĳ���ض���;�ͷ���Ȩ�ı�֤
* ��������
* ���ۺ������Σ��人��Դ�뵼�����޹�˾������򿪷��̻�Ӧ�̾��������и����
* ��ʹ����֪�䷢���Ŀ�����ʱ��Ҳ����ˣ����ݵĶ�ʧ���𻵣�ֱ�ӵġ��ر�ġ�������
* ���ӵ��𺦣����κκ���Ծ����𺦣�������ҵ�����롢������Ԥ�ڿɽ�ʡ����
* ��ʧ��
* ĳЩ˾��Ͻ���������ֱ�ӵġ������Ļ����Ե������κε��ų������ƣ����ĳЩ��
* ȫ�������ų������ƿ��ܲ�������������
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

//�ж�
#define  DEBUG_USART_IRQ                UART1_IRQn
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
void GTIM_Configuration(void);
void NVIC_Configuration(void);
void USART_SendString(UART_TypeDef* USARTx, char *String);
void AutoBaudRate(UART_TypeDef* USARTx);

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
  //����RCC
  RCC_Configuration();
  
  //����GPIO
  GPIO_Configuration();
    
  //����UART
  UART_Configuration();

  //����GTIM
  GTIM_Configuration();

  //����NVIC
  NVIC_Configuration();

  //ʹ��UARTx RC�ж�
  USART_ITConfig(DEBUG_USARTx, USART_IT_RC, ENABLE);

  USART_SendString(DEBUG_USARTx, "\r\nCW32F003 UART AutoBaudRate\r\n");
  USART_SendString(DEBUG_USARTx, "\r\nPC������0xF8��Ϊ����ͷ��������\r\n");

  //�Զ������ʼ��
  AutoBaudRate(DEBUG_USARTx);

  while(1)
  {  
    //�ж��շ�
  }
}

/**
 * @brief ����RCC
 * 
 */
void RCC_Configuration(void)
{
  //SYSCLK = HSI = 8MHz = HCLK = PCLK
  RCC_HSI_Enable(RCC_HSIOSC_DIV6);

  //����ʱ��ʹ��
  RCC_AHBPeriphClk_Enable(DEBUG_USART_TX_GPIO_CLK | DEBUG_USART_RX_GPIO_CLK, ENABLE);
  DEBUG_USART_APBClkENx(DEBUG_USART_CLK, ENABLE);
  RCC_APBPeriphClk_Enable1(RCC_APB1_PERIPH_GTIM, ENABLE);
}

/**
 * @brief ����GPIO
 * 
 */
void GPIO_Configuration(void)
{
  GPIO_InitTypeDef GPIO_InitStructure;

  //UART TX RX ���� 
  DEBUG_USART_AFTX;                     
  DEBUG_USART_AFRX;                     

  GPIO_InitStructure.IT = GPIO_IT_NONE;
  GPIO_InitStructure.Pins = DEBUG_USART_TX_GPIO_PIN;
  GPIO_InitStructure.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_Init(DEBUG_USART_TX_GPIO_PORT, &GPIO_InitStructure);
    
  GPIO_InitStructure.Pins = DEBUG_USART_RX_GPIO_PIN;
  GPIO_InitStructure.Mode = GPIO_MODE_INPUT_PULLUP;
  GPIO_Init(DEBUG_USART_RX_GPIO_PORT, &GPIO_InitStructure);
}

/**
 * @brief ����UART
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
 * @brief ����GTIM
 * 
 */
void GTIM_Configuration(void)
{
  GTIM_InitTypeDef GTIM_InitStructure; 

  GTIM_InitStructure.Mode = GTIM_MODE_GATE;              //�ſ�ģʽ
  GTIM_InitStructure.OneShotMode = GTIM_COUNT_CONTINUE;
  GTIM_InitStructure.Prescaler = GTIM_PRESCALER_DIV1;    //PCLK����
  GTIM_InitStructure.ReloadValue = 0xFFFF;
  GTIM_InitStructure.ToggleOutState = DISABLE;
  GTIM_TimeBaseInit(&GTIM_InitStructure);

  //ETR��ԴΪDEBUG_USARTx��RXD�ź�
  CW_SYSCTRL->GTIMETR_f.GTIMETR = 1;

  //ETR���Լ��˲������͵�ƽ�����˲�
  GTIM_ETRConfig(GTIM_ETR_POL_FALL_LOW, GTIM_ETR_FILTER_NONE);
}

/**
 * @brief ����NVIC
 * 
 */
void NVIC_Configuration(void)
{
  //���ȼ��������ȼ�����
  NVIC_SetPriority(DEBUG_USART_IRQ, 0);
  //UARTx�ж�ʹ��
  NVIC_EnableIRQ(DEBUG_USART_IRQ);
}

/**
 * @brief �����ַ���
 * 
 * @param USARTx :USARTx����
 *        ����������:
 *           CW_UART1��CW_UART2
 * @param String :�����͵��ַ���
 */
void USART_SendString(UART_TypeDef* USARTx, char *String)
{
  while(*String != '\0')
  {
    USART_SendData_8bit(USARTx, *String);
    while(USART_GetFlagStatus(USARTx, USART_FLAG_TXE) == RESET);
    String++;
  }
  while(USART_GetFlagStatus(USARTx, USART_FLAG_TXBUSY) == SET);
}

/**
 * @brief �Զ������ʼ��
 * 
 * @param USARTx :USARTx����
 *        ����������:
 *           CW_UART1��CW_UART2
 * @note
 *    -16������
 *    -GTIM.CNTδ���������
 */
void AutoBaudRate(UART_TypeDef* USARTx)
{
  uint32_t temp;
  //ʧ��RXEN
  USARTx->CR1_f.RXEN = 0;
  //ʹ��RXD�������ж�
  REGBITS_SET(DEBUG_USART_RX_GPIO_PORT->RISEIE, DEBUG_USART_RX_GPIO_PIN);
  //����GTIM
  CW_GTIM->CR0_f.EN = 1;
  while(REGBITS_GET(DEBUG_USART_RX_GPIO_PORT->ISR, DEBUG_USART_RX_GPIO_PIN) == RESET);
  //ʧ��RXD�������ж�
  REGBITS_CLR(DEBUG_USART_RX_GPIO_PORT->RISEIE, DEBUG_USART_RX_GPIO_PIN);
  //�ر�GTIM
  CW_GTIM->CR0_f.EN = 0;
  //����жϱ�־
  REGBITS_CLR(DEBUG_USART_RX_GPIO_PORT->ICR, DEBUG_USART_RX_GPIO_PIN); 
  //����BRRI��BRRF
  temp = ((CW_GTIM->CNT) + 2) / 4;
  USARTx->BRRI = (uint16_t)(temp >> 4);
  USARTx->BRRF = (uint16_t)(temp & 0x0F);
  //ʹ��RXEN
  USARTx->CR1_f.RXEN = 1;
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

