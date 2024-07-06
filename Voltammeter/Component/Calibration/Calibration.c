#include "Calibration.h"
#include "FLASH.h"

#define CalibrationOpen		1
#define CalibrationDown		0

uint16_t VA_Standard[5];
float V_K;
float A_K;

void ComputeK(void) {
	V_K = (5 - 3.3) / (VA_Standard[2] - VA_Standard[1]) * 1000; 
	A_K = (1.5 - 0.3) / (VA_Standard[4] - VA_Standard[3]) * 1000; 
}

void Calibration_ReadInfo(void) {
	FLASH_Read(0, VA_Standard, 5);
	
	/* δУ׼������������ֵ */
	if (0xAA != VA_Standard[0]) {
		VA_Standard[1] = 3.3 / 23 / 1.5 * 4096;
		VA_Standard[2] = 5.0 / 23 / 1.5 * 4096;
		VA_Standard[3] = 0.3 * 0.1 / 1.5 * 4096;
		VA_Standard[4] = 1.5 * 0.1 / 1.5 * 4096;
	}

	ComputeK();
}

void Calibration_SaveInfo(void) {
	VA_Standard[0] = 0xAA;
	FLASH_Write(0, VA_Standard, 5);
}

void Calibration_SetInfo(uint8_t Index, uint16_t Data) {
	VA_Standard[Index] = Data;
}

uint16_t ADC_ToVoltage(uint16_t ADCValue) {
	
#if CalibrationOpen
	uint16_t ResultVoltage = ADCValue * V_K;
#else
	/**
	 * 1500    			1.5V�Ļ�׼��ѹ ͬʱ �Խ���Ŵ�1000��������ʾ
	 * >>12   			12λAD��Ч�ڳ���4096
	 * (R1+R2)/R1   �����ѹ
	 */
	uint16_t ResultVoltage = (ADCValue * 1500 >> 12) * (R1 + R2) / R1;
	
//	if (ResultVoltage >= 1000) {
//		if (ResultVoltage % 10 >= 5) {
//			ResultVoltage = ResultVoltage / 10 + 1;
//		} else {
//			ResultVoltage = ResultVoltage / 10;	
//		}
//	}
#endif

	return ResultVoltage;
}

uint16_t ADC_ToElectricity(uint16_t ADCValue) {
		
#if CalibrationDown
	uint16_t ResultElectricity = ADCValue * A_K;
#else
	/**
	 * 1500    			1.5V�Ļ�׼��ѹ ͬʱ �Խ���Ŵ�1000��������ʾ
	 * >>12   			12λAD��Ч�ڳ���4096
	 * 10           �Ŵ�10�����ٺ����±��ڲ鿴С�������λ
	 */
	uint16_t ResultElectricity = ADCValue * 1500 * 10 >> 12;
#endif
	
	return ResultElectricity;
}
