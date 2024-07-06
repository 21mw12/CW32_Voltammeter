#include "main.h"

uint8_t Flag_Key;         //������־λ
uint8_t Flag_LED;         //LED��ʾ��־λ

int main()
{
  RCC_Configuration();
	gpio_init();
	GPIO_WritePin(CW_GPIOC,GPIO_PIN_0,GPIO_Pin_SET);  //��ʼ����LED�ƴ���Ϩ��״̬
	
	while(1)
    {
      Key_Scan();
			LED_Lighting();
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


void Key_Scan(void)
{
  if(GPIO_ReadPin(CW_GPIOB,GPIO_PIN_2) == GPIO_Pin_RESET)  //���PB2�Ƿ�Ϊ�͵�ƽ
    {
          Flag_Key = 1;
    }
  if(Flag_Key)     //�����жϱ�־λ
    {
      if(GPIO_ReadPin(CW_GPIOB,GPIO_PIN_2) == GPIO_Pin_SET)    //��������Ѿ��ɿ�
        {
          Flag_Key = 0;   //�����־λ���ȴ���һ�ΰ������
          if(Flag_LED == 0) Flag_LED = 1; //�������¸ñ�LED��ʾ��־λ��ֵ������ʾ��־λ����LED   
          else Flag_LED = 0;
        }
    }
}

void LED_Lighting(void)
{
  if(Flag_LED == 1)
        {
          GPIO_WritePin(CW_GPIOC,GPIO_PIN_0,GPIO_Pin_RESET);        //��
        }
        else 
        {
          GPIO_WritePin(CW_GPIOC,GPIO_PIN_0,GPIO_Pin_SET);       //��
        }
}
