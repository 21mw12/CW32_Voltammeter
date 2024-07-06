#ifndef __BTIM_H__
#define __BTIM_H__

///////////////////////////////////////////////////////////
//
// �ļ����ܣ�������ʱ������
// �汾��V1.0
// ���ߣ�īε��MW��
// �޸�ʱ�䣺2023/05/12
//
// ע�������жϴ������ظ����壬����interrupts_cw32f003.c�ļ�����д������
//
///////////////////////////////////////////////////////////

#include "base_types.h"
#include "cw32f003.h"
#include "cw32f003_btim.h"

/**
  * @brief ��ʱ��1��ʼ��
  * @param us ��ʱ���жϴ���ʱ�䣨��λus��
  * @return ��
  */
void BTIM1_Init(uint16_t us);

/**
  * @brief ��ʱ��2��ʼ��
  * @param us ��ʱ���жϴ���ʱ�䣨��λus��
  * @return ��
  */
void BTIM2_Init(uint16_t us);


/* ��ʱ���жϴ�����ģ�� */
//void BTIM1_TRQHandler(void) {
//	if (BTIM_GetITStatus(CW_BTIM1, BTIM_IT_OV)) {
//		BTIM_ClearITPendingBit(CW_BTIM1, BTIM_IT_OV);
//		
//		
//	}
//}

#endif
