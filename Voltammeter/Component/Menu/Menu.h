#ifndef __MENU_H
#define __MENU_H


///////////////////////////////////////////////////////////
//
// 文件功能：菜单界面显示
// 版本：V1.0
// 作者：墨蔚（MW）
// 修改时间：2024/07/04
//
///////////////////////////////////////////////////////////

#include "base_types.h"

/**
  * @brief 电压电流同时显示界面
  * @param VData  待显示的电压值
  * @param AData  待显示的电流值
  * @return 无
  */
void Menu_VA(uint16_t VData, uint16_t AData);

/**
  * @brief 只显示电压界面
  * @param VData  待显示的电压值
  * @return 无
  */
void Menu_OnlyV(uint16_t VData);

/**
  * @brief 只显示电流界面
  * @param AData  待显示的电流值
  * @return 无
  */
void Menu_OnlyA(uint16_t AData);

/**
  * @brief 电压1采集界面
  * @param VData  待显示的电压原始值
  * @return 无
  */
void Menu_SetV1(uint16_t VData);

/**
  * @brief 电压2采集界面
  * @param VData  待显示的电压原始值
  * @return 无
  */
void Menu_SetV2(uint16_t VData);

/**
  * @brief 电流1采集界面
  * @param AData  待显示的电流原始值
  * @return 无
  */
void Menu_SetA1(uint16_t AData);

/**
  * @brief 电流2采集界面
  * @param AData  待显示的电流原始值
  * @return 无
  */
void Menu_SetA2(uint16_t AData);

#endif
