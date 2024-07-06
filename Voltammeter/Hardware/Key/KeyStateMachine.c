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
  * @brief ��ȡ�������������»��ͷţ����浽�ṹ��
  * @return ��
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
	
	BTIM2_Init(20000); //��ʼ��20ms�Ķ�ʱ��
}

void Key_GetState(void) {
	KEY_GetAction();	// ��ȡ����״̬

	switch(KeyCfg.KEY_Status) {
		/**
			* ״̬������
			* ��״̬�°��°�����״̬����������״̬��״̬���������¼�
		  */
		case KEY_Status_Idle:
			if (KeyCfg.KEY_Action == KEY_Action_Press)	{
				KeyCfg.KEY_Status = KEY_Status_Debounce;
			}
			KeyCfg.KEY_Event = KEY_Event_Null;
			break;

		/**
			* ״̬������
			* �ú����Ƕ�ʱ���������Ե���һ�ζ�ʱ����ʱʱֱ�Ӳ鿴��ǰIO��״̬�Ϳ���֪�������Ƿ��а���
			* ��ǰ��Ҫ��ʱ������ʱ����ɶ�ʱ������
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
			* ״̬��ȷ�ϰ���
			* ����������²��Ҽ���ֵ�ﵽ������׼ʱ��״̬������ȷ�ϳ�����״̬���������¼�
			* ����������²��Ҽ���ֵδ�ﵽ������׼ʱ��������һ��״̬�������������¼�
			* ��������ɿ���״̬���������״̬��״̬�������������¼�
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
			* ״̬��ȷ�ϳ���
			* ����������£�״̬���������¼�
			* ��������ɿ���״̬���������״̬��״̬�����������¼�
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
			* ״̬���ȴ��ٴΰ���
			* ��������ͷţ���������˫�����ʱ����״̬���������״̬��״̬�����������¼�
			* ��������ͷţ�����С��˫�����ʱ����������һ��״̬���������¼�
			* ����������£�״̬������ڶ��ΰ���״̬
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
			* ״̬��ȷ���ٴΰ���
			* ����������£��������ڳ���ʱ����״̬�����������¼�
			* ����������£�����С�ڳ���ʱ����������һ��״̬���������¼�
			* ��������ͷţ�״̬������˫���¼�
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
