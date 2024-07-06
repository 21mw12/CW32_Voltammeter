#ifndef __ADCTRANS_H__
#define __ADCTRANS_H__

///////////////////////////////////////////////////////////
//
// 文件功能：
// 版本：V1.0
// 作者：墨蔚（MW）
// 修改时间：2023/05/12
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
  * @brief ADC数据计算为电压数据
  * @return 电压值
  */
uint16_t ADC_ToVoltage(uint16_t ADCValue);


uint16_t ADC_ToElectricity(uint16_t ADCValue);

#endif
