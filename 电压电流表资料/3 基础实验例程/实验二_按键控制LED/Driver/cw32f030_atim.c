/**
 * @file cw32f030_atim.c
 * @author P&S (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2021-04-29
 * 
 * @copyright Copyright (c) 2021
 * 
 */
/* Includes ------------------------------------------------------------------*/
#include "cw32f030_atim.h"

/* Private_TypesDefinitions --------------------------------------------------*/

/* Private_Defines -----------------------------------------------------------*/

/* Private_Variables ---------------------------------------------------------*/

/* Private_FunctionPrototypes ------------------------------------------------*/

/* Private_Functions ---------------------------------------------------------*/

/* Public_Functions ----------------------------------------------------------*/
/**
 * @brief ATIM��λ���Ĵ����ָ�ΪĬ��ֵ
 */
void ATIM_DeInit(void)
{
    CW_SYSCTRL->APBRST2_f.ATIM = 0;
    CW_SYSCTRL->APBRST2_f.ATIM = 1;
}


/**
 * @brief ATIM ��ʼ��
 * @param ATIM_InitStruct  ���ATIM_InitTypeDef�Ķ���
 */
void ATIM_Init(ATIM_InitTypeDef *ATIM_InitStruct)
{
    assert_param(IS_ATIM_COUNTING_DIRECTION(ATIM_InitStruct->CounterDirection));
    assert_param(IS_ATIM_OP_MODE(ATIM_InitStruct->CounterOPMode));
    assert_param(IS_ATIM_COUNT_MODE(ATIM_InitStruct->CounterAlignedMode));
    assert_param(IS_ATIM_PRESCALER(ATIM_InitStruct->Prescaler));
    assert_param(IS_ATIM_CLOCK(ATIM_InitStruct->ClockSelect));

    REGBITS_MODIFY(CW_ATIM->CR, ATIM_CR_DIR_Msk | ATIM_CR_ONESHOT_Msk |\
                                ATIM_CR_PRS_Msk | ATIM_CR_MODE_Msk |\
                                ATIM_CR_BUFPEN_Msk | ATIM_CR_CT_Msk \
                                ,\
                                ATIM_InitStruct->CounterDirection | ATIM_InitStruct->CounterOPMode |
                                ATIM_InitStruct->Prescaler | ATIM_InitStruct->CounterAlignedMode |
                                (ATIM_InitStruct->BufferState ? ATIM_BUFFER_ENABLE : ATIM_BUFFER_DISABLE) |
                                ATIM_InitStruct->ClockSelect);

    CW_ATIM->ARR = ATIM_InitStruct->ReloadValue;

    CW_ATIM->RCR = ATIM_InitStruct->RepetitionCounter | (ATIM_InitStruct->OverFlowMask? 1UL<<8 : 0) | \
                   (ATIM_InitStruct->UnderFlowMask ? 1UL<<9 : 0);
}


/**
 * @brief ATIM ����
 * 
 * @param NewState ENABLE or DISABLE
 */
void ATIM_Cmd(FunctionalState NewState)
{
    CW_ATIM->CR_f.EN = NewState;
}

/**
 * @brief ATIM�ж�����
 * @param ATIM_IT �ж�Դ
 * @param NewState ENABLE �� DISABLE
 */
void ATIM_ITConfig(uint32_t ATIM_IT, FunctionalState NewState)
{   
    if (NewState != DISABLE)
    {
        CW_ATIM->CR |= ATIM_IT;
    }
    else
    {
        CW_ATIM->CR &= ~ATIM_IT;
    }    
}

/**
 * @brief ��ȡATIM�жϱ�־λ
 * @param ATIM_IT �ж�Դ
 * @return ITStatus 
 */
ITStatus ATIM_GetITStatus(uint32_t ATIM_IT)
{
	return  (CW_ATIM->ISR & ATIM_IT) ? SET : RESET;
    
}

/**
 * @brief ���ATIM�жϱ�־λ
 */
void ATIM_ClearITPendingBit(uint32_t ATIM_IT)
{
    CW_ATIM->ICR = ~ATIM_IT;
}

/**
 * @brief ����ATIM����ֵ
 * @param Value 
 */
void ATIM_SetReloadValue(uint32_t Value)
{
    CW_ATIM->ARR = Value;
}

/**
 * @brief ����ͨ��1�Ĺ���
 * 
 * @param Function ATIM_CHxA_BUFF ATIM_CHxA_CIE ATIM_CHxA_CDE
 *                 ATIM_CHxB_BUFF ATIM_CHxB_CIE ATIM_CHxB_CDE
 * @param NewState ENABLE �� DISABLE
 */
void ATIM_CH1Config(uint32_t Function, FunctionalState NewState)
{
    if (NewState != DISABLE)
    {
        CW_ATIM->CH1CR |= Function;
    }
    else
    {
        CW_ATIM->CH1CR &= ~(Function);
    }
}

/**
 * @brief ����ͨ��2�Ĺ���
 * 
 * @param Function ATIM_CHxA_BUFF ATIM_CHxA_CIE ATIM_CHxA_CDE
 *                 ATIM_CHxB_BUFF ATIM_CHxB_CIE ATIM_CHxB_CDE
 * @param NewState ENABLE �� DISABLE
 */
void ATIM_CH2Config(uint32_t Function, FunctionalState NewState)
{
    if (NewState != DISABLE)
    {
        CW_ATIM->CH2CR |= Function;
    }
    else
    {
        CW_ATIM->CH2CR &= ~(Function);
    }
}

/**
 * @brief ����ͨ��3�Ĺ���
 * 
 * @param Function ATIM_CHxA_BUFF ATIM_CHxA_CIE ATIM_CHxA_CDE
 *                 ATIM_CHxB_BUFF ATIM_CHxB_CIE ATIM_CHxB_CDE
 * @param NewState ENABLE �� DISABLE
 */
void ATIM_CH3Config(uint32_t Function, FunctionalState NewState)
{
    if (NewState != DISABLE)
    {
        CW_ATIM->CH3CR |= Function;
    }
    else
    {
        CW_ATIM->CH3CR &= ~(Function);
    }
}

/**
 * @brief ����ͨ��4�Ĺ���
 * 
 * @param Function ATIM_CH4_BUFF ATIM_CH4_CIE ATIM_CH4_CDE *                 
 * @param NewState ENABLE �� DISABLE
 */
void ATIM_CH4Config(uint32_t Function, FunctionalState NewState)
{
    if (NewState != DISABLE)
    {
        CW_ATIM->CH4CR |= Function;
    }
    else
    {
        CW_ATIM->CH4CR &= ~(Function);
    }
}

/**
 * @brief ���벶��ͨ��1A����
 * @param ATIM_ICInitStruct 
 */
void ATIM_IC1AInit(ATIM_ICInitTypeDef* ATIM_ICInitStruct)
{
    assert_param(IS_ATIM_IC_POLARITY(ATIM_ICInitStruct->ICPolarity));
    assert_param(IS_ATIM_IC_FILTER(ATIM_ICInitStruct->ICFilter));
    REGBITS_MODIFY(CW_ATIM->CH1CR, (ATIM_CH1CR_BKSA_Msk | ATIM_CH1CR_CSA_Msk),
                   (ATIM_ICInitStruct->ICPolarity | ATIM_CH_A_IC));
    CW_ATIM->FLTR_f.OCM1AFLT1A = ATIM_ICInitStruct->ICFilter;
}

/**
 * @brief ���벶��ͨ��1B����
 * @param ATIM_ICInitStruct 
 */
void ATIM_IC1BInit(ATIM_ICInitTypeDef* ATIM_ICInitStruct)
{
    assert_param(IS_ATIM_IC_POLARITY(ATIM_ICInitStruct->ICPolarity));
    assert_param(IS_ATIM_IC_FILTER(ATIM_ICInitStruct->ICFilter));

    REGBITS_MODIFY(CW_ATIM->CH1CR, (ATIM_CH1CR_BKSB_Msk | ATIM_CH1CR_CSB_Msk),
                   (ATIM_ICInitStruct->ICPolarity << 2 | ATIM_CH_B_IC));    
    CW_ATIM->FLTR_f.OCM1BFLT1B = ATIM_ICInitStruct->ICFilter;
}


/**
 * @brief ���벶��ͨ��2A����
 * @param ATIM_ICInitStruct 
 */
void ATIM_IC2AInit(ATIM_ICInitTypeDef* ATIM_ICInitStruct)
{
    assert_param(IS_ATIM_IC_POLARITY(ATIM_ICInitStruct->ICPolarity));
    assert_param(IS_ATIM_IC_FILTER(ATIM_ICInitStruct->ICFilter));

    REGBITS_MODIFY(CW_ATIM->CH2CR, (ATIM_CH2CR_BKSA_Msk | ATIM_CH2CR_CSA_Msk),
                   (ATIM_ICInitStruct->ICPolarity | ATIM_CH_A_IC));    
    CW_ATIM->FLTR_f.OCM2AFLT2A = ATIM_ICInitStruct->ICFilter;
}

/**
 * @brief ���벶��ͨ��2B����
 * @param ATIM_ICInitStruct 
 */
void ATIM_IC2BInit(ATIM_ICInitTypeDef* ATIM_ICInitStruct)
{
    assert_param(IS_ATIM_IC_POLARITY(ATIM_ICInitStruct->ICPolarity));
    assert_param(IS_ATIM_IC_FILTER(ATIM_ICInitStruct->ICFilter));

    REGBITS_MODIFY(CW_ATIM->CH2CR, (ATIM_CH2CR_BKSB_Msk | ATIM_CH2CR_CSB_Msk),
                   (ATIM_ICInitStruct->ICPolarity << 2 | ATIM_CH_B_IC));   
    CW_ATIM->FLTR_f.OCM2BFLT2B = ATIM_ICInitStruct->ICFilter;
}

/**
 * @brief ���벶��ͨ��3A����
 * @param ATIM_ICInitStruct 
 */
void ATIM_IC3AInit(ATIM_ICInitTypeDef* ATIM_ICInitStruct)
{
    assert_param(IS_ATIM_IC_POLARITY(ATIM_ICInitStruct->ICPolarity));
    assert_param(IS_ATIM_IC_FILTER(ATIM_ICInitStruct->ICFilter));

    REGBITS_MODIFY(CW_ATIM->CH3CR, (ATIM_CH3CR_BKSA_Msk | ATIM_CH3CR_CSA_Msk),
                   (ATIM_ICInitStruct->ICPolarity | ATIM_CH_A_IC));
    CW_ATIM->FLTR_f.OCM3AFLT3A = ATIM_ICInitStruct->ICFilter;
}

/**
 * @brief ���벶��ͨ��3B����
 * @param ATIM_ICInitStruct 
 */
void ATIM_IC3BInit(ATIM_ICInitTypeDef* ATIM_ICInitStruct)
{
    assert_param(IS_ATIM_IC_POLARITY(ATIM_ICInitStruct->ICPolarity));
    assert_param(IS_ATIM_IC_FILTER(ATIM_ICInitStruct->ICFilter));

    REGBITS_MODIFY(CW_ATIM->CH3CR, (ATIM_CH3CR_BKSB_Msk | ATIM_CH3CR_CSB_Msk),
                   (ATIM_ICInitStruct->ICPolarity << 2 | ATIM_CH_B_IC));   
    CW_ATIM->FLTR_f.OCM3BFLT3B = ATIM_ICInitStruct->ICFilter;
}

/**
 * @brief CH1A�Ƚ��������
 * @param ATIM_OCInitStruct 
 */
void ATIM_OC1AInit(ATIM_OCInitTypeDef * ATIM_OCInitStruct)
{
    assert_param(IS_ATIM_OC_MODE(ATIM_OCInitStruct->OCMode));
    assert_param(IS_ATIM_OC_POLARITY(ATIM_OCInitStruct->OCPolarity));
    assert_param(IS_ATIM_OC_IT(ATIM_OCInitStruct->OCInterruptSelect));
    assert_param(IS_FUNCTIONAL_STATE(ATIM_OCInitStruct->BufferState));
    assert_param(IS_FUNCTIONAL_STATE(ATIM_OCInitStruct->OCDMAState));
    assert_param(IS_FUNCTIONAL_STATE(ATIM_OCInitStruct->OCInterruptState));

    REGBITS_MODIFY(CW_ATIM->FLTR, ATIM_FLTR_OCM1AFLT1A_Msk | ATIM_FLTR_CCP1A_Msk, 
                   ATIM_OCInitStruct->OCMode | (ATIM_OCInitStruct->OCPolarity << 3));    
    CW_ATIM->CR_f.CISA = ATIM_OCInitStruct->OCInterruptSelect << 21;
    REGBITS_MODIFY(CW_ATIM->CH1CR,  ATIM_CH1CR_BUFEA_Msk | ATIM_CH1CR_CDEA_Msk | ATIM_CH1CR_CIEA_Msk,
                   (ATIM_OCInitStruct->BufferState ? ATIM_CH1CR_BUFEA_Msk:0)|\
                   (ATIM_OCInitStruct->OCDMAState ? ATIM_CH1CR_CDEA_Msk:0) |\
                   (ATIM_OCInitStruct->OCInterruptState ? ATIM_CH1CR_CIEA_Msk:0));  
} 

/**
 * @brief CH1B�Ƚ��������
 * @param ATIM_OCInitStruct 
 */
void ATIM_OC1BInit(ATIM_OCInitTypeDef * ATIM_OCInitStruct)
{
    assert_param(IS_ATIM_OC_MODE(ATIM_OCInitStruct->OCMode));
    assert_param(IS_ATIM_OC_POLARITY(ATIM_OCInitStruct->OCPolarity));
    assert_param(IS_ATIM_OC_IT(ATIM_OCInitStruct->OCInterruptSelect));
    assert_param(IS_FUNCTIONAL_STATE(ATIM_OCInitStruct->BufferState));
    assert_param(IS_FUNCTIONAL_STATE(ATIM_OCInitStruct->OCDMAState));
    assert_param(IS_FUNCTIONAL_STATE(ATIM_OCInitStruct->OCInterruptState));

    REGBITS_MODIFY(CW_ATIM->FLTR, ATIM_FLTR_OCM1BFLT1B_Msk | ATIM_FLTR_CCP1B_Msk,
                   (ATIM_OCInitStruct->OCMode << 4) | (ATIM_OCInitStruct->OCPolarity << 7));

    
    REGBITS_MODIFY(CW_ATIM->CH1CR, ATIM_CH1CR_CISB_Msk | ATIM_CH1CR_BUFEB_Msk | ATIM_CH1CR_CDEB_Msk | ATIM_CH1CR_CIEB_Msk,
                   (ATIM_OCInitStruct->OCInterruptSelect << 12) | \
                   (ATIM_OCInitStruct->BufferState ? ATIM_CH1CR_BUFEB_Msk:0)|\
                   (ATIM_OCInitStruct->OCDMAState ? ATIM_CH1CR_CDEB_Msk:0) |\
                   (ATIM_OCInitStruct->OCInterruptState ? ATIM_CH1CR_CIEB_Msk:0));
} 
   
/**
 * @brief CH2A�Ƚ��������
 * @param ATIM_OCInitStruct 
 */
void ATIM_OC2AInit(ATIM_OCInitTypeDef * ATIM_OCInitStruct)
{
    assert_param(IS_ATIM_OC_MODE(ATIM_OCInitStruct->OCMode));
    assert_param(IS_ATIM_OC_POLARITY(ATIM_OCInitStruct->OCPolarity));

    REGBITS_MODIFY(CW_ATIM->FLTR, ATIM_FLTR_OCM2AFLT2A_Msk | ATIM_FLTR_CCP2A_Msk,
                   (ATIM_OCInitStruct->OCMode << 8) | (ATIM_OCInitStruct->OCPolarity << 11));
     
    CW_ATIM->CR_f.CISA = ATIM_OCInitStruct->OCInterruptSelect << 21;
    REGBITS_MODIFY(CW_ATIM->CH2CR,  ATIM_CH2CR_BUFEA_Msk | ATIM_CH2CR_CDEA_Msk | ATIM_CH2CR_CIEA_Msk,
                   (ATIM_OCInitStruct->BufferState ? ATIM_CH2CR_BUFEA_Msk:0)|\
                   (ATIM_OCInitStruct->OCDMAState ? ATIM_CH2CR_CDEA_Msk:0) |\
                   (ATIM_OCInitStruct->OCInterruptState ? ATIM_CH2CR_CIEA_Msk:0)); 
} 

/**
 * @brief CH2B�Ƚ��������
 * @param ATIM_OCInitStruct 
 */
void ATIM_OC2BInit(ATIM_OCInitTypeDef * ATIM_OCInitStruct)
{
    assert_param(IS_ATIM_OC_MODE(ATIM_OCInitStruct->OCMode));
    assert_param(IS_ATIM_OC_POLARITY(ATIM_OCInitStruct->OCPolarity));
    assert_param(IS_ATIM_OC_IT(ATIM_OCInitStruct->OCInterruptSelect));
    assert_param(IS_FUNCTIONAL_STATE(ATIM_OCInitStruct->BufferState));
    assert_param(IS_FUNCTIONAL_STATE(ATIM_OCInitStruct->OCDMAState));
    assert_param(IS_FUNCTIONAL_STATE(ATIM_OCInitStruct->OCInterruptState));

    REGBITS_MODIFY(CW_ATIM->FLTR, ATIM_FLTR_OCM2BFLT2B_Msk | ATIM_FLTR_CCP2B_Msk,
                   (ATIM_OCInitStruct->OCMode << 12) | (ATIM_OCInitStruct->OCPolarity << 15));

    REGBITS_MODIFY(CW_ATIM->CH2CR, ATIM_CH2CR_CISB_Msk | ATIM_CH2CR_BUFEB_Msk | ATIM_CH2CR_CDEB_Msk | ATIM_CH1CR_CIEB_Msk,
                   (ATIM_OCInitStruct->OCInterruptSelect << 12) | \
                   (ATIM_OCInitStruct->BufferState ? ATIM_CH2CR_BUFEB_Msk:0)|\
                   (ATIM_OCInitStruct->OCDMAState ? ATIM_CH2CR_CDEB_Msk:0) |\
                   (ATIM_OCInitStruct->OCInterruptState ? ATIM_CH2CR_CIEB_Msk:0));
} 

/**
 * @brief CH3A�Ƚ��������
 * @param ATIM_OCInitStruct 
 */
void ATIM_OC3AInit(ATIM_OCInitTypeDef * ATIM_OCInitStruct)
{
    assert_param(IS_ATIM_OC_MODE(ATIM_OCInitStruct->OCMode));
    assert_param(IS_ATIM_OC_POLARITY(ATIM_OCInitStruct->OCPolarity));
    assert_param(IS_ATIM_OC_IT(ATIM_OCInitStruct->OCInterruptSelect));
    assert_param(IS_FUNCTIONAL_STATE(ATIM_OCInitStruct->BufferState));
    assert_param(IS_FUNCTIONAL_STATE(ATIM_OCInitStruct->OCDMAState));
    assert_param(IS_FUNCTIONAL_STATE(ATIM_OCInitStruct->OCInterruptState));

    REGBITS_MODIFY(CW_ATIM->FLTR, ATIM_FLTR_OCM3AFLT3A_Msk | ATIM_FLTR_CCP3A_Msk,
                   (ATIM_OCInitStruct->OCMode << 16) | (ATIM_OCInitStruct->OCPolarity << 19));

    CW_ATIM->CR_f.CISA = ATIM_OCInitStruct->OCInterruptSelect << 21;
    REGBITS_MODIFY(CW_ATIM->CH3CR,  ATIM_CH3CR_BUFEA_Msk | ATIM_CH3CR_CDEA_Msk | ATIM_CH3CR_CIEA_Msk,
                   (ATIM_OCInitStruct->BufferState ? ATIM_CH3CR_BUFEA_Msk:0)|\
                   (ATIM_OCInitStruct->OCDMAState ? ATIM_CH3CR_CDEA_Msk:0) |\
                   (ATIM_OCInitStruct->OCInterruptState ? ATIM_CH3CR_CIEA_Msk:0));  
} 

/**
 * @brief CH3B�Ƚ��������
 * @param ATIM_OCInitStruct 
 */
void ATIM_OC3BInit(ATIM_OCInitTypeDef * ATIM_OCInitStruct)
{
    assert_param(IS_ATIM_OC_MODE(ATIM_OCInitStruct->OCMode));
    assert_param(IS_ATIM_OC_POLARITY(ATIM_OCInitStruct->OCPolarity));
    assert_param(IS_ATIM_OC_IT(ATIM_OCInitStruct->OCInterruptSelect));
    assert_param(IS_FUNCTIONAL_STATE(ATIM_OCInitStruct->BufferState));
    assert_param(IS_FUNCTIONAL_STATE(ATIM_OCInitStruct->OCDMAState));
    assert_param(IS_FUNCTIONAL_STATE(ATIM_OCInitStruct->OCInterruptState));

    REGBITS_MODIFY(CW_ATIM->FLTR, ATIM_FLTR_OCM3BFLT3B_Msk | ATIM_FLTR_CCP3B_Msk,
                   (ATIM_OCInitStruct->OCMode << 20) | (ATIM_OCInitStruct->OCPolarity << 23));

    REGBITS_MODIFY(CW_ATIM->CH3CR, ATIM_CH3CR_CISB_Msk | ATIM_CH3CR_BUFEB_Msk | ATIM_CH3CR_CDEB_Msk | ATIM_CH1CR_CIEB_Msk,
                   (ATIM_OCInitStruct->OCInterruptSelect << 12) | \
                   (ATIM_OCInitStruct->BufferState ? ATIM_CH3CR_BUFEB_Msk:0)|\
                   (ATIM_OCInitStruct->OCDMAState ? ATIM_CH3CR_CDEB_Msk:0) |\
                   (ATIM_OCInitStruct->OCInterruptState ? ATIM_CH3CR_CIEB_Msk:0));
}


/**
 * @brief ͨ��4�ıȽ�����
 * @param NewState ͨ���Ƚ�ʹ��
 * @param ITSelect �жϲ�������ѡ�񣬲���Ϊ���в���֮һ
 *        @arg ATIM_OC_IT_NONE
 *        @arg ATIM_OC_IT_UP_COUNTER
 *        @arg ATIM_OC_IT_DOWN_COUNTER
 *        @arg ATIM_OC_IT_BOTH_COUNTER
 * @param DMAState �Ƚϴ���DMAʹ��
 * @param ITState �Ƚϴ����ж�ʹ��
 * @param BufferState �Ƚϻ���ʹ�ܿ���
 */
void ATIM_OC4Init(FunctionalState NewState, uint32_t ITSelect, FunctionalState DMAState,
                        FunctionalState ITState, FunctionalState BufferState)
{
    assert_param(IS_ATIM_OC_IT(ITSelect));

    CW_ATIM->CH4CR = (NewState ? 1UL << 5 :0 ) | (ITSelect << 3) | (DMAState ? 1UL << 2 : 0) | \
                     (ITState ? 1UL << 1 : 0) | (BufferState ? 1 : 0);

}

/**
 * @brief ����PWM����Ĳ���
 * 
 * @param OCREFAType �Ƚ���A����Ƚϻ�˫��Ƚ� OCREFA_TYPE_SINGLE OCREFA_TYPE_DOUBLE
 * @param OutputType PWM������Ͷ����򻥲� OUTPUT_TYPE_ALONE OUTPUT_TYPE_COMP
 * @param Deadtime ����ʱ�䣬��λΪ��ʱ���ļ���ʱ϶��-1����ֹ�� 0~0xFF�����������ʱ϶
 *                 ȡֵ��Χ��
 */
void ATIM_PWMOutputConfig(uint32_t OCREFAType, uint32_t OutputType, int16_t Deadtime)
{
    assert_param(IS_ATIM_OCREFA_TYPE(OCREFAType));
    assert_param(IS_ATIM_OUTPUT_TYPE(OutputType));
    assert_param(IS_ATIM_DEADTIME(Deadtime));

    REGBITS_MODIFY(CW_ATIM->CR, ATIM_CR_COMP_Msk | ATIM_CR_PWM2S_Msk, OCREFAType | OutputType);
    if (Deadtime >= 0 )
    {
        CW_ATIM->DTR_f.DTEN = 1;
        CW_ATIM->DTR_f.DTR = Deadtime;
    }
    else
    {
        CW_ATIM->DTR_f.DTEN = 0;
    }
}

void ATIM_CtrlPWMOutputs(FunctionalState NewState)
{
    assert_param(IS_FUNCTIONAL_STATE(NewState));

    CW_ATIM->DTR_f.MOE = NewState;
}

/**
 * @brief �����ⲿ��������
 * @param ATIM_ETRPolarity �ⲿ�����ź���Ч���� ����Ϊ���в���֮һ��
 *        @arg ATIM_ETR_POLARITY_NONINVERT: ͬ��
 *        @arg ATIM_ETR_POLARITY_INVERT: ����
 * @param ETRFilter �ⲿ����ͨ�����˲����� ����Ϊ���в���֮һ��
 *        @arg ATIM_ETR_FILTER_NONE: ���˲�
 *        @arg ATIM_ETR_FILTER_PCLK_N3: PCLKʱ�Ӳ�����3��������Ч
 *        @arg ATIM_ETR_FILTER_PCLKDIV4_N3: PCLK/4ʱ�Ӳ�����3��������Ч
 *        @arg ATIM_ETR_FILTER_PCLKDIV16_N3: PCLK/16ʱ�Ӳ�����3��������Ч
 *        @arg ATIM_ETR_FILTER_PCLKDIV64_N3: PCLK/64ʱ�Ӳ�����3��������Ч
 */
void ATIM_ETRConfig(uint32_t ATIM_ETRPolarity, uint32_t ATIM_ETRFilter)
{
    assert_param(IS_ATIM_ETR_POLARITY(ATIM_ETRPolarity));
    assert_param(IS_ATIM_ETR_FILTER(ATIM_ETRFilter));

    REGBITS_MODIFY(CW_ATIM->FLTR,
                   ATIM_FLTR_ETP_Msk | ATIM_FLTR_FLTET_Msk,
                   ATIM_ETRPolarity | ATIM_ETRFilter);
}

/**
 * @brief ����Brake�����źŵĲ���
 * @param ATIM_BrakePolarity �źż��ԣ�����Ϊ���в���֮һ��
 *        @arg ATIM_BRAKE_POLARITY_NONINVERT: ͬ��
 *        @arg ATIM_BRAKE_POLARITY_INVERT: ����
 * @param ATIM_BrakeFilter
 *        @arg ATIM_BRAKE_FILTER_NONE: ���˲�
 *        @arg ATIM_BRAKE_FILTER_PCLK_N3: PCLKʱ�Ӳ�����3��������Ч
 *        @arg ATIM_BRAKE_FILTER_PCLKDIV4_N3: PCLK/4ʱ�Ӳ�����3��������Ч
 *        @arg ATIM_BRAKE_FILTER_PCLKDIV16_N3: PCLK/16ʱ�Ӳ�����3��������Ч
 *        @arg ATIM_BRAKE_FILTER_PCLKDIV64_N3: PCLK/64ʱ�Ӳ�����3��������Ч 
 */
void ATIM_BrakeConfig(uint32_t ATIM_BrakePolarity, uint32_t ATIM_BrakeFilter)
{
    assert_param(IS_ATIM_BRAKE_POLARITY(ATIM_BrakePolarity));
    assert_param(IS_ATIM_BRAKE_FILTER(ATIM_BrakeFilter));

    REGBITS_MODIFY(CW_ATIM->FLTR,
                   ATIM_FLTR_BKP_Msk | ATIM_FLTR_FLTBK_Msk,
                   ATIM_BrakePolarity | ATIM_BrakeFilter);
}

/**
 * @brief ����ATIM����ADC�Ĳ����Ĵ���Դ
 * @param ATIM_ADCTriggerSource ����Ϊ���в���֮һ
 *        @arg ATIM_ADC_TRIGGER_CH3B
 *        @arg ATIM_ADC_TRIGGER_CH2B
 *        @arg ATIM_ADC_TRIGGER_CH1B
 *        @arg ATIM_ADC_TRIGGER_CH3A
 *        @arg ATIM_ADC_TRIGGER_CH2A
 *        @arg ATIM_ADC_TRIGGER_CH1A
 *        @arg ATIM_ADC_TRIGGER_UPDATA_EVENT
 * @param NewState DISABLE��ENABLE
 */
void ATIM_ADCTriggerConfig(uint32_t ATIM_ADCTriggerSource, FunctionalState NewState)
{
    assert_param(IS_ATIM_ADC_TRIGGER(ATIM_ADCTriggerSource));
    assert_param(IS_FUNCTIONAL_STATE(NewState));

    if (NewState != DISABLE)
    {

        CW_ATIM->TRIG |= (ATIM_ADCTriggerSource | ATIM_ADC_TRIGGER_GLOBAL);
    }
    else
    {
        CW_ATIM->TRIG &= ~ATIM_ADCTriggerSource;
    }    
}

uint16_t ATIM_GetCapture1A(void)
{
    return (uint16_t) CW_ATIM->CH1CCRA;
}


uint16_t ATIM_GetCapture2A(void)
{
    return (uint16_t) CW_ATIM->CH2CCRA;
}


uint16_t ATIM_GetCapture3A(void)
{
    return (uint16_t) CW_ATIM->CH3CCRA;
}


uint16_t ATIM_GetCapture1B(void)
{
    return (uint16_t) CW_ATIM->CH1CCRB;
}


uint16_t ATIM_GetCapture2B(void)
{
    return (uint16_t) CW_ATIM->CH2CCRB;
}


uint16_t ATIM_GetCapture3B(void)
{
    return (uint16_t) CW_ATIM->CH3CCRB;
}


void ATIM_SetCompare1A(uint16_t Compare)
{
    CW_ATIM->CH1CCRA = (uint32_t)Compare;
}

void ATIM_SetCompare2A(uint16_t Compare)
{
    CW_ATIM->CH2CCRA = (uint32_t)Compare;
}

void ATIM_SetCompare3A(uint16_t Compare)
{
    CW_ATIM->CH3CCRA = (uint32_t)Compare;
}

void ATIM_SetCompare1B(uint16_t Compare)
{
    CW_ATIM->CH1CCRB = (uint32_t)Compare;
}

void ATIM_SetCompare2B(uint16_t Compare)
{
    CW_ATIM->CH2CCRB = (uint32_t)Compare;
}

void ATIM_SetCompare3B(uint16_t Compare)
{
    CW_ATIM->CH3CCRB = (uint32_t)Compare;
}

void ATIM_SetCompare4(uint16_t Compare)
{
    CW_ATIM->CH4CCR = (uint32_t) Compare;
}

void ATIM_MasterModeConfig(uint8_t ATIM_MasterOutput)
{
    assert_param(IS_ATIM_MASTER_OUTPUT(ATIM_MasterOutput));

    CW_ATIM->MSCR_f.MMS = ATIM_MasterOutput;
}

void ATIM_SlaverModeConfig(uint8_t ATIM_SlaverType)
{
    assert_param(IS_ATIM_SLAVER_TYPE(ATIM_SlaverType));

    CW_ATIM->MSCR_f.SMS = ATIM_SlaverType;
}

void ATIM_TriggerSelect(uint8_t ATIM_TriggerSource)
{
    assert_param(IS_ATIM_TRIGGER_SOURCE(ATIM_TriggerSource));

    CW_ATIM->MSCR_f.TS = ATIM_TriggerSource;
}

void ATIM_UpdateEventSelect(uint8_t ATIM_UpdateEvent)
{
    assert_param(IS_ATIM_UPDATE_EVENT(ATIM_UpdateEvent));

    CW_ATIM->CR_f.URS = ATIM_UpdateEvent;
}
