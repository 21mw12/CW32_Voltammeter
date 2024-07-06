#ifndef __AVERAGE_FILTER_H
#define __AVERAGE_FILTER_H

///////////////////////////////////////////////////////////
//
// 文件功能：均值滤波功能
// 版本：V1.0
// 作者：墨蔚（MW）
// 修改时间：2024/07/01
//
///////////////////////////////////////////////////////////

#include "base_types.h"

/**
  * @brief 均值滤波
  * @param data 数据数组
  * @param size 数据量
  * @return 滤波后的值
	* 
	* 注：除去最大最小值的情况下取平均值
  */
uint16_t AverageFilter(uint16_t* data, uint32_t size);

#endif
