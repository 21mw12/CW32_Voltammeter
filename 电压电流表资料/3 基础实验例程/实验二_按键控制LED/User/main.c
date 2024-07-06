#include "main.h"
#include "gpio.h"

uint8_t Flag_LED;

int main()
{
  RCC_Configuration();
  Gpio_Init();
	LED_Init();
	
	while(1)
	{
		Key_Scan();
    LED_Lighting();
	}
}

void RCC_Configuration(void)
{
  RCC_HSI_Enable(RCC_HSIOSC_DIV6);
/* 1. ����HCLK��PCLK�ķ�Ƶϵ����*/
  RCC_HCLKPRS_Config(RCC_HCLK_DIV1);
  RCC_PCLKPRS_Config(RCC_PCLK_DIV1);
/* 2. ʹ��PLL��ͨ��HSI��Ƶ��64MHz */
  RCC_PLL_Enable(RCC_PLLSOURCE_HSI, 8000000, 8);     
///< ��ʹ�õ�ʱ��ԴHCLK����24M,С�ڵ���48MHz������FLASH ���ȴ�����Ϊ2 cycle
///< ��ʹ�õ�ʱ��ԴHCLK����48M,С�ڵ���72MHz������FLASH ���ȴ�����Ϊ3 cycle    
  __RCC_FLASH_CLK_ENABLE();
  FLASH_SetLatency(FLASH_Latency_3);
/* 3. ʱ���л���PLL */
  RCC_SysClk_Switch(RCC_SYSCLKSRC_PLL);
  RCC_SystemCoreClockUpdate(64000000);
}

void LED_Init(void)
{
  GPIO_WritePin(CW_GPIOC,GPIO_PIN_13,GPIO_Pin_SET);  //��ʼ����LED�ƴ���Ϩ��״̬
}

void LED_Lighting(void)
{
  if(Flag_LED == 1)
    {
      GPIO_WritePin(CW_GPIOC,GPIO_PIN_13,GPIO_Pin_RESET);        //��
    }
  else 
    {
      GPIO_WritePin(CW_GPIOC,GPIO_PIN_13,GPIO_Pin_SET);       //��
    }
}
