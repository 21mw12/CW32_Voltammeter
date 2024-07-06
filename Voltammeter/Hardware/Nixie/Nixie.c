#include "Nixie.h"
#include "cw32f003_rcc.h"
#include "cw32f003_gpio.h"

uint8_t NixieData[23] =  {0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x07, 0x7F, 0x6F,		// 0 ~ 9
													0xbf, 0x86, 0xdb, 0xcf, 0xe6, 0xed, 0xfd, 0x87, 0xff, 0xef,		// 0.~ 9.
													0x3E, 0x77, 0x00};		// U A 空白

uint8_t NixieShowNumInfo[6];

void Nixie_Init(void) {
	__RCC_GPIOA_CLK_ENABLE();
	__RCC_GPIOB_CLK_ENABLE();
	__RCC_GPIOC_CLK_ENABLE();
	
	GPIO_InitTypeDef GPIO_InitStructure;
	
	GPIO_InitStructure.IT = GPIO_IT_NONE;
	GPIO_InitStructure.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStructure.Pins = GPIO_PIN_0 | GPIO_PIN_1 | GPIO_PIN_4;
	GPIO_Init(CW_GPIOA, &GPIO_InitStructure);
	
	GPIO_InitStructure.Pins = GPIO_PIN_0 | GPIO_PIN_2 | GPIO_PIN_3 | GPIO_PIN_4 | GPIO_PIN_6 | GPIO_PIN_7;
	GPIO_Init(CW_GPIOB, &GPIO_InitStructure);
	
	GPIO_InitStructure.Pins = GPIO_PIN_0 | GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_3 | GPIO_PIN_4;
	GPIO_Init(CW_GPIOC, &GPIO_InitStructure);
}


/**
  * @brief 清除显示的内容
  * @return 无
  */
void Nixie_NumClear(void) {
	GPIO_WritePin(Nixie_Port_A, Nixie_Pin_A, GPIO_Pin_RESET);
	GPIO_WritePin(Nixie_Port_B, Nixie_Pin_B, GPIO_Pin_RESET);
	GPIO_WritePin(Nixie_Port_C, Nixie_Pin_C, GPIO_Pin_RESET);
	GPIO_WritePin(Nixie_Port_D, Nixie_Pin_D, GPIO_Pin_RESET);
	GPIO_WritePin(Nixie_Port_E, Nixie_Pin_E, GPIO_Pin_RESET);
	GPIO_WritePin(Nixie_Port_F, Nixie_Pin_F, GPIO_Pin_RESET);
	GPIO_WritePin(Nixie_Port_G, Nixie_Pin_G, GPIO_Pin_RESET);
	GPIO_WritePin(Nixie_Port_DP, Nixie_Pin_DP, GPIO_Pin_RESET);
}

/**
 * @brief 关闭选位
 * @return 无
 */
void Nixie_CloseLocation() {
	GPIO_WritePin(Nixie_Port_COM1, Nixie_Pin_COM1, GPIO_Pin_SET);
	GPIO_WritePin(Nixie_Port_COM2, Nixie_Pin_COM2, GPIO_Pin_SET);
	GPIO_WritePin(Nixie_Port_COM3, Nixie_Pin_COM3, GPIO_Pin_SET);
	GPIO_WritePin(Nixie_Port_COM4, Nixie_Pin_COM4, GPIO_Pin_SET);
	GPIO_WritePin(Nixie_Port_COM5, Nixie_Pin_COM5, GPIO_Pin_SET);
	GPIO_WritePin(Nixie_Port_COM6, Nixie_Pin_COM6, GPIO_Pin_SET);
}

/**
  * @brief 设置显示的位置
  * @param Index 显示位置
  * @return 无
  */
void Nixie_SetLocation(uint8_t Index) {
	Nixie_CloseLocation();
	
	switch (Index) {
		case 0:
			GPIO_WritePin(Nixie_Port_COM3, Nixie_Pin_COM3, GPIO_Pin_RESET);	// COM3
			break;
		case 1:
			GPIO_WritePin(Nixie_Port_COM2, Nixie_Pin_COM2, GPIO_Pin_RESET);	// COM2
			break;
		case 2:
			GPIO_WritePin(Nixie_Port_COM1, Nixie_Pin_COM1, GPIO_Pin_RESET);	// COM1
			break;
		case 3:
			GPIO_WritePin(Nixie_Port_COM6, Nixie_Pin_COM6, GPIO_Pin_RESET);	// COM6
			break;
		case 4:
			GPIO_WritePin(Nixie_Port_COM5, Nixie_Pin_COM5, GPIO_Pin_RESET);	// COM5
			break;
		case 5:
			GPIO_WritePin(Nixie_Port_COM4, Nixie_Pin_COM4, GPIO_Pin_RESET);	// COM4
			break;
		default:
			break;
	}
}

/**
  * @brief 设置显示的内容
  * @param Number 显示内容
  * @return 无
  */
void Nixie_SetNum(uint8_t Number) {
	
	for (uint8_t i = 0; i < 8; i++) {
		GPIO_PinState state = (GPIO_PinState)((NixieData[Number] >> i) & 0x01);
		
		switch (i) {
			case 0:
				GPIO_WritePin(Nixie_Port_A, Nixie_Pin_A, state);		// A
				break;
			case 1:
				GPIO_WritePin(Nixie_Port_B, Nixie_Pin_B, state);		// B
				break;
			case 2:
				GPIO_WritePin(Nixie_Port_C, Nixie_Pin_C, state);		// C
				break;
			case 3:
				GPIO_WritePin(Nixie_Port_D, Nixie_Pin_D, state);		// D
				break;
			case 4:
				GPIO_WritePin(Nixie_Port_E, Nixie_Pin_E, state);		// E
				break;
			case 5:
				GPIO_WritePin(Nixie_Port_F, Nixie_Pin_F, state);   // F
				break;
			case 6:
				GPIO_WritePin(Nixie_Port_G, Nixie_Pin_G, state);		// G
				break;
			case 7:
				GPIO_WritePin(Nixie_Port_DP, Nixie_Pin_DP, state);		// DP
				break;
			default:
				break;
		}
	}
}

/**
  * @brief 设置显示的内容带点（点亮DP位）
  * @return 无
  */
void Nixie_SetDot(void) {
	GPIO_WritePin(Nixie_Port_DP, Nixie_Pin_DP, GPIO_Pin_SET);		// DP
}

void Nixie_Show(void) {
	static uint8_t index = 0;
	
	Nixie_SetLocation(index);
	Nixie_SetNum(NixieShowNumInfo[index]);

	if (++index > 5) index = 0;
}

void Nixie_ClearNumInfo(void) {
	NixieShowNumInfo[0] = 22;
	NixieShowNumInfo[1] = 22;
	NixieShowNumInfo[2] = 22;
	NixieShowNumInfo[3] = 22;
	NixieShowNumInfo[4] = 22;
	NixieShowNumInfo[5] = 22;
}
