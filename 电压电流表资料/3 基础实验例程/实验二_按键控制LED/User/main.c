#include "main.h"
#include "gpio.h"

uint8_t Flag_LED;

int main()
{
  RCC_Configuration();
  Gpio_Init();
	LED_Init();
	
	while(1)
	{
		Key_Scan();
    LED_Lighting();
	}
}

void RCC_Configuration(void)
{
  RCC_HSI_Enable(RCC_HSIOSC_DIV6);
/* 1. 设置HCLK和PCLK的分频系数　*/
  RCC_HCLKPRS_Config(RCC_HCLK_DIV1);
  RCC_PCLKPRS_Config(RCC_PCLK_DIV1);
/* 2. 使能PLL，通过HSI倍频到64MHz */
  RCC_PLL_Enable(RCC_PLLSOURCE_HSI, 8000000, 8);     
///< 当使用的时钟源HCLK大于24M,小于等于48MHz：设置FLASH 读等待周期为2 cycle
///< 当使用的时钟源HCLK大于48M,小于等于72MHz：设置FLASH 读等待周期为3 cycle    
  __RCC_FLASH_CLK_ENABLE();
  FLASH_SetLatency(FLASH_Latency_3);
/* 3. 时钟切换到PLL */
  RCC_SysClk_Switch(RCC_SYSCLKSRC_PLL);
  RCC_SystemCoreClockUpdate(64000000);
}

void LED_Init(void)
{
  GPIO_WritePin(CW_GPIOC,GPIO_PIN_13,GPIO_Pin_SET);  //初始化让LED灯处于熄灭状态
}

void LED_Lighting(void)
{
  if(Flag_LED == 1)
    {
      GPIO_WritePin(CW_GPIOC,GPIO_PIN_13,GPIO_Pin_RESET);        //亮
    }
  else 
    {
      GPIO_WritePin(CW_GPIOC,GPIO_PIN_13,GPIO_Pin_SET);       //灭
    }
}
