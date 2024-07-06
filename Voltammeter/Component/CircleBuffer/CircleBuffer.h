#ifndef __CIRCLE_BUFFER_H
#define __CIRCLE_BUFFER_H

///////////////////////////////////////////////////////////
//
// �ļ����ܣ����λ������Ļ�������
// �汾��V1.0
// ���ߣ�īε��MW��
// �޸�ʱ�䣺2024/02/22
//
///////////////////////////////////////////////////////////

#include "base_types.h"

/* ���λ������е��������� */
#define CBuf_Type		uint16_t

/* ���λ������ṹ�� */
typedef struct {
	uint32_t pRead;
	uint32_t pWrite;
	uint32_t len;
	CBuf_Type* buf;	
} sCircleBuffer;

/**
  * @brief ���λ�������ʼ��
  * @param pCBuf ���λ������ṹ��
  * @param Len ��������С
  * @param Buf ��������ַ
  * @return ��
  */
void CircleBuffer_Init(sCircleBuffer* pCBuf, uint32_t Len, CBuf_Type* Buf);

/**
  * @brief ���λ�����������
  * @param pCBuf ���λ������ṹ��
  * @param Val ������ֵ
  * @return 1 Ϊ�����ɹ�
	* 				0 Ϊ����ʧ��
  */
uint8_t CircleBuffer_Read(sCircleBuffer* pCBuf, CBuf_Type* Val);

/**
  * @brief ���λ�����д����
  * @param pCBuf ���λ������ṹ��
  * @param Val д���ֵ
  * @return 1 Ϊ�����ɹ�
	* 				0 Ϊ����ʧ��
  */
uint8_t CircleBuffer_Write(sCircleBuffer* pCBuf, CBuf_Type Val);

#endif
