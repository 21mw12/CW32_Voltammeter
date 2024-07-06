#ifndef __MENU_H
#define __MENU_H


///////////////////////////////////////////////////////////
//
// �ļ����ܣ��˵�������ʾ
// �汾��V1.0
// ���ߣ�īε��MW��
// �޸�ʱ�䣺2024/07/04
//
///////////////////////////////////////////////////////////

#include "base_types.h"

/**
  * @brief ��ѹ����ͬʱ��ʾ����
  * @param VData  ����ʾ�ĵ�ѹֵ
  * @param AData  ����ʾ�ĵ���ֵ
  * @return ��
  */
void Menu_VA(uint16_t VData, uint16_t AData);

/**
  * @brief ֻ��ʾ��ѹ����
  * @param VData  ����ʾ�ĵ�ѹֵ
  * @return ��
  */
void Menu_OnlyV(uint16_t VData);

/**
  * @brief ֻ��ʾ��������
  * @param AData  ����ʾ�ĵ���ֵ
  * @return ��
  */
void Menu_OnlyA(uint16_t AData);

/**
  * @brief ��ѹ1�ɼ�����
  * @param VData  ����ʾ�ĵ�ѹԭʼֵ
  * @return ��
  */
void Menu_SetV1(uint16_t VData);

/**
  * @brief ��ѹ2�ɼ�����
  * @param VData  ����ʾ�ĵ�ѹԭʼֵ
  * @return ��
  */
void Menu_SetV2(uint16_t VData);

/**
  * @brief ����1�ɼ�����
  * @param AData  ����ʾ�ĵ���ԭʼֵ
  * @return ��
  */
void Menu_SetA1(uint16_t AData);

/**
  * @brief ����2�ɼ�����
  * @param AData  ����ʾ�ĵ���ԭʼֵ
  * @return ��
  */
void Menu_SetA2(uint16_t AData);

#endif
