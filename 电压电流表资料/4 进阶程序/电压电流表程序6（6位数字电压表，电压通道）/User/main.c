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
			if(timecount>= 100)     //300ms�ı�һ���������ʾֵ//	
			{
				timecount=0;
				Volt_Cal();
        Display(V_Buffer);
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

uint32_t Mean_Value_Filter(uint16_t *value, uint32_t size)     //��ֵ�˲�
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
		//if(sum>1)sum+=4; ����У׼
    return sum;
}

void Volt_Cal(void)
{ 	
	V_Buffer = Mean_Value_Filter(Volt_Buffer,ADC_SAMPLE_SIZE);; //ʹ�þ�ֵ�˲�	
  V_Buffer = (V_Buffer * ADC_REF_VALUE  * (R2 + R1)/R1*10)>> 12;
}	

