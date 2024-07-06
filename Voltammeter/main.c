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

/* ADC�ɼ����õĵ�ѹ����ԭʼֵ */
#define Filter_Count		100		// ��������
uint8_t Flag_OriginalValue = 0;
uint16_t V_OriginalValue[Filter_Count];
uint16_t A_OriginalValue[Filter_Count];

/* �������õĵ�ѹ����ֵ */
uint16_t voltage = 0;
uint16_t electricity = 0;

/* ��ʾģʽ */
uint8_t menu = 4;

extern KEY_Configure_TypeDef KeyCfg;

#if BLE_Function == 1
uint32_t Ble_Time = 0;
#endif

void RCC_Configuration(void) {
	FLASH_SetLatency(FLASH_Latency_2);	// ��Ƶ48ʱӦ����Ϊ2
	RCC_HSI_Enable(RCC_HSIOSC_DIV1);		// ������ƵΪ48MHz
	RCC_SYSCLKSRC_Config(RCC_SYSCLKSRC_HSI);	// ѡ��SYSCLKʱ��Դ
	RCC_HCLKPRS_Config(RCC_HCLK_DIV1);	// ����HCLK����ϵ��
	RCC_PCLKPRS_Config(RCC_PCLK_DIV8);	// ����PCLK����ϵ��
	InitTick(48000000);                 // SYSTICK �Ĺ���Ƶ��Ϊ48MHz��ÿms�ж�һ��
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
		/* �ɼ�ADC���� */
		ADC_GetValue();
		
		/* ADC��β��� */
		V_OriginalValue[Flag_OriginalValue] = ADCValue[0];
		A_OriginalValue[Flag_OriginalValue] = ADCValue[1];
		if (++Flag_OriginalValue == Filter_Count) {
			Flag_OriginalValue = 0;
		}
		
		/* ��ֵ�˲� */
		voltage = AverageFilter(V_OriginalValue, Filter_Count);
		electricity = AverageFilter(A_OriginalValue, Filter_Count);
			
		if (menu >= 4) {
			/* ��ѹ����������� */
			voltage = ADC_ToVoltage(voltage);
			electricity = ADC_ToElectricity(electricity);
		}
		
		// 0123 456
		/* ��ʾ�����л� */
		switch (menu) {
			
			case 0:	// ���õ�ѹУ׼��1
				Menu_SetV1(ADCValue[0]);
				break;
			case 1:	// ���õ�ѹУ׼��2
				Menu_SetV2(ADCValue[0]);
				break;
			case 2: // ���õ���У׼��1
				Menu_SetA1(ADCValue[1]);
				break;
			case 3:	// ���õ���У׼��2
				Menu_SetA2(ADCValue[1]);
				break;
			
			case 4:	// ��ѹ��������ʾ
				Menu_VA(voltage, electricity);
				break;
			case 5: // �߾��ȵ�ѹ��ʾ
				Menu_OnlyV(voltage);
				break;
			case 6: // �߾��ȵ�����ʾ
				Menu_OnlyA(electricity);
				break;
		}
	

#if BLE_Function == 1
		// ��������
		if (GetTick() >= (Ble_Time + 1000)) {
			Ble_Time = GetTick();
			UART_SendString("hello\r\n");	
		}
#endif

		FirmwareDelay(10000);
  }
}

/* 2msˢ��һ�� */
void BTIM1_IRQHandler(void) {
	if (BTIM_GetITStatus(CW_BTIM1, BTIM_IT_OV)) {
		BTIM_ClearITPendingBit(CW_BTIM1, BTIM_IT_OV);
		
		Nixie_Show();
	}
}

void BTIM2_IRQHandler(void) {
	if (BTIM_GetITStatus(CW_BTIM2, BTIM_IT_OV)) {
		BTIM_ClearITPendingBit(CW_BTIM2, BTIM_IT_OV);
		Key_GetState();  //����״̬��
		
		/* ���������л���ʾģʽ����ѹ����ͬʱ��ʾ���߾��ȵ�ѹ��ʾ���߾��ȵ�����ʾ�� */
		if(KeyCfg.KEY_Event == KEY_Event_SingleClick){
			menu++;
			if (menu == 4) {
				menu = 0;
			}
			if (menu == 7) {
				menu = 4;
			}
		}
		/* ˫����������У׼ģʽ */
		if(KeyCfg.KEY_Event == KEY_Event_DoubleClick){
			if (menu >= 4) {
				menu = 0;
			} else {
				Calibration_SetInfo(menu + 1, (menu == 0 || menu == 1) ? ADCValue[0] : ADCValue[1]);
			}
		}
		/* ������������У׼ */
		if(KeyCfg.KEY_Event == KEY_Event_LongPress)	{
			menu = 4;
			Calibration_SaveInfo();
		}
		
	}
}

