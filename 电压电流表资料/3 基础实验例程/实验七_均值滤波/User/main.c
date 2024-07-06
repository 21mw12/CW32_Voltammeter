#include "main.h"

extern uint16_t Volt_Buffer[ADC_SAMPLE_SIZE];
uint16_t Cal_Buffer;
uint32_t Led_Dis_Time;

int main()
{
  RCC_Configuration();
	Seg_Init();
	Btim1_Init();
	ADC_init();
	
	while(1)
    {
			if(GetTick() >= (Led_Dis_Time + 100))     //300ms改变一次数码管显示值
			{
			  Led_Dis_Time = GetTick();
				Volt_Cal();
        Display(Cal_Buffer);
			}
    }
}

void RCC_Configuration(void)
{
  FLASH_SetLatency(FLASH_Latency_2); // 设置主频为48MHZ需要注意，Flah的访问周期需要更改为FLASH_Latency_2。
  RCC_HSI_Enable(RCC_HSIOSC_DIV1);   // 设置频率为48M
	RCC_SYSCLKSRC_Config(RCC_SYSCLKSRC_HSI);  //选择SYSCLK时钟源  48MHz
	RCC_HCLKPRS_Config(RCC_HCLK_DIV1);  //配置SYSTICK到HCLK分频系数  48MHz
	RCC_PCLKPRS_Config(RCC_PCLK_DIV8); //配置HCLK 到 PCLK的分频系数  6MHz
	InitTick(48000000);                // SYSTICK 的工作频率为48MHz，每ms中断一次
}

uint32_t Mean_Value_Filter(uint16_t *value, uint32_t size)     //均值滤波
{
    uint32_t sum = 0;
    uint16_t max = 0;
    uint16_t min = 0xffff;
    int      i;

    for(i = 0; i < size; i++)
    {
        sum += value[i];
        if(value[i] > max)
        {
            max = value[i];
        }
        if(value[i] < min)
        {
            min = value[i];
        }
    }
    sum -= max + min;
    sum  = sum / (size - 2);
		//if(sum>1)sum+=4; 后期校准
    return sum;
}

void Volt_Cal(void)
{
//	Cal_Buffer = Mean_Value_Filter(Volt_Buffer,ADC_SAMPLE_SIZE);; //使用均值滤波
	ADC_GetSqr0Result(&Cal_Buffer);  ///当前采集值显示出来
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

