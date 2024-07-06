#include "ADC.h"
#include "cw32f003_rcc.h"
#include "cw32f003_gpio.h"
#include "cw32f003_adc.h"

uint16_t ADCValue[2];

void ADC_ChannelInit(void) {
	__RCC_GPIOB_CLK_ENABLE();
	__RCC_ADC_CLK_ENABLE();
	
	/* ���ų�ʼ�� */
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.IT = GPIO_IT_NONE;
	GPIO_InitStructure.Mode = GPIO_MODE_ANALOG;
	GPIO_InitStructure.Pins = ADC_Pin_9;
	GPIO_Init(ADC_Port, &GPIO_InitStructure);
	PB01_ANALOG_ENABLE();		// ʹ��ģ������
	PB05_ANALOG_ENABLE();
	
	ADC_InitTypeDef ADC_InitStruct;
	ADC_StructInit(&ADC_InitStruct);
	ADC_InitStruct.ADC_ClkDiv = ADC_Clk_Div4;		// ADCʱ������ PCLK/4 = 6/4 = 1.5MHz
	ADC_InitStruct.ADC_SampleTime = ADC_SampTime10Clk;	// ��������Ϊ10
	ADC_InitStruct.ADC_VrefSel = ADC_Vref_BGR1p5;	// �ο���ѹ1.5V
	
	ADC_SerialChTypeDef ADC_SerialStruct;
	ADC_SerialStruct.ADC_InitStruct = ADC_InitStruct;
	ADC_SerialStruct.ADC_Sqr0Chmux = ADC_SqrCh9;		// ADC���У�PB01��ͨ��9
	ADC_SerialStruct.ADC_Sqr1Chmux = ADC_SqrCh11;		// ADC���У�PB05��ͨ��11
	ADC_SerialStruct.ADC_SqrEns = ADC_SqrEns01;			// ����0~1
	ADC_SerialChContinuousModeCfg(&ADC_SerialStruct);	// ����Ϊ����ת��ģʽ
	
	ADC_ClearITPendingAll();	// ��������ж�״̬
	ADC_Enable();
	ADC_SoftwareStartConvCmd(ENABLE);	// �������ADC
}

void ADC_GetValue(void) {
	ADC_GetSqr0Result(&ADCValue[0]);
	ADC_GetSqr1Result(&ADCValue[1]);
}
