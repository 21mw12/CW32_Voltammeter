#include "KeyStateMachine.h"
#include "BTIM.h"
#include "cw32f003_rcc.h"
#include "cw32f003_gpio.h"

KEY_Configure_TypeDef KeyCfg={
		0,
		KEY_Action_Release,
		KEY_Status_Idle,
		KEY_Event_Null
};

/**
  * @brief 获取按键动作，按下或释放，保存到结构体
  * @return 无
  */
void KEY_GetAction(void) {
	if(GPIO_ReadPin(Key_Port, Key_Pin) == RESET)	{
		KeyCfg.KEY_Action = KEY_Action_Press;
	}	else {
		KeyCfg.KEY_Action =  KEY_Action_Release;
	}
}

void Key_Init(void) { 
	__RCC_GPIOA_CLK_ENABLE();
	
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.IT = GPIO_IT_NONE;
	GPIO_InitStructure.Mode = GPIO_MODE_INPUT_PULLUP;
	GPIO_InitStructure.Pins = Key_Pin;
	GPIO_Init(Key_Port, &GPIO_InitStructure);
	
	BTIM2_Init(20000); //初始化20ms的定时器
}

void Key_GetState(void) {
	KEY_GetAction();	// 获取按键状态

	switch(KeyCfg.KEY_Status) {
		/**
			* 状态：空闲
			* 此状态下按下按键，状态机进入消抖状态，状态机不产生事件
		  */
		case KEY_Status_Idle:
			if (KeyCfg.KEY_Action == KEY_Action_Press)	{
				KeyCfg.KEY_Status = KEY_Status_Debounce;
			}
			KeyCfg.KEY_Event = KEY_Event_Null;
			break;

		/**
			* 状态：消抖
			* 该函数是定时触发，所以当下一次定时器到时时直接查看当前IO口状态就可以知道按键是否有按下
			* 以前需要延时消抖的时间会由定时器跳过
			*/
		case KEY_Status_Debounce:
			if (KeyCfg.KEY_Action == KEY_Action_Press) {
				KeyCfg.KEY_Status = KEY_Status_ConfirmPress;
			} else {
				KeyCfg.KEY_Status = KEY_Status_Idle;
			}
			KeyCfg.KEY_Event = KEY_Event_Null;
			break;

		/**
			* 状态：确认按下
			* 如果按键按下并且计数值达到长按标准时，状态机进入确认长按，状态机不产生事件
			* 如果按键按下并且计数值未达到长按标准时，计数加一，状态机不产生单击事件
			* 如果按键松开，状态机进入空闲状态，状态机不产生单击事件
		  */
		case KEY_Status_ConfirmPress:
			if ((KeyCfg.KEY_Action == KEY_Action_Press) && (KeyCfg.KEY_Count >= KEY_LONG_PRESS_TIME)) {
				KeyCfg.KEY_Count = 0;
				KeyCfg.KEY_Status = KEY_Status_ConfirmPressLong;
				KeyCfg.KEY_Event = KEY_Event_Null;
			}
			else if((KeyCfg.KEY_Action == KEY_Action_Press) && (KeyCfg.KEY_Count < KEY_LONG_PRESS_TIME)) {
				KeyCfg.KEY_Count++;
				KeyCfg.KEY_Event = KEY_Event_Null;
			}
			else {
				KeyCfg.KEY_Count = 0;
				KeyCfg.KEY_Status = KEY_Status_WaiteAgain;
				KeyCfg.KEY_Event = KEY_Event_Null;//KEY_Event_SingleClick;
			}
			break;
			
		/**
			* 状态：确认长按
			* 如果按键按下，状态机不产生事件
			* 如果按键松开，状态机进入空闲状态，状态机产生长按事件
			*/
		case KEY_Status_ConfirmPressLong:
			if(KeyCfg.KEY_Action == KEY_Action_Press) {
				KeyCfg.KEY_Event = KEY_Event_Null;
			} else {
				KeyCfg.KEY_Status = KEY_Status_Idle;
				KeyCfg.KEY_Event = KEY_Event_LongPress;
			}
			KeyCfg.KEY_Count = 0;
			break;
			
		/**
			* 状态：等待再次按下
			* 如果按键释放，计数大于双击间隔时长，状态机进入空闲状态，状态机产生单击事件
			* 如果按键释放，计数小于双击间隔时长，计数加一，状态机不产生事件
			* 如果按键按下，状态机进入第二次按下状态
		  */
		case KEY_Status_WaiteAgain:
			if ((KeyCfg.KEY_Action != KEY_Action_Press) && (KeyCfg.KEY_Count >= KEY_WAIT_DOUBLE_TIME))	{
				KeyCfg.KEY_Count = 0;
				KeyCfg.KEY_Status = KEY_Status_Idle;  
				KeyCfg.KEY_Event = KEY_Event_SingleClick;
			}
			else if ((KeyCfg.KEY_Action != KEY_Action_Press) && (KeyCfg.KEY_Count < KEY_WAIT_DOUBLE_TIME)) {
				KeyCfg.KEY_Count++;
				KeyCfg.KEY_Event = KEY_Event_Null;
			}
			else {
				KeyCfg.KEY_Count = 0;
				KeyCfg.KEY_Status = KEY_Status_ConfirmSecondPress;
				KeyCfg.KEY_Event = KEY_Event_Null;
			}
			break;

		/**
			* 状态：确认再次按下
			* 如果按键按下，计数大于长按时长，状态机产生单击事件
			* 如果按键按下，计数小于长按时长，计数加一，状态机不产生事件
			* 如果按键释放，状态机产生双击事件
		  */
		case KEY_Status_ConfirmSecondPress:
			if ((KeyCfg.KEY_Action == KEY_Action_Press) && (KeyCfg.KEY_Count >= KEY_LONG_PRESS_TIME)) {
				KeyCfg.KEY_Count = 0;
				KeyCfg.KEY_Status = KEY_Status_ConfirmPressLong;
				KeyCfg.KEY_Event = KEY_Event_Null;//KEY_Event_SingleClick;
			}
			else if ((KeyCfg.KEY_Action == KEY_Action_Press) && (KeyCfg.KEY_Count < KEY_LONG_PRESS_TIME)) {
				KeyCfg.KEY_Count++;
				KeyCfg.KEY_Event = KEY_Event_Null;
			}
      else {
        KeyCfg.KEY_Count = 0;
				KeyCfg.KEY_Status = KEY_Status_Idle;
				KeyCfg.KEY_Event = KEY_Event_DoubleClick;
      }
			break;

		default:
			break;
	}
}
