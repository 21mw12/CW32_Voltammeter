/**
 * @file cw32f030_adc.c
 * @author P&S (you@domain.com)
 * @brief
 * @version 0.1
 * @file cw32f030_adc.c
 * @author P&S (you@domain.com)
 * @brief
 * @version 0.1
 * @date 2021-07-12
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

/******************************************************************************
 * Include files
 ******************************************************************************/
#include "cw32f030.h"
#include "cw32f030_adc.h"

/**
 ******************************************************************************
 ** \addtogroup AdcGroup
 ******************************************************************************/
//@{
/******************************************************************************
 * Local pre-processor symbols/macros ('#define')
 ******************************************************************************/

/******************************************************************************
 * Global variable definitions (declared in header file with 'extern')
 ******************************************************************************/

/******************************************************************************
 * Local type definitions ('typedef')
 ******************************************************************************/

/******************************************************************************
 * Local function prototypes ('static')
 ******************************************************************************/

/******************************************************************************
 * Local variable definitions ('static')
 ******************************************************************************/

/*****************************************************************************
 * Function implementation - global ('extern') and local ('static')
 *****************************************************************************/

/**
 * @brief   
 *          ��ȡADC�����ж�״̬
 *
 * @param   pFlagAdcIrq
 */
void ADC_GetITStatusAll(volatile uint8_t* pFlagAdcIrq)
{
	*pFlagAdcIrq = (uint8_t) (CW_ADC->ISR);
}

/**
 * @brief
 *          ��ȡADCָ�����ж�״̬
 *
 * @param   ADC_IT:
 *          @arg ADC_IT_READY
 *          @arg ADC_IT_OVW
 *          @arg ADC_IT_WDTR
 *          @arg ADC_IT_WDTH
 *          @arg ADC_IT_WDTL
 *          @arg ADC_IT_EOA
 *          @arg ADC_IT_EOS
 *          @arg ADC_IT_EOC
 *
 * @return  ITStatus: SET or RESET
 */
ITStatus ADC_GetITStatus(uint16_t ADC_IT)
{
	assert_param(IS_ADC_GET_IT(IT)(ADC_IT));
	return (REGBITS_GET(CW_ADC->ISR, ADC_IT) ? SET : RESET);
}

/**
 * @brief
 *          ���ADC�����ж�״̬
 */
void ADC_ClearITPendingAll(void)
{
	REGBITS_CLR(CW_ADC->ICR,
			(ADC_ISR_OVW_Msk | ADC_ISR_WDTR_Msk |\
            ADC_ISR_WDTH_Msk | ADC_ISR_WDTL_Msk | ADC_ISR_EOA_Msk |\
            ADC_ISR_EOS_Msk | ADC_ISR_EOC_Msk));
}

/**
 * @brief
 *          ���ADCָ�����ж�״̬
 *
 * @param   ADC_IT
 *          @arg ADC_IT_OVW
 *          @arg ADC_IT_WDTR
 *          @arg ADC_IT_WDTH
 *          @arg ADC_IT_WDTL
 *          @arg ADC_IT_EOA
 *          @arg ADC_IT_EOS
 *          @arg ADC_IT_EOC
 */
void ADC_ClearITPendingBit(uint16_t ADC_IT)
{
	assert_param(IS_ADC_GET_IT(IT)(ADC_IT));
	REGBITS_CLR(CW_ADC->ICR, ADC_IT);
}

/**
 * @brief
 *          ADC�ж�ʹ��
 *
 * @param   intPriority
 */
void ADC_EnableIrq(uint8_t intPriority)
{
	ADC_EnableNvic(intPriority);
}

/**
 * @brief   
 *          ADC�жϽ�ֹ
 */
void ADC_DisableIrq(void)
{
	REGBITS_CLR(CW_ADC->IER,
			ADC_IER_OVW_Msk | ADC_IER_WDTR_Msk | ADC_IER_WDTH_Msk |\
			ADC_IER_WDTL_Msk | ADC_IER_EOA_Msk | ADC_IER_EOS_Msk |\
			ADC_IER_EOC_Msk);
	ADC_DisableNvic();
}

/**
 * @brief
 *          ADCģ�⿴�Ź�����
 *
 * @param   ADC_WdtStruct
 */
void ADC_WdtConfig(ADC_WdtTypeDef *ADC_WdtStruct)
{
    ASSERT(NULL != ADC_WdtStruct);
    assert_param(IS_ADC_WDT_CH(ADC_WdtStruct->ADC_WdtCh ));
    assert_param(IS_ADC_WDT_EN(ADC_WdtStruct->ADC_WdtAll ));
    assert_param(IS_ADC_WDTR_EN(ADC_WdtStruct->ADC_WdtrIrq ));
    assert_param(IS_ADC_WDTH_EN(ADC_WdtStruct->ADC_WdthIrq ));
    assert_param(IS_ADC_WDTL_EN(ADC_WdtStruct->ADC_WdtlIrq ));

	//����ͨ��ģ�⿴�Ź�ʹ�ܿ���
	//��ֵ�Ƚ�ͨ��ѡ��
	REGBITS_MODIFY(CW_ADC->CR1, ADC_CR1_WDTALL_Msk | ADC_CR1_WDTCH_Msk,
			ADC_WdtStruct->ADC_WdtAll |\
            ADC_WdtStruct->ADC_WdtCh);

	REGBITS_MODIFY(CW_ADC->IER,
			ADC_IER_WDTR_Msk | ADC_IER_WDTH_Msk | ADC_IER_WDTL_Msk,
			ADC_WdtStruct->ADC_WdtrIrq |\
            ADC_WdtStruct->ADC_WdthIrq |\
            ADC_WdtStruct->ADC_WdtlIrq);
	CW_ADC->VTH = ADC_WdtStruct->ADC_Vth;              //ģ�⿴�Ź�������ֵ
	CW_ADC->VTL = ADC_WdtStruct->ADC_Vtl;              //ģ�⿴�Ź�������ֵ

	if (ADC_WdtStruct->ADC_WdtCh == ADC_WdtVref1P2)
	{
		REGBITS_SET(CW_ADC->CR0, ADC_CR0_BGREN_Msk);
	}
}

/**
 * @brief   
 *          ADC��ʼ��
 *
 * @param   ADC_InitStruct
 */
void ADC_Init(ADC_InitTypeDef *ADC_InitStruct)
{
    ASSERT(NULL != ADC_InitStruct);
    assert_param(IS_ADC_OP_MODE(ADC_InitStruct->ADC_OpMode ));
    assert_param(IS_ADC_CLK_DIV(ADC_InitStruct->ADC_ClkDiv ));
    assert_param(IS_ADC_SAMPLE_TIME(ADC_InitStruct->ADC_SampleTime ));
    assert_param(IS_ADC_VREF_SEL(ADC_InitStruct->ADC_VrefSel ));
    assert_param(IS_ADC_BUF_ENABLE(ADC_InitStruct->ADC_InBufEn ));
    assert_param(IS_ADC_TS_ENABLE(ADC_InitStruct->ADC_TsEn ));
    assert_param(IS_ADC_DMA_ENABLE(ADC_InitStruct->ADC_DMAEn ));
    assert_param(IS_ADC_DATA_ALIGN(ADC_InitStruct->ADC_Align ));
    assert_param(IS_ADC_ACC_ENABLE(ADC_InitStruct->ADC_AccEn ));

/*	if (NULL == ADC_InitStruct)
	{
		return;
	}*/

	REGBITS_MODIFY(CW_ADC->CR0,
			ADC_CR0_BUF_Msk | ADC_CR0_SAM_Msk | ADC_CR0_CLK_Msk |\
            ADC_CR0_REF_Msk | ADC_CR0_TSEN_Msk | ADC_CR0_MODE_Msk,
			ADC_InitStruct->ADC_InBufEn |\
            ADC_InitStruct->ADC_SampleTime |\
            ADC_InitStruct->ADC_ClkDiv |\
            ADC_InitStruct->ADC_VrefSel |\
            ADC_InitStruct->ADC_TsEn |\
            ADC_InitStruct->ADC_OpMode);

	REGBITS_MODIFY(CW_ADC->CR1, ADC_CR1_DMAEN_Msk | ADC_CR1_ALIGN_Msk,
			ADC_InitStruct->ADC_DMAEn |\
            ADC_InitStruct->ADC_Align);

	if (ADC_InitStruct->ADC_AccEn)
	{
		REGBITS_MODIFY(CW_ADC->CR2, ADC_CR2_ACCEN_Msk | ADC_CR2_ACCRST_Msk,
				ADC_InitStruct->ADC_AccEn |\
                1u << ADC_CR2_ACCRST_Pos);
	}
}

/**
 * @brief 
 *        ADCĬ��ֵ��ʼ��
 * 
 * @param ADC_InitStruct 
 */
void ADC_StructInit(ADC_InitTypeDef *ADC_InitStruct)
{
	/* Reset ADC init structure parameters values */
	ADC_InitStruct->ADC_OpMode = ADC_SingleChOneMode; //��ͨ������ת��ģʽ
	ADC_InitStruct->ADC_ClkDiv = ADC_Clk_Div1; //PCLK
	ADC_InitStruct->ADC_SampleTime = ADC_SampTime5Clk; //5��ADCʱ������
	ADC_InitStruct->ADC_VrefSel = ADC_Vref_VDDA; //VDDA�ο���ѹ
	ADC_InitStruct->ADC_InBufEn = ADC_BufDisable; //�رո�����
	ADC_InitStruct->ADC_TsEn = ADC_TsDisable; //�ر������¶ȴ�����
	ADC_InitStruct->ADC_DMAEn = ADC_DmaDisable; //������DMA
	ADC_InitStruct->ADC_Align = ADC_AlignRight; //ADCת������Ҷ���
	ADC_InitStruct->ADC_AccEn = ADC_AccDisable; //ת������ۼӲ�ʹ��
}

/**
 * @brief
 *        ADCģ�⿴�Ź�Ĭ��ֵ��ʼ��
 * 
 * @param ADC_WdtStruct 
 */
void ADC_WdtInit(ADC_WdtTypeDef *ADC_WdtStruct)
{
	ADC_WdtStruct->ADC_WdtCh = ADC_WdtCh0;
	ADC_WdtStruct->ADC_WdtAll = ADC_WdtDisable;
	ADC_WdtStruct->ADC_WdtrIrq = ADC_WdtrDisable;
	ADC_WdtStruct->ADC_WdthIrq = ADC_WdthDisable;
	ADC_WdtStruct->ADC_WdtlIrq = ADC_WdtlDisable;
	ADC_WdtStruct->ADC_Vth = 0x0FFF;
	ADC_WdtStruct->ADC_Vtl = 0x00;
}

/**
 * @brief 
 *        ADC�ⲿ�жϴ���Դ����
 * 
 * @param ADC_TRIG:
 *        @arg ADC_TRIG_DMA
 *        @arg ADC_TRIG_I2C2
 *        @arg ADC_TRIG_I2C1
 *        @arg ADC_TRIG_SPI2
 *        @arg ADC_TRIG_SPI1
 *        @arg ADC_TRIG_UART3
 *        @arg ADC_TRIG_UART2
 *        @arg ADC_TRIG_UART1
 *        @arg ADC_TRIG_BTIM3
 *        @arg ADC_TRIG_BTIM2
 *        @arg ADC_TRIG_BTIM1
 *        @arg ADC_TRIG_GTIM4
 *        @arg ADC_TRIG_GTIM3
 *        @arg ADC_TRIG_GTIM2
 *        @arg ADC_TRIG_GTIM1
 *        @arg ADC_TRIG_ATIM
 * @param NewState:
 *        @arg DISABLE
 *        @arg ENABLE
 */
void ADC_ExtTrigCfg(uint16_t ADC_TRIG, FunctionalState NewState)
{
	uint16_t trigMask = 0;
	/* Check the parameters */
	assert_param(IS_FUNCTIONAL_STATE(NewState));
	assert_param(IS_ADC_TRIG(ADC_TRIG));
	/* Get the ADC TRIG index */
	trigMask = ADC_TRIG;
	if (NewState != DISABLE)
	{
		/* Enable the selected ADC interrupts */
		CW_ADC->TRIGGER |= trigMask;
	}
	else
	{
		/* Disable the selected ADC interrupts */
		CW_ADC->TRIGGER &= (~(uint32_t) trigMask);
	}
}

/**
 * @brief   
 *          ADCȥ��ʼ��
 */
void ADC_DeInit(void)
{
	// Enable ADC reset state
	REGBITS_CLR(CW_SYSCTRL->APBRST2, SYSCTRL_APBRST2_ADC_Msk);
	// Release ADC from reset state
	REGBITS_SET(CW_SYSCTRL->APBRST2, SYSCTRL_APBRST2_ADC_Msk);
}

/**
 * @brief 
 *        ADCת�������������
 * 
 * @param NewState
 *        @arg DISABLE
 *        @arg ENABLE
 */
void ADC_SoftwareStartConvCmd(FunctionalState NewState)
{
	/* Check the parameters */
	assert_param(IS_FUNCTIONAL_STATE(NewState));
	if (NewState != DISABLE)
	{
		REGBITS_SET(CW_ADC->START, ADC_START_START_Msk);
	}
	else
	{
		REGBITS_CLR(CW_ADC->START, ADC_START_START_Msk);
	}
}

/**
 * @brief   
 *          ADCʹ��
 */
void ADC_Enable(void)
{
	REGBITS_SET(CW_ADC->CR0, ADC_CR0_EN_Msk);
	//�ȴ� ADC ģ���������
	while (!ADC_GetITStatus(ADC_IT_READY));
}

/**
 * @brief   
 *          ADC����
 */
void ADC_Disable(void)
{
	REGBITS_CLR(CW_ADC->CR0, ADC_CR0_EN_Msk);
}

/**
 * @brief   
 *          ��ͨ��ת��ģʽ��������
 *
 * @param   ADC_SingleChStruct
 */
void ADC_SingleChCommon(ADC_SingleChTypeDef *ADC_SingleChStruct)
{
    ASSERT(NULL != ADC_SingleChStruct);
    assert_param(IS_ADC_CH_SEL(ADC_SingleChStruct->ADC_Chmux ));
    assert_param(IS_ADC_DATA_DISCARD(ADC_SingleChStruct->ADC_DiscardEn ));

/*	if (NULL == ADC_SingleChStruct)
	{
		return;
	}*/

	ADC_Init(&ADC_SingleChStruct->ADC_InitStruct);
	ADC_BufEnSingleCh(ADC_SingleChStruct->ADC_Chmux);
	if (ADC_SingleChStruct->ADC_WdtStruct.ADC_WdtAll == ADC_WdtEnable)
	{
		ADC_WdtConfig(&ADC_SingleChStruct->ADC_WdtStruct);
	}

	REGBITS_MODIFY(CW_ADC->CR1, ADC_CR1_DISCARD_Msk | ADC_CR1_CHMUX_Msk,
			ADC_SingleChStruct->ADC_DiscardEn |\
            ADC_SingleChStruct->ADC_Chmux);
}

/**
 * @brief
 *        ADC��ͨ������ת��ģʽ����
 * 
 * @param ADC_SingleChStruct 
 */
void ADC_SingleChOneModeCfg(ADC_SingleChTypeDef *ADC_SingleChStruct)
{
	ADC_SingleChCommon(ADC_SingleChStruct);
	REGBITS_MODIFY(CW_ADC->CR0, ADC_CR0_MODE_Msk, ADC_SingleChOneMode);
}

/**
 * @brief 
 *        ADC��ͨ�����ת��ģʽ����
 * 
 * @param ADC_SingleChStruct 
 * @param cntAdcSample: 0 ~ 255
 */
void ADC_SingleChMoreModeCfg(ADC_SingleChTypeDef *ADC_SingleChStruct,
		uint8_t cntAdcSample)
{
	ADC_SingleChStruct->ADC_InitStruct.ADC_AccEn = ADC_AccEnable;	//Must be added

	ADC_SingleChCommon(ADC_SingleChStruct);
	REGBITS_MODIFY(CW_ADC->CR0, ADC_CR0_MODE_Msk, ADC_SingleChMoreMode);
	CW_ADC->CR2_f.CNT = cntAdcSample;
}

/**
 * @brief
 *        ADC��ͨ������ת��ģʽ����
 * 
 * @param ADC_SingleChStruct 
 */
void ADC_SingleChContinuousModeCfg(ADC_SingleChTypeDef *ADC_SingleChStruct)
{
	ADC_SingleChCommon(ADC_SingleChStruct);
	REGBITS_MODIFY(CW_ADC->CR0, ADC_CR0_MODE_Msk, ADC_SingleChContinuousMode);
}

/**
 * @brief 
 *        ADC����ת��ģʽ��������
 * 
 * @param ADC_SerialChStruct 
 */
void ADC_SerialChCommon(ADC_SerialChTypeDef *ADC_SerialChStruct)
{
	if (NULL == ADC_SerialChStruct)
	{
		return;
	}

	ADC_Init(&ADC_SerialChStruct->ADC_InitStruct);

	switch (ADC_SerialChStruct->ADC_SqrEns)
	{
	case ADC_SqrEns0:
		ADC_Sqr0ChannelCfg(ADC_SerialChStruct);
		break;
	case ADC_SqrEns01:
		ADC_Sqr01ChannelCfg(ADC_SerialChStruct);
		break;
	case ADC_SqrEns02:
		ADC_Sqr02ChannelCfg(ADC_SerialChStruct);
		break;
	case ADC_SqrEns03:
		ADC_Sqr03ChannelCfg(ADC_SerialChStruct);
		break;

	default:
		break;
	}

}

/**
 * @brief 
 *        ADC��������ת��ģʽ����
 * 
 * @param ADC_SerialChStruct 
 */
void ADC_SerialChContinuousModeCfg(ADC_SerialChTypeDef *ADC_SerialChStruct)
{
	ADC_SerialChCommon(ADC_SerialChStruct);
	REGBITS_MODIFY(CW_ADC->CR0, ADC_CR0_MODE_Msk, ADC_SerialChContinuousMode);
}

/**
 * @brief 
 *        ADC����ɨ��ת��ģʽ����
 * 
 * @param ADC_SerialChStruct 
 */
void ADC_SerialChScanModeCfg(ADC_SerialChTypeDef *ADC_SerialChStruct)
{
	ADC_SerialChCommon(ADC_SerialChStruct);
	REGBITS_MODIFY(CW_ADC->CR0, ADC_CR0_MODE_Msk, ADC_SerialChScanMode);
}

/**
 * @brief 
 *        ADC���ж��ת��ģʽ����
 * 
 * @param ADC_SerialChStruct 
 * @param cntAdcSample: 0 ~ 255
 */
void ADC_SerialChMoreModeCfg(ADC_SerialChTypeDef *ADC_SerialChStruct,
		uint8_t cntAdcSample)
{
	ADC_SerialChStruct->ADC_InitStruct.ADC_AccEn = ADC_AccEnable;	//Must be added

	ADC_SerialChCommon(ADC_SerialChStruct);
	REGBITS_MODIFY(CW_ADC->CR0, ADC_CR0_MODE_Msk, ADC_SerialChMoreMode);

	CW_ADC->CR2_f.CNT = cntAdcSample;
}

/**
 * @brief 
 *        ADC���ж���ת��ģʽ����
 * 
 * @param ADC_SerialChStruct 
 */
void ADC_SerialChBreakModeCfg(ADC_SerialChTypeDef *ADC_SerialChStruct)
{
	ADC_SerialChCommon(ADC_SerialChStruct);
	REGBITS_MODIFY(CW_ADC->CR0, ADC_CR0_MODE_Msk, ADC_SerialChBreakMode);
}

/**
 * @brief   
 *          ��ͨ��ģʽ�����ø�����ʹ��
 *
 * @param   enAdcSampCh:
 *          @arg ADC_ExInputCH0
 *          @arg ADC_ExInputCH1
 *          @arg ADC_ExInputCH2
 *          @arg ADC_ExInputCH3
 *          @arg ADC_ExInputCH4
 *          @arg ADC_ExInputCH5
 *          @arg ADC_ExInputCH6
 *          @arg ADC_ExInputCH7
 *          @arg ADC_ExInputCH8
 *          @arg ADC_ExInputCH9
 *          @arg ADC_ExInputCH10
 *          @arg ADC_ExInputCH11
 *          @arg ADC_ExInputCH12
 *          @arg ADC_VddaDiV3Input
 *          @arg ADC_TsInput
 *          @arg ADC_Vref1P2Input
 */
void ADC_BufEnSingleCh(uint32_t enAdcSampCh)
{
	if ((enAdcSampCh == ADC_VddaDiV3Input) || (enAdcSampCh == ADC_TsInput)
			|| (enAdcSampCh == ADC_Vref1P2Input))
	{
		REGBITS_SET(CW_ADC->CR0, ADC_CR0_BUF_Msk);
	}

	if (enAdcSampCh == ADC_Vref1P2Input)
	{
		REGBITS_SET(CW_ADC->CR0, ADC_CR0_BGREN_Msk);
	}

	//���ADCͨ��ѡ���������¶ȴ����������ѹ������Ҫʹ�������¶ȴ�����
	else if (enAdcSampCh == ADC_TsInput)
	{
		//ʹ�������¶ȴ�����
		REGBITS_SET(CW_ADC->CR0, ADC_CR0_TSEN_Msk);
	}
}

/**
 * @brief 
 *          ����ģʽ�����ø�����ʹ��
 * 
 * @param enAdcSampCh:
 *        @arg ADC_SqrCh0
 *        @arg ADC_SqrCh1
 *        @arg ADC_SqrCh2
 *        @arg ADC_SqrCh3
 *        @arg ADC_SqrCh4
 *        @arg ADC_SqrCh5
 *        @arg ADC_SqrCh6
 *        @arg ADC_SqrCh7
 *        @arg ADC_SqrCh8
 *        @arg ADC_SqrCh9
 *        @arg ADC_SqrCh10
 *        @arg ADC_SqrCh11
 *        @arg ADC_SqrCh12
 *        @arg ADC_SqrVddaDiV3
 *        @arg ADC_SqrTs
 *        @arg ADC_SqrVref1P2
 */
void ADC_BufEnSerialCh(uint32_t enAdcSampCh)
{
	if ((enAdcSampCh == ADC_SqrVddaDiV3) || (enAdcSampCh == ADC_SqrTs)
			|| (enAdcSampCh == ADC_SqrVref1P2))
	{
		REGBITS_SET(CW_ADC->CR0, ADC_CR0_BUF_Msk);
	}

	if (enAdcSampCh == ADC_SqrVref1P2)
	{
		REGBITS_SET(CW_ADC->CR0, ADC_CR0_BGREN_Msk);
	}

	//���ADCͨ��ѡ���������¶ȴ����������ѹ������Ҫʹ�������¶ȴ�����
	else if (enAdcSampCh == ADC_SqrTs)
	{
		//ʹ�������¶ȴ�����
		REGBITS_SET(CW_ADC->CR0, ADC_CR0_TSEN_Msk);
	}
}

/**
 * @brief   
 *          ����SQR0ת��ͨ������
 *
 * @param   ADC_SerialChStruct
 */
void ADC_Sqr0ChannelCfg(ADC_SerialChTypeDef *ADC_SerialChStruct)
{
    ASSERT(NULL != ADC_SerialChStruct);
    assert_param(IS_ADC_SQR_CH(ADC_SerialChStruct->ADC_Sqr0Chmux ));
    assert_param(IS_ADC_SQR_ENS(ADC_SerialChStruct->ADC_SqrEns ));

	//ADC_SerialChStruct->ADC_SqrEns = ADC_SqrEns0;
	REGBITS_MODIFY(CW_ADC->SQR, ADC_SQR_ENS_Msk | ADC_SQR_SQR0_Msk,
			ADC_SerialChStruct->ADC_SqrEns |\
            ADC_SerialChStruct->ADC_Sqr0Chmux);

	ADC_BufEnSerialCh(ADC_SerialChStruct->ADC_Sqr0Chmux);
}

/**
 * @brief
 *          ����SQR0/SQR1ת��ͨ������
 *
 * @param   ADC_SerialChStruct
 */
void ADC_Sqr01ChannelCfg(ADC_SerialChTypeDef *ADC_SerialChStruct)
{
    ASSERT(NULL != ADC_SerialChStruct);
    assert_param(IS_ADC_SQR_CH(ADC_SerialChStruct->ADC_Sqr0Chmux ));
    assert_param(IS_ADC_SQR_CH(ADC_SerialChStruct->ADC_Sqr1Chmux ));
    assert_param(IS_ADC_SQR_ENS(ADC_SerialChStruct->ADC_SqrEns ));

	//ADC_SerialChStruct->ADC_SqrEns = ADC_SqrEns01;
	REGBITS_MODIFY(CW_ADC->SQR,
			ADC_SQR_ENS_Msk | ADC_SQR_SQR0_Msk | ADC_SQR_SQR1_Msk,
			ADC_SerialChStruct->ADC_SqrEns |\
            (ADC_SerialChStruct->ADC_Sqr1Chmux << ADC_SQR_SQR1_Pos) |\
            ADC_SerialChStruct->ADC_Sqr0Chmux);

	ADC_BufEnSerialCh(ADC_SerialChStruct->ADC_Sqr0Chmux);
	ADC_BufEnSerialCh(ADC_SerialChStruct->ADC_Sqr1Chmux);
}

/**
 * @brief
 *          ����SQR0~SQR2ת��ͨ������
 *
 * @param   ADC_SerialChStruct
 */
void ADC_Sqr02ChannelCfg(ADC_SerialChTypeDef *ADC_SerialChStruct)
{
    ASSERT(NULL != ADC_SerialChStruct);
    assert_param(IS_ADC_SQR_CH(ADC_SerialChStruct->ADC_Sqr0Chmux ));
    assert_param(IS_ADC_SQR_CH(ADC_SerialChStruct->ADC_Sqr1Chmux ));
    assert_param(IS_ADC_SQR_CH(ADC_SerialChStruct->ADC_Sqr2Chmux ));
    assert_param(IS_ADC_SQR_ENS(ADC_SerialChStruct->ADC_SqrEns ));

    //ADC_SerialChStruct->ADC_SqrEns = ADC_SqrEns02;
	REGBITS_MODIFY(CW_ADC->SQR,
			ADC_SQR_ENS_Msk | ADC_SQR_SQR0_Msk |\
            ADC_SQR_SQR1_Msk | ADC_SQR_SQR2_Msk,
			ADC_SerialChStruct->ADC_SqrEns |\
            (ADC_SerialChStruct->ADC_Sqr2Chmux << ADC_SQR_SQR2_Pos) |\
            (ADC_SerialChStruct->ADC_Sqr1Chmux << ADC_SQR_SQR1_Pos) |\
            ADC_SerialChStruct->ADC_Sqr0Chmux);

	ADC_BufEnSerialCh(ADC_SerialChStruct->ADC_Sqr0Chmux);
	ADC_BufEnSerialCh(ADC_SerialChStruct->ADC_Sqr1Chmux);
	ADC_BufEnSerialCh(ADC_SerialChStruct->ADC_Sqr2Chmux);
}

/**
 * @brief
 *          ����SQR0~SQR2ת��ͨ������
 *
 * @param   ADC_SerialChStruct
 */
void ADC_Sqr03ChannelCfg(ADC_SerialChTypeDef *ADC_SerialChStruct)
{
    ASSERT(NULL != ADC_SerialChStruct);
    assert_param(IS_ADC_SQR_CH(ADC_SerialChStruct->ADC_Sqr0Chmux ));
    assert_param(IS_ADC_SQR_CH(ADC_SerialChStruct->ADC_Sqr1Chmux ));
    assert_param(IS_ADC_SQR_CH(ADC_SerialChStruct->ADC_Sqr2Chmux ));
    assert_param(IS_ADC_SQR_CH(ADC_SerialChStruct->ADC_Sqr3Chmux ));
    assert_param(IS_ADC_SQR_ENS(ADC_SerialChStruct->ADC_SqrEns ));

    //ADC_SerialChStruct->ADC_SqrEns = ADC_SqrEns03;
	REGBITS_MODIFY(CW_ADC->SQR,
			ADC_SQR_ENS_Msk | ADC_SQR_SQR0_Msk |\
            ADC_SQR_SQR1_Msk | ADC_SQR_SQR2_Msk | ADC_SQR_SQR3_Msk,
			ADC_SerialChStruct->ADC_SqrEns |\
            (ADC_SerialChStruct->ADC_Sqr3Chmux << ADC_SQR_SQR3_Pos) |\
            (ADC_SerialChStruct->ADC_Sqr2Chmux << ADC_SQR_SQR2_Pos) |\
            (ADC_SerialChStruct->ADC_Sqr1Chmux << ADC_SQR_SQR1_Pos) |\
            ADC_SerialChStruct->ADC_Sqr0Chmux);

	ADC_BufEnSerialCh(ADC_SerialChStruct->ADC_Sqr0Chmux);
	ADC_BufEnSerialCh(ADC_SerialChStruct->ADC_Sqr1Chmux);
	ADC_BufEnSerialCh(ADC_SerialChStruct->ADC_Sqr2Chmux);
	ADC_BufEnSerialCh(ADC_SerialChStruct->ADC_Sqr3Chmux);
}

/**
 * @brief   
 *          ����DMA��ȡ����
 *
 * @param   NewState:
 *          @arg DISABLE
 *          @arg ENABLE
 */
void ADC_DMACmd(FunctionalState NewState)
{
	assert_param(IS_FUNCTIONAL_STATE(NewState));
	if (NewState != DISABLE)
	{
		REGBITS_SET(CW_ADC->CR1, ADC_CR1_DMAEN_Msk);
	}
	else
	{
		REGBITS_CLR(CW_ADC->CR1, ADC_CR1_DMAEN_Msk);
	}
}

/**
 * @brief 
 *       ����DMA��ȡʹ��
 * 
 */
void ADC_DMAEnable(void)
{
	REGBITS_SET(CW_ADC->CR1, ADC_CR1_DMAEN_Msk);
}

/**
 * @brief 
 *       ����DMA��ȡ��ֹ
 * 
 */
void ADC_DMADisable(void)
{
	REGBITS_CLR(CW_ADC->CR1, ADC_CR1_DMAEN_Msk);
}

/**
 * @brief   
 *          ��ȡ����ת������ֵ
 *
 * @param
 * 
 * @return uint16_t 
 */
uint16_t ADC_GetConversionValue(void)
{
	return (uint16_t)(CW_ADC->RESULT0);
}

/**
 * @brief   
 *          ��ȡSQR0ͨ������ֵ
 *
 * @param   pAdcResult
 */
void ADC_GetSqr0Result(uint16_t* pAdcResult)
{
	if (NULL == pAdcResult)
	{
		return;
	}
	*pAdcResult = (uint16_t)(CW_ADC->RESULT0);
}

/**
 * @brief 
 *          ��ȡSQR1ͨ������ֵ
 * 
 * @param   pAdcResult
 */
void ADC_GetSqr1Result(uint16_t* pAdcResult)
{
	if (NULL == pAdcResult)
	{
		return;
	}
	*pAdcResult = (uint16_t)(CW_ADC->RESULT1);
}

/**
 * @brief 
 *          ��ȡSQR2ͨ������ֵ
 * 
 * @param   pAdcResult
 */
void ADC_GetSqr2Result(uint16_t* pAdcResult)
{
	if (NULL == pAdcResult)
	{
		return;
	}
	*pAdcResult = (uint16_t)(CW_ADC->RESULT2);
}

/**
 * @brief 
 *          ��ȡSQR3ͨ������ֵ
 * 
 * @param   pAdcResult
 */
void ADC_GetSqr3Result(uint16_t* pAdcResult)
{
	if (NULL == pAdcResult)
	{
		return;
	}
	*pAdcResult = (uint16_t)(CW_ADC->RESULT3);
}

/**
 * @brief   
 *          ��ȡ�ۼӲ���ֵ
 *
 * @param   pAdcAccResult
 */
void ADC_GetAccResult(uint32_t* pAdcAccResult)
{
	if (NULL == pAdcAccResult)
	{
		return;
	}

	*pAdcAccResult = (uint32_t)(CW_ADC->RESULTACC);
}

/**
 * @brief   
 *          �����ۼӲ���ֵ
 */
void ADC_ClrAccResult(void)
{
	REGBITS_SET(CW_ADC->CR2, ADC_CR2_ACCRST_Msk);
}

/**
 * @brief   
 *          ����ADC�ο���ѹ
 *
 * @param   ADC_VrefSel:
 *          @arg ADC_Vref_BGR1p5
 *          @arg ADC_Vref_BGR2p5
 *          @arg ADC_Vref_Extern1
 *          @arg ADC_Vref_VDDA
 */
void ADC_SetVref(uint32_t ADC_VrefSel)
{
    assert_param(IS_ADC_VREF_SEL(ADC_VrefSel ));

	REGBITS_MODIFY(CW_ADC->CR0, ADC_CR0_REF_Msk,
			ADC_VrefSel);
}
/**
 * @brief   
 *          ����ADC������뷽ʽ
 *
 * @param   enAlign:
 *          @arg ADC_AlignRight
 *          @arg ADC_AlignLeft
 */
void ADC_SetAlign(uint32_t enAlign)
{
	REGBITS_MODIFY(CW_ADC->CR1, ADC_CR1_ALIGN_Msk, enAlign);
}

/**
 * @brief 
 *        ���õ�ͨ��ADCת���������������
 * 
 * @param enDiscard:
 *        @arg ADC_DiscardNull
 *        @arg ADC_DiscardEnable
 */
void ADC_SetDiscard(uint32_t enDiscard)
{
    assert_param(IS_ADC_DATA_DISCARD(enDiscard));
    REGBITS_MODIFY(CW_ADC->CR1, ADC_CR1_DISCARD_Msk, enDiscard);
}

/**
 * @brief 
 *        ���������¶ȴ�����ʹ�ܿ���
 * 
 * @param enTs:
 *        @arg ADC_TsDisable
 *        @arg ADC_TsEnable
 */
void ADC_SetTs(uint32_t enTs)
{
    assert_param(IS_ADC_TS_ENABLE(enTs));
    REGBITS_MODIFY(CW_ADC->CR0, ADC_CR0_TSEN_Msk, enTs);

}

/**
 * @brief 
 *        ��ȡADC�ο���ѹ1.5Vʱ���¶ȴ������Ĳ����¶�
 * 
 * @param fAdcTsDegree 
 */
void ADC_GetTsVref1V5(float *fAdcTsDegree)
{
	uint16_t u16AdcResult;
	uint8_t temp1;
        uint16_t temp2;
	temp1 = *((uint8_t*) (ADDR_T0));
	temp2 = *((uint16_t*) (ADDR_TRIM_1P5));
	u16AdcResult = ADC_GetConversionValue();
	*fAdcTsDegree = temp1 * 0.5f + COEFF_TS * 1.5f * (u16AdcResult - temp2);
}

/**
 * @brief 
 *        ��ȡADC�ο���ѹ2.5Vʱ���¶ȴ������Ĳ����¶�
 * 
 * @param fAdcTsDegree 
 */
void ADC_GetTsVref2V5(float *fAdcTsDegree)
{
	uint16_t u16AdcResult;
	uint8_t temp1;
    uint16_t temp2;
	temp1 = *((uint8_t*) (ADDR_T0));
	temp2 = *((uint16_t*) (ADDR_TRIM_2P5));
	u16AdcResult = ADC_GetConversionValue();
	*fAdcTsDegree = temp1 * 0.5f + COEFF_TS * 2.5f * (u16AdcResult - temp2);
}

/**
 * @brief
 *          ADC�Զ�ֹͣ����
 *
 * @param   enAutoStop:
 *          @arg ADC_AutoStopDisable
 *          @arg ADC_AutoStopEnable
 */
void ADC_AutoStop(uint32_t enAutoStop)
{
	REGBITS_MODIFY(CW_ADC->START, ADC_START_AUTOSTOP_Msk, enAutoStop);
}

/**
 * @brief 
 *          ADC�ж�����
 * 
 * @param   ADC_IT:
 *          @arg ADC_IT_READY
 *          @arg ADC_IT_OVW
 *          @arg ADC_IT_WDTR
 *          @arg ADC_IT_WDTH
 *          @arg ADC_IT_WDTL
 *          @arg ADC_IT_EOA
 *          @arg ADC_IT_EOS
 *          @arg ADC_IT_EOC
 * @param   NewState:
 *          @arg DISABLE
 *          @arg ENABLE
 */
void ADC_ITConfig(uint16_t ADC_IT, FunctionalState NewState)
{
	uint8_t itMask = 0;
	/* Check the parameters */
	assert_param(IS_FUNCTIONAL_STATE(NewState));
	assert_param(IS_ADC_IT(ADC_IT));
	/* Get the ADC IT index */
	itMask = (uint8_t) ADC_IT;
	if (NewState != DISABLE)
	{
		/* Enable the selected ADC interrupts */
		CW_ADC->IER |= itMask;
	}
	else
	{
		/* Disable the selected ADC interrupts */
		CW_ADC->IER &= (~(uint32_t) itMask);
	}
}

/**
 * @brief
 *          ʹ��NVIC��ADC�ж�
 *
 * @param   intPriority:
 *          @arg 0 ~ 3
 */
void ADC_EnableNvic(uint8_t intPriority)
{
	if (intPriority < (1UL << __NVIC_PRIO_BITS))
	{
		NVIC_ClearPendingIRQ(ADC_IRQn);
		NVIC_EnableIRQ(ADC_IRQn);
		NVIC_SetPriority(ADC_IRQn, intPriority);
	}
}

/**
 * @brief
 *          ����NVIC��ADC�ж�
 *
 * @param
 *
 */
void ADC_DisableNvic(void)
{
	NVIC_ClearPendingIRQ(ADC_IRQn);
	NVIC_DisableIRQ(ADC_IRQn);
	NVIC_SetPriority(ADC_IRQn, ADC_INT_PRIORITY);
}
//@} // AdcGroup

/******************************************************************************
 * EOF (not truncated)
 ******************************************************************************/

