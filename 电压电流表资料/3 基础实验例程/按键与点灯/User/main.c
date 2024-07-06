#include "main.h"
#include "GPIO.h"
#include "Segment_Display.h"

uint8_t Flag_Seg;        //数码管显示标志位

void RCC_Configuration()
{
	FLASH_SetLatency(FLASH_Latency_2); // 设置主频为48MHZ需要注意，Flah的访问周期需要更改为FLASH_Latency_2。
  RCC_HSI_Enable(RCC_HSIOSC_DIV1);   // 设置频率为48M
	RCC_SYSCLKSRC_Config(RCC_SYSCLKSRC_HSI);  //选择SYSCLK时钟源  48MHz
	RCC_HCLKPRS_Config(RCC_HCLK_DIV1);  //配置SYSTICK到HCLK分频系数  48MHz
}

int main()
{
  RCC_Configuration();
	GPIO_init();
	Seg_Init();
	
	while(1)
	{
	  Key_Scan();                   //按键扫描
		Seg_LED();                    //数码管显示
	}
}
