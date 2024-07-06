#include "gpio.h"

uint8_t Flag_Key;         //������־λ
extern uint8_t Flag_LED;  //LED��ʾ��־λ

void Gpio_Init(void)
{
	__RCC_GPIOC_CLK_ENABLE();//��GPIOC��ʱ��
	GPIO_InitTypeDef GPIO_InitStruct;
	GPIO_InitStruct.Pins = GPIO_PIN_13;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.IT = GPIO_IT_NONE;
	GPIO_InitStruct.Speed = GPIO_SPEED_HIGH;
  GPIO_Init(CW_GPIOC, &GPIO_InitStruct);
	
	__RCC_GPIOB_CLK_ENABLE();//��GPIOB��ʱ��
	GPIO_InitStruct.Pins = GPIO_PIN_2;
	GPIO_InitStruct.Mode = GPIO_MODE_INPUT_PULLDOWN;
  GPIO_InitStruct.IT = GPIO_IT_NONE;
  GPIO_Init(CW_GPIOB, &GPIO_InitStruct);
}

void Key_Scan(void)
{
  if(GPIO_ReadPin(CW_GPIOB,GPIO_PIN_2) == GPIO_Pin_SET)  //���PB2�Ƿ�Ϊ�ߵ�ƽ
    {
          Flag_Key = 1;
    }
  if(Flag_Key)                                           //�����жϱ�־λ
    {
      if(GPIO_ReadPin(CW_GPIOB,GPIO_PIN_2) == GPIO_Pin_RESET)    //��������Ѿ��ɿ�
        {
          Flag_Key = 0;   //�����־λ���ȴ���һ�ΰ������
          if(Flag_LED == 0) Flag_LED = 1; //�������¸ñ�LED��ʾ��־λ��ֵ������ʾ��־λ����LED   
          else Flag_LED = 0;
        }
    }
}
