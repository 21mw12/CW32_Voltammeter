#ifndef __ADC_H__
#define __ADC_H__

///////////////////////////////////////////////////////////
//
// �ļ����ܣ�ADC��ȡ
// �汾��V1.0
// ���ߣ�īε��MW��
// �޸�ʱ�䣺2023/05/12
//
///////////////////////////////////////////////////////////

#include "base_types.h"
#include "cw32f003.h"

/* ADC���� */
#define ADC_Port			CW_GPIOB
#define ADC_Pin_9			GPIO_PIN_1
#define ADC_Pin_11		GPIO_PIN_5

/* ADC�ɼ��������ݣ��ֱ���Դ��ͨ��0��ͨ��1 */
extern uint16_t ADCValue[2];

/**
  * @brief ADCͨ����ʼ��
  * @return ��
  */
void ADC_ChannelInit(void);

/**
  * @brief ��ȡADC���ж�Ӧ����
  * @return ADCԭʼ����
  */
void ADC_GetValue(void);

#endif
