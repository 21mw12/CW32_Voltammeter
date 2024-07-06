#include "main.h"

uint8_t Flag_Key;         //按键标志位
uint8_t Flag_LED;         //LED显示标志位

int main()
{
  RCC_Configuration();
	gpio_init();
	GPIO_WritePin(CW_GPIOC,GPIO_PIN_0,GPIO_Pin_SET);  //初始化让LED灯处于熄灭状态
	
	while(1)
    {
      Key_Scan();
			LED_Lighting();
    }
}

void RCC_Configuration(void)
{
  FLASH_SetLatency(FLASH_Latency_2); // 设置主频为48MHZ需要注意，Flah的访问周期需要更改为FLASH_Latency_2。
  RCC_HSI_Enable(RCC_HSIOSC_DIV1);   // 设置频率为48M
	RCC_SYSCLKSRC_Config(RCC_SYSCLKSRC_HSI);  //选择SYSCLK时钟源  48MHz
	RCC_HCLKPRS_Config(RCC_HCLK_DIV1);  //配置SYSTICK到HCLK分频系数  48MHz
	RCC_PCLKPRS_Config(RCC_PCLK_DIV8); //配置HCLK 到 PCLK的分频系数  6MHz
}


void Key_Scan(void)
{
  if(GPIO_ReadPin(CW_GPIOB,GPIO_PIN_2) == GPIO_Pin_RESET)  //检测PB2是否为低电平
    {
          Flag_Key = 1;
    }
  if(Flag_Key)     //接着判断标志位
    {
      if(GPIO_ReadPin(CW_GPIOB,GPIO_PIN_2) == GPIO_Pin_SET)    //如果按键已经松开
        {
          Flag_Key = 0;   //清零标志位，等待下一次按键检测
          if(Flag_LED == 0) Flag_LED = 1; //按键按下该变LED显示标志位的值，由显示标志位控制LED   
          else Flag_LED = 0;
        }
    }
}

void LED_Lighting(void)
{
  if(Flag_LED == 1)
        {
          GPIO_WritePin(CW_GPIOC,GPIO_PIN_0,GPIO_Pin_RESET);        //亮
        }
        else 
        {
          GPIO_WritePin(CW_GPIOC,GPIO_PIN_0,GPIO_Pin_SET);       //灭
        }
}
