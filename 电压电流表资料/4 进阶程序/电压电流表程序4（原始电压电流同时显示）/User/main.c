#include "main.h"
#include "log.h"

extern uint16_t Volt_Buffer[ADC_SAMPLE_SIZE];
uint16_t V_Buffer,I_Buffer;

unsigned int spp_start=0;
uint32_t ble_time=0;

unsigned int timecount=0;

uint16_t sampledata=0;

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
				DisplayI(I_Buffer);
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

void Volt_Cal(void)
{ 
	ADC_GetSqr0Result(&sampledata);  ///当前采集值显示出来	
	
//	ADC_GetSqr0Result(&V_Buffer);  ///当前采集值显示出来
  V_Buffer = (sampledata * ADC_REF_VALUE >> 12) * (R2 + R1)/R1;
	// 四舍五入
    if(V_Buffer % 10 >= 5)
    {
        V_Buffer = V_Buffer / 10 + 1;
    }
    else
    {
        V_Buffer = V_Buffer / 10;
    }
		
		
	  ADC_GetSqr1Result(&I_Buffer);  ///当前采集值显示出来
		I_Buffer=I_Buffer * ADC_REF_VALUE >> 12;
		 /**
        mv =I_Buffer * ADC_REF_VALUE >> 12,
        R = 100mr,
        10ma = mv/R/10=mv/0.1/10 = mv
     */	
}	

