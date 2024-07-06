#ifndef __Key_H__
#define __Key_H__

///////////////////////////////////////////////////////////
//
// �ļ����ܣ���������
// �汾��V1.0
// ���ߣ�īε��MW��
// �޸�ʱ�䣺2023/05/12
//
///////////////////////////////////////////////////////////

#include "base_types.h"
#include "cw32f003.h"

#define KEY_Port		CW_GPIOA
#define KEY_Pin			GPIO_PIN_3

typedef enum {
	KeyIdle = 0,
	KeyPress = 1,
} KeyState;

/**
  * @brief ������ʼ��
  * @return ��
  */
void Key_Init(void);

/**
  * @brief ��ȡ����״̬
  * @return 
  */
KeyState Key_GetState(void);

#endif
