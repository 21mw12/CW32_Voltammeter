#include "Segment_Display.h"

extern uint8_t Flag_Seg;       

void Seg_Init(void)
{
  GPIO_WritePin(CW_GPIOC,GPIO_PIN_4,GPIO_Pin_RESET);
  GPIO_WritePin(CW_GPIOB,GPIO_PIN_7,GPIO_Pin_RESET);          //Ãð
}
void Seg_LED(void)
{
  if(Flag_Seg == 1)
	{
	  GPIO_WritePin(CW_GPIOC,GPIO_PIN_4,GPIO_Pin_SET);
		GPIO_WritePin(CW_GPIOB,GPIO_PIN_7,GPIO_Pin_RESET);          //ÁÁ
	}
	else 
	{
	  GPIO_WritePin(CW_GPIOC,GPIO_PIN_4,GPIO_Pin_RESET);
		GPIO_WritePin(CW_GPIOB,GPIO_PIN_7,GPIO_Pin_RESET);          //Ãð
	}
}

