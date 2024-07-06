#ifndef __UART2_H
#define __UART2_H

#include "stdint.h"
#include "cw32f003_rcc.h"
#include "cw32f003_gpio.h"
#include "cw32f003_uart.h"

void Uart2_Init(void);
void USART_SendString(UART_TypeDef *USARTx, char *String);

#endif
