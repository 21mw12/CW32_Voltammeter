#include "main.h"

extern uint16_t Volt_Buffer;
uint16_t Cal_Buffer;   //计算电压时的中间变量

int main()
{
  RCC_Configuration();
	Seg_Init();
	Btim1_Init();
	ADC_init();
	
	while(1)
    {
				Volt_Cal();
        Display(Cal_Buffer); 
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

void Volt_Cal(void)
{
	Cal_Buffer = Volt_Buffer;
  Cal_Buffer = (Cal_Buffer * ADC_REF_VALUE >> 12) * (R2 + R1)/R1;
	// 四舍五入
    if(Cal_Buffer % 10 >= 5)
    {
        Cal_Buffer = Cal_Buffer / 10 + 1;
    }
    else
    {
        Cal_Buffer = Cal_Buffer / 10;
    }
}	

