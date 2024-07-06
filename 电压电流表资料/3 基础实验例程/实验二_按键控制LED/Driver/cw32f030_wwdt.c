/**
 * @file cw32f030_wwdt.c
 * @author P&S (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2021-04-23
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
#include "cw32f030_wwdt.h"

/* Private_TypesDefinitions --------------------------------------------------*/

/* Private_Defines -----------------------------------------------------------*/

/* Private_Variables ---------------------------------------------------------*/

/* Private_FunctionPrototypes ------------------------------------------------*/

/* Private_Functions ---------------------------------------------------------*/

/* Public_Functions ----------------------------------------------------------*/

/**
 * @brief WWDTȥ��ʼ��
 * @param ��
 * @return ��
 */
void WWDT_DeInit(void)
{
  CW_SYSCTRL->APBRST1_f.WWDT = 0;
  CW_SYSCTRL->APBRST1_f.WWDT = 1;
}

/**
 * @brief ��ʼ��WWDT
 * @param WWDT_InitStruct ����ṹ�嶨��WWDT_InitTypeDef
 */
void WWDT_Init(WWDT_InitTypeDef* WWDT_InitStruct)
{
  assert_param(IS_WWDT_COUNTER(WWDT_InitStruct->WWDT_CounterValue));
  assert_param(IS_WWDT_PRESCALER(WWDT_InitStruct->WWDT_Prescaler));
  assert_param(IS_WWDT_WINDOW_VALUE(WWDT_InitStruct->WWDT_WindowValue));

  CW_SYSCTRL->APBEN1_f.WWDT = 1U;    /* WWDT��APB���߷���ʱ��ʹ�� */
  
  CW_WWDT->CR0 = (WWDT_InitStruct->WWDT_CounterValue & WWDT_CR0_WCNT_Msk);

  if(WWDT_InitStruct->WWDT_ITState == ENABLE)
  {
    CW_WWDT->CR1 = WWDT_InitStruct->WWDT_WindowValue | WWDT_InitStruct->WWDT_Prescaler | WWDT_CR1_IE_Msk;
  }
  else
  {
    CW_WWDT->CR1 = (WWDT_InitStruct->WWDT_WindowValue | WWDT_InitStruct->WWDT_Prescaler) & (~WWDT_CR1_IE_Msk);
  }
  
  
}

/**
 * @brief ʹ��WWDT��ʹ��WWDT���ܽ�ֹ
 */
void WWDT_Cmd(void)
{
  CW_WWDT->CR0_f.EN = 1U;
}

/**
 * @brief ι������
 * @param Counter WWDT�������ĸ���ֵ��ȡֵ��Χ0x40~0x7F
 */
void WWDT_Refresh(uint8_t Counter)
{
  assert_param(IS_WWDT_COUNTER(Counter));

  CW_WWDT->CR0_f.WCNT = Counter;
}

/**
 * @brief ����WWDT��Ԥ��Ƶϵ��
 * @param WWDT_Prescaler ȡֵ��ΧWWDT_Prescaler_DIV4096~WWDT_Prescaler_DIV524288
 */
void WWDT_SetPrescaler(uint32_t WWDT_Prescaler)
{
  assert_param(IS_WWDT_PRESCALER(WWDT_Prescaler));
  REGBITS_MODIFY(CW_WWDT->CR1, WWDT_CR1_PRS_Msk, WWDT_Prescaler);  
}

/**
 * @brief ����WWDT�Ĵ���ϵ��
 * @param WindowValue ����ֵ��ȡֵ��Χ0x40~0x7F
 */
void WWDT_SetWindowValue(uint8_t WindowValue)
{
  assert_param(IS_WWDT_WINDOW_VALUE(WindowValue));

  CW_WWDT->CR1_f.WINR = WindowValue;
}

/**
 * @brief ��ȡ��ǰ��������ֵ
 * @return uint8_t ��ǰ��������ֵ
 */
uint8_t WWDT_GetCounterValue(void)
{
  return (uint8_t) (CW_WWDT->CR0 & WWDT_CR0_WCNT_Msk);
}

/**
 * @brief ��ȡ��ǰ���õĴ���ֵ
 * @return uint8_t ��ǰ���õĴ���ֵ
 */
uint8_t WWDT_GetWindowValue(void)
{
  return (uint8_t) (CW_WWDT->CR1 & WWDT_CR1_WINR_Msk);
}

/**
 * @brief  ����WWDT��Ԥ����ж�ʹ�� ��λ��Ĭ�Ϲر��ж�ʹ��
 */
void WWDT_EnableIT(void)
{
  CW_WWDT->CR1_f.IE = ENABLE;
}

/**
 * @brief ��ȡWWDT��״̬�Ĵ�����Ԥ���λ״̬
 * @return FlagStatus 
 */
FlagStatus WWDT_GetFlagStatus(void)
{
  return (FlagStatus)(CW_WWDT->SR);
}

/**
 * @brief ���WWDT��״̬�Ĵ�����Ԥ���λ״̬
 */
void WWDT_ClearFlag(void)
{
  REGBITS_CLR(CW_WWDT->SR, WWDT_SR_POV_Msk);
}
