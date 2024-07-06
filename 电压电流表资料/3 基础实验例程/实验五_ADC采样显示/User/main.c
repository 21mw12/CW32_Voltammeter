#include "main.h"

extern uint16_t Volt_Buffer;
uint16_t Cal_Buffer;   //�����ѹʱ���м����

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
  FLASH_SetLatency(FLASH_Latency_2); // ������ƵΪ48MHZ��Ҫע�⣬Flah�ķ���������Ҫ����ΪFLASH_Latency_2��
  RCC_HSI_Enable(RCC_HSIOSC_DIV1);   // ����Ƶ��Ϊ48M
	RCC_SYSCLKSRC_Config(RCC_SYSCLKSRC_HSI);  //ѡ��SYSCLKʱ��Դ  48MHz
	RCC_HCLKPRS_Config(RCC_HCLK_DIV1);  //����SYSTICK��HCLK��Ƶϵ��  48MHz
	RCC_PCLKPRS_Config(RCC_PCLK_DIV8); //����HCLK �� PCLK�ķ�Ƶϵ��  6MHz
}

void Volt_Cal(void)
{
	Cal_Buffer = Volt_Buffer;
  Cal_Buffer = (Cal_Buffer * ADC_REF_VALUE >> 12) * (R2 + R1)/R1;
	// ��������
    if(Cal_Buffer % 10 >= 5)
    {
        Cal_Buffer = Cal_Buffer / 10 + 1;
    }
    else
    {
        Cal_Buffer = Cal_Buffer / 10;
    }
}	

