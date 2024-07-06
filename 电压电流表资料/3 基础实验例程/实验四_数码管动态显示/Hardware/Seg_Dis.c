#include "Seg_Dis.h"

/*  ��������ܱ����
 0x3f   0x06   0x5b   0x4f  0x66  0x6d
   0      1     2      3     4     5
 0x7d  0x07   0x7f    0x6f  0x77  0x7c
   6    7      8       9     A     B
 0x39  0x5e   0x79    0x71
   C    D       E      F      */
uint8_t Seg_Table[16] = {0x3f, 0x06, 0x5b, 0x4f, 0x66, 0x6d, 0x7d, 0x07,
                         0x7f, 0x6f, 0x77, 0x7c, 0x39, 0x5e, 0x79, 0x71};
uint8_t Seg_Reg[3] = {0,0,0};

void Seg_Init(void)
{
	__RCC_GPIOA_CLK_ENABLE();//��GPIOA��ʱ��
	__RCC_GPIOB_CLK_ENABLE();//��GPIOB��ʱ��
  __RCC_GPIOC_CLK_ENABLE();//��GPIOC��ʱ��
	
	GPIO_InitTypeDef GPIO_InitStruct; 
		
	GPIO_InitStruct.Pins = GPIO_PIN_0 | GPIO_PIN_4; //PA00,E;PA04,G
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.IT = GPIO_IT_NONE;
	GPIO_InitStruct.Speed = GPIO_SPEED_HIGH;
  GPIO_Init(CW_GPIOA, &GPIO_InitStruct);
	
	GPIO_InitStruct.Pins = GPIO_PIN_6 | GPIO_PIN_4 | GPIO_PIN_2 | GPIO_PIN_0 | GPIO_PIN_3 | GPIO_PIN_7; //PB06,B;PB04,C;PB02,D;PB00,F;PB03,DP  //PB07��COM1
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.IT = GPIO_IT_NONE;
	GPIO_InitStruct.Speed = GPIO_SPEED_HIGH;
  GPIO_Init(CW_GPIOB, &GPIO_InitStruct);
	
	GPIO_InitStruct.Pins = GPIO_PIN_4 | GPIO_PIN_3 | GPIO_PIN_2; //PC04,A; //PC03,COM2;PC02,COM3
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.IT = GPIO_IT_NONE;
	GPIO_InitStruct.Speed = GPIO_SPEED_HIGH;
  GPIO_Init(CW_GPIOC, &GPIO_InitStruct);
}

void Seg_Dis(uint8_t Pos,uint8_t Num)
{
	int i;
	uint8_t Dis_Value;
	Dis_Value = Seg_Table[Num];
	
	for(i = 0; i < 8; i++)
	{
      switch(i)
        {
          case 0:
              GPIO_WritePin(CW_GPIOC,GPIO_PIN_4,(Dis_Value >> i) & 0x01);    //PC04,A
              break;
          case 1:
              GPIO_WritePin(CW_GPIOB,GPIO_PIN_6,(Dis_Value >> i) & 0x01);    //PB06,B
              break;
          case 2:
              GPIO_WritePin(CW_GPIOB,GPIO_PIN_4,(Dis_Value >> i) & 0x01);    //PB04,C
              break;
          case 3:
              GPIO_WritePin(CW_GPIOB,GPIO_PIN_2,(Dis_Value >> i) & 0x01);    //PB02,D
              break;
          case 4:
              GPIO_WritePin(CW_GPIOA,GPIO_PIN_0,(Dis_Value >> i) & 0x01);    //PA00,E
              break;
          case 5:
              GPIO_WritePin(CW_GPIOB,GPIO_PIN_0,(Dis_Value >> i) & 0x01);    //PB00,F
              break;
          case 6:
              GPIO_WritePin(CW_GPIOA,GPIO_PIN_4,(Dis_Value >> i) & 0x01);    //PA04,G
              break;
          case 7:
              GPIO_WritePin(CW_GPIOB,GPIO_PIN_3,(Dis_Value >> i) & 0x01);    //PB03,DP
              break;
          default:
              break;
				}
	}
	
	switch(Pos)
	{
	  case 0:
      GPIO_WritePin(CW_GPIOB,GPIO_PIN_7,GPIO_Pin_RESET);  //PB07,COM1
		  GPIO_WritePin(CW_GPIOC,GPIO_PIN_3,GPIO_Pin_SET);    //PC03,COM2
		  GPIO_WritePin(CW_GPIOC,GPIO_PIN_2,GPIO_Pin_SET);    //PC02,COM3
      break;
    case 1:
      GPIO_WritePin(CW_GPIOB,GPIO_PIN_7,GPIO_Pin_SET);    //PB07,COM1
		  GPIO_WritePin(CW_GPIOC,GPIO_PIN_3,GPIO_Pin_RESET);  //PC03,COM2
		  GPIO_WritePin(CW_GPIOC,GPIO_PIN_2,GPIO_Pin_SET);    //PC02,COM3
      break;
    case 2:
      GPIO_WritePin(CW_GPIOB,GPIO_PIN_7,GPIO_Pin_SET);    //PB07,COM1
		  GPIO_WritePin(CW_GPIOC,GPIO_PIN_3,GPIO_Pin_SET);    //PC03,COM2
		  GPIO_WritePin(CW_GPIOC,GPIO_PIN_2,GPIO_Pin_RESET);  //PC02,COM3
      break;
		default:
      break;
	}
}

/**
 * @brief �ر����й�����
 * 
 */
void Close_Com(void)
{
  GPIO_WritePin(CW_GPIOB,GPIO_PIN_7,GPIO_Pin_SET);    //PB07,COM1
	GPIO_WritePin(CW_GPIOC,GPIO_PIN_3,GPIO_Pin_SET);    //PC03,COM2
	GPIO_WritePin(CW_GPIOC,GPIO_PIN_2,GPIO_Pin_SET);    //PC02,COM3
}

void Display(uint32_t value)
{
  uint8_t Hundreds;
  uint8_t Tens;
  uint8_t Units; // ��λ��
	
	Units     = value % 10;
	Tens      = value / 10 % 10;
  Hundreds  = value / 100 % 10;
	
	Seg_Reg[0] = Hundreds;
	Seg_Reg[1] = Tens;
	Seg_Reg[2] = Units;
}

/**
 * @brief �����ɨ����ʾ����,��ʱ�������Ե���
 *
 */
void Dis_Refresh(void)
{
  static uint8_t num = 0;

	Close_Com();//�ȹرչ�����,��ֹ��Ӱ
	Seg_Dis(num,Seg_Reg[num]);
	num++;
  if(num > 2)
  {
    num = 0;
  }
}
