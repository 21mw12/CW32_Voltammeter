#include "BTIM.h"
#include "cw32f003_rcc.h"

void BTIM1_Init(uint16_t us) {
	__RCC_BTIM_CLK_ENABLE();
	NVIC_EnableIRQ(BTIM1_IRQn);
	
	BTIM_TimeBaseInitTypeDef BTIM_TimeBaseInitStruct;
	BTIM_TimeBaseInitStruct.BTIM_Mode = BTIM_Mode_TIMER;
	BTIM_TimeBaseInitStruct.BTIM_OPMode = BTIM_OPMode_Repetitive;	// 连续运行模式
	BTIM_TimeBaseInitStruct.BTIM_Period = 6 * us - 1;
	BTIM_TimeBaseInitStruct.BTIM_Prescaler = BTIM_PRS_DIV1;	// 6MHz
	BTIM_TimeBaseInit(CW_BTIM1, &BTIM_TimeBaseInitStruct);
	
	BTIM_ITConfig(CW_BTIM1, BTIM_IT_OV, ENABLE);
	BTIM_Cmd(CW_BTIM1, ENABLE);
}

void BTIM2_Init(uint16_t us) {
	__RCC_BTIM_CLK_ENABLE();
	NVIC_EnableIRQ(BTIM2_IRQn);
	
	BTIM_TimeBaseInitTypeDef BTIM_TimeBaseInitStruct;
	BTIM_TimeBaseInitStruct.BTIM_Mode = BTIM_Mode_TIMER;
	BTIM_TimeBaseInitStruct.BTIM_OPMode = BTIM_OPMode_Repetitive;	// 连续运行模式
	BTIM_TimeBaseInitStruct.BTIM_Period = 6 * us - 1;
	BTIM_TimeBaseInitStruct.BTIM_Prescaler = BTIM_PRS_DIV1;	// 6MHz
	BTIM_TimeBaseInit(CW_BTIM2, &BTIM_TimeBaseInitStruct);
	
	BTIM_ITConfig(CW_BTIM2, BTIM_IT_OV, ENABLE);
	BTIM_Cmd(CW_BTIM2, ENABLE);
}
