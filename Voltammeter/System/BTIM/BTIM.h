#ifndef __BTIM_H__
#define __BTIM_H__

///////////////////////////////////////////////////////////
//
// 文件功能：基础定时器功能
// 版本：V1.0
// 作者：墨蔚（MW）
// 修改时间：2023/05/12
//
// 注：如遇中断处理函数重复定义，需在interrupts_cw32f003.c文件中书写或屏蔽
//
///////////////////////////////////////////////////////////

#include "base_types.h"
#include "cw32f003.h"
#include "cw32f003_btim.h"

/**
  * @brief 定时器1初始化
  * @param us 定时器中断触发时间（单位us）
  * @return 无
  */
void BTIM1_Init(uint16_t us);

/**
  * @brief 定时器2初始化
  * @param us 定时器中断触发时间（单位us）
  * @return 无
  */
void BTIM2_Init(uint16_t us);


/* 定时器中断处理函数模板 */
//void BTIM1_TRQHandler(void) {
//	if (BTIM_GetITStatus(CW_BTIM1, BTIM_IT_OV)) {
//		BTIM_ClearITPendingBit(CW_BTIM1, BTIM_IT_OV);
//		
//		
//	}
//}

#endif
