#include "gpio.h"

void gpio_init(void)
{
  GPIO_InitTypeDef GPIO_Init_Struct;
  __RCC_GPIOC_CLK_ENABLE();

  GPIO_Init_Struct.IT   = GPIO_IT_NONE;
  GPIO_Init_Struct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_Init_Struct.Pins = GPIO_PIN_0;
  GPIO_Init(CW_GPIOC, &GPIO_Init_Struct);
	PC00_SETLOW();
}

