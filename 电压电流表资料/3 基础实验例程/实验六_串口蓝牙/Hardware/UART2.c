#include "UART2.h"

void Uart2_Init(void)
{        
    RCC_AHBPeriphClk_Enable(RCC_AHB_PERIPH_GPIOA, ENABLE);      //ʹ�ܴ���Ҫ�õ���GPIOʱ��
    RCC_APBPeriphClk_Enable1(RCC_APB1_PERIPH_UART2, ENABLE);    //ʹ�ܴ���ʱ��
    
    GPIO_InitTypeDef GPIO_InitStructure;                        //GPIO��ʼ��
    GPIO_InitStructure.IT = GPIO_IT_NONE;
    GPIO_InitStructure.Pins =  GPIO_PIN_7;
    GPIO_InitStructure.Mode = GPIO_MODE_INPUT_PULLUP;
    GPIO_InitStructure.Speed = GPIO_SPEED_HIGH;
    GPIO_Init(CW_GPIOA, &GPIO_InitStructure);
    PA07_AFx_UART2RXD();
        
    GPIO_InitStructure.IT = GPIO_IT_NONE;
    GPIO_InitStructure.Pins = GPIO_PIN_6;
    GPIO_InitStructure.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStructure.Speed = GPIO_SPEED_HIGH;
    GPIO_Init(CW_GPIOA, &GPIO_InitStructure);
    PA06_AFx_UART2TXD();
  
    USART_InitTypeDef USART_InitStructure;                       //���ڳ�ʼ��
    USART_InitStructure.USART_BaudRate = 115200;                 //���ò�����
    USART_InitStructure.USART_Over = USART_Over_16;              //���ڲ�����ʽ
    USART_InitStructure.USART_Source = USART_Source_PCLK;        //���ڴ���ʱ��Դ����PCLK
    USART_InitStructure.USART_UclkFreq = RCC_Sysctrl_GetPClkFreq();  //Ƶ��ΪPCLK��Ƶ��
    USART_InitStructure.USART_StartBit = USART_StartBit_FE;      //���ݿ�ʼλ
    USART_InitStructure.USART_StopBits = USART_StopBits_1;       //����ֹͣλ
    USART_InitStructure.USART_Parity = USART_Parity_No ;         //��У��
    USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//��Ӳ������
    USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;  //����/����ʹ��
    USART_Init(CW_UART2, &USART_InitStructure);
}

void USART_SendString(UART_TypeDef *USARTx, char *String)
{
    while (*String != '\0')     //\0��ʾû������
    {
        USART_SendData_8bit(USARTx, *String);   //����һλ8bit����
        while (USART_GetFlagStatus(USARTx, USART_FLAG_TXE) == RESET);  //���ͻ�����δ����ȴ�
        String++;              //����һ����ɺ�׼��������һλ����
    }
    while (USART_GetFlagStatus(USARTx, USART_FLAG_TXBUSY) == SET);     //���ʹ���״̬æ��ȴ�  
}
