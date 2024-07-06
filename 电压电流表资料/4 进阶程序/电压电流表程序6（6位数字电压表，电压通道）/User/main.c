#include "main.h"
#include "log.h"

extern uint16_t Volt_Buffer[ADC_SAMPLE_SIZE];
extern uint16_t Curr_Buffer[ADC_SAMPLE_SIZE];
uint32_t V_Buffer,I_Buffer;

unsigned int spp_start=0;
uint32_t ble_time=0;

unsigned int timecount=0;


int main()
{
  RCC_Configuration();
	Seg_Init();
	Btim1_Init();
	ADC_init();
	LogInit();
	ble_time = GetTick();
	
	while(1)
    {
			if(timecount>= 100)     //300ms改变一次数码管显示值//	
			{
				timecount=0;
				Volt_Cal();
        Display(V_Buffer);
			}
			
			if((spp_start == 0) && (GetTick() > ble_time+3000))  //上电延时3S后，开始蓝牙自动上传
        {
            spp_start = 1;
            printf("AT+CR\r\n");//关闭回传信息 
            ble_time = GetTick();
        }
				
				if((spp_start == 1) && (GetTick() >ble_time+1000))  //上电延时3S后，开始蓝牙自动上传
        {
            spp_start = 2;								
            printf("AT+CL01\r\n");//关闭回传信息\r\n");//进入低功耗          
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
	V_Buffer = Mean_Value_Filter(Volt_Buffer,ADC_SAMPLE_SIZE);; //使用均值滤波	
  V_Buffer = (V_Buffer * ADC_REF_VALUE  * (R2 + R1)/R1*10)>> 12;
}	

