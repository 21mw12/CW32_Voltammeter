#ifndef __AVERAGE_FILTER_H
#define __AVERAGE_FILTER_H

///////////////////////////////////////////////////////////
//
// �ļ����ܣ���ֵ�˲�����
// �汾��V1.0
// ���ߣ�īε��MW��
// �޸�ʱ�䣺2024/07/01
//
///////////////////////////////////////////////////////////

#include "base_types.h"

/**
  * @brief ��ֵ�˲�
  * @param data ��������
  * @param size ������
  * @return �˲����ֵ
	* 
	* ע����ȥ�����Сֵ�������ȡƽ��ֵ
  */
uint16_t AverageFilter(uint16_t* data, uint32_t size);

#endif
