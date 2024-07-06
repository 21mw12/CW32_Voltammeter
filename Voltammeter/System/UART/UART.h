#ifndef __UART_H__
#define __UART_H__

///////////////////////////////////////////////////////////
//
// 文件功能：UART功能
// 版本：V1.0
// 作者：墨蔚（MW）
// 修改时间：2023/05/12
//
///////////////////////////////////////////////////////////

#include "base_types.h"
#include "cw32f003.h"

/**
  * @brief 串口初始化
  * @return 无
  */
void UART_Init(void);

/**
  * @brief 串口发送字符串数据
  * @param String 字符串数据
  * @return 无
  */
void UART_SendString(char* String);

#endif
