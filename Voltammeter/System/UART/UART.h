#ifndef __UART_H__
#define __UART_H__

///////////////////////////////////////////////////////////
//
// �ļ����ܣ�UART����
// �汾��V1.0
// ���ߣ�īε��MW��
// �޸�ʱ�䣺2023/05/12
//
///////////////////////////////////////////////////////////

#include "base_types.h"
#include "cw32f003.h"

/**
  * @brief ���ڳ�ʼ��
  * @return ��
  */
void UART_Init(void);

/**
  * @brief ���ڷ����ַ�������
  * @param String �ַ�������
  * @return ��
  */
void UART_SendString(char* String);

#endif
