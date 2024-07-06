#include "main.h"
#include "log.h"
#include "flash.h"

extern uint16_t Volt_Buffer[ADC_SAMPLE_SIZE];
extern uint16_t Curr_Buffer[ADC_SAMPLE_SIZE];
extern uint8_t Seg_Reg[6];
uint16_t V_Buffer,I_Buffer;

unsigned int spp_start=0;
uint32_t ble_time=0;

unsigned int timecount=0;

//5V��15V У׼
unsigned int X05=0;
unsigned int X15=0;

unsigned int Y15=15;
unsigned int Y05=5;
float K; //б��


//0.5A��1.5A У׼
unsigned int IX05=0;
unsigned int IX15=0;

unsigned int IY15=150;
unsigned int IY05=50;
float KI; //б��

//����ģʽ
unsigned char Mode=0;
//mode0 :��ѹ����������ʾģʽ
//mode1 :��ѹ5VУ׼
//mode2 :��ѹ15VУ׼
//mode3 :����0.5AУ׼
//mode4 :����1.5AУ׼

unsigned char BrushFlag=0;


void KEYGPIO_Init(void)
{
	__RCC_GPIOA_CLK_ENABLE();//��GPIOA��ʱ��	
	GPIO_InitTypeDef GPIO_InitStruct; 
		
	GPIO_InitStruct.Pins = GPIO_PIN_3; //PA03 KEY1
	GPIO_InitStruct.Mode = GPIO_MODE_INPUT_PULLUP;
  GPIO_InitStruct.IT = GPIO_IT_NONE;
	GPIO_InitStruct.Speed = GPIO_SPEED_HIGH;
  GPIO_Init(CW_GPIOA, &GPIO_InitStruct);
}


extern void DisplaySETV(uint32_t value);
void DisplayBuff(void)
{
  if(Mode==0)
  {
		 Display(V_Buffer);
		 DisplayI(I_Buffer);
	}		
	else if(Mode==1) //S.05.
	{
		Seg_Reg[0] =5+10;
		Seg_Reg[1] =0;
		Seg_Reg[2]=5+10;
		DisplaySETV(V_Buffer);
	}
	else if(Mode==2) //S.15.
	{
		Seg_Reg[0] =5+10;
		Seg_Reg[1] =1;
		Seg_Reg[2]=5+10;
		DisplaySETV(V_Buffer);
	}
	else if(Mode==3) //A.0.5
	{
		Seg_Reg[0] =20;
		Seg_Reg[1] =0+10;
		Seg_Reg[2]=5;
		DisplayI(I_Buffer);
	}
	else if(Mode==4) //A.1.5
	{
		Seg_Reg[0] =20;
		Seg_Reg[1] =1+10;
		Seg_Reg[2]=5;
		DisplayI(I_Buffer);
	}
}

void ComputeK(void)
{
	K=(Y15-Y05);
	K=K/(X15-X05);
	
	KI=(IY15-IY05);
	KI=KI/(IX15-IX05);
}

void save_calibration(void)
{
	 uint16_t da[5];
	  da[0]=0xaa;
	  da[1]=X05;
	  da[2]=X15;
	  da[3]=IX05;
	  da[4]=IX15;
    flash_erase();
    flash_write(0,da,5);
}
/**
 * @brief
 *
 */
void read_vol_cur_calibration(void)
{
    uint16_t da[5];
    flash_read(0,da, 5);
	  if(da[0]!=0xaa)//��ûУ׼��ʱ����������ֵ�����洢
		{
			X15=15.0/23/1.5*4096;
			X05=5.0/23/1.5*4096;
			IX05=0.5*0.1/1.5*4096;
			IX15=1.5*0.1/1.5*4096;
      save_calibration();
		}
		else 
		{
			X05=da[1];
			X15=da[2];
			IX05=da[3];
			IX15=da[4];
		}
		
}
int main()
{
	unsigned char key_1=1;
	
  RCC_Configuration();
	KEYGPIO_Init();
	Seg_Init();
	Btim1_Init();
	ADC_init();
	LogInit();
	ble_time = GetTick();
	
	read_vol_cur_calibration();
	ComputeK();
	
	
	while(1)
    {
			if(BrushFlag==1)
			{
				DisplayBuff();
				BrushFlag=0;
			}
			
			if(timecount>= 300)     //300ms�ı�һ���������ʾֵ//	
			{
				timecount=0;
				Volt_Cal();
				BrushFlag=1;
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
	float t,KT1;
	
	V_Buffer = Mean_Value_Filter(Volt_Buffer,ADC_SAMPLE_SIZE);//ʹ�þ�ֵ�˲�
	I_Buffer = Mean_Value_Filter(Curr_Buffer,ADC_SAMPLE_SIZE); //ʹ�þ�ֵ�˲�
	
	if(V_Buffer>=X05)
	{
		t=V_Buffer-X05;
	  V_Buffer=(K*t+Y05)*1000;}
	else
  { 
		KT1=5000;
		KT1=KT1/X05;
		V_Buffer=KT1*V_Buffer;
	}
	// ��������
    if(V_Buffer % 10 >= 5)
    {
        V_Buffer = V_Buffer / 10 + 1;
    }
    else
    {
        V_Buffer = V_Buffer / 10;
    }
		
		
	if(I_Buffer>=IX05)
	{
		 t=I_Buffer-IX05;
	   I_Buffer=(KI*t+IY05)*10;
	}
	else
	{
		KT1=500;
		KT1=KT1/IX05;
		I_Buffer=KT1*I_Buffer;
	}
	
		if(I_Buffer % 10 >= 5)
    {
        I_Buffer = I_Buffer / 10 + 1;
    }
    else
    {
        I_Buffer = I_Buffer / 10;
    }
	//	I_Buffer=I_Buffer * ADC_REF_VALUE >> 12;
		 /**
        mv =I_Buffer * ADC_REF_VALUE >> 12,
        R = 100mr,
        10ma = mv/R/10=mv/0.1/10 = mv
     */	
}	

void BTIM1_IRQHandler(void)
{
  static uint32_t Cnt=0,keytime=0,timecount1=0;
	
  /* USER CODE BEGIN */
  if (BTIM_GetITStatus(CW_BTIM1, BTIM_IT_OV))
  {
    BTIM_ClearITPendingBit(CW_BTIM1, BTIM_IT_OV);
    Get_ADC_Value();
		
		timecount++;
    Dis_Refresh();//�����ɨ����ʾ
		
		 //PA3
		if(GPIO_ReadPin(CW_GPIOA,GPIO_PIN_3)==GPIO_Pin_RESET)
       {
			    keytime++;timecount1=0;
				 
					 if(keytime>=3000&&Mode!=0) // ����3S ��ģʽ��Ϊ0
					 {
						 //У׼
						 if(Mode==1)
						 {
							 X05=Mean_Value_Filter(Volt_Buffer,ADC_SAMPLE_SIZE);
							 save_calibration();ComputeK();Volt_Cal();BrushFlag=1;Mode=0;
						 }
						 if(Mode==2)
						 {
							 X15=Mean_Value_Filter(Volt_Buffer,ADC_SAMPLE_SIZE);
							 save_calibration();ComputeK();Volt_Cal();BrushFlag=1;Mode=0;
						 }
						 if(Mode==3)
						 {
							 IX05=Mean_Value_Filter(Curr_Buffer,ADC_SAMPLE_SIZE);
							 save_calibration();ComputeK();Volt_Cal();BrushFlag=1;Mode=0;
						 }
						 if(Mode==4)
						 {
							 IX15=Mean_Value_Filter(Curr_Buffer,ADC_SAMPLE_SIZE);
							 save_calibration();ComputeK();Volt_Cal();BrushFlag=1;Mode=0;
						 }						 
					 }
			 }
		else 
		{
			 if(keytime>=60&&keytime<1000)
			 {
				  Mode++;
					if(Mode>=5)Mode=0;
				  BrushFlag=1; //���������
			 }
			 
			 keytime=0;
			 
			 if(Mode!=0) //15S������ ����MODE0
			 {
			   timecount1++;
				 if(timecount1>=15000)
				 {
					 Mode=0;timecount1=0;
				 }
			 }
		}		
  }
  /* USER CODE END */
}
