#include "main.h"
#include "Seg_Dis.h"
#include "BTIM1.h"

int main()
{
  RCC_Configuration();
	Seg_Init();
	Btim1_Init();
	Display(648);
	while(1)
    {
        
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
