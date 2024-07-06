#ifndef __CALIBRATION_H
#define __CALIBRATION_H

///////////////////////////////////////////////////////////
//
// 文件功能：校准设置以及数据转换
// 版本：V1.0
// 作者：墨蔚（MW）
// 修改时间：2024/07/04
//
//   VCC
//    |
//    |
//   [ ] R2
//    |
//    ——————— ADC＿Pin
//    |
//   [ ] R1
//    |
//   GND
//
///////////////////////////////////////////////////////////

#include "base_types.h"
#include "cw32f003.h"

/* 分压电阻，如上图所示 */
#define R1					10
#define R2					220

/**
 * 标准采集参数
 * 分别表示：是否采集标志位、3.3V标准、5V标准、0.3A标准、1.5A标准
 */
extern uint16_t VA_Standard[5];

/**
  * @brief 读取校准所需计算数据
  * @return 无
  */
void Calibration_ReadInfo(void);

/**
  * @brief 保存校准所需计算数据
  * @return 无
  */
void Calibration_SaveInfo(void);

/**
  * @brief 设置校准所需计算数据
  * @param Index 校准数据的下表
  * @param Data  校准数据值	
  * @return 无
  */
void Calibration_SetInfo(uint8_t Index, uint16_t Data);

/**
  * @brief 计算电压值
  * @param ADCValue ADC采集值
  * @return 电压值
  */
uint16_t ADC_ToVoltage(uint16_t ADCValue);

/**
  * @brief 计算电流值
  * @param ADCValue ADC采集值
  * @return 电流值
  */
uint16_t ADC_ToElectricity(uint16_t ADCValue);

#endif
