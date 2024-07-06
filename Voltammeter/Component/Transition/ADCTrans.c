#include "ADCTrans.h"

uint16_t ADC_ToVoltage(uint16_t ADCValue) {	
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

	return ResultVoltage;
}

uint16_t ADC_ToElectricity(uint16_t ADCValue) {
	/**
	 * 1500    			1.5V�Ļ�׼��ѹ ͬʱ �Խ���Ŵ�1000��������ʾ
	 * >>12   			12λAD��Ч�ڳ���4096
	 * 10           �Ŵ�10�����ٺ����±��ڲ鿴С�������λ
	 */
	uint16_t ResultElectricity = ADCValue * 1500 * 10 >> 12;
	return ResultElectricity;
}
