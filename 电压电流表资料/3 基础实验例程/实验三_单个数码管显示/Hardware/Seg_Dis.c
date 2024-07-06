#include "Seg_Dis.h"

/*  共阴数码管编码表：
 0x3f   0x06   0x5b   0x4f  0x66  0x6d
   0      1     2      3     4     5
 0x7d  0x07   0x7f    0x6f  0x77  0x7c
   6    7      8       9     A     B
 0x39  0x5e   0x79    0x71
   C    D       E      F      */
uint8_t Seg_Table[16]     = {0x3f, 0x06, 0x5b, 0x4f, 0x66, 0x6d, 0x7d, 0x07,
                             0x7f, 0x6f, 0x77, 0x7c, 0x39, 0x5e, 0x79, 0x71};

void Seg_Init(void)
{
	__RCC_GPIOA_CLK_ENABLE();//打开GPIOA的时钟
	__RCC_GPIOB_CLK_ENABLE();//打开GPIOB的时钟
  __RCC_GPIOC_CLK_ENABLE();//打开GPIOC的时钟
	
	GPIO_InitTypeDef GPIO_InitStruct; 
		
	GPIO_InitStruct.Pins = GPIO_PIN_0 | GPIO_PIN_4; //PA00,E;PA04,G
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.IT = GPIO_IT_NONE;
	GPIO_InitStruct.Speed = GPIO_SPEED_HIGH;
  GPIO_Init(CW_GPIOA, &GPIO_InitStruct);
	
	GPIO_InitStruct.Pins = GPIO_PIN_6 | GPIO_PIN_4 | GPIO_PIN_2 | GPIO_PIN_0 | GPIO_PIN_3 | GPIO_PIN_7; //PB06,B;PB04,C;PB02,D;PB00,F;PB03,DP  //PB07，COM1
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
	  case 1:
      GPIO_WritePin(CW_GPIOB,GPIO_PIN_7,GPIO_Pin_RESET);  //PB07,COM1
		  GPIO_WritePin(CW_GPIOC,GPIO_PIN_3,GPIO_Pin_SET);    //PC03,COM2
		  GPIO_WritePin(CW_GPIOC,GPIO_PIN_2,GPIO_Pin_SET);    //PC02,COM3
      break;
    case 2:
      GPIO_WritePin(CW_GPIOB,GPIO_PIN_7,GPIO_Pin_SET);    //PB07,COM1
		  GPIO_WritePin(CW_GPIOC,GPIO_PIN_3,GPIO_Pin_RESET);  //PC03,COM2
		  GPIO_WritePin(CW_GPIOC,GPIO_PIN_2,GPIO_Pin_SET);    //PC02,COM3
      break;
    case 3:
      GPIO_WritePin(CW_GPIOB,GPIO_PIN_7,GPIO_Pin_SET);    //PB07,COM1
		  GPIO_WritePin(CW_GPIOC,GPIO_PIN_3,GPIO_Pin_SET);    //PC03,COM2
		  GPIO_WritePin(CW_GPIOC,GPIO_PIN_2,GPIO_Pin_RESET);  //PC02,COM3
      break;
		default:
      break;
	}
}
