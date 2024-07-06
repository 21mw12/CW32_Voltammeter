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
			if(GetTick() >= (Led_Dis_Time + 100))     //300ms�ı�һ���������ʾֵ
			{
			  Led_Dis_Time = GetTick();
				Volt_Cal();
        Display(Cal_Buffer);
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
//	Cal_Buffer = Mean_Value_Filter(Volt_Buffer,ADC_SAMPLE_SIZE);; //ʹ�þ�ֵ�˲�
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

