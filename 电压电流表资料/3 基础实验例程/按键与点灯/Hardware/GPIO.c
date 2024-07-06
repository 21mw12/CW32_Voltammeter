#include "GPIO.h"

uint8_t Flag_Key;         //������־λ
extern uint8_t Flag_Seg;

void GPIO_init(void)
{
  GPIO_InitTypeDef GPIO_Init_Struct;                 //�ṹ�嶨��
  __RCC_GPIOA_CLK_ENABLE();                          //��GPIOʱ��
	__RCC_GPIOB_CLK_ENABLE();
	__RCC_GPIOC_CLK_ENABLE();
  //PA03��������
	GPIO_Init_Struct.IT   = GPIO_IT_NONE;              //���ж�
  GPIO_Init_Struct.Mode = GPIO_MODE_INPUT_PULLUP;    //��������
  GPIO_Init_Struct.Pins = GPIO_PIN_3;
  GPIO_Init(CW_GPIOA, &GPIO_Init_Struct);            
	//PB07λѡ����
	GPIO_Init_Struct.IT   = GPIO_IT_NONE;
  GPIO_Init_Struct.Mode = GPIO_MODE_OUTPUT_PP;       //�������
  GPIO_Init_Struct.Pins = GPIO_PIN_7;
  GPIO_Init(CW_GPIOB, &GPIO_Init_Struct);
	//PC04��������
	GPIO_Init_Struct.IT   = GPIO_IT_NONE;
  GPIO_Init_Struct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_Init_Struct.Pins = GPIO_PIN_4;
  GPIO_Init(CW_GPIOC, &GPIO_Init_Struct);
}

void Key_Scan(void)
{
  if(GPIO_ReadPin(CW_GPIOA,GPIO_PIN_3) == GPIO_Pin_RESET)
	{
	  Flag_Key = 1;
	}
	if(Flag_Key)
	{
	  if(GPIO_ReadPin(CW_GPIOA,GPIO_PIN_3) == GPIO_Pin_SET)
        {
            Flag_Key = 0;
					if(Flag_Seg == 0) Flag_Seg = 1;
					else Flag_Seg = 0;
        }
	}
}
