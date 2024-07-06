#ifndef __Key_H__
#define __Key_H__

///////////////////////////////////////////////////////////
//
// 文件功能：按键功能
// 版本：V1.0
// 作者：墨蔚（MW）
// 修改时间：2023/05/12
//
///////////////////////////////////////////////////////////

#include "base_types.h"
#include "cw32f003.h"

#define KEY_Port		CW_GPIOA
#define KEY_Pin			GPIO_PIN_3

typedef enum {
	KeyIdle = 0,
	KeyPress = 1,
} KeyState;

/**
  * @brief 按键初始化
  * @return 无
  */
void Key_Init(void);

/**
  * @brief 获取按键状态
  * @return 
  */
KeyState Key_GetState(void);

#endif
