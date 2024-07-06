#include "UART.h"
#include "cw32f003_rcc.h"
#include "cw32f003_gpio.h"
#include "cw32f003_uart.h"

void UART_Init(void) {
	/* ʱ�ӳ�ʼ�� */
	RCC_AHBPeriphClk_Enable(RCC_AHB_PERIPH_GPIOA, ENABLE);
	RCC_APBPeriphClk_Enable1(RCC_APB1_PERIPH_UART2, ENABLE);
	
	/* �˿ڳ�ʼ�� */
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.IT = GPIO_IT_NONE;
	GPIO_InitStructure.Pins = GPIO_PIN_7;
	GPIO_InitStructure.Mode = GPIO_MODE_INPUT_PULLUP;
	GPIO_Init(CW_GPIOA, &GPIO_InitStructure);
	PA07_AFx_UART2RXD();
	
	GPIO_InitStructure.Pins = GPIO_PIN_6;
	GPIO_InitStructure.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_Init(CW_GPIOA, &GPIO_InitStructure);
	PA06_AFx_UART2TXD();
	
	/* ���ڳ�ʼ�� */
	USART_InitTypeDef USART_InitStructure;
	USART_InitStructure.USART_BaudRate = 115200;
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
	USART_InitStructure.USART_StartBit = USART_StartBit_FE;	// ��ʼλ
	USART_InitStructure.USART_StopBits = USART_StopBits_1;	// һλֹͣλ
	USART_InitStructure.USART_Parity = USART_Parity_No;			// ��У��λ
	USART_InitStructure.USART_Over = USART_Over_16;			// ���ڲ�����ʽ
	USART_InitStructure.USART_Source = USART_Source_PCLK;		// ���ڴ���ʱ��ʹ��PCLK
	USART_InitStructure.USART_UclkFreq = RCC_Sysctrl_GetPClkFreq();		// Ƶ��ΪPCLK��Ƶ��
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;	// ��Ӳ��������
	USART_Init(CW_UART2, &USART_InitStructure);
}

void UART_SendString(char* String) {
	while (*String != '\0') {
		USART_SendData_8bit(CW_UART2, *String);
		while (USART_GetFlagStatus(CW_UART2, USART_FLAG_TXE) == RESET);
		String++;
	}
	while (USART_GetFlagStatus(CW_UART2, USART_FLAG_TXBUSY) == SET);
}
