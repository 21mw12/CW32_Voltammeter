#include "UART.h"
#include "cw32f003_rcc.h"
#include "cw32f003_gpio.h"
#include "cw32f003_uart.h"

void UART_Init(void) {
	/* 时钟初始化 */
	RCC_AHBPeriphClk_Enable(RCC_AHB_PERIPH_GPIOA, ENABLE);
	RCC_APBPeriphClk_Enable1(RCC_APB1_PERIPH_UART2, ENABLE);
	
	/* 端口初始化 */
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
	
	/* 串口初始化 */
	USART_InitTypeDef USART_InitStructure;
	USART_InitStructure.USART_BaudRate = 115200;
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
	USART_InitStructure.USART_StartBit = USART_StartBit_FE;	// 开始位
	USART_InitStructure.USART_StopBits = USART_StopBits_1;	// 一位停止位
	USART_InitStructure.USART_Parity = USART_Parity_No;			// 无校验位
	USART_InitStructure.USART_Over = USART_Over_16;			// 串口采样方式
	USART_InitStructure.USART_Source = USART_Source_PCLK;		// 串口传输时钟使用PCLK
	USART_InitStructure.USART_UclkFreq = RCC_Sysctrl_GetPClkFreq();		// 频率为PCLK的频率
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;	// 无硬件控制流
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
