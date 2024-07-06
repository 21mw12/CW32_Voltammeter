#ifndef __NIXIE_H__
#define __NIXIE_H__

///////////////////////////////////////////////////////////
//
// �ļ����ܣ�����ܵ���ʾ����
// �汾��V1.0
// ���ߣ�īε��MW��
// �޸�ʱ�䣺2023/05/12
//
///////////////////////////////////////////////////////////

#include "base_types.h"
#include "cw32f003.h"

/* �����COM�˽ӿ� */
#define Nixie_Port_COM1		CW_GPIOB
#define Nixie_Pin_COM1		GPIO_PIN_7
#define Nixie_Port_COM2		CW_GPIOC
#define Nixie_Pin_COM2		GPIO_PIN_3
#define Nixie_Port_COM3		CW_GPIOC
#define Nixie_Pin_COM3		GPIO_PIN_2
#define Nixie_Port_COM4		CW_GPIOA
#define Nixie_Pin_COM4		GPIO_PIN_1
#define Nixie_Port_COM5		CW_GPIOC
#define Nixie_Pin_COM5		GPIO_PIN_0
#define Nixie_Port_COM6		CW_GPIOC
#define Nixie_Pin_COM6		GPIO_PIN_1

/* �����Pin�˽ӿ� */
#define Nixie_Port_A			CW_GPIOC
#define Nixie_Pin_A				GPIO_PIN_4
#define Nixie_Port_B			CW_GPIOB
#define Nixie_Pin_B				GPIO_PIN_6
#define Nixie_Port_C			CW_GPIOB
#define Nixie_Pin_C				GPIO_PIN_4
#define Nixie_Port_D			CW_GPIOB
#define Nixie_Pin_D				GPIO_PIN_2
#define Nixie_Port_E			CW_GPIOA
#define Nixie_Pin_E				GPIO_PIN_0
#define Nixie_Port_F			CW_GPIOB
#define Nixie_Pin_F				GPIO_PIN_0
#define Nixie_Port_G			CW_GPIOA
#define Nixie_Pin_G				GPIO_PIN_4
#define Nixie_Port_DP			CW_GPIOB
#define Nixie_Pin_DP			GPIO_PIN_3

/* ��ʾ�������飬�������ÿλ������ */
extern uint8_t NixieShowNumInfo[6];

/**
  * @brief ����ܳ�ʼ��
  * @return ��
  */
void Nixie_Init(void);

/**
  * @brief �������ʾ
  * @return ��
  */
void Nixie_Show(void);

/**
  * @brief ���������Դ�
  * @return ��
  */
void Nixie_ClearNumInfo(void);

#endif
