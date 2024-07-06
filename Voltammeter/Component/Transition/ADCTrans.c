#include "ADCTrans.h"

uint16_t ADC_ToVoltage(uint16_t ADCValue) {	
	/**
	 * 1500    			1.5V的基准电压 同时 对结果放大1000倍便于显示
	 * >>12   			12位AD等效于除以4096
	 * (R1+R2)/R1   电阻分压
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
	 * 1500    			1.5V的基准电压 同时 对结果放大1000倍便于显示
	 * >>12   			12位AD等效于除以4096
	 * 10           放大10倍，再毫安下便于查看小数点后三位
	 */
	uint16_t ResultElectricity = ADCValue * 1500 * 10 >> 12;
	return ResultElectricity;
}
