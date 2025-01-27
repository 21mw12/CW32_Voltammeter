#ifndef __KEYSTATEMACHINE_H
#define __KEYSTATEMACHINE_H

////////////////////////////////////////////////////////////////////////////
//
// 文件功能：通过状态机来实现按键的单击双击和长按功能
// 作者：老子姓李！(SCDN平台) | nanshoui163(github平台)
// CSDN连接：https://blog.csdn.net/qq_44078824/article/details/123753825
//					 https://blog.csdn.net/qq_44078824/article/details/123757354
// github连接：https://github.com/nanshoui163/KeyStateMachine
//             https://github.com/nanshoui163/KeyStateMachine2
//
//	原作者信息在上，这里只做个人的二次理解并转换为个人的代码风格！！！
//
////////////////////////////////////////////////////////////////////////////

#include "base_types.h"
#include "cw32f003.h"

/* 长按的触发时长 */
#define KEY_LONG_PRESS_TIME    50  // 20ms*50 = 1s
/* 双击的间隔时长 */
#define KEY_WAIT_DOUBLE_TIME   25 // 20ms*25 = 500ms

/* 按键引脚配置信息 */
#define Key_Port			CW_GPIOA
#define Key_Pin 			GPIO_PIN_3	

/* 状态机状态 */
typedef enum {
	KEY_Status_Idle = 0, 					// 空闲
	KEY_Status_Debounce,  				// 消抖
	KEY_Status_ConfirmPress,    	// 确认按下	
	KEY_Status_ConfirmPressLong, 	// 确认长按
	KEY_Status_WaiteAgain, 				// 等待再次按下
	KEY_Status_ConfirmSecondPress // 确认再次按下
} KEY_StatusList_TypeDef;

/* 按键事件 */
typedef enum {
	KEY_Event_Null = 0x00, 					// 空闲
	KEY_Event_SingleClick = 0x01, 	// 单击
	KEY_Event_DoubleClick = 0x02,  	// 双击
	KEY_Event_LongPress = 0x04 			// 长按
} KEY_EventList_TypeDef;

/* 按键状态 */
typedef enum { 
	KEY_Action_Press = 0,		// 按下
	KEY_Action_Release			// 释放
} KEY_Action_TypeDef;

/* 按键结构体 */
typedef struct {
	uint16_t									KEY_Count;		// 按键长按时长计数
	KEY_Action_TypeDef				KEY_Action;		// 按键状态
	KEY_StatusList_TypeDef		KEY_Status;		// 状态机状态
	KEY_EventList_TypeDef			KEY_Event;		// 按键事件
} KEY_Configure_TypeDef;

/**
  * @brief 按键初始化
  * @return 无
  */
void Key_Init(void);

/**
  * @brief 调用状态机获取按键状态
  * @return 无
  */
void Key_GetState(void);

/* 中断函数格式 */
//void BTIM2_IRQHandler(void) {
//	if (BTIM_GetITStatus(CW_BTIM2, BTIM_IT_OV)) {
//		BTIM_ClearITPendingBit(CW_BTIM2, BTIM_IT_OV);
//		Key_GetState();  //调用状态机
//		
//		/* 单击处理 */
//		if(KeyCfg.KEY_Event == KEY_Event_SingleClick){
//
//		}
//		/* 双击处理 */
//		if(KeyCfg.KEY_Event == KEY_Event_DoubleClick){
//
//		}
//		/* 长按处理 */
//		if(KeyCfg.KEY_Event == KEY_Event_LongPress)	{
//
//		}
//		
//	}
//}

#endif
