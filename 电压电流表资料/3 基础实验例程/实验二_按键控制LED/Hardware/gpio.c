#include "gpio.h"

uint8_t Flag_Key;         //按键标志位
extern uint8_t Flag_LED;  //LED显示标志位

void Gpio_Init(void)
{
	__RCC_GPIOC_CLK_ENABLE();//打开GPIOC的时钟
	GPIO_InitTypeDef GPIO_InitStruct;
	GPIO_InitStruct.Pins = GPIO_PIN_13;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.IT = GPIO_IT_NONE;
	GPIO_InitStruct.Speed = GPIO_SPEED_HIGH;
  GPIO_Init(CW_GPIOC, &GPIO_InitStruct);
	
	__RCC_GPIOB_CLK_ENABLE();//打开GPIOB的时钟
	GPIO_InitStruct.Pins = GPIO_PIN_2;
	GPIO_InitStruct.Mode = GPIO_MODE_INPUT_PULLDOWN;
  GPIO_InitStruct.IT = GPIO_IT_NONE;
  GPIO_Init(CW_GPIOB, &GPIO_InitStruct);
}

void Key_Scan(void)
{
  if(GPIO_ReadPin(CW_GPIOB,GPIO_PIN_2) == GPIO_Pin_SET)  //检测PB2是否为高电平
    {
          Flag_Key = 1;
    }
  if(Flag_Key)                                           //接着判断标志位
    {
      if(GPIO_ReadPin(CW_GPIOB,GPIO_PIN_2) == GPIO_Pin_RESET)    //如果按键已经松开
        {
          Flag_Key = 0;   //清零标志位，等待下一次按键检测
          if(Flag_LED == 0) Flag_LED = 1; //按键按下该变LED显示标志位的值，由显示标志位控制LED   
          else Flag_LED = 0;
        }
    }
}
