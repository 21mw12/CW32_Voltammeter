/**
 * @file cw32f030_uart.c
 * @author P&S (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2021-06-26
 * 
 * @copyright Copyright (c) 2021
 * 
 */
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

/* Includes ------------------------------------------------------------------*/
#include "cw32f030_uart.h"

/* Private_TypesDefinitions --------------------------------------------------*/

/* Private_Defines -----------------------------------------------------------*/

/* Private_Variables ---------------------------------------------------------*/

/* Private_FunctionPrototypes ------------------------------------------------*/

/* Private_Functions ---------------------------------------------------------*/

/* Public_Functions ----------------------------------------------------------*/

/**
 * @brief ͨ��USARTx����һ������(16bit)
 * 
 * @param USARTx :USARTx����
 *        ����������:
 *           CW_UART1��CW_UART2��CW_UART3
 * @param Data :�����͵�����
 */
void USART_SendData(UART_TypeDef* USARTx, uint16_t Data)
{
  assert_param(IS_USART_ALL_PERIPH(USARTx));
  assert_param(IS_USART_DATA_16BIT(Data));

  USARTx->TDR = (Data & (uint16_t)0x01FF);
}

/**
 * @brief ͨ��USARTx����һ������(8bit)
 * 
 * @param USARTx :USARTx����
 *        ����������:
 *           CW_UART1��CW_UART2��CW_UART3
 * @param Data :�����͵�����
 */
void USART_SendData_8bit(UART_TypeDef* USARTx, uint8_t Data)
{
  assert_param(IS_USART_ALL_PERIPH(USARTx));
  assert_param(IS_USART_DATA_8BIT(Data));

  USARTx->TDR = Data;
}

/**
 * @brief ͨ��USARTx����һ������(16bit)
 * 
 * @param USARTx :USARTx����
 *        ����������:
 *           CW_UART1��CW_UART2��CW_UART3
 * @return uint16_t ��:���յ�����
 */
uint16_t USART_ReceiveData(UART_TypeDef* USARTx)
{
  assert_param(IS_USART_ALL_PERIPH(USARTx));

  return (uint16_t)(USARTx->RDR & (uint16_t)0x01FF);
}

/**
 * @brief ͨ��USARTx����һ������(8bit)
 * 
 * @param USARTx :USARTx����
 *        ����������:
 *           CW_UART1��CW_UART2��CW_UART3
 * @return uint8_t ��:���յ�����
 */
uint8_t USART_ReceiveData_8bit(UART_TypeDef* USARTx)
{
  assert_param(IS_USART_ALL_PERIPH(USARTx));
  
  return (uint8_t)(USARTx->RDR);
}

/**
 * @brief ����USART_InitStruct��ָ���Ĳ�����ʼ��UARTx����
 * 
 * @param USARTx :USARTx����
 *        ����������:
 *           CW_UART1��CW_UART2��CW_UART3
 * @param USART_InitStruct :ָ��USART_InitTypeDef���ͽṹ���ָ��
 */
void USART_Init(UART_TypeDef* USARTx, USART_InitTypeDef* USART_InitStruct)
{
  uint16_t integerdivider = 0x00;
  uint16_t fractionaldivider = 0x00;
  float32_t temp = 0;

  assert_param(IS_USART_ALL_PERIPH(USARTx));
  assert_param(IS_USART_BAUDRATE(USART_InitStruct->USART_BaudRate));
  assert_param(IS_USART_Over(USART_InitStruct->USART_Over));
  assert_param(IS_USART_Source(USART_InitStruct->USART_Source));
  assert_param(IS_USART_UCLKFREQ(USART_InitStruct->USART_UclkFreq));
  assert_param(IS_USART_StartBit(USART_InitStruct->USART_StartBit));  
  assert_param(IS_USART_STOPBITS(USART_InitStruct->USART_StopBits));
  assert_param(IS_USART_PARITY(USART_InitStruct->USART_Parity));
  assert_param(IS_USART_MODE(USART_InitStruct->USART_Mode));
  assert_param(IS_USART_HARDWARE_FLOW_CONTROL(USART_InitStruct->USART_HardwareFlowControl));
    
  /* UARTx_CR1 */
  REGBITS_MODIFY(USARTx->CR1, UARTx_CR1_OVER_Msk | UARTx_CR1_START_Msk  |\
                              UARTx_CR1_STOP_Msk | UARTx_CR1_PARITY_Msk |\
                              UARTx_CR1_RXEN_Msk | UARTx_CR1_TXEN_Msk    \
                              ,\
                              (uint32_t)USART_InitStruct->USART_Over |\
                              USART_InitStruct->USART_StartBit       |\
                              USART_InitStruct->USART_StopBits       |\
                              USART_InitStruct->USART_Parity         |\
                              USART_InitStruct->USART_Mode);

  /* UARTx_CR2 */
  REGBITS_MODIFY(USARTx->CR2, UARTx_CR2_SOURCE_Msk | UARTx_CR2_RTSEN_Msk |\
                              UARTx_CR2_CTSEN_Msk  \
                              ,\
                              (uint32_t)USART_InitStruct->USART_Source |\
                              USART_InitStruct->USART_HardwareFlowControl);
    
  /* ���������� */
  if(USART_Over_16 == USART_InitStruct->USART_Over)
  {
    /* 16������ */
    temp = (float32_t)(USART_InitStruct->USART_UclkFreq) / (16 * (USART_InitStruct->USART_BaudRate));
    integerdivider = (uint16_t)temp;
    fractionaldivider = (uint16_t)((temp - integerdivider)*16 + 0.5);
    USARTx->BRRI = (uint16_t)integerdivider;
    USARTx->BRRF = (uint16_t)fractionaldivider;
  }
  else if(USART_Over_8 == USART_InitStruct->USART_Over) 
  {
    /* 8������ */
    integerdivider = (uint16_t)((float32_t)(USART_InitStruct->USART_UclkFreq) / (8 * (USART_InitStruct->USART_BaudRate)) + 0.5); 
    USARTx->BRRI = (uint16_t)integerdivider;
  }
  else if(USART_Over_4 == USART_InitStruct->USART_Over)  
  {
    /* 4������ */
    integerdivider = (uint16_t)((float32_t)(USART_InitStruct->USART_UclkFreq) / (4 * (USART_InitStruct->USART_BaudRate)) + 0.5); 
    USARTx->BRRI = (uint16_t)integerdivider; 
  }   
  else  
  {
    /* ר�ò��� */
    /* ר�ò������ʺϴ���ʱ��ԴΪLSE����LSIʱ������2400bps��4800bps��9600bps�������µ�UARTͨ�� */
    integerdivider = (uint16_t)((float32_t)(USART_InitStruct->USART_UclkFreq)*256 / (USART_InitStruct->USART_BaudRate) + 0.5); 
    USARTx->BRRI = (uint16_t)integerdivider;     
  }   
}

/**
 * @brief Ĭ��ֵ��ֵUSART_InitStruct�ṹ���Ա
 * 
 * @param USART_InitStruct :ָ��USART_InitTypeDef���ͽṹ���ָ��
 */
void USART_StructInit(USART_InitTypeDef* USART_InitStruct)
{
  /* USART_InitStruct members default value */
  USART_InitStruct->USART_BaudRate = 9600;
  USART_InitStruct->USART_Over = USART_Over_16;
  USART_InitStruct->USART_Source = USART_Source_PCLK;
  USART_InitStruct->USART_StartBit = USART_StartBit_FE;
  USART_InitStruct->USART_StopBits = USART_StopBits_1;
  USART_InitStruct->USART_Parity = USART_Parity_No ;
  USART_InitStruct->USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
  USART_InitStruct->USART_HardwareFlowControl = USART_HardwareFlowControl_None;  
}

/**
 * @brief USARTxͬ��ģʽ��ʼ����CPOL=1��CPHA=1��ֻ��������
 * 
 * @param USARTx :USARTx����
 *        ����������:
 *           CW_UART1��CW_UART2��CW_UART3
 * @param USART_ClockInitStruct :ָ��USART_ClockInitTypeDef���ͽṹ���ָ��
 */
void USART_ClockInit(UART_TypeDef* USARTx, USART_ClockInitTypeDef* USART_ClockInitStruct)
{
  assert_param(IS_USART_ALL_PERIPH(USARTx));
  assert_param(IS_USART_CLOCK(USART_ClockInitStruct->USART_Clock));
  assert_param(IS_USART_Source(USART_ClockInitStruct->USART_Source));
  
  REGBITS_MODIFY(USARTx->CR1, UARTx_CR1_SYNC_Msk, (uint32_t)USART_ClockInitStruct->USART_Clock);
  REGBITS_MODIFY(USARTx->CR2, UARTx_CR2_SOURCE_Msk, (uint32_t)USART_ClockInitStruct->USART_Source); 
}

/**
 * @brief Ĭ��ֵ��ֵUSART_ClockInitStruct�ṹ���Ա
 * 
 * @param USART_ClockInitStruct :ָ��USART_ClockInitTypeDef���ͽṹ���ָ��
 */
void USART_ClockStructInit(USART_ClockInitTypeDef* USART_ClockInitStruct)
{
  /* USART_ClockInitStruct members default value */
  USART_ClockInitStruct->USART_Clock = USART_Clock_Disable;
  USART_ClockInitStruct->USART_Source = USART_Source_PCLK;
}

/**
 * @brief UART1ȥ��ʼ��
 * 
 */
void UART1_DeInit(void)
{
  CW_SYSCTRL->APBRST2_f.UART1 = 0;
  CW_SYSCTRL->APBRST2_f.UART1 = 1;
}

/**
 * @brief UART2ȥ��ʼ��
 * 
 */
void UART2_DeInit(void)
{
  CW_SYSCTRL->APBRST1_f.UART2 = 0;
  CW_SYSCTRL->APBRST1_f.UART2 = 1;
}

/**
 * @brief UART3ȥ��ʼ��
 * 
 */
void UART3_DeInit(void)
{
  CW_SYSCTRL->APBRST1_f.UART3 = 0;
  CW_SYSCTRL->APBRST1_f.UART3 = 1;  
}

/**
 * @brief ʹ��/ʧ��USARTx�ж�
 * 
 * @param USARTx :USARTx����
 *        ����������:
 *           CW_UART1��CW_UART2��CW_UART3
 * @param USART_IT :�ж�Դ
 *   ����������:
 *     @arg USART_IT_CTS:  CTS�źű仯�ж�
 *     @arg USART_IT_PE:   ��żУ������ж�
 *     @arg USART_IT_FE:   ֡�ṹ�����ж�
 *     @arg USART_IT_RC:   ��������ж�
 *     @arg USART_IT_TC:   ��������ж�
 *     @arg USART_IT_TXE:  ���ͻ�����ж�
 * @param NewState :ENABLE or DISABLE 
 */
void USART_ITConfig(UART_TypeDef* USARTx, uint16_t USART_IT, FunctionalState NewState)
{
  assert_param(IS_USART_ALL_PERIPH(USARTx));
  assert_param(IS_USART_IT(USART_IT));
  assert_param(IS_FUNCTIONAL_STATE(NewState));

  NewState ? (USARTx->IER |= USART_IT) : (USARTx->IER &= (uint16_t)~USART_IT);
  
  // if (NewState != DISABLE)
  // {
  //   USARTx->IER |= USART_IT;
  // }
  // else
  // {
  //   USARTx->IER &= (uint16_t)~USART_IT;
  // }
}

/**
 * @brief ��ȡUSARTx�жϱ�־λ
 * 
 * @param USARTx :USARTx����
 *        ����������:
 *           CW_UART1��CW_UART2��CW_UART3
 * @param USART_IT :�ж�Դ
 *   ���������ǣ�
 *     @arg USART_IT_CTS:   CTS�źű仯�ж�
 *     @arg USART_IT_PE:    ��żУ������ж�
 *     @arg USART_IT_FE:    ֡�ṹ�����ж�
 *     @arg USART_IT_RC:    ��������ж�
 *     @arg USART_IT_TC:    ��������ж�
 *     @arg USART_IT_TXE:   ���ͻ��������ж� 
 * @return ITStatus :USART_IT��ǰ״̬ (SET or RESET)
 */
ITStatus USART_GetITStatus(UART_TypeDef* USARTx, uint16_t USART_IT)
{
  assert_param(IS_USART_ALL_PERIPH(USARTx));
  assert_param(IS_USART_IT(USART_IT));

  return (REGBITS_GET(USARTx->ISR, USART_IT) ? SET : RESET);
}

/**
 * @brief ���USARTx�жϱ�־λ
 * 
 * @param USARTx :USARTx����
 *        ����������:
 *           CW_UART1��CW_UART2��CW_UART3
 * @param USART_IT :�ж�Դ
 *   ���������ǣ�
 *     @arg USART_IT_CTS:   CTS�źű仯�ж�
 *     @arg USART_IT_PE:    ��żУ������ж�
 *     @arg USART_IT_FE:    ֡�ṹ�����ж�
 *     @arg USART_IT_RC:    ��������ж�
 *     @arg USART_IT_TC:    ��������ж�
 * @note
 *    -TXE�жϱ�־λֻ��ͨ��дUARTx_TDR�Ĵ��������
 *    -RC�жϱ�־λֻ��������������ͨ����UARTx_RDR�Ĵ��������
 */
void USART_ClearITPendingBit(UART_TypeDef* USARTx, uint16_t USART_IT)
{
  assert_param(IS_USART_ALL_PERIPH(USARTx));
  assert_param(IS_USART_CLEAR_IT(USART_IT));

  REGBITS_CLR(USARTx->ICR, USART_IT); 
}

/**
 * @brief ��ȡUSARTx��־λ
 * 
 * @param USARTx :USARTx����
 *        ����������:
 *           CW_UART1��CW_UART2��CW_UART3
 * @param  USART_FLAG :��־
 *   ���������ǣ�
 *     @arg USART_FLAG_TXBUSY:  ����æ��־
 *     @arg USART_FLAG_CTSLV:   CTS�źŵ�ƽ״̬��־
 *     @arg USART_FLAG_CTS:     CTS�źű仯��־
 *     @arg USART_FLAG_MATCH:   �ӻ���ַƥ���־
 *     @arg USART_FLAG_PE:      ��żУ������־
 *     @arg USART_FLAG_FE:      ֡�ṹ�����־
 *     @arg USART_FLAG_RC:      ������ɱ�־
 *     @arg USART_FLAG_TC:      ������ɱ�־
 *     @arg USART_FLAG_TXE:     ���ͻ������ձ�־ 
 * @return FlagStatus :USART_FLAG��ǰ״̬ (SET or RESET)
 */
FlagStatus USART_GetFlagStatus(UART_TypeDef* USARTx, uint16_t USART_FLAG)
{
  assert_param(IS_USART_ALL_PERIPH(USARTx));
  assert_param(IS_USART_FLAG(USART_FLAG));

  return (REGBITS_GET(USARTx->ISR, USART_FLAG) ? SET : RESET); 
}

/**
 * @brief ���USARTx��־λ
 * 
 * @param USARTx :USARTx����
 *        ����������:
 *           CW_UART1��CW_UART2��CW_UART3
 * @param  USART_FLAG :��־
 *   ���������ǣ�
 *     @arg USART_FLAG_CTS:     CTS�źű仯��־
 *     @arg USART_FLAG_PE:      ��żУ������־
 *     @arg USART_FLAG_FE:      ֡�ṹ�����־
 *     @arg USART_FLAG_RC:      ������ɱ�־
 *     @arg USART_FLAG_TC:      ������ɱ�־
 * @note
 *    -TXBUSY��CTSLV��MATCH��־λ��Ӳ���Զ����ú����
 *    -TXE��־λֻ��ͨ��дUARTx_TDR�Ĵ��������
 *    -RC��־λֻ��������������ͨ����UARTx_RDR�Ĵ��������
 */
void USART_ClearFlag(UART_TypeDef* USARTx, uint16_t USART_FLAG)
{
  assert_param(IS_USART_ALL_PERIPH(USARTx));
  assert_param(IS_USART_CLEAR_FLAG(USART_FLAG));

  REGBITS_CLR(USARTx->ICR, USART_FLAG);
}

/**
 * @brief ʹ��/ʧ��TXD�����RXD����
 * 
 * @param USARTx :USARTx����
 *        ����������:
 *           CW_UART1��CW_UART2��CW_UART3
 * @param USART_EN :ʹ��
 *   ���������ǣ�
 *     @arg USART_EN_Tx: TXD���
 *     @arg USART_EN_Rx: RXD����
 * @param NewState :ENABLE or DISABLE
 */
void USART_TxRxEN(UART_TypeDef* USARTx, uint16_t USART_EN, FunctionalState NewState)
{
  assert_param(IS_USART_ALL_PERIPH(USARTx));
  assert_param(IS_USART_TxRxEN(USART_EN));  
  assert_param(IS_FUNCTIONAL_STATE(NewState)); 

  NewState ? (USARTx->CR1 |= USART_EN) : (USARTx->CR1 &= (uint16_t)~USART_EN);
  
  // if (NewState != DISABLE)
  // {
  //   USARTx->CR1 |= USART_EN;
  // }
  // else
  // {
  //   USARTx->CR1 &= (uint16_t)~USART_EN;
  // }
}

/**
 * @brief ʹ��/ʧ��TXD����źš�RXD�����źŷ���
 * 
 * @param USARTx :USARTx����
 *        ����������:
 *           CW_UART1��CW_UART2��CW_UART3
 * @param USART_INV :����
 *   ���������ǣ�
 *     @arg USART_INV_Tx: TXD����źŷ���
 *     @arg USART_INV_Rx: RXD�����źŷ���
 * @param NewState :ENABLE or DISABLE
 */
void USART_TxRxINV(UART_TypeDef* USARTx, uint16_t USART_INV, FunctionalState NewState)
{
  assert_param(IS_USART_ALL_PERIPH(USARTx));
  assert_param(IS_USART_TxRxINV(USART_INV));  
  assert_param(IS_FUNCTIONAL_STATE(NewState)); 

  NewState ? (USARTx->CR2 |= USART_INV) : (USARTx->CR2 &= (uint16_t)~USART_INV);
  
  // if (NewState != DISABLE)
  // {
  //   USARTx->CR2 |= USART_INV;
  // }
  // else
  // {
  //   USARTx->CR2 &= (uint16_t)~USART_INV;
  // }
}

/**
 * @brief ʹ��/ʧ��USARTx��˫��ͨ��
 * 
 * @param USARTx :USARTx����
 *        ����������:
 *           CW_UART1��CW_UART2��CW_UART3
 * @param NewState :ENABLE or DISABLE
 */

void USART_HalfDuplexCmd(UART_TypeDef* USARTx, FunctionalState NewState)
{
  assert_param(IS_USART_ALL_PERIPH(USARTx));
  assert_param(IS_FUNCTIONAL_STATE(NewState));

  USARTx->CR2_f.SIGNAL = NewState;
}

/**
 * @brief ʹ��/ʧ��USARTx DMA
 * 
 * @param USARTx :USARTx����
 *        ����������:
 *           CW_UART1��CW_UART2��CW_UART3
 * @param USART_DMAReq :DMA����
 *   ���������ǣ�
 *     @arg USART_DMAReq_Tx: DMA��������
 *     @arg USART_DMAReq_Rx: DMA��������
 * @param NewState :ENABLE or DISABLE
 */
void USART_DMACmd(UART_TypeDef* USARTx, uint16_t USART_DMAReq, FunctionalState NewState)
{
  assert_param(IS_USART_ALL_PERIPH(USARTx));
  assert_param(IS_USART_DMAREQ(USART_DMAReq));  
  assert_param(IS_FUNCTIONAL_STATE(NewState)); 

  NewState ? (USARTx->CR2 |= USART_DMAReq) : (USARTx->CR2 &= (uint16_t)~USART_DMAReq);

  // if (NewState != DISABLE)
  // {
  //   USARTx->CR2 |= USART_DMAReq;
  // }
  // else
  // {
  //   USARTx->CR2 &= (uint16_t)~USART_DMAReq;
  // }
}

/**
 * @brief USARTx���ͨ������
 * 
 * @param USARTx :USARTx����
 *        ����������:
 *           CW_UART1��CW_UART2��CW_UART3
 * @param USART_Address :�ӻ���ַ
 * @param USART_AddressMsK :�ӻ���ַ����
 * @note
 *        �����ʹӻ���������Ϊ�Զ���У��
 */
void USART_SetMultiMode(UART_TypeDef* USARTx, uint8_t USART_Address, uint8_t USART_AddressMsK)
{
  assert_param(IS_USART_ALL_PERIPH(USARTx));
  assert_param(IS_USART_ADDRESS(USART_Address));
  assert_param(IS_USART_ADDRESSMSK(USART_AddressMsK));

  REGBITS_SET(USARTx->CR2, UARTx_CR2_ADDREN_Msk);
  REGBITS_MODIFY(USARTx->ADDR, UARTx_ADDR_ADDR_Msk, (uint32_t)USART_Address);
  REGBITS_MODIFY(USARTx->MASK, UARTx_MASK_MASK_Msk, (uint32_t)USART_AddressMsK);
}






