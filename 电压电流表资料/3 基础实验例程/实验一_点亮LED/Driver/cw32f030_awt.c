/**
 * @file cw32f030_awt.c
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2021-05-18
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
#include "cw32f030_awt.h"

/* Private_TypesDefinitions --------------------------------------------------*/

/* Private_Defines -----------------------------------------------------------*/

/* Private_Variables ---------------------------------------------------------*/

/* Private_FunctionPrototypes ------------------------------------------------*/

/* Private_Functions ---------------------------------------------------------*/

/* Public_Functions ----------------------------------------------------------*/

/**
 * @brief AWT  ȥ��ʼ��
 * 
 */
void AWT_DeInit(void)
{ 
  CW_AWT->CR = 0UL;
  CW_AWT->ARR = 0x0000FFFFUL;
  CW_AWT->IER = 0UL;
  CW_AWT->ICR = 0UL;
}

/**
 * @brief AWT��ʱ��������ʼ��
 * 
 * @param AWT_TimeCntInitStruct 
 */
void AWT_TimeCntInit(AWT_TimeCntInitTypeDef* AWT_TimeCntInitStruct)
{ 
  assert_param(IS_AWT_CLKSOURCE(AWT_TimeCntInitStruct->AWT_ClkSource));
  assert_param(IS_AWT_PRS_DIV(AWT_TimeCntInitStruct->AWT_Prescaler));
  assert_param(IS_AWT_ARR(AWT_TimeCntInitStruct->AWT_Period)); 
  assert_param(IS_AWT_MODE(AWT_TimeCntInitStruct->AWT_Mode));

  REGBITS_MODIFY(CW_AWT->CR, AWT_CR_SRC_Msk |\
                             AWT_CR_PRS_Msk |\
                             AWT_CR_MD_Msk
                             ,\
                             AWT_TimeCntInitStruct->AWT_ClkSource |\
                             AWT_TimeCntInitStruct->AWT_Prescaler |\
                             AWT_TimeCntInitStruct->AWT_Mode); 

  CW_AWT->ARR = AWT_TimeCntInitStruct->AWT_Period;  
}

/**
 * @brief �ṹ������AWT_TimeCntInitStruct��ʼ��
 * 
 * @param AWT_TimeCntInitStruct 
 */
void AWT_TimeCntStructInit(AWT_TimeCntInitTypeDef * AWT_TimeCntInitStruct)
{
  AWT_TimeCntInitStruct->AWT_ClkSource = AWT_CLKSOURCE_HSIOSC;
  AWT_TimeCntInitStruct->AWT_Prescaler = AWT_PRS_DIV2;
  AWT_TimeCntInitStruct->AWT_Mode = AWT_MODE_TIMECNT;  
  AWT_TimeCntInitStruct->AWT_Period = (uint32_t)0x0000FFFF;
}

/**
 * @brief ʹ��AWT��ʱ��
 * 
 * @param NewState 
 */
void AWT_Cmd(FunctionalState NewState)
{
  assert_param(IS_FUNCTIONAL_STATE(NewState));

  if (NewState != DISABLE)
  {
    CW_AWT->CR |= AWT_CR_EN;
  }
  else
  {
    CW_AWT->CR &= (~AWT_CR_EN);
  }

}

/**
 * @brief ����AWT���ж�
 * 
 * @param AWT_IT 
 * @param NewState 
 */
void AWT_ITConfig(uint32_t AWT_IT, FunctionalState NewState)
{
  assert_param(IS_FUNCTIONAL_STATE(NewState));
  assert_param(IS_AWT_IT(AWT_IT));

  if (NewState != DISABLE)
  {
    CW_AWT->IER |= AWT_IT;
  }
  else
  {
    CW_AWT->IER &= (~AWT_IT);
  }
}


/**
 * @brief ��ȡAWT�жϱ�־
 * 
 * @param AWT_IT 
 * @return FlagStatus 
 */
FlagStatus AWT_GetITStatus(uint32_t AWT_IT)
{
  assert_param(IS_AWT_IT(AWT_IT));

  return (CW_AWT->ISR & AWT_IT) ? SET : RESET;
}

/**
 * @brief ���AWT�жϱ�־
 * 
 * @param AWT_IT 
 */
void AWT_ClearITPendingBit(uint32_t AWT_IT)
{
  assert_param(IS_AWT_IT(AWT_IT));

  CW_AWT->ICR &= (~AWT_IT);

}

/**
 * @brief AWT����ʱ��Դ����
 * 
 * @param AWT_ClkSrouce 
 */
void AWT_ClkSourceConfig(uint32_t AWT_ClkSource)
{  
  assert_param(IS_AWT_CLKSOURCE(AWT_ClkSource));

  REGBITS_MODIFY(CW_AWT->CR, AWT_CR_SRC_Msk, AWT_ClkSource); 
}

/**
 * @brief AWT����ʱ�ӷ�Ƶϵ������
 * 
 * @param Prescaler 
 */
void AWT_PrescalerConfig(uint32_t AWT_Prescaler)
{  
  assert_param(IS_AWT_PRS_DIV(AWT_Prescaler));

  REGBITS_MODIFY(CW_AWT->CR, AWT_CR_PRS_Msk, AWT_Prescaler); 
}

/**
 * @brief ��ȡAWT������CNT�Ĵ���ֵ
 * 
 * @return uint16_t 
 */
uint16_t AWT_GetCounter(void)
{
  return (uint16_t)(CW_AWT->CNT);
}

/**
 * @brief ��ȡAWT����������ֵ�Ĵ���ARRֵ
 * 
 * @return uint16_t 
 */
uint16_t AWT_GetAutoreload(void)
{
  return (uint16_t)(CW_AWT->ARR);
}

/**
 * @brief ��ȡAWTʱ��Դ
 * 
 * @return uint32_t 
 */
uint32_t AWT_GetClkSource(void)
{
  return (uint32_t)((CW_AWT->CR_f.SRC) );
}

/**
 * @brief ��ȡAWTʱ�ӷ�Ƶϵ��
 * 
 * @return uint32_t 
 */
uint32_t AWT_GetPrescaler(void)
{
  return (uint32_t)((CW_AWT->CR_f.PRS) );
}


