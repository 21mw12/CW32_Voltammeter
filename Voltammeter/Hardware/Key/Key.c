#include "Key.h"
#include "cw32f003_rcc.h"
#include "cw32f003_gpio.h"

void Key_Init(void) {
	__RCC_GPIOA_CLK_ENABLE();
	
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.IT = GPIO_IT_NONE;
	GPIO_InitStructure.Mode = GPIO_MODE_INPUT_PULLUP;
	GPIO_InitStructure.Pins = KEY_Pin;
	GPIO_Init(KEY_Port, &GPIO_InitStructure);
}

KeyState Key_GetState(void) {
	if (GPIO_ReadPin(KEY_Port, KEY_Pin) == GPIO_Pin_RESET) {
		FirmwareDelay(2000);
		while(GPIO_ReadPin(KEY_Port, KEY_Pin) == GPIO_Pin_RESET);
		FirmwareDelay(2000);
		return KeyPress;
	}
	return KeyIdle;
}
