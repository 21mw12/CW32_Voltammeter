#ifndef _FLASH_H_
#define _FLASH_H_

////////////////////////////////////////////////////////////////////////////
//
// �ļ����ܣ���дFlash����
// ���ߣ�CW32�ٷ�
//
//	ԭ������Ϣ���ϣ�����ֻ�����˵Ķ�����Ⲣת��Ϊ���˵Ĵ����񣡣���
//
////////////////////////////////////////////////////////////////////////////

#include "base_types.h"
#include "cw32f003.h"

/**
  * @brief д��flash
  * @param offset ��ʼƫ����
  * @param data ��������
  * @param lenght �������ݳ���
  * @return 
  */
void FLASH_Write(uint16_t offset, uint16_t *data, uint16_t lenght);

/**
  * @brief ����flash
  * @param offset ��ʼƫ����
  * @param data ��������
  * @param lenght �������ݳ���
  * @return 
  */
void FLASH_Read(uint16_t offset, uint16_t *data, uint16_t lenght);
#endif
