/**
 * @file cw32f030_iwdt.c
 * @author P&S (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2021-04-25
 * 
 * @copyright Copyright (c) 2021
 * 
 */
/* Includes ------------------------------------------------------------------*/
#include "cw32f030_iwdt.h"

/* Private_TypesDefinitions --------------------------------------------------*/

/* Private_Defines -----------------------------------------------------------*/

/* Private_Variables ---------------------------------------------------------*/

/* Private_FunctionPrototypes ------------------------------------------------*/

/* Private_Functions ---------------------------------------------------------*/

/* Public_Functions ----------------------------------------------------------*/

/**
 * @brief IWDTȥ��ʼ��
 */
void IWDT_DeInit(void)
{
    CW_SYSCTRL->APBRST1_f.IWDT = 0;
    CW_SYSCTRL->APBRST1_f.IWDT = 1;
}

/**
 * @brief IWDT��ʼ��
 * @param IWDT_InitStruct �ýṹ�����IWDT��Ҫ���õĲ���
 */
void IWDT_Init(IWDT_InitTypeDef *IWDT_InitStruct)
{
    assert_param(IS_IWDT_PRESCALER(IWDT_InitStruct->IWDT_Prescaler));
    assert_param(IS_IWDT_ACTION(IWDT_InitStruct->IWDT_OverFlowAction));
    assert_param(IS_IWDT_SLEEP_MODE(IWDT_InitStruct->IWDT_Pause));
    assert_param(IS_IWDT_WINDOW_VALUE(IWDT_InitStruct->IWDT_WindowValue));
    assert_param(IS_IWDT_RELOAD(IWDT_InitStruct->IWDT_ReloadValue));

    __IWDT_RUN();                // ��Ҫ������IWDT�󣬲����޸������Ĵ���
    __IWDT_UNLOCK();             // �����Ĵ�������
    if (IWDT_InitStruct->IWDT_ITState == ENABLE)
    {
        CW_IWDT->CR = IWDT_InitStruct->IWDT_Prescaler | \
                      IWDT_InitStruct->IWDT_OverFlowAction | \
                      IWDT_CR_IE_Msk | IWDT_InitStruct->IWDT_Pause;
    }
    else
    {
        CW_IWDT->CR = (IWDT_InitStruct->IWDT_Prescaler | \
                      IWDT_InitStruct->IWDT_OverFlowAction | \
                      IWDT_InitStruct->IWDT_Pause);
    }

    CW_IWDT->ARR = IWDT_InitStruct->IWDT_ReloadValue;
    CW_IWDT->WINR = IWDT_InitStruct->IWDT_WindowValue;    

    __IWDT_LOCK();
}

/**
 * @brief ����IWDT
 */
void inline IWDT_Cmd(void)
{
    __IWDT_RUN();
}

/**
 * @brief ι��
 */
void inline IWDT_Refresh(void)
{
    __IWDT_REFRESH();
}

/**
 * @brief �Ĵ�����������
 */
void inline IWDT_Unlock(void)
{
    __IWDT_UNLOCK();
}

/**
 * @brief �Ĵ�����������
 */
void inline IWDT_Lock(void)
{
    __IWDT_LOCK();
}

/**
 * @brief ֹͣIWDT
 */
void inline IWDT_Stop(void)
{
    __IWDT_STOP();
}

/**
 * @brief ����IWDT��Ԥ��Ƶ����
 * @param IWDT_Prescaler ȡֵ��Χ IWDT_Prescaler_DIV4~IWDT_Prescaler_DIV512
 */
void IWDT_SetPrescaler(uint32_t IWDT_Prescaler)
{
    assert_param(IS_IWDT_PRESCALER(IWDT_Prescaler));

    __IWDT_UNLOCK();
    while(CW_IWDT->SR & IWDT_SR_CRF_Msk);
    CW_IWDT->CR_f.PRS = IWDT_Prescaler;
    __IWDT_LOCK();
}

/**
 * @brief ����IWDT�Ĵ���ֵ
 * @param WindowValue ȡֵ��Χ0x00000000~0x00000FFF,��ֵΪ0x00000FFFʱ�����ڹ��ܲ�����
 */
void IWDT_SetWindowValue(uint32_t WindowValue)
{
    assert_param(IS_IWDT_WINDOW_VALUE(WindowValue));

    __IWDT_UNLOCK();
    while(CW_IWDT->SR & IWDT_SR_WINRF_Msk);
    CW_IWDT->WINR = WindowValue;
    __IWDT_LOCK();
}

/**
 * @brief ����IWDT�����ؼĴ�����ֵ
 * @param ReloadValue ȡֵ��Χ0x00000000~0x00000FFF
 */
void IWDT_SetReloadValue(uint32_t ReloadValue)
{
    assert_param(IS_IWDT_RELOAD(ReloadValue));

    __IWDT_UNLOCK();
    while(CW_IWDT->SR & IWDT_SR_ARRF_Msk);
    CW_IWDT->ARR = ReloadValue;
    __IWDT_LOCK();
}

/**
 * @brief ����IWDT���ж�ʹ�������
 * @param NewState IWDT�ж�ʹ��λ״̬ ��Χ��ENABLE��DISABLE
 */
void IWDT_ITConfig(FunctionalState NewState)
{
    assert_param(IS_FUNCTIONAL_STATE(NewState));

    __IWDT_UNLOCK();
    while(CW_IWDT->SR & IWDT_SR_CRF_Msk);
    NewState ? (CW_IWDT->CR_f.IE = ENABLE):(CW_IWDT->CR_f.IE = DISABLE);
    __IWDT_LOCK();
}

/**
 * @brief ��ȡIWDT��״̬
 * @param StatusBit ״̬λ��λ��,ȡֵ��ΧΪ��IWDT_SR_CRF_Msk
 *                                          IWDT_SR_ARRF_Msk
 *                                          IWDT_SR_WINRF_Msk
 *                                          IWDT_SR_OV_Msk
 *                                          IWDT_SR_RUN_Msk
 *                                          IWDT_SR_RELOAD_Msk
 * 
 * @return FlagStatus 
 */
FlagStatus IWDT_GetFlagStatus(uint32_t StatusBit)
{
    return (FlagStatus)(CW_IWDT->SR & StatusBit);
}

/**
 * @brief ���IWDT�������־OV
 */
void inline IWDT_ClearOVFlag(void)
{
    CW_IWDT->SR_f.OV = 0;
}

/**
 * @brief 
 * @return uint32_t ����IWDT�ļ���ֵ
 */
uint32_t IWDT_GetCounterValue(void)
{
    uint32_t tmp1, tmp2;
    do {
        tmp1 = CW_IWDT->CNT;
        tmp2 = CW_IWDT->CNT;        
    }while(tmp1 != tmp2);

    return tmp1;    
}
