#include "main.h"
#include "log.h"

extern uint16_t Volt_Buffer[ADC_SAMPLE_SIZE];
uint16_t Cal_Buffer;

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
			if(timecount>= 100)     //300ms�ı�һ���������ʾֵ//	
			{
				timecount=0;
				Volt_Cal();
        Display(Cal_Buffer);
			}
			
			if((spp_start == 0) && (GetTick() > ble_time+3000))  //�ϵ���ʱ3S�󣬿�ʼ�����Զ��ϴ�
        {
            spp_start = 1;
            printf("AT+CR\r\n");//�رջش���Ϣ 
            ble_time = GetTick();
        }
				
				if((spp_start == 1) && (GetTick() >ble_time+1000))  //�ϵ���ʱ3S�󣬿�ʼ�����Զ��ϴ�
        {
            spp_start = 2;								
            printf("AT+CL01\r\n");//�رջش���Ϣ\r\n");//����͹���          
        }
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
	ADC_GetSqr0Result(&Cal_Buffer);  ///��ǰ�ɼ�ֵ��ʾ����
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

