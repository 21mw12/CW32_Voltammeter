#ifndef __ADCTRANS_H__
#define __ADCTRANS_H__

///////////////////////////////////////////////////////////
//
// �ļ����ܣ�
// �汾��V1.0
// ���ߣ�īε��MW��
// �޸�ʱ�䣺2023/05/12
//
//   VCC
//    |
//    |
//   [ ] R2
//    |
//    �������������� ADC��Pin
//    |
//   [ ] R1
//    |
//   GND
//
///////////////////////////////////////////////////////////

#include "base_types.h"
#include "cw32f003.h"

/* ��ѹ���裬����ͼ��ʾ */
#define R1					10
#define R2					220

/**
  * @brief ADC���ݼ���Ϊ��ѹ����
  * @return ��ѹֵ
  */
uint16_t ADC_ToVoltage(uint16_t ADCValue);


uint16_t ADC_ToElectricity(uint16_t ADCValue);

#endif
