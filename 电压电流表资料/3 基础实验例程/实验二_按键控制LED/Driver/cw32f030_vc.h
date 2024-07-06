/**
 * @file cw32f030_vc.h
 * @author P&S (you@domain.com)
 * @brief
 * @version 0.1
 * @date 2021-06-21
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

#ifndef __CW32F030_VC_H
#define __CW32F030_VC_H

/******************************************************************************
 * Include files
 ******************************************************************************/
#include "base_types.h"

/* C binding of definitions if building with C++ compiler */
#ifdef __cplusplus
extern "C"
{
#endif

/**
 ******************************************************************************
 ** \defgroup VcGroup Voltage Comparator (VC)
 **
 ******************************************************************************/
//@{

/******************************************************************************
 * Global type definitions
 ******************************************************************************/
#define  VC_INT_PRIORITY            ((uint32_t)3)    /*VC interrupt priority (lowest by default)  */

/** @defgroup VC_interrupts_definition
  * @{
  */
#define VC_IT_HIGH                   ((uint16_t)0x0080)
#define VC_IT_RISE                   ((uint16_t)0x0040)
#define VC_IT_FALL                   ((uint16_t)0x0020)


#define IS_VC_IT(IT) ((((IT) & (uint16_t)0xFF00) == 0x00) && ((IT) != 0x00))
#define IS_VC_GET_IT(IT) (((IT) == VC_IT_HIGH) || \
                          ((IT) == VC_IT_RISE) || \
                          ((IT) == VC_IT_FALL))

/** @defgroup VC_flags_definition
  * @{
  */
#define VC_FLAG_READY				((uint16_t)0x0004)
#define VC_FLAG_FLTV				((uint16_t)0x0002)
#define VC_FLAG_INTF				((uint16_t)0x0001)

#define IS_VC_FLAG(FLAG) ((((FLAG) & (uint16_t)0xFF00) == 0x00) && ((FLAG) != 0x00))
#define IS_VC_GET_FLAG(FLAG) 	(((FLAG) == VC_FLAG_READY) || \
								 ((FLAG) == VC_FLAG_FLTV) || \
								 ((FLAG) == VC_FLAG_INTF))

/** @defgroup VC_DivEn
  * @{
  */
#define VC_Div_Disable		((uint32_t)0x00000000)
#define VC_Div_Enable		((uint32_t)0x00000040)

#define IS_VC_DIV_EN(DIV_EN)		(((DIV_EN) == VC_Div_Disable) || \
									((DIV_EN) == VC_Div_Enable))

/** @defgroup VC_DivVref
  * @{
  */
#define VC_DivVref_VDDA		((uint32_t)0x00000000)
#define VC_DivVref_ADC		((uint32_t)0x00000080)

#define IS_VC_DIV_VREF(DIV_VREF)		(((DIV_VREF) == VC_DivVref_VDDA) || \
										((DIV_VREF) == VC_DivVref_ADC))

/** @defgroup VC_InputP
  * @{
  * VC1                 VC2
  * ����ͨ��0  PA00	    ����ͨ��0 PA05
  * ����ͨ��1  PA01		����ͨ��1 PA06
  * ����ͨ��2  PA02		����ͨ��2 PA07
  * ����ͨ��3  PA03		����ͨ��3 PB00
  * ����ͨ��4  PA04		����ͨ��4 PB01
  * ����ͨ��5  PA05		����ͨ��5 PB02
  * ����ͨ��6  PA06		����ͨ��6 PB10
  * ����ͨ��7  PA07		����ͨ��7 PB11
  */
#define VC_InputP_Ch0		((uint32_t)0x00000000)
#define VC_InputP_Ch1		((uint32_t)0x00000100)
#define VC_InputP_Ch2		((uint32_t)0x00000200)
#define VC_InputP_Ch3		((uint32_t)0x00000300)
#define VC_InputP_Ch4		((uint32_t)0x00000400)
#define VC_InputP_Ch5		((uint32_t)0x00000500)
#define VC_InputP_Ch6		((uint32_t)0x00000600)
#define VC_InputP_Ch7		((uint32_t)0x00000700)


#define IS_VC_INPUT_P(INPUT_P)		(((INPUT_P) == VC_InputP_Ch0) || \
									 ((INPUT_P) == VC_InputP_Ch1) || \
									 ((INPUT_P) == VC_InputP_Ch2) || \
									 ((INPUT_P) == VC_InputP_Ch3) || \
									 ((INPUT_P) == VC_InputP_Ch4) || \
									 ((INPUT_P) == VC_InputP_Ch5) || \
									 ((INPUT_P) == VC_InputP_Ch6) || \
									 ((INPUT_P) == VC_InputP_Ch7))

/** @defgroup VC_InputN
  * @{
  * VC1                 VC2
  * ����ͨ��0  PA00	    ����ͨ��0 PA05
  * ����ͨ��1  PA01		����ͨ��1 PA06
  * ����ͨ��2  PA02		����ͨ��2 PA07
  * ����ͨ��3  PA03		����ͨ��3 PB00
  * ����ͨ��4  PA04		����ͨ��4 PB01
  * ����ͨ��5  PA05		����ͨ��5 PB02
  * ����ͨ��6  PA06		����ͨ��6 PB10
  * ����ͨ��7  PA07		����ͨ��7 PB11
  * VDDA��ѹ			    VDDA��ѹ
  * ADC VREF            ADC VREF
  * BGR 1.2V 		    BGR 1.2V
  * �¶ȴ�����			    �¶ȴ�����
  */
#define VC_InputN_Ch0			((uint32_t)0x00000000)
#define VC_InputN_Ch1			((uint32_t)0x00001000)
#define VC_InputN_Ch2			((uint32_t)0x00002000)
#define VC_InputN_Ch3			((uint32_t)0x00003000)
#define VC_InputN_Ch4			((uint32_t)0x00004000)
#define VC_InputN_Ch5			((uint32_t)0x00005000)
#define VC_InputN_Ch6			((uint32_t)0x00006000)
#define VC_InputN_Ch7			((uint32_t)0x00007000)
#define VC_InputN_DivOut		((uint32_t)0x00008000)
#define VC_InputN_AdcVref		((uint32_t)0x00009000)
#define VC_InputN_Bgr1P2		((uint32_t)0x0000A000)
#define VC_InputN_Ts			((uint32_t)0x0000B000)

#define IS_VC_INPUT_N(INPUT_N)		(((INPUT_N) == VC_InputN_Ch0) || \
									 ((INPUT_N) == VC_InputN_Ch1) || \
									 ((INPUT_N) == VC_InputN_Ch2) || \
									 ((INPUT_N) == VC_InputN_Ch3) || \
									 ((INPUT_N) == VC_InputN_Ch4) || \
									 ((INPUT_N) == VC_InputN_Ch5) || \
									 ((INPUT_N) == VC_InputN_Ch6) || \
									 ((INPUT_N) == VC_InputN_Ch7) || \
									 ((INPUT_N) == VC_InputN_DivOut) || \
									 ((INPUT_N) == VC_InputN_AdcVref) || \
									 ((INPUT_N) == VC_InputN_Bgr1P2) || \
									 ((INPUT_N) == VC_InputN_Ts))

/** @defgroup VC_Hys
  * @{
  */
#define VC_Hys_Off		((uint32_t)0x00000000)
#define VC_Hys_10mV		((uint32_t)0x00000008)
#define VC_Hys_20mV		((uint32_t)0x00000010)
#define VC_Hys_30mV		((uint32_t)0x00000018)

#define IS_VC_HYS(HYS)		(((HYS) == VC_Hys_Off) || \
							((HYS) == VC_Hys_10mV) || \
							((HYS) == VC_Hys_20mV) || \
							((HYS) == VC_Hys_30mV))

/** @defgroup VC_Resp
  * @{
  */
#define VC_Resp_ExtraLow		((uint32_t)0x00000000)
#define VC_Resp_Low				((uint32_t)0x00000002)
#define VC_Resp_Medium			((uint32_t)0x00000004)
#define VC_Resp_High			((uint32_t)0x00000006)

#define IS_VC_RESP(RESP)		(((RESP) == VC_Resp_ExtraLow) || \
								((RESP) == VC_Resp_Low) || \
								((RESP) == VC_Resp_Medium) || \
								((RESP) == VC_Resp_High))

/** @defgroup VC_FilterEn
  * @{
  */
#define VC_Filter_Disable		((uint32_t)0x00000000)
#define VC_Filter_Enable		((uint32_t)0x00000001)

#define IS_VC_FILTER(FILTER)		(((FILTER) == VC_Filter_Disable) || \
									((FILTER) == VC_Filter_Enable))

/** @defgroup VC_FilterClk
  * @{
  */
#define VC_FltClk_RC150K		((uint32_t)0x00000000)
#define VC_FltClk_PCLK			((uint32_t)0x00000010)

#define IS_VC_FLT_CLK(FLT_CLK)		(((FLT_CLK) == VC_FltClk_RC150K) || \
									((FLT_CLK) == VC_FltClk_PCLK))

/** @defgroup VC_FilterTime
  * @{
  */
#define VC_FltTime_1Clk			((uint32_t)0x00000000)
#define VC_FltTime_3Clk			((uint32_t)0x00000002)
#define VC_FltTime_7Clk			((uint32_t)0x00000004)
#define VC_FltTime_15Clk		((uint32_t)0x00000006)
#define VC_FltTime_63Clk		((uint32_t)0x00000008)
#define VC_FltTime_255Clk		((uint32_t)0x0000000A)
#define VC_FltTime_1023Clk		((uint32_t)0x0000000C)
#define VC_FltTime_4095Clk		((uint32_t)0x0000000E)


#define IS_VC_FLT_TIME(FLT_TIME)		(((FLT_TIME) == VC_FltTime_1Clk)   || \
										((FLT_TIME) == VC_FltTime_3Clk)    || \
										((FLT_TIME) == VC_FltTime_7Clk)    || \
										((FLT_TIME) == VC_FltTime_15Clk)   || \
										((FLT_TIME) == VC_FltTime_63Clk)   || \
										((FLT_TIME) == VC_FltTime_255Clk)  || \
										((FLT_TIME) == VC_FltTime_1023Clk) || \
										((FLT_TIME) == VC_FltTime_4095Clk))

/** @defgroup VC_WindowEn
  * @{
  */
#define VC_Window_Disable		((uint32_t)0x00000000)
#define VC_Window_Enable		((uint32_t)0x00000080)

#define IS_VC_WINDOW(WINDOW)		(((WINDOW) == VC_Window_Disable) || \
									((WINDOW) == VC_Window_Enable))

/** @defgroup VC_Polarity
  * @{
  */
#define VC_Polarity_Low			((uint32_t)0x00000000)
#define VC_Polarity_High		((uint32_t)0x00000040)

#define IS_VC_POLARITY(POLARITY)		(((POLARITY) == VC_Polarity_Low) || \
										((POLARITY) == VC_Polarity_High))

/** @defgroup VC_BlankFlt
  * @{
  */
#define VC_BlankFlt_4Clk		((uint32_t)0x00000000)
#define VC_BlankFlt_8Clk		((uint32_t)0x00002000)
#define VC_BlankFlt_16Clk		((uint32_t)0x00004000)
#define VC_BlankFlt_32Clk		((uint32_t)0x00006000)
#define VC_BlankFlt_64Clk		((uint32_t)0x00008000)
#define VC_BlankFlt_128Clk		((uint32_t)0x0000A000)
#define VC_BlankFlt_256Clk		((uint32_t)0x0000C000)
#define VC_BlankFlt_512Clk		((uint32_t)0x0000E000)

#define IS_VC_BLANK_FLT(BLANK_FLT)		(((BLANK_FLT) == VC_BlankFlt_4Clk)   || \
										((BLANK_FLT) == VC_BlankFlt_8Clk)    || \
										((BLANK_FLT) == VC_BlankFlt_16Clk)   || \
										((BLANK_FLT) == VC_BlankFlt_32Clk)   || \
										((BLANK_FLT) == VC_BlankFlt_64Clk)   || \
										((BLANK_FLT) == VC_BlankFlt_128Clk)  || \
										((BLANK_FLT) == VC_BlankFlt_256Clk)  || \
										((BLANK_FLT) == VC_BlankFlt_512Clk))

/** @defgroup VC_BlankCh3B
  * @{
  */
#define VC_BlankCh3B_Disable		((uint32_t)0x00000000)
#define VC_BlankCh3B_Enable			((uint32_t)0x00001000)

#define IS_VC_BLANK_CH3B(BLANK_CH3B)		(((BLANK_CH3B) == VC_BlankCh3B_Disable) || \
											((BLANK_CH3B) == VC_BlankCh3B_Enable))

/** @defgroup VC_BlankCh2B
  * @{
  */
#define VC_BlankCh2B_Disable		((uint32_t)0x00000000)
#define VC_BlankCh2B_Enable			((uint32_t)0x00000800)

#define IS_VC_BLANK_CH2B(BLANK_CH2B)		(((BLANK_CH2B) == VC_BlankCh2B_Disable) || \
											((BLANK_CH2B) == VC_BlankCh2B_Enable))

/** @defgroup VC_BlankCh1B
  * @{
  */
#define VC_BlankCh1B_Disable		((uint32_t)0x00000000)
#define VC_BlankCh1B_Enable			((uint32_t)0x00000400)

#define IS_VC_BLANK_CH1B(BLANK_CH1B)		(((BLANK_CH1B) == VC_BlankCh1B_Disable) || \
											((BLANK_CH1B) == VC_BlankCh1B_Enable))


/** @defgroup VC_ATIMBk
  * @{
  */
#define VC_ATIMBk_Disable		((uint32_t)0x00000000)
#define VC_ATIMBk_Enable		((uint32_t)0x00000200)

#define IS_VC_ATIMBK(ATIMBK)		(((ATIMBK) == VC_ATIMBk_Disable) || \
									((ATIMBK) == VC_ATIMBk_Enable))

/** @defgroup VC_ATIMClr
  * @{
  */
#define VC_ATIMClr_Disable		((uint32_t)0x00000000)
#define VC_ATIMClr_Enable		((uint32_t)0x00000100)

#define IS_VC_ATIMCLR(ATIMCLR)		(((ATIMCLR) == VC_ATIMClr_Disable) || \
									((ATIMCLR) == VC_ATIMClr_Enable))


/**
 ******************************************************************************
 ** @brief VCģ������
 *****************************************************************************/
typedef struct
{
    uint32_t 	VC_DivVref;     	// 6-bit VDDA divider����ο���ѹѡ��
    uint32_t 	VC_DivEn;        	// ʹ��6-bit VDDA divider
    uint8_t 	VC_DivValue;		// 6-bit VDDA divider����ֵ
}VC_DivTypeDef;

/**
 ******************************************************************************
 ** @brief VCͨ������
 *****************************************************************************/
typedef struct
{
    uint32_t VC_InputP;        	// P������
    uint32_t VC_InputN;        	// N������
    uint32_t VC_Hys;         	// VC����
    uint32_t VC_Resp;      		// VC��Ӧ�ٶ�
    uint32_t VC_FilterEn;	    // VC�����˲�ʹ��
    uint32_t VC_FilterClk;      // �˲�ʱ��Դ
    uint32_t VC_FilterTime;		// ����˲�ʱ��
    uint32_t VC_Window;	      	// VC���ڱȽϹ���ʹ��
    uint32_t VC_Polarity;	    // VC����źż�������
}VC_InitTypeDef;

/**
 ******************************************************************************
 ** @brief  VCģ��Blank��������
 *****************************************************************************/
typedef struct
{
	uint32_t            VC_BlankFlt; /*Blank���ڳ���ʱ��*/

	uint32_t			VC_BlankCh3B;  /*ATIM��CH3����VCx����Blank����*/

	uint32_t 			VC_BlankCh2B; /*ATIM��CH2����VCx����Blank����*/

	uint32_t 			VC_BlankCh1B; /*ATIM��CH1����VCx����Blank����*/
}VC_BlankTypeDef;

/**
 ******************************************************************************
 ** @brief  VC������ӵ�ATIM��BK/CLR�ź�����
 *****************************************************************************/
typedef struct
{
	uint32_t 		VC_ATIMBk; 			/*VCx������ӵ�ATIM��BK�ź�*/

	uint32_t		VC_OutAtimClr;		/*VCx������ӵ�ATIM��CLR�ź�*/
}VC_OutTypeDef;

/******************************************************************************
 * Global definitions
 ******************************************************************************/

/******************************************************************************
 * Local type definitions ('typedef')
 ******************************************************************************/

/******************************************************************************
 * Global variable definitions ('extern')
 ******************************************************************************/

/******************************************************************************
 * Global function prototypes (definition in C source)
 ******************************************************************************/
//VC1/VC2ģ��VCx���������źų�ʼ��
void VC1VC2_INNInit(VC_InitTypeDef* VC_InitStruct);

//VCͨ��1��ʼ��
void VC1_ChannelInit(VC_InitTypeDef* VC_InitStruct);
//VCͨ��2��ʼ��
void VC2_ChannelInit(VC_InitTypeDef* VC_InitStruct);
//VCͨ��1ȥ��ʼ��
void VC1_ChannelDeInit(void);
//VCͨ��2ȥ��ʼ��
void VC2_ChannelDeInit(void);
//VCģ��ȥ��ʼ��
void VC_DeInit(void);

//VC1/VC2ģ��DIV�ο���ѹ��ʼ��
void VC1VC2_DIVInit(VC_DivTypeDef* VC_DivStruct);
//VC1/VC2ģ��DIV�ο���ѹȥ��ʼ��
void VC1VC2_DIVDeInit(void);

//VC1ͨ��ʹ��
void VC1_EnableChannel(void);
//VC2ͨ��ʹ��
void VC2_EnableChannel(void);
//VC1ͨ������
void VC1_DisableChannel(void);
//VC2ͨ������
void VC2_DisableChannel(void);

//VC1����˲�ʹ��
void VC1_EnableFilter(void);
//VC2����˲�ʹ��
void VC2_EnableFilter(void);
//VC1����˲�����
void VC1_DisableFilter(void);
//VC2����˲�����
void VC2_DisableFilter(void);

//VCͨ��1/2 �������Ĭ��ֵ��ʼ��
void VC1VC2_OutInit(VC_OutTypeDef* VC_OutStruct);
//VCͨ��1�����������
void VC1_OutputCfg(VC_OutTypeDef* VC_OutStruct);
//VCͨ��2�����������
void VC2_OutputCfg(VC_OutTypeDef* VC_OutStruct);

//VCͨ��1/2 BlanK����Ĭ��ֵ��ʼ��
void VC1VC2_BlankInit(VC_BlankTypeDef* VC_BlankStruct);
//VCͨ��1 BlanK��������
void VC1_BlankCfg(VC_BlankTypeDef* VC_BlankStruct);
//VCͨ��2 BlanK��������
void VC2_BlankCfg(VC_BlankTypeDef* VC_BlankStruct);

//VCͨ��1���ڱȽϹ�������
void VC1_WindowEnable(boolean_t bWindow);
//VCͨ��2���ڱȽϹ�������
void VC2_WindowEnable(boolean_t bWindow);

//VCͨ��1����źż�������
void VC1_PolarityCfg(boolean_t bPolarity);
//VCͨ��2����źż�������
void VC2_PolarityCfg(boolean_t bPolarity);

//ʹ��NVIC��VCx�ж�
void VC_EnableNvic(IRQn_Type enIrqn, uint8_t intPriority);
//��ֹNVIC��VC�ж�
void VC_DisableNvic(IRQn_Type enIrqn);
//VCͨ��1�жϽ���
void VC1_DisableIrq(void);
//VCͨ��2�жϽ���
void VC2_DisableIrq(void);
//VCͨ��1�ж�ʹ��
void VC1_EnableIrq(uint8_t intPriority);
//VCͨ��2�ж�ʹ��
void VC2_EnableIrq(uint8_t intPriority);
//����VC1�жϴ�����ʽ
void VC1_ITConfig(uint16_t VC_IT, FunctionalState NewState);
//����VC2�жϴ�����ʽ
void VC2_ITConfig(uint16_t VC_IT, FunctionalState NewState);

//���VC1�жϱ�־
void VC1_ClearIrq(void);
//���VC2�жϱ�־
void VC2_ClearIrq(void);

//��ȡVC1״̬
FlagStatus VC1_GetFlagStatus(uint16_t VC_FLAG);
//��ȡVC2״̬
FlagStatus VC2_GetFlagStatus(uint16_t VC_FLAG);

//@} // VcGroup

#ifdef __cplusplus
}
#endif

#endif /* __CW32F030_VC_H */
/******************************************************************************
 * EOF (not truncated)
 ******************************************************************************/

