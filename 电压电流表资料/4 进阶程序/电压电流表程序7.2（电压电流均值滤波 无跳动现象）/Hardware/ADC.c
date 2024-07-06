#include "ADC.h"

uint16_t Volt_Buffer[ADC_SAMPLE_SIZE];
uint16_t Curr_Buffer[ADC_SAMPLE_SIZE];

void ADC_init(void)
{
    ADC_InitTypeDef     ADC_InitStructure;         //ADC���ýṹ��
    ADC_SerialChTypeDef ADC_SerialChStructure;     //ADC����ͨ���ṹ��
    GPIO_InitTypeDef    GPIO_Init_Struct;
	
    __RCC_GPIOB_CLK_ENABLE(); //��ADC��Ӧ����ʱ��   
    __RCC_ADC_CLK_ENABLE();   // ��ADCʱ��
	
    GPIO_Init_Struct.IT   = GPIO_IT_NONE;
    GPIO_Init_Struct.Mode = GPIO_MODE_ANALOG;//��GPIO��ģʽ���ó�ģ�⹦��
    GPIO_Init_Struct.Pins = GPIO_PIN_1;      // PB01�ǵ�ѹ�ɼ�����
    GPIO_Init(CW_GPIOB, &GPIO_Init_Struct);
    PB01_ANALOG_ENABLE();                    //ʹ��ģ������
		PB05_ANALOG_ENABLE(); 
	
    ADC_StructInit(&ADC_InitStructure);      // ADCĬ��ֵ��ʼ��
    ADC_InitStructure.ADC_ClkDiv     = ADC_Clk_Div128; //ADC����ʱ������ PCLK/4 = 6/4 = 1.5Mhz
	
/*�źŵ�ѹ�ϵ�ʱ�����Խ��Ͳο���ѹ����߷ֱ��ʡ� �ı�ο���ѹ��ͬ�������Ʊ�ʾ�ĵ�ѹֵ�ͻ᲻һ����
  ���Ķ����ƣ�ȫ1����ʾ�ľ�����Ĳο���ѹ���ڼ���ʵ�ʵ�ѹʱ������Ҫ���ο���ѹ���ǽ�ȥ��*/
    ADC_InitStructure.ADC_VrefSel    = ADC_Vref_BGR1p5;     //�ο���ѹ����Ϊ1.5V
    ADC_InitStructure.ADC_SampleTime = ADC_SampTime10Clk;   //���ڵ�ѹ�ź�Ϊ�����źţ�ADC����ʱ��Ϊʮ��ADC����������ȷ��׼ȷ

   	ADC_SerialChStructure.ADC_Sqr0Chmux  = ADC_SqrCh9;      //����ADC���У�PB01��ADC�ĵ�9ͨ��
    ADC_SerialChStructure.ADC_Sqr1Chmux  = ADC_SqrCh11;
    ADC_SerialChStructure.ADC_SqrEns     = ADC_SqrEns01;
    ADC_SerialChStructure.ADC_InitStruct = ADC_InitStructure; //ADC��ʼ��
		
    ADC_SerialChContinuousModeCfg(&ADC_SerialChStructure);   //ADC��������ת��ģʽ����
    ADC_ClearITPendingAll();           //���ADC�����ж�״̬
    ADC_Enable();                      // ADCʹ��
    ADC_SoftwareStartConvCmd(ENABLE);  //ADCת�������������
}

void Get_ADC_Value(void)
{
	static uint8_t cnt;
  ADC_GetSqr0Result(&Volt_Buffer[cnt]);
  ADC_GetSqr1Result(&Curr_Buffer[cnt]);	
	
	cnt++;
	if(cnt >= ADC_SAMPLE_SIZE)
    {
        cnt = 0;
    }
}
