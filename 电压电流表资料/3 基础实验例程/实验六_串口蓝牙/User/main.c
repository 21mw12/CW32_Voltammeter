#include "main.h"

extern uint16_t Volt_Buffer;
uint16_t Cal_Buffer;
uint32_t Ble_Time=0;

int main()
{
  RCC_Configuration();
	//Seg_Init();
	Btim1_Init();
	ADC_init();
	Uart2_Init();
	char data_reg[24];
	
	while(1)
    {
			if(GetTick() >= (Ble_Time + 1000))
        {
					Ble_Time = GetTick();
			    Volt_Cal();                                  //��ѹ����
			    sprintf(data_reg,"volt=%u\r\n",Cal_Buffer);  //��ӡ����
			    USART_SendString(CW_UART2,data_reg);         // 1000ms�ϴ�һ�����ݸ�����
				}
     // Display(Cal_Buffer); 
    }
}

void RCC_Configuration(void)
{
  FLASH_SetLatency(FLASH_Latency_2); // ������ƵΪ48MHZ��Ҫע�⣬Flah�ķ���������Ҫ����ΪFLASH_Latency_2��
  RCC_HSI_Enable(RCC_HSIOSC_DIV1);   // ����Ƶ��Ϊ48M
	RCC_SYSCLKSRC_Config(RCC_SYSCLKSRC_HSI);  //ѡ��SYSCLKʱ��Դ  48MHz
	RCC_HCLKPRS_Config(RCC_HCLK_DIV1);  //����SYSTICK��HCLK��Ƶϵ��  48MHz
	RCC_PCLKPRS_Config(RCC_PCLK_DIV8); //����HCLK �� PCLK�ķ�Ƶϵ��  6MHz
  InitTick(48000000);                // SYSTICK �Ĺ���Ƶ��Ϊ48MHz��ÿms�ж�һ��
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

