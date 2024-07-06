#include "main.h"
#include "GPIO.h"
#include "Segment_Display.h"

uint8_t Flag_Seg;        //�������ʾ��־λ

void RCC_Configuration()
{
	FLASH_SetLatency(FLASH_Latency_2); // ������ƵΪ48MHZ��Ҫע�⣬Flah�ķ���������Ҫ����ΪFLASH_Latency_2��
  RCC_HSI_Enable(RCC_HSIOSC_DIV1);   // ����Ƶ��Ϊ48M
	RCC_SYSCLKSRC_Config(RCC_SYSCLKSRC_HSI);  //ѡ��SYSCLKʱ��Դ  48MHz
	RCC_HCLKPRS_Config(RCC_HCLK_DIV1);  //����SYSTICK��HCLK��Ƶϵ��  48MHz
}

int main()
{
  RCC_Configuration();
	GPIO_init();
	Seg_Init();
	
	while(1)
	{
	  Key_Scan();                   //����ɨ��
		Seg_LED();                    //�������ʾ
	}
}
