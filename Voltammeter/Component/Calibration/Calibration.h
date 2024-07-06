#ifndef __CALIBRATION_H
#define __CALIBRATION_H

///////////////////////////////////////////////////////////
//
// �ļ����ܣ�У׼�����Լ�����ת��
// �汾��V1.0
// ���ߣ�īε��MW��
// �޸�ʱ�䣺2024/07/04
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
 * ��׼�ɼ�����
 * �ֱ��ʾ���Ƿ�ɼ���־λ��3.3V��׼��5V��׼��0.3A��׼��1.5A��׼
 */
extern uint16_t VA_Standard[5];

/**
  * @brief ��ȡУ׼�����������
  * @return ��
  */
void Calibration_ReadInfo(void);

/**
  * @brief ����У׼�����������
  * @return ��
  */
void Calibration_SaveInfo(void);

/**
  * @brief ����У׼�����������
  * @param Index У׼���ݵ��±�
  * @param Data  У׼����ֵ	
  * @return ��
  */
void Calibration_SetInfo(uint8_t Index, uint16_t Data);

/**
  * @brief �����ѹֵ
  * @param ADCValue ADC�ɼ�ֵ
  * @return ��ѹֵ
  */
uint16_t ADC_ToVoltage(uint16_t ADCValue);

/**
  * @brief �������ֵ
  * @param ADCValue ADC�ɼ�ֵ
  * @return ����ֵ
  */
uint16_t ADC_ToElectricity(uint16_t ADCValue);

#endif
