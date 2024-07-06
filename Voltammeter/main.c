#include "main.h"
#include "cw32f003_systick.h"
#include "cw32f003_gpio.h"
#include "cw32f003_flash.h"
#include "Nixie.h"
#include "KeyStateMachine.h"
#include "BTIM.h"
#include "ADC.h"
#include "UART.h"
#include "AverageFilter.h"
#include "Calibration.h"
#include "Menu.h"

#define BLE_Function		0

/* ADC采集所得的电压电流原始值 */
#define Filter_Count		100		// 采样次数
uint8_t Flag_OriginalValue = 0;
uint16_t V_OriginalValue[Filter_Count];
uint16_t A_OriginalValue[Filter_Count];

/* 计算所得的电压电流值 */
uint16_t voltage = 0;
uint16_t electricity = 0;

/* 显示模式 */
uint8_t menu = 4;

extern KEY_Configure_TypeDef KeyCfg;

#if BLE_Function == 1
uint32_t Ble_Time = 0;
#endif

void RCC_Configuration(void) {
	FLASH_SetLatency(FLASH_Latency_2);	// 主频48时应设置为2
	RCC_HSI_Enable(RCC_HSIOSC_DIV1);		// 设置主频为48MHz
	RCC_SYSCLKSRC_Config(RCC_SYSCLKSRC_HSI);	// 选择SYSCLK时钟源
	RCC_HCLKPRS_Config(RCC_HCLK_DIV1);	// 设置HCLK分配系数
	RCC_PCLKPRS_Config(RCC_PCLK_DIV8);	// 设置PCLK分配系数
	InitTick(48000000);                 // SYSTICK 的工作频率为48MHz，每ms中断一次
}

int32_t main(void) {
	RCC_Configuration();

	Nixie_Init();
	Key_Init();
	ADC_ChannelInit();
	BTIM1_Init(2000);
#if BLE_Function == 1
	UART_Init();
#endif
	
	Calibration_ReadInfo();
	
  while (1) {
		/* 采集ADC数据 */
		ADC_GetValue();
		
		/* ADC多次采样 */
		V_OriginalValue[Flag_OriginalValue] = ADCValue[0];
		A_OriginalValue[Flag_OriginalValue] = ADCValue[1];
		if (++Flag_OriginalValue == Filter_Count) {
			Flag_OriginalValue = 0;
		}
		
		/* 均值滤波 */
		voltage = AverageFilter(V_OriginalValue, Filter_Count);
		electricity = AverageFilter(A_OriginalValue, Filter_Count);
			
		if (menu >= 4) {
			/* 电压电流结果计算 */
			voltage = ADC_ToVoltage(voltage);
			electricity = ADC_ToElectricity(electricity);
		}
		
		// 0123 456
		/* 显示界面切换 */
		switch (menu) {
			
			case 0:	// 设置电压校准点1
				Menu_SetV1(ADCValue[0]);
				break;
			case 1:	// 设置电压校准点2
				Menu_SetV2(ADCValue[0]);
				break;
			case 2: // 设置电流校准点1
				Menu_SetA1(ADCValue[1]);
				break;
			case 3:	// 设置电流校准点2
				Menu_SetA2(ADCValue[1]);
				break;
			
			case 4:	// 电压电流均显示
				Menu_VA(voltage, electricity);
				break;
			case 5: // 高精度电压显示
				Menu_OnlyV(voltage);
				break;
			case 6: // 高精度电流显示
				Menu_OnlyA(electricity);
				break;
		}
	

#if BLE_Function == 1
		// 蓝牙测试
		if (GetTick() >= (Ble_Time + 1000)) {
			Ble_Time = GetTick();
			UART_SendString("hello\r\n");	
		}
#endif

		FirmwareDelay(10000);
  }
}

/* 2ms刷新一次 */
void BTIM1_IRQHandler(void) {
	if (BTIM_GetITStatus(CW_BTIM1, BTIM_IT_OV)) {
		BTIM_ClearITPendingBit(CW_BTIM1, BTIM_IT_OV);
		
		Nixie_Show();
	}
}

void BTIM2_IRQHandler(void) {
	if (BTIM_GetITStatus(CW_BTIM2, BTIM_IT_OV)) {
		BTIM_ClearITPendingBit(CW_BTIM2, BTIM_IT_OV);
		Key_GetState();  //调用状态机
		
		/* 单击处理：切换显示模式（电压电流同时显示，高精度电压显示，高精度电流显示） */
		if(KeyCfg.KEY_Event == KEY_Event_SingleClick){
			menu++;
			if (menu == 4) {
				menu = 0;
			}
			if (menu == 7) {
				menu = 4;
			}
		}
		/* 双击处理：进入校准模式 */
		if(KeyCfg.KEY_Event == KEY_Event_DoubleClick){
			if (menu >= 4) {
				menu = 0;
			} else {
				Calibration_SetInfo(menu + 1, (menu == 0 || menu == 1) ? ADCValue[0] : ADCValue[1]);
			}
		}
		/* 长按处理：保存校准 */
		if(KeyCfg.KEY_Event == KEY_Event_LongPress)	{
			menu = 4;
			Calibration_SaveInfo();
		}
		
	}
}

