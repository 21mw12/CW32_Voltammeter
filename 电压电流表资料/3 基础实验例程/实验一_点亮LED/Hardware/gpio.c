#include "gpio.h"

void Gpio_Init(void)
{
	__RCC_GPIOC_CLK_ENABLE();//打开GPIOC的时钟
	GPIO_InitTypeDef GPIO_InitStruct;
	GPIO_InitStruct.Pins = GPIO_PIN_13;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.IT = GPIO_IT_NONE;
	GPIO_InitStruct.Speed = GPIO_SPEED_HIGH;
  GPIO_Init(CW_GPIOC, &GPIO_InitStruct);
}
