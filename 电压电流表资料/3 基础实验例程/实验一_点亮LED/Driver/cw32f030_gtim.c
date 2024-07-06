/**
 * @file cw32f030_gtim.c
 * @author P&S (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2021-04-27
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
#include "cw32f030_gtim.h"

/* Private_TypesDefinitions --------------------------------------------------*/

/* Private_Defines -----------------------------------------------------------*/

/* Private_Variables ---------------------------------------------------------*/

/* Private_FunctionPrototypes ------------------------------------------------*/

/* Private_Functions ---------------------------------------------------------*/

/* Public_Functions ----------------------------------------------------------*/

/**
 * @brief 
 * @param GTIMx 
 */
void GTIM1_DeInit(void)
{
    CW_SYSCTRL->APBRST1_f.GTIM1 = 0;
    CW_SYSCTRL->APBRST1_f.GTIM1 = 1;
}

void GTIM2_DeInit(void)
{
    CW_SYSCTRL->APBRST1_f.GTIM2 = 0;
    CW_SYSCTRL->APBRST1_f.GTIM2 = 1;
}

void GTIM3_DeInit(void)
{
    CW_SYSCTRL->APBRST2_f.GTIM3 = 0;
    CW_SYSCTRL->APBRST2_f.GTIM3 = 1;
}

void GTIM4_DeInit(void)
{
    CW_SYSCTRL->APBRST2_f.GTIM4 = 0;
    CW_SYSCTRL->APBRST2_f.GTIM4 = 1;
}

/**
 * @brief GTIM�Ļ���������ʼ��
 * @param GTIMx ȡֵ��Χ��CW_GTIM1,CW_GTIM2,CW_GTIM3,CW_GTIM4
 * @param GTIM_InitStruct ���GTIM_InitTypeDef�Ķ���
 */
void GTIM_TimeBaseInit(GTIM_TypeDef *GTIMx, GTIM_InitTypeDef *GTIM_InitStruct)
{
    assert_param(IS_GTIM_DEFINE(GTIMx));
    assert_param(IS_GTIM_MODE(GTIM_InitStruct->Mode));
    assert_param(IS_GTIM_ONESHOT(GTIM_InitStruct->OneShotMode));
    assert_param(IS_GTIM_PRESCALER(GTIM_InitStruct->Prescaler));

    REGBITS_MODIFY(GTIMx->CR0, GTIMx_CR0_PRS_Msk | GTIMx_CR0_ONESHOT_Msk |\
                               GTIMx_CR0_MODE_Msk | GTIMx_CR0_TOGEN_Msk, \
                               GTIM_InitStruct->Prescaler | GTIM_InitStruct->OneShotMode |\
                               GTIM_InitStruct->Mode |\
                               (GTIM_InitStruct->ToggleOutState ? GTIMx_CR0_TOGEN_Msk : 0));

    GTIMx->ARR = GTIM_InitStruct->ReloadValue;
}

/**
 * @brief ����ģʽ��ʼ����
 * @param GTIMx ȡֵ��Χ��CW_GTIM1,CW_GTIM2,CW_GTIM3,CW_GTIM4
 * @param GTIM_EncodeInitStruct 
 */
void GTIM_EncodeInit(GTIM_TypeDef *GTIMx, GTIM_EncodeInitTypeDef *GTIM_EncodeInitStruct)
{
    uint32_t tmp;
    assert_param(IS_GTIM_DEFINE(GTIMx));
    assert_param(IS_GTIM_ENCODE_MODE(GTIM_EncodeInitStruct->EncodeMode));
    assert_param(IS_GTIM_ENCODE_RESET(GTIM_EncodeInitStruct->EncodeResetMode));
    assert_param(IS_GTIM_ENCODE_RELOAD(GTIM_EncodeInitStruct->EncodeReloadMode));
    assert_param(IS_GTIM_CHx_FILTER(GTIM_EncodeInitStruct->CH1Filter));
    assert_param(IS_GTIM_CHx_FILTER(GTIM_EncodeInitStruct->CH2Filter));
    assert_param(IS_GTIM_CHx_FILTER(GTIM_EncodeInitStruct->CH3Filter));
    assert_param(IS_GTIM_CHx_INVERT(GTIM_EncodeInitStruct->CH1Invert));
    assert_param(IS_GTIM_CHx_INVERT(GTIM_EncodeInitStruct->CH2Invert));
    assert_param(IS_GTIM_CHx_INVERT(GTIM_EncodeInitStruct->CH3Invert));

    REGBITS_MODIFY(GTIMx->CR0,
                   GTIMx_CR0_ENCRELOAD_Msk | GTIMx_CR0_ENCRESET_Msk | GTIMx_CR0_ENCMODE_Msk,
                   GTIM_EncodeInitStruct->EncodeMode | GTIM_EncodeInitStruct->EncodeResetMode |
                   GTIM_EncodeInitStruct->EncodeReloadMode);

    tmp = GTIM_EncodeInitStruct->CH1Filter | GTIM_EncodeInitStruct->CH1Invert |
          (GTIM_EncodeInitStruct->CH2Filter << 4) | (GTIM_EncodeInitStruct->CH2Invert << 7) |
          (GTIM_EncodeInitStruct->CH3Filter << 8) | (GTIM_EncodeInitStruct->CH3Invert << 11);
    REGBITS_MODIFY(GTIMx->CR1, ~(GTIMx_CR1_CH4FLT_Msk | GTIMx_CR1_CH4POL_Msk), tmp);
}

/**
 * @brief �Ƚ�������ܳ�ʼ��
 * @param GTIMx ȡֵ��Χ��CW_GTIM1,CW_GTIM2,CW_GTIM3,CW_GTIM4
 * @param CHx ���ͨ����CH1~CH4
 * @param OCMode 
 */
void GTIM_OCInit(GTIM_TypeDef *GTIMx, uint32_t CHx, uint32_t OCMode)
{
    assert_param(IS_GTIM_DEFINE(GTIMx));
    assert_param(IS_GTIM_CHANNEL(CHx));
    assert_param(IS_GTIM_OC_OUTPUT(OCMode));

    REGBITS_MODIFY(GTIMx->CMMR, (GTIMx_CMMR_CC1M_Msk << CHx), (OCMode << CHx));
}

void GTIM_ICInit(GTIM_TypeDef *GTIMx, GTIM_ICInitTypeDef *GTIM_ICInitStruct)
{
    assert_param(IS_GTIM_DEFINE(GTIMx));
    assert_param(IS_GTIM_CHANNEL(GTIM_ICInitStruct->CHx));
    assert_param(IS_GTIM_ICPolarity(GTIM_ICInitStruct->ICPolarity));
    assert_param(IS_GTIM_CHx_FILTER(GTIM_ICInitStruct->ICFilter));
    assert_param(IS_GTIM_CHx_INVERT(GTIM_ICInitStruct->ICInvert));

    REGBITS_MODIFY(GTIMx->CMMR, (GTIMx_CMMR_CC1M_Msk << GTIM_ICInitStruct->CHx),
                   (GTIM_ICInitStruct->ICPolarity << GTIM_ICInitStruct->CHx));

    REGBITS_MODIFY(GTIMx->CR1, (0xFUL << GTIM_ICInitStruct->CHx),
                   (GTIM_ICInitStruct->ICFilter | (GTIM_ICInitStruct->ICInvert << 3)) << GTIM_ICInitStruct->CHx);
}

/**
 * @brief GTIMʹ��
 * @param GTIMx 
 */
void GTIM_Cmd(GTIM_TypeDef *GTIMx, FunctionalState NewState)
{
    assert_param(IS_GTIM_DEFINE(GTIMx));
    assert_param(IS_FUNCTIONAL_STATE(NewState));

    GTIMx->CR0_f.EN = NewState;
}

/**
 * @brief ����ETR�źŵļ��Ժ��˲���
 * @param GTIMx 
 * @param ETRPolarity ����
 * @param ETRFilter �˲�����
 */
void GTIM_ETRConfig(GTIM_TypeDef *GTIMx, uint32_t ETRPolarity, uint32_t ETRFilter)
{
    assert_param(IS_GTIM_DEFINE(GTIMx));
    assert_param(IS_GTIM_ETR_POL(ETRPolarity));
    assert_param(IS_GTIM_ETR_FILTER(ETRFilter));

    REGBITS_MODIFY(GTIMx->CR0, GTIMx_CR0_TRS_Msk | GTIMx_CR0_POL_Msk, ETRPolarity);

    REGBITS_MODIFY(GTIMx->ETR, GTIMx_ETR_ETRFLT_Msk, ETRFilter);
}

/**
 * @brief 
 * 
 * @param ITRSouce ITR_SOURCE_BTIM1 ITR_SOURCE_BTIM2 ITR_SOURCE_BTIM3
 *                 ITR_SOURCE_GTIM2 ITR_SOURCE_GTIM3 ITR_SOURCE_GTIM4
 *                 ITR_SOURCE_ATIM
 */
void GTIM1_ITRConfig(uint32_t ITRSouce)
{
    assert_param(IS_ITR_SOURCE(ITRSouce));
    assert_param(ITRSouce != ITR_SOURCE_GTIM1);

    REGBITS_SET(CW_GTIM1->CR0, GTIMx_CR0_TRS_Msk);

    CW_SYSCTRL->TIMITR_f.GTIM1ITR = ITRSouce;
}

/**
 * @brief 
 * 
 * @param ITRSouce ITR_SOURCE_BTIM1 ITR_SOURCE_BTIM2 ITR_SOURCE_BTIM3
 *                 ITR_SOURCE_GTIM1 ITR_SOURCE_GTIM3 ITR_SOURCE_GTIM4
 *                 ITR_SOURCE_ATIM
 */
void GTIM2_ITRConfig(uint32_t ITRSouce)
{
    assert_param(IS_ITR_SOURCE(ITRSouce));
    assert_param(ITRSouce != ITR_SOURCE_GTIM2);

    REGBITS_SET(CW_GTIM2->CR0, GTIMx_CR0_TRS_Msk);

    CW_SYSCTRL->TIMITR_f.GTIM2ITR = ITRSouce;
}

/**
 * @brief 
 * 
 * @param ITRSouce ITR_SOURCE_BTIM1 ITR_SOURCE_BTIM2 ITR_SOURCE_BTIM3
 *                 ITR_SOURCE_GTIM1 ITR_SOURCE_GTIM2 ITR_SOURCE_GTIM4
 *                 ITR_SOURCE_ATIM
 */
void GTIM3_ITRConfig(uint32_t ITRSouce)
{
    assert_param(IS_ITR_SOURCE(ITRSouce));
    assert_param(ITRSouce != ITR_SOURCE_GTIM3);

    REGBITS_SET(CW_GTIM3->CR0, GTIMx_CR0_TRS_Msk);

    CW_SYSCTRL->TIMITR_f.GTIM3ITR = ITRSouce;
}

/**
 * @brief 
 * 
 * @param ITRSouce ITR_SOURCE_BTIM1 ITR_SOURCE_BTIM2 ITR_SOURCE_BTIM3
 *                 ITR_SOURCE_GTIM1 ITR_SOURCE_GTIM2 ITR_SOURCE_GTIM3 
 *                 ITR_SOURCE_ATIM
 */
void GTIM4_ITRConfig(uint32_t ITRSouce)
{
    assert_param(IS_ITR_SOURCE(ITRSouce));
    assert_param(ITRSouce != ITR_SOURCE_GTIM4);

    REGBITS_SET(CW_GTIM1->CR0, GTIMx_CR0_TRS_Msk);

    CW_SYSCTRL->TIMITR_f.GTIM4ITR = ITRSouce;
}

/**
 * @brief ��������ͨ���Ĳ���
 * @param GTIMx 
 * @param CHx 
 * @param CHxFilter 
 * @param CHxInvert 
 */
void GTIM_ICChannelConfig(GTIM_TypeDef *GTIMx, uint32_t CHx, uint32_t CHxFilter, uint32_t CHxInvert)
{
    assert_param(IS_GTIM_DEFINE(GTIMx));
    assert_param(IS_GTIM_CHANNEL(CHx));
    assert_param(IS_GTIM_CHx_FILTER(CHxFilter));
    assert_param(IS_GTIM_CHx_INVERT(CHxInvert));

    REGBITS_MODIFY(GTIMx->CR1, (0xFUL << CHx), (CHxFilter | (CHxInvert << 3)) << CHx);
}

/**
 * @brief ����Ԥ��Ƶϵ��
 * @param GTIMx 
 * @param GTIMPrescaler 
 */
void GTIM_SetPrescaler(GTIM_TypeDef *GTIMx, uint32_t GTIMPrescaler)
{
    assert_param(IS_GTIM_DEFINE(GTIMx));
    assert_param(IS_GTIM_PRESCALER(GTIMPrescaler));

    REGBITS_MODIFY(GTIMx->CR0, GTIMx_CR0_PRS_Msk, GTIMPrescaler);
}

/**
 * @brief ��������ֵ
 * @param GTIMx 
 * @param ReloadValue ȡֵ��Χ��0x0000~0xFFFF
 */
void GTIM_SetReloadValue(GTIM_TypeDef *GTIMx, uint32_t ReloadValue)
{
    assert_param(IS_GTIM_DEFINE(GTIMx));

    GTIMx->ARR = ReloadValue;
}

/**
 * @brief 
 * @param GTIMx 
 * @param Value 
 */
void GTIM_SetCounterValue(GTIM_TypeDef *GTIMx, uint32_t Value)
{
    assert_param(IS_GTIM_DEFINE(GTIMx));

    GTIMx->CNT = Value;
}

void GTIM_SetCompare1(GTIM_TypeDef *GTIMx, uint32_t Value)
{
    assert_param(IS_GTIM_DEFINE(GTIMx));

    GTIMx->CCR1 = 0x0000FFFF & Value;
}

void GTIM_SetCompare2(GTIM_TypeDef *GTIMx, uint32_t Value)
{
    assert_param(IS_GTIM_DEFINE(GTIMx));

    GTIMx->CCR2 = 0x0000FFFF & Value;
}

void GTIM_SetCompare3(GTIM_TypeDef *GTIMx, uint32_t Value)
{
    assert_param(IS_GTIM_DEFINE(GTIMx));

    GTIMx->CCR3 = 0x0000FFFF & Value;
}

void GTIM_SetCompare4(GTIM_TypeDef *GTIMx, uint32_t Value)
{
    assert_param(IS_GTIM_DEFINE(GTIMx));

    GTIMx->CCR4 = 0x0000FFFF & Value;
}

/**
 * @brief �õ�����ֵ
 * @param GTIMx 
 * @return uint32_t 
 */
uint32_t GTIM_GetCounterValue(GTIM_TypeDef *GTIMx)
{
    assert_param(IS_GTIM_DEFINE(GTIMx));

    return GTIMx->CNT;
}

/**
 * @brief 
 * @param GTIMx 
 * @return uint32_t 
 */
uint32_t GTIM_GetCapture1(GTIM_TypeDef *GTIMx)
{
    assert_param(IS_GTIM_DEFINE(GTIMx));

    return GTIMx->CCR1;
}

/**
 * @brief 
 * @param GTIMx 
 * @return uint32_t 
 */
uint32_t GTIM_GetCapture2(GTIM_TypeDef *GTIMx)
{
    assert_param(IS_GTIM_DEFINE(GTIMx));

    return GTIMx->CCR2;
}

/**
 * @brief 
 * @param GTIMx 
 * @return uint32_t 
 */
uint32_t GTIM_GetCapture3(GTIM_TypeDef *GTIMx)
{
    assert_param(IS_GTIM_DEFINE(GTIMx));

    return GTIMx->CCR3;
}

/**
 * @brief 
 * @param GTIMx 
 * @return uint32_t 
 */
uint32_t GTIM_GetCapture4(GTIM_TypeDef *GTIMx)
{
    assert_param(IS_GTIM_DEFINE(GTIMx));

    return GTIMx->CCR4;
}

/**
 * @brief 
 * @param GTIMx 
 * @param GTIM_IT 
 * @param NewState 
 */
void GTIM_ITConfig(GTIM_TypeDef *GTIMx, uint32_t GTIM_IT, FunctionalState NewState)
{
    assert_param(IS_GTIM_DEFINE(GTIMx));
    assert_param(IS_GTIM_IT(GTIM_IT));
    assert_param(IS_FUNCTIONAL_STATE(NewState));

    if (NewState != DISABLE)
    {
        GTIMx->IER |= GTIM_IT;
    }
    else
    {
        GTIMx->IER &= ~GTIM_IT;
    }
}

/**
 * @brief 
 * @param GTIMx 
 * @param GTIM_IT 
 * @return ITStatus 
 */
ITStatus GTIM_GetITStatus(GTIM_TypeDef *GTIMx, uint32_t GTIM_IT)
{
    assert_param(IS_GTIM_DEFINE(GTIMx));
    assert_param(IS_GTIM_GET_IT(GTIM_IT));

    return (GTIMx->ISR & GTIM_IT) ? SET : RESET;
}

/**
 * @brief 
 * @param GTIMx 
 * @param GTIM_IT 
 */
void GTIM_ClearITPendingBit(GTIM_TypeDef *GTIMx, uint32_t GTIM_IT)
{
    assert_param(IS_GTIM_DEFINE(GTIMx));
    assert_param(IS_GTIM_IT(GTIM_IT));

    GTIMx->ICR = ~GTIM_IT;
}

/**
 * @brief 
 * @param GTIMx 
 * @param GTIM_DMA 
 */
void GTIM_DMAConfig(GTIM_TypeDef *GTIMx, uint32_t GTIM_DMA, FunctionalState NewState)
{
    assert_param(IS_GTIM_DEFINE(GTIMx));
    assert_param(IS_GTIM_DMA(GTIM_DMA));
    assert_param(IS_FUNCTIONAL_STATE(NewState));

    NewState ? (GTIMx->DMA |= GTIM_DMA) : (GTIMx->DMA &= ~GTIM_DMA);
}
