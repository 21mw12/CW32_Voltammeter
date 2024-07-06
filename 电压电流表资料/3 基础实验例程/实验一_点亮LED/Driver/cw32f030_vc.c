/**
 * @file cw32f030_vc.c
 * @author P&S (you@domain.com)
 * @brief
 * @version 0.1
 * @date 2021-07-27
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
#include "cw32f030_vc.h"
#include "cw32f030_adc.h"

/**
 ******************************************************************************
 ** \addtogroup VcGroup
 ******************************************************************************/
//@{

/******************************************************************************
 * Local pre-processor symbols/macros ('#define')
 ******************************************************************************/
#define IS_VALID_CHANNEL(x)     ( VcChannel1==(x) || VcChannel2 == (x))
#define IS_VALID_STAT(x)        ( VcCmpResult==(x) || VcIntrResult == (x))
#define IS_VALID_DIV(x)         ( (x) <= 64u )

#define IS_VALID_INPUT_P(x)     ( (x) <= VcInPCh7 )

#define IS_VALID_INPUT_N(x)     ( (x) <= AiAdcVref )

#define IS_VALID_DLY(x)         ( (VcDelay30mv == (x)) ||\
                                  (VcDelay20mv == (x)) ||\
                                  (VcDelay10mv == (x)) ||\
                                  (VcDelayoff == (x)) )

#define IS_VALID_BIAS(x)        ( (VcRespExtraLow == (x)) ||\
                                  (VcRespLow == (x)) ||\
                                  (VcRespMedium == (x)) ||\
                                  (VcRespHigh == (x)) )

#define IS_VALID_CLK(x)         ( (x) <= LvdFilterHsi )

#define IS_VALID_FILTER(x)      ( (x) <= VcFilter4095Clk )

#define IS_VALID_BLANK(x)       ( (x) <= VcBlankAtimCh3 )

#define IS_VALID_OUTPUT(x)      ( (x) <= VcOutAtimClr )

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
 *          ʹ��NVIC��VCx�ж�
 *
 * @param   enIrqn:
 *          @arg VC1_IRQn
 *          @arg VC2_IRQn
 * @param   intPriority:
 *          @arg 0 ~ 3
 */
void VC_EnableNvic(IRQn_Type enIrqn, uint8_t intPriority)
{
	if (intPriority < (1UL << __NVIC_PRIO_BITS))
	{
		NVIC_ClearPendingIRQ(enIrqn);
		NVIC_EnableIRQ(enIrqn);
		NVIC_SetPriority(enIrqn, intPriority);
	}
}

/**
 * @brief   
 *          VCͨ��1�ж�ʹ��
 *
 * @param   intPriority:
 *          @arg 0 ~ 3
 *
 *          @return
 */
void VC1_EnableIrq(uint8_t intPriority)
{
    VC_EnableNvic(VC1_IRQn, intPriority);
    REGBITS_SET(CW_VC1->CR0, VCx_CR0_IE_Msk);
}

/**
 * @brief
 *          VCͨ��2�ж�ʹ��
 *
 * @param   intPriority:
 *          @arg 0 ~ 3
 *
 *          @return
 */
void VC2_EnableIrq(uint8_t intPriority)
{
	VC_EnableNvic(VC2_IRQn, intPriority);
    REGBITS_SET(CW_VC2->CR0, VCx_CR0_IE_Msk);
}

/**
 * @brief   
 *          VCͨ��1�жϽ���
 *
 * @return
 */
void VC1_DisableIrq(void)
{
	REGBITS_CLR(CW_VC1->CR0, VCx_CR0_IE_Msk);
    VC_DisableNvic(VC1_IRQn);
}

/**
 * @brief   
 *          VCͨ��2�жϽ���
 *
 * @return
 */
void VC2_DisableIrq(void)
{
	REGBITS_CLR(CW_VC2->CR0, VCx_CR0_IE_Msk);
    VC_DisableNvic(VC2_IRQn);
}

/**
 * @brief   
 *          ��ֹNVIC��VC�ж�
 *
 * @param   enIrqn:
 *          @arg VC1_IRQn
 *          @arg VC2_IRQn
 *
 * @return
 */
void VC_DisableNvic(IRQn_Type enIrqn)
{
    NVIC_ClearPendingIRQ(enIrqn);
    NVIC_DisableIRQ(enIrqn);
}

/**
 * @brief
 *          ��ȡVC1ָ�����ж�״̬
 *
 * @param   VC_FLAG:
 *          @arg VC_FLAG_READY
 *          @arg VC_FLAG_FLTV
 *          @arg VC_FLAG_INTF
 *
 * @return  FlagStatus: SET or RESET
 */
FlagStatus VC1_GetFlagStatus(uint16_t VC_FLAG)
{
	assert_param(IS_VC_GET_FLAG(VC_FLAG));
	return (REGBITS_GET(CW_VC1->SR, VC_FLAG) ? SET : RESET);
}

/**
 * @brief
 *          ��ȡVC2ָ�����ж�״̬
 *
 * @param   VC_FLAG:
 *          @arg VC_FLAG_READY
 *          @arg VC_FLAG_FLTV
 *          @arg VC_FLAG_INTF
 *
 * @return  FlagStatus: SET or RESET
 */
FlagStatus VC2_GetFlagStatus(uint16_t VC_FLAG)
{
	assert_param(IS_VC_GET_FLAG(VC_FLAG));
	return (REGBITS_GET(CW_VC2->SR, VC_FLAG) ? SET : RESET);
}

/**
 * @brief   
 *          ���VC1�жϱ�־
 *
 * @param
 *
 * @return
 */
void VC1_ClearIrq(void)
{
	REGBITS_CLR(CW_VC1->SR, VCx_SR_INTF_Msk);
}

/**
 * @brief   
 *          ���VC2�жϱ�־
 *
 * @param
 *
 * @return
 */
void VC2_ClearIrq(void)
{
	REGBITS_CLR(CW_VC2->SR, VCx_SR_INTF_Msk);
}

/**
 * @brief   
 *          VC1/VC2ģ��DIV�ο���ѹ��ʼ��
 *
 * @param   VC_DivStruct
 *
 * @return
 */
void VC1VC2_DIVInit(VC_DivTypeDef* VC_DivStruct)
{
    ASSERT(NULL != VC_DivStruct);
    assert_param(IS_VC_DIV_EN(VC_DivStruct->VC_DivEn));
    assert_param(IS_VC_DIV_VREF(VC_DivStruct->VC_DivVref));

    REGBITS_MODIFY(CW_VC1->DIV, VCx_DIV_EN_Msk | VCx_DIV_VIN_Msk, \
    		VC_DivStruct->VC_DivEn | VC_DivStruct->VC_DivVref);

    REGBITS_MODIFY(CW_VC2->DIV, VCx_DIV_EN_Msk | VCx_DIV_VIN_Msk, \
    		VC_DivStruct->VC_DivEn | VC_DivStruct->VC_DivVref);

    if (VC_DivStruct->VC_DivValue < 0x40)
    {
        CW_VC1->DIV_f.DIV = VC_DivStruct->VC_DivValue;
        CW_VC2->DIV_f.DIV = VC_DivStruct->VC_DivValue;
    }
    else
    {
    }
}

/**
 * @brief   
 *          VC1/VC2ģ��DIV�ο���ѹȥ��ʼ��
 *
 * @param
 *
 * @return
 */
void VC1VC2_DIVDeInit(void)
{
	CW_VC1->DIV = 0x0u;
	CW_VC2->DIV = 0x0u;
}

/**
 * @brief   
 *          VC1/VC2ģ��VCx���������źų�ʼ��
 *
 * @param   VC_InitStruct
 *
 * @return
 */
void VC1VC2_INNInit(VC_InitTypeDef* VC_InitStruct)
{
    ASSERT(NULL != VC_InitStruct);
    assert_param(IS_VC_INPUT_N(VC_InitStruct->VC_InputN));

    switch (VC_InitStruct->VC_InputN)
    {
    case VC_InputN_Ts:
    	//VCx���������ź�Ϊ�¶ȴ�����
        //��ADCʱ��
        REGBITS_SET( CW_SYSCTRL->APBEN2, SYSCTRL_APBEN2_ADC_Msk );
        REGBITS_SET(CW_ADC->CR0, ADC_CR0_TSEN_Msk | ADC_CR0_BGREN_Msk);
    	break;

    case VC_InputN_Bgr1P2:
    	//VCx���������ź�ΪBGR 1.2V
        //��ADCʱ��
        REGBITS_SET( CW_SYSCTRL->APBEN2, SYSCTRL_APBEN2_ADC_Msk );
        REGBITS_SET( CW_ADC->CR0, ADC_CR0_BGREN_Msk );
    	break;

    case VC_InputN_AdcVref:
    	//VCx���������ź�ΪADC VREF
        //��ADCʱ��
        REGBITS_SET( CW_SYSCTRL->APBEN2, SYSCTRL_APBEN2_ADC_Msk );
        ADC_Enable();
    	break;

    default:
    	break;
    }
}

/**
 * @brief
 *          VCͨ��1��ʼ��
 *
 * @param   VC_InitStruct
 *
 * @return
 */
void VC1_ChannelInit(VC_InitTypeDef* VC_InitStruct)
{
    ASSERT(NULL != VC_InitStruct);
    assert_param(IS_VC_INPUT_P(VC_InitStruct->VC_InputP));
    assert_param(IS_VC_INPUT_N(VC_InitStruct->VC_InputN));
    assert_param(IS_VC_HYS(VC_InitStruct->VC_Hys));
    assert_param(IS_VC_RESP(VC_InitStruct->VC_Resp));
    assert_param(IS_VC_FILTER(VC_InitStruct->VC_FilterEn));
    assert_param(IS_VC_FLT_CLK(VC_InitStruct->VC_FilterClk));
    assert_param(IS_VC_FLT_TIME(VC_InitStruct->VC_FilterTime));
    assert_param(IS_VC_WINDOW(VC_InitStruct->VC_Window));
    assert_param(IS_VC_POLARITY(VC_InitStruct->VC_Polarity));

    REGBITS_MODIFY(CW_VC1->CR0, \
    		VCx_CR0_INN_Msk | VCx_CR0_INP_Msk | \
			VCx_CR0_WINDOW_Msk | VCx_CR0_POL_Msk | \
			VCx_CR0_HYS_Msk | VCx_CR0_RESP_Msk, \
			VC_InitStruct->VC_InputN | \
			VC_InitStruct->VC_InputP | \
			VC_InitStruct->VC_Window | \
			VC_InitStruct->VC_Polarity | \
			VC_InitStruct->VC_Hys | \
			VC_InitStruct->VC_Resp);

    REGBITS_MODIFY(CW_VC1->CR1, \
    		VCx_CR1_FLTCLK_Msk | VCx_CR1_FLTTIME_Msk | \
			VCx_CR1_FLTEN_Msk, \
    		VC_InitStruct->VC_FilterClk | \
			VC_InitStruct->VC_FilterTime | \
			VC_InitStruct->VC_FilterEn);

    //VCx���������źų�ʼ��
    VC1VC2_INNInit(VC_InitStruct);
}

/**
 * @brief   
 *          VCͨ��2��ʼ��
 *
 * @param   VC_InitStruct
 *
 * @return
 */
void VC2_ChannelInit(VC_InitTypeDef* VC_InitStruct)
{
    ASSERT(NULL != VC_InitStruct);
    assert_param(IS_VC_INPUT_P(VC_InitStruct->VC_InputP));
    assert_param(IS_VC_INPUT_N(VC_InitStruct->VC_InputN));
    assert_param(IS_VC_HYS(VC_InitStruct->VC_Hys));
    assert_param(IS_VC_RESP(VC_InitStruct->VC_Resp));
    assert_param(IS_VC_FILTER(VC_InitStruct->VC_FilterEn));
    assert_param(IS_VC_FLT_CLK(VC_InitStruct->VC_FilterClk));
    assert_param(IS_VC_FLT_TIME(VC_InitStruct->VC_FilterTime));
    assert_param(IS_VC_WINDOW(VC_InitStruct->VC_Window));
    assert_param(IS_VC_POLARITY(VC_InitStruct->VC_Polarity));

    REGBITS_MODIFY(CW_VC2->CR0, \
    		VCx_CR0_INN_Msk | VCx_CR0_INP_Msk | \
			VCx_CR0_WINDOW_Msk | VCx_CR0_POL_Msk | \
			VCx_CR0_HYS_Msk | VCx_CR0_RESP_Msk, \
			VC_InitStruct->VC_InputN | \
			VC_InitStruct->VC_InputP | \
			VC_InitStruct->VC_Window | \
			VC_InitStruct->VC_Polarity | \
			VC_InitStruct->VC_Hys | \
			VC_InitStruct->VC_Resp);

    REGBITS_MODIFY(CW_VC2->CR1, \
    		VCx_CR1_FLTCLK_Msk | VCx_CR1_FLTTIME_Msk | \
			VCx_CR1_FLTEN_Msk, \
    		VC_InitStruct->VC_FilterClk | \
			VC_InitStruct->VC_FilterTime | \
			VC_InitStruct->VC_FilterEn);

    //VCx���������źų�ʼ��
    VC1VC2_INNInit(VC_InitStruct);
}

/**
 * @brief   
 *          VCģ��ȥ��ʼ��
 *
 * @return
 */
void VC_DeInit(void)
{
	// Enable VC reset state
	REGBITS_CLR(CW_SYSCTRL->APBRST2, SYSCTRL_APBRST2_VC_Msk);
	// Release VC from reset state
	REGBITS_SET(CW_SYSCTRL->APBRST2, SYSCTRL_APBRST2_VC_Msk);

	VC1_ChannelDeInit();
	VC2_ChannelDeInit();
}

/**
 * @brief
 *          VCͨ��1ȥ��ʼ��
 *
 * @return
 */
void VC1_ChannelDeInit(void)
{
	CW_VC1->CR0 = 0u;
	CW_VC1->CR1 = 0u;
    VC_DisableNvic(VC1_IRQn);
}

/**
 * @brief   
 *          VCͨ��2ȥ��ʼ��
 *
 * @return
 */
void VC2_ChannelDeInit(void)
{
	CW_VC2->CR0 = 0u;
	CW_VC2->CR1 = 0u;
    VC_DisableNvic(VC2_IRQn);
}

/**
 * @brief   
 *          VC1ͨ��ʹ��
 *
 * @return
 */
void VC1_EnableChannel(void)
{
	REGBITS_SET(CW_VC1->CR0, VCx_CR0_EN_Msk);
	//�ȴ�VCx�ȶ�
	while(!(VC1_GetFlagStatus(VC_FLAG_READY)));
}

/**
 * @brief   
 *          VC2ͨ��ʹ��
 *
 * @return
 */
void VC2_EnableChannel(void)
{
	REGBITS_SET(CW_VC2->CR0, VCx_CR0_EN_Msk);
	//�ȴ�VCx�ȶ�
	while(!(VC2_GetFlagStatus(VC_FLAG_READY)));
}

/**
 * @brief   
 *          VC1ͨ������
 *
 * @return
 */
void VC1_DisableChannel(void)
{
	REGBITS_CLR(CW_VC1->CR0, VCx_CR0_EN_Msk);
}

/**
 * @brief   
 *          VC2ͨ������
 *
 * @return
 */
void VC2_DisableChannel(void)
{
	REGBITS_CLR(CW_VC2->CR0, VCx_CR0_EN_Msk);
}

/**
 * @brief   
 *          VC1����˲�ʹ��
 *
 * @return
 */
void VC1_EnableFilter(void)
{
	REGBITS_SET(CW_VC1->CR1, VCx_CR1_FLTEN_Msk);
}

/**
 * @brief   
 *          VC2����˲�ʹ��
 *
 * @return
 */
void VC2_EnableFilter(void)
{
	REGBITS_SET(CW_VC2->CR1, VCx_CR1_FLTEN_Msk);
}

/**
 * @brief
 *          VC1����˲�����
 *
 * @return
 */
void VC1_DisableFilter(void)
{
	REGBITS_CLR(CW_VC1->CR1, VCx_CR1_FLTEN_Msk);
}

/**
 * @brief
 *          VC2����˲�����
 *
 * @return
 */
void VC2_DisableFilter(void)
{
	REGBITS_CLR(CW_VC2->CR1, VCx_CR1_FLTEN_Msk);
}

/**
 * @brief
 *          VCͨ��1/2 �������Ĭ��ֵ��ʼ��
 * @param   VC_OutStruct
 *
 * @return
 */
void VC1VC2_OutInit(VC_OutTypeDef* VC_OutStruct)
{
	VC_OutStruct->VC_ATIMBk = 0u;
	VC_OutStruct->VC_OutAtimClr = 0u;
}

/**
 * @brief
 *          VCͨ��1�����������
 * @param   VC_OutStruct
 *
 * @return
 */
void VC1_OutputCfg(VC_OutTypeDef* VC_OutStruct)
{
    ASSERT(NULL != VC_OutStruct);
    assert_param(IS_VC_ATIMBK(VC_OutStruct->VC_ATIMBk));
    assert_param(IS_VC_ATIMCLR(VC_OutStruct->VC_OutAtimClr));

	REGBITS_MODIFY(CW_VC1->CR1, \
			VCx_CR1_ATIMBK_Msk | VCx_CR1_ATIMCLR_Msk,
			VC_OutStruct->VC_ATIMBk | \
			VC_OutStruct->VC_OutAtimClr);
}

/**
 * @brief
 *          VCͨ��2�����������
 * @param   VC_OutStruct
 *
 * @return
 */
void VC2_OutputCfg(VC_OutTypeDef* VC_OutStruct)
{
    ASSERT(NULL != VC_OutStruct);
    assert_param(IS_VC_ATIMBK(VC_OutStruct->VC_ATIMBk));
    assert_param(IS_VC_ATIMCLR(VC_OutStruct->VC_OutAtimClr));

	REGBITS_MODIFY(CW_VC2->CR1, \
			VCx_CR1_ATIMBK_Msk | VCx_CR1_ATIMCLR_Msk,
			VC_OutStruct->VC_ATIMBk | \
			VC_OutStruct->VC_OutAtimClr);
}

/**
 * @brief
 *          VCͨ��1/2 BlanK����Ĭ��ֵ��ʼ��
 * @param   VC_BlankStruct
 *
 * @return
 */
void VC1VC2_BlankInit(VC_BlankTypeDef* VC_BlankStruct)
{
	VC_BlankStruct->VC_BlankFlt = 0u;
	VC_BlankStruct->VC_BlankCh3B = 0u;
	VC_BlankStruct->VC_BlankCh2B = 0u;
	VC_BlankStruct->VC_BlankCh1B = 0u;
}

/**
 * @brief
 *          VCͨ��1 BlanK��������
 * @param   VC_BlankStruct
 *
 * @return
 */
void VC1_BlankCfg(VC_BlankTypeDef* VC_BlankStruct)
{
    ASSERT(NULL != VC_BlankStruct);
    assert_param(IS_VC_BLANK_FLT(VC_BlankStruct->VC_BlankFlt));
    assert_param(IS_VC_BLANK_CH3B(VC_BlankStruct->VC_BlankCh3B));
    assert_param(IS_VC_BLANK_CH2B(VC_BlankStruct->VC_BlankCh2B));
    assert_param(IS_VC_BLANK_CH1B(VC_BlankStruct->VC_BlankCh1B));

	REGBITS_MODIFY(CW_VC1->CR1, \
			VCx_CR1_BLANKFLT_Msk | VCx_CR1_BLANKCH3B_Msk | \
			VCx_CR1_BLANKCH2B_Msk | VCx_CR1_BLANKCH1B_Msk,
			VC_BlankStruct->VC_BlankFlt | \
			VC_BlankStruct->VC_BlankCh3B | \
			VC_BlankStruct->VC_BlankCh2B | \
			VC_BlankStruct->VC_BlankCh1B);
}

/**
 * @brief
 *          VCͨ��2 BlanK��������
 * @param   VC_BlankStruct
 *
 * @return
 */
void VC2_BlankCfg(VC_BlankTypeDef* VC_BlankStruct)
{
    ASSERT(NULL != VC_BlankStruct);
    assert_param(IS_VC_BLANK_FLT(VC_BlankStruct->VC_BlankFlt));
    assert_param(IS_VC_BLANK_CH3B(VC_BlankStruct->VC_BlankCh3B));
    assert_param(IS_VC_BLANK_CH2B(VC_BlankStruct->VC_BlankCh2B));
    assert_param(IS_VC_BLANK_CH1B(VC_BlankStruct->VC_BlankCh1B));

	REGBITS_MODIFY(CW_VC2->CR1, \
			VCx_CR1_BLANKFLT_Msk | VCx_CR1_BLANKCH3B_Msk | \
			VCx_CR1_BLANKCH2B_Msk | VCx_CR1_BLANKCH1B_Msk,
			VC_BlankStruct->VC_BlankFlt | \
			VC_BlankStruct->VC_BlankCh3B | \
			VC_BlankStruct->VC_BlankCh2B | \
			VC_BlankStruct->VC_BlankCh1B);
}

/**
 * @brief
 *          VCͨ��1���ڱȽϹ�������
 *
 * @param   bWindow: TRUE or FALSE
 *
 * @return
 */
void VC1_WindowEnable(boolean_t bWindow)
{
    if (bWindow)
    {
    	REGBITS_SET(CW_VC1->CR0, VCx_CR0_WINDOW_Msk);
    }
    else
    {
    	REGBITS_CLR(CW_VC1->CR0, VCx_CR0_WINDOW_Msk);
    }
}

/**
 * @brief
 *          VCͨ��2���ڱȽϹ�������
 *
 * @param   bWindow: TRUE or FALSE
 *
 * @return
 */
void VC2_WindowEnable(boolean_t bWindow)
{
    if (bWindow)
    {
    	REGBITS_SET(CW_VC2->CR0, VCx_CR0_WINDOW_Msk);
    }
    else
    {
    	REGBITS_CLR(CW_VC2->CR0, VCx_CR0_WINDOW_Msk);
    }
}

/**
 * @brief
 *          VCͨ��1����źż�������
 *
 * @param   bPolarity: TRUE or FALSE
 *
 * @return
 */
void VC1_PolarityCfg(boolean_t bPolarity)
{
    if (bPolarity)
    {
    	REGBITS_SET(CW_VC1->CR0, VCx_CR0_POL_Msk);
    }
    else
    {
    	REGBITS_CLR(CW_VC1->CR0, VCx_CR0_POL_Msk);
    }
}

/**
 * @brief
 *          VCͨ��2����źż�������
 *
 * @param   bPolarity: TRUE or FALSE
 *
 * @return
 */
void VC2_PolarityCfg(boolean_t bPolarity)
{
    if (bPolarity)
    {
    	REGBITS_SET(CW_VC2->CR0, VCx_CR0_POL_Msk);
    }
    else
    {
    	REGBITS_CLR(CW_VC2->CR0, VCx_CR0_POL_Msk);
    }
}

/**
 * @brief
 *          VC1�ж�����
 *
 * @param   VC_IT:
 *          @arg VC_IT_HIGH
 *          @arg VC_IT_RISE
 *          @arg VC_IT_FALL
 * @param   NewState:
 *          @arg DISABLE
 *          @arg ENABLE
 */
void VC1_ITConfig(uint16_t VC_IT, FunctionalState NewState)
{
	/* Check the parameters */
	assert_param(IS_FUNCTIONAL_STATE(NewState));
	assert_param(IS_VC_IT(VC_IT));
	if (NewState != DISABLE)
	{
		/* Enable the selected VC interrupts */
		CW_VC1->CR1 |= VC_IT;
	}
	else
	{
		/* Disable the selected VC interrupts */
		CW_VC1->CR1 &= (~(uint32_t) VC_IT);
	}
}

/**
 * @brief
 *          VC2�ж�����
 *
 * @param   VC_IT:
 *          @arg VC_IT_READY
 *          @arg VC_IT_OVW
 *          @arg VC_IT_WDTR
 * @param   NewState:
 *          @arg DISABLE
 *          @arg ENABLE
 */
void VC2_ITConfig(uint16_t VC_IT, FunctionalState NewState)
{
	uint8_t itMask = 0;
	/* Check the parameters */
	assert_param(IS_FUNCTIONAL_STATE(NewState));
	assert_param(IS_VC_IT(VC_IT));
	/* Get the VC IT index */
	itMask = (uint8_t) VC_IT;
	if (NewState != DISABLE)
	{
		/* Enable the selected VC interrupts */
		CW_VC2->CR1 |= itMask;
	}
	else
	{
		/* Disable the selected VC interrupts */
		CW_VC2->CR1 &= (~(uint32_t) itMask);
	}
}

//@} // VcGroup


/******************************************************************************
 * EOF (not truncated)
 ******************************************************************************/

