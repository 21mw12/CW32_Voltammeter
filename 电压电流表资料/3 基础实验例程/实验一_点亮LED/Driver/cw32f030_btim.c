/**
 * @file cw32f030_btim.c
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2021-04-22
 * 
 * @copyright Copyright (c) 2021
 * 
 */

/*******************************************************************************
*
* ������ɺ�������Ϣ
* �人��Դ�뵼�����޹�˾������ʹ�����б�̴���ʾ���ķ�ר���İ�Ȩ��ɣ��������ɴ�
* ���ɸ��������ض���Ҫ�����Ƶ����ƹ��ܡ����ݲ��ܱ��ų����κη�����֤���人��Դ��
* �������޹�˾������򿪷��̺͹�Ӧ�̶Գ������֧�֣�����У����ṩ�κ���ʾ��
* ���ı�֤�������������������ڰ������й������ԡ�������ĳ���ض���;�ͷ���Ȩ�ı�֤
* ��������
* ���ۺ������Σ��人��Դ�뵼�����޹�˾������򿪷��̻�Ӧ�̾��������и����
* ��ʹ����֪�䷢���Ŀ�����ʱ��Ҳ����ˣ����ݵĶ�ʧ���𻵣�ֱ�ӵġ��ر�ġ�������
* ���ӵ��𺦣����κκ���Ծ����𺦣�������ҵ�����롢������Ԥ�ڿɽ�ʡ����
* ��ʧ��
* ĳЩ˾��Ͻ���������ֱ�ӵġ������Ļ����Ե������κε��ų������ƣ����ĳЩ��
* ȫ�������ų������ƿ��ܲ�������������
*
*******************************************************************************/

/* Includes ------------------------------------------------------------------*/
#include "cw32f030_btim.h"

/* Private_TypesDefinitions --------------------------------------------------*/

/* Private_Defines -----------------------------------------------------------*/

/* Private_Variables ---------------------------------------------------------*/

/* Private_FunctionPrototypes ------------------------------------------------*/

/* Private_Functions ---------------------------------------------------------*/

/* Public_Functions ----------------------------------------------------------*/

/*******************************************************************************
// ˵����ȥ��ʼ��
// ������BTIMx xΪ1~3
// ����ֵ����
*******************************************************************************/

void BTIM_DeInit(BTIM_TypeDef* BTIMx)
{
  assert_param(IS_BTIM_ALL_PERIPH(BTIMx));
  
  BTIMx->BCR = 0UL;
  BTIMx->ARR = 0x0000FFFF;
  BTIMx->CNT = 0UL;
  BTIMx->ACR = 0UL;
  BTIMx->IER = 0UL;
  BTIMx->ICR = 0UL;
  BTIMx->DMA = 0UL;  
}

/*******************************************************************************
// ˵����BTIM������ʱ����ʼ��
// ������BTIMx CW_BTIM1~3
// ������BTIM_TimeBaseInitStruct ָ��BTIM_TimeBaseInitTypeDef���ͽṹ���ָ��
// ����ֵ����
*******************************************************************************/
void BTIM_TimeBaseInit(BTIM_TypeDef* BTIMx, BTIM_TimeBaseInitTypeDef* BTIM_TimeBaseInitStruct)
{ 
  assert_param(IS_BTIM_ALL_PERIPH(BTIMx));
  assert_param(IS_BTIM_MODE(BTIM_TimeBaseInitStruct->BTIM_Mode));
  assert_param(IS_BTIM_PRS_DIV(BTIM_TimeBaseInitStruct->BTIM_Prescaler));
  REGBITS_MODIFY(BTIMx->BCR, BTIMx_BCR_MODE_Msk| BTIMx_BCR_PRS_Msk | BTIMx_BCR_ONESHOT_Msk,
                 BTIM_TimeBaseInitStruct->BTIM_Mode | BTIM_TimeBaseInitStruct->BTIM_Prescaler |
                 BTIM_TimeBaseInitStruct->BTIM_OPMode);
  BTIMx->ARR = BTIM_TimeBaseInitStruct->BTIM_Period;  
}

/*******************************************************************************
// ˵�����ṹ������BTIM_TimeBaseInitStruct��ʼ��
// ������BTIM_TimeBaseInitStruct
// ����ֵ����
*******************************************************************************/

void BTIM_TimeBaseStructInit(BTIM_TimeBaseInitTypeDef* BTIM_TimeBaseInitStruct)
{
  BTIM_TimeBaseInitStruct->BTIM_Prescaler =  BTIM_PRS_DIV1;
  BTIM_TimeBaseInitStruct->BTIM_Mode = BTIM_Mode_TIMER;
  BTIM_TimeBaseInitStruct->BTIM_Period = 0xFFFF;  
}

/*******************************************************************************
// ˵����ʹ��BTIMx��ʱ��
// ������BTIM_TimeBaseInitStruct
// ����ֵ����
*******************************************************************************/
void BTIM_Cmd(BTIM_TypeDef* BTIMx, FunctionalState NewState)
{
  assert_param(IS_BTIM_ALL_PERIPH(BTIMx));
  assert_param(IS_FUNCTIONAL_STATE(NewState));
  NewState ? (BTIMx->BCR |= BTIMx_BCR_EN_Msk) : (BTIMx->BCR &= ~BTIMx_BCR_EN_Msk);
}


/*******************************************************************************
// ˵��������BTIMx���ж�
// ������BTIMx CW_BTIM1~3
// ������BTIM_IT �ж��¼�����
// ������NewState �ж��¼����͵�״̬��ENABLE �� DISABLE
// ����ֵ����
*******************************************************************************/
void BTIM_ITConfig(BTIM_TypeDef* BTIMx, uint16_t BTIM_IT, FunctionalState NewState)
{
  assert_param(IS_BTIM_ALL_PERIPH(BTIMx));
  assert_param(IS_FUNCTIONAL_STATE(NewState));
  assert_param(IS_BTIM_IT(BTIM_IT));

  NewState ? ( BTIMx->IER |= BTIM_IT) : (BTIMx->IER &= ~BTIM_IT);
}


/*******************************************************************************
// ˵��������BTIMx��DMA����
// ������BTIMx CW_BTIM1~3
// ������BTIM_DMASource DMA�����¼�����
// ������NewState �ж��¼����͵�״̬��ENABLE �� DISABLE
// ����ֵ����
*******************************************************************************/
void BTIM_DMACmd(BTIM_TypeDef* BTIMx, uint16_t BTIM_DMASource, FunctionalState NewState)
{
  assert_param(IS_BTIM_ALL_PERIPH(BTIMx));
  assert_param(IS_FUNCTIONAL_STATE(NewState));
  assert_param(IS_BTIM_DMA_SOURCE(BTIM_DMASource));

  NewState ? (BTIMx->DMA |= BTIM_DMASource) : (BTIMx->DMA &= ~BTIM_DMASource);
}

/*******************************************************************************
// ˵��������BTIMx��Ԥ����ϵ��
// ������BTIMx CW_BTIM1~3
// ������Prescaler Ԥ����ϵ��
// ������BTIM_PSCReloadMode Ԥ����ϵ�����������»��������ʱ����,ȡֵ��Χ
//       BTIM_PSCReloadMode_Update Ԥ����ϵ�������ʱ����
//       BTIM_PSCReloadMode_Immediate Ԥ����ϵ����������
// ����ֵ����
*******************************************************************************/
void BTIM_PrescalerConfig(BTIM_TypeDef* BTIMx, uint16_t Prescaler, uint16_t BTIM_PSCReloadMode)
{  
  assert_param(IS_BTIM_ALL_PERIPH(BTIMx));
  assert_param(IS_BTIM_PRS_DIV(Prescaler));
  assert_param(IS_BTIM_PRESCALER_RELOAD(BTIM_PSCReloadMode));

  REGBITS_MODIFY(BTIMx->BCR, BTIMx_BCR_PRS_Msk, Prescaler);  
  
  if (BTIM_PSCReloadMode ==BTIM_PSCReloadMode_Immediate)
  {
    BTIMx->BCR &= ~BTIMx_BCR_EN_Msk;
    BTIMx->BCR |= BTIMx_BCR_EN_Msk; 
  }   
}

/*******************************************************************************
// ˵��������BTIMx�Ĺ���ģʽ
// ������BTIMx CW_BTIM1~3
// ������BTIM_Mode ģʽ����
//       BTIM_Mode_TIMER   ��ʱ��ģʽ
//       BTIM_Mode_COUNTER ������ģʽ
//       BTIM_Mode_TRIGGER ��������ģʽ
//       BTIM_Mode_GATE    �ſ�ģʽ    
// ����ֵ����
*******************************************************************************/
void BTIM_ModeConfig(BTIM_TypeDef* BTIMx, uint16_t BTIM_Mode)
{
  assert_param(IS_BTIM_ALL_PERIPH(BTIMx));
  assert_param(IS_BTIM_MODE(BTIM_Mode));

  REGBITS_MODIFY(BTIMx->BCR, BTIMx_BCR_MODE_Msk, BTIM_Mode); 
}

/*******************************************************************************
// ˵��������BTIMx�Ĵ��������ź���Դ
// ������BTIMx CW_BTIM1~3
// ������BTIM_InputTriggerSource ����Դ
//       BTIM_TS_ITR   �ڲ�ITR�ź�
//       BTIM_TS_ETR   �ⲿETR�ź�
// ����ֵ����
*******************************************************************************/
void BTIM_SelectInputTrigger(BTIM_TypeDef* BTIMx, uint16_t BTIM_InputTriggerSource)
{ 
  assert_param(IS_BTIM_ALL_PERIPH(BTIMx));
  assert_param(IS_BTIM_TRIGGER_SELECTION(BTIM_InputTriggerSource));

  REGBITS_MODIFY(BTIMx->BCR, BTIMx_BCR_TRS_Msk, BTIM_InputTriggerSource);   
}

/*******************************************************************************
// ˵��������BTIMx�ⲿ����ETR�źŵļ���
// ������BTIMx CW_BTIM1~3
// ������BTIM_ETR_Polarity  ��������
//       BTIM_ETR_Polarity_Positive   ������
//       BTIM_ETR_Polarity_Negative ������
// ����ֵ����
*******************************************************************************/
void BTIM_SelectETRInputPolarity(BTIM_TypeDef* BTIMx, uint16_t BTIM_ETR_Polarity)
{
  assert_param(IS_BTIM_ALL_PERIPH(BTIMx));
  assert_param(IS_BTIM_ETR_POLARITY(BTIM_ETR_Polarity));

  REGBITS_MODIFY(BTIMx->BCR, BTIMx_BCR_POL_Msk, BTIM_ETR_Polarity);
}

/*******************************************************************************
// ˵��������BTIMx�ĵ�������ģʽ
// ������BTIMx CW_BTIM1~3
// ������BTIM_OPMode  ��������
//       BTIM_OPMode_Single   ��������
//       BTIM_OPMode_Repetitive ��������
// ����ֵ����
*******************************************************************************/
void BTIM_SelectOnePulseMode(BTIM_TypeDef* BTIMx, uint16_t BTIM_OPMode)
{
  assert_param(IS_BTIM_ALL_PERIPH(BTIMx));
  assert_param(IS_BTIM_OPM_MODE(BTIM_OPMode));

  REGBITS_MODIFY(BTIMx->BCR, BTIMx_BCR_ONESHOT_Msk, BTIM_OPMode);
}

/*******************************************************************************
// ˵��������BTIMx�ķ�ת�������
// ������BTIMx CW_BTIM1~3
// ������NewState ENABLE �� DISABLE
// ����ֵ����
*******************************************************************************/
void BTIM_OutputToggleCmd(BTIM_TypeDef* BTIMx, FunctionalState NewState)
{
  assert_param(IS_BTIM_ALL_PERIPH(BTIMx));
  assert_param(IS_FUNCTIONAL_STATE(NewState));

  NewState ? (BTIMx->BCR |= BTIMx_BCR_TOGEN_Msk) : (BTIMx->BCR &= ~BTIMx_BCR_TOGEN_Msk);
}

/*******************************************************************************
// ˵��������BTIMx���ⲿ����ETR
// ������BTIMx CW_BTIM1~3
// ������BTIM_ExtTRGPolarity ETR�źŵļ��� BTIM_ETR_Polarity_Positive
//                                         BTIM_ETR_Polarity_Negative
// ������ExtTRGFilter  ETR�˲�������
// ����ֵ����
*******************************************************************************/
void BTIM_ETRConfig(BTIM_TypeDef* BTIMx, uint16_t BTIM_ExtTRGPolarity, uint16_t ExtTRGFilter)
{
  assert_param(IS_BTIM_ALL_PERIPH(BTIMx));
  assert_param(IS_BTIM_ETR_POLARITY(BTIM_ExtTRGPolarity));
  assert_param(IS_BTIM_EXT_FILTER(ExtTRGFilter));

  REGBITS_MODIFY(BTIMx->BCR, BTIMx_BCR_POL_Msk, BTIM_ExtTRGPolarity);
  REGBITS_MODIFY(BTIMx->ACR, BTIMx_ACR_ETRFLT_Msk, ExtTRGFilter);
}

/*******************************************************************************
// ˵��������BTIM�ļ�����ֵ
// ������BTIMx CW_BTIM1~3
// ������Counter ��Χ0x0000~0xFFFF
// ����ֵ����
*******************************************************************************/
void BTIM_SetCounter(BTIM_TypeDef* BTIMx, uint16_t Counter)
{
  assert_param(IS_BTIM_ALL_PERIPH(BTIMx));
  
  BTIMx->CNT = Counter;  
}

/*******************************************************************************
// ˵��������BTIM���Զ�����ֵ
// ������BTIMx CW_BTIM1~3
// ������Autoreload ��Χ0x0000~0xFFFF
// ����ֵ����
*******************************************************************************/
void BTIM_SetAutoreload(BTIM_TypeDef* BTIMx, uint16_t Autoreload)
{
  assert_param(IS_BTIM_ALL_PERIPH(BTIMx));
  
  BTIMx->ARR = Autoreload;  
}

/*******************************************************************************
// ˵������ȡBTIM�ĵ�ǰ����ֵ
// ������BTIMx CW_BTIM1~3
// ����ֵ��CNT�Ĵ�����ֵ
*******************************************************************************/
uint16_t BTIM_GetCounter(BTIM_TypeDef* BTIMx)
{
  assert_param(IS_BTIM_ALL_PERIPH(BTIMx));
  
  return BTIMx->CNT;  
}

/*******************************************************************************
// ˵������ȡBTIM�ĵ�ǰ�Զ�����ֵ
// ������BTIMx CW_BTIM1~3
// ����ֵ��ARR�Ĵ�����ֵ
*******************************************************************************/
uint16_t BTIM_GetAutoreload(BTIM_TypeDef* BTIMx)
{
  assert_param(IS_BTIM_ALL_PERIPH(BTIMx));
  
  return BTIMx->ARR;  
}

/*******************************************************************************
// ˵������ȡBTIM�ĵ�ǰԤ����ϵ��
// ������BTIMx CW_BTIM1~3
// ����ֵ��Ԥ��Ƶ����ǰ����ʹ�õķ�Ƶϵ��
*******************************************************************************/
uint16_t BTIM_GetPrescaler(BTIM_TypeDef* BTIMx)
{
  assert_param(IS_BTIM_ALL_PERIPH(BTIMx));
  
  return BTIMx->BCR_f.PRSSTATUS;  
}
/*******************************************************************************
// ˵���� ���BTIM��״̬�Ĵ����ĸ�״̬λ�Ƿ���λ
// ������ BTIMx CW_BTIM1~3
// ������ BTIM_FLAG ָ����״̬λ ��������Χ�� BTIM_IT_OV 
//                                           BTIM_IT_TI
//                                           BTIM_IT_TOP
//                    
// ����ֵ�� Ԥ��Ƶ����ǰ����ʹ�õķ�Ƶϵ��
*******************************************************************************/
FlagStatus BTIM_GetITStatus(BTIM_TypeDef* BTIMx, uint16_t BTIM_FLAG)
{
  assert_param(IS_BTIM_ALL_PERIPH(BTIMx));
  assert_param(IS_BTIM_IT(BTIM_FLAG));

  return (REGBITS_GET(BTIMx->ISR, BTIM_FLAG) ? SET : RESET);  
}

/*******************************************************************************
// ˵���� ���BTIM��״̬�Ĵ����ĸ�״̬λ
// ������ BTIMx CW_BTIM1~3
// ������ BTIM_FLAG ָ����״̬λ ��������Χ�� BTIM_IT_OV 
//                                           BTIM_IT_TI
//                                           BTIM_IT_TOP
//                    
// ����ֵ�� Ԥ��Ƶ����ǰ����ʹ�õķ�Ƶϵ��
*******************************************************************************/
void BTIM_ClearITPendingBit(BTIM_TypeDef* BTIMx, uint16_t BTIM_FLAG)
{
  assert_param(IS_BTIM_ALL_PERIPH(BTIMx));
  assert_param(IS_BTIM_IT(BTIM_FLAG));

  REGBITS_CLR(BTIMx->ICR, BTIM_FLAG);
}
