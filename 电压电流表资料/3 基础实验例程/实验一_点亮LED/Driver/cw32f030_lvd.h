/**
 * @file cw32f030_lvd.h
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

#ifndef __CW32F030_LVD_H
#define __CW32F030_LVD_H

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
 ** \defgroup LvdGroup Low Voltage Detector (LVD)
 **
 ******************************************************************************/
//@{
/******************************************************************************
 * Global definitions
 ******************************************************************************/
#define  LVD_INT_PRIORITY            ((uint32_t)3)    /*VC interrupt priority (lowest by default)  */

/**
  * @}
  */
/** @defgroup LVD_interrupts_definition
  * @{
  */
#define LVD_TRIG_LEVEL                  ((uint16_t)0x0080)
#define LVD_TRIG_FALL                   ((uint16_t)0x0040)
#define LVD_TRIG_RISE                   ((uint16_t)0x0020)


#define IS_LVD_TRIG(TRIG) ((((TRIG) & (uint16_t)0xFF00) == 0x00) && ((TRIG) != 0x00))
#define IS_LVD_GET_TRIG(TRIG) (((TRIG) == LVD_TRIG_LEVEL) || \
                          ((TRIG) == LVD_TRIG_FALL) || \
                          ((TRIG) == LVD_TRIG_RISE))

/** @defgroup LVD_flags_definition
  * @{
  */
#define LVD_FLAG_FLTV                 ((uint16_t)0x0002)
#define LVD_FLAG_INTF                 ((uint16_t)0x0001)

#define IS_LVD_FLAG(FLAG) ((((FLAG) & (uint16_t)0xFF00) == 0x00) && ((FLAG) != 0x00))
#define IS_LVD_GET_FLAG(FLAG) (((FLAG) == LVD_FLAG_FLTV) || \
                              ((FLAG) == LVD_FLAG_INTF))


/** @defgroup LVD_Action
  * @{
  */
#define LVD_Action_Irq			((uint32_t)0x00000000)
#define LVD_Action_Reset		((uint32_t)0x00000002)

#define IS_LVD_ACTION(ACTION) (((ACTION) == LVD_Action_Irq) || \
                           ((ACTION) == LVD_Action_Reset))

/** @defgroup LVD_Source
  * @{
  */
#define LVD_Source_VDDA		((uint32_t)0x00000000)
#define LVD_Source_PA00		((uint32_t)0x00000004)
#define LVD_Source_PB00		((uint32_t)0x00000008)
#define LVD_Source_PB11		((uint32_t)0x0000000C)

#define IS_LVD_SOURCE(SOURCE)		(((SOURCE) == LVD_Source_VDDA) || \
							    	((SOURCE) == LVD_Source_PA00) || \
									((SOURCE) == LVD_Source_PB00) || \
									((SOURCE) == LVD_Source_PB11))

/** @defgroup LVD_Threshold
  * @{
  */
#define LVD_Threshold_2p0V		((uint32_t)0x00000000)
#define LVD_Threshold_2p11V		((uint32_t)0x00000010)
#define LVD_Threshold_2p22V		((uint32_t)0x00000020)
#define LVD_Threshold_2p33V		((uint32_t)0x00000030)
#define LVD_Threshold_2p44V		((uint32_t)0x00000040)
#define LVD_Threshold_2p55V		((uint32_t)0x00000050)
#define LVD_Threshold_2p66V		((uint32_t)0x00000060)
#define LVD_Threshold_2p77V		((uint32_t)0x00000070)
#define LVD_Threshold_2p88V		((uint32_t)0x00000080)
#define LVD_Threshold_2p99V		((uint32_t)0x00000090)
#define LVD_Threshold_3p1V		((uint32_t)0x000000A0)
#define LVD_Threshold_3p21V		((uint32_t)0x000000B0)
#define LVD_Threshold_3p32V		((uint32_t)0x000000C0)
#define LVD_Threshold_3p43V		((uint32_t)0x000000D0)
#define LVD_Threshold_3p54V		((uint32_t)0x000000E0)
#define LVD_Threshold_3p65V		((uint32_t)0x000000F0)

#define IS_LVD_THRESHOLD(THRESHOLD)		(((THRESHOLD) == LVD_Threshold_2p0V) || \
							    		((THRESHOLD) == LVD_Threshold_2p11V) || \
										((THRESHOLD) == LVD_Threshold_2p22V) || \
										((THRESHOLD) == LVD_Threshold_2p33V) || \
										((THRESHOLD) == LVD_Threshold_2p44V) || \
										((THRESHOLD) == LVD_Threshold_2p55V) || \
										((THRESHOLD) == LVD_Threshold_2p66V) || \
										((THRESHOLD) == LVD_Threshold_2p77V) || \
										((THRESHOLD) == LVD_Threshold_2p88V) || \
										((THRESHOLD) == LVD_Threshold_2p99V) || \
										((THRESHOLD) == LVD_Threshold_3p1V)  || \
										((THRESHOLD) == LVD_Threshold_3p21V) || \
										((THRESHOLD) == LVD_Threshold_3p32V) || \
										((THRESHOLD) == LVD_Threshold_3p43V) || \
										((THRESHOLD) == LVD_Threshold_3p54V) || \
										((THRESHOLD) == LVD_Threshold_3p65V))

/** @defgroup LVD_Filter
  * @{
  */
#define LVD_Filter_Disable		((uint32_t)0x00000000)
#define LVD_Filter_Enable		((uint32_t)0x00000001)

#define IS_LVD_FILTER(FILTER) (((FILTER) == LVD_Filter_Disable) || \
                           ((FILTER) == LVD_Filter_Enable))

/** @defgroup LVD_FilterClk
  * @{
  */
#define LVD_FilterClk_RC150K		((uint32_t)0x00000000)
#define LVD_FilterClk_HSI			((uint32_t)0x00000010)

#define IS_LVD_FILTER_CLK(FILTER_CLK) (((FILTER_CLK) == LVD_FilterClk_RC150K) || \
                           	   	   	   ((FILTER_CLK) == LVD_FilterClk_HSI))

/** @defgroup LVD_FilterTime
  * @{
  */
#define LVD_FilterTime_1Clk			((uint32_t)0x00000000)
#define LVD_FilterTime_3Clk			((uint32_t)0x00000002)
#define LVD_FilterTime_7Clk			((uint32_t)0x00000004)
#define LVD_FilterTime_15Clk		((uint32_t)0x00000006)
#define LVD_FilterTime_63Clk		((uint32_t)0x00000008)
#define LVD_FilterTime_255Clk		((uint32_t)0x0000000A)
#define LVD_FilterTime_1023Clk		((uint32_t)0x0000000C)
#define LVD_FilterTime_4095Clk		((uint32_t)0x0000000E)

#define IS_LVD_FILTER_TIME(FILTER_TIME)	(((FILTER_TIME) == LVD_FilterTime_1Clk) || \
										((FILTER_TIME) == LVD_FilterTime_3Clk) || \
										((FILTER_TIME) == LVD_FilterTime_7Clk) || \
										((FILTER_TIME) == LVD_FilterTime_15Clk) || \
										((FILTER_TIME) == LVD_FilterTime_63Clk) || \
										((FILTER_TIME) == LVD_FilterTime_255Clk) || \
										((FILTER_TIME) == LVD_FilterTime_1023Clk) || \
										((FILTER_TIME) == LVD_FilterTime_4095Clk))

/**
 ******************************************************************************
 ** @brief LVD����
 ** \note
 ******************************************************************************/
typedef struct
{
    uint32_t	LVD_Action;       // LVD��������
    uint32_t	LVD_Source;       // LVD�����ѹԴ
    uint32_t	LVD_Threshold;    // LVD��ֵ��ѹ
    uint32_t	LVD_FilterEn;       // �Ƿ�ʹ������˲�
    uint32_t	LVD_FilterClk;    // �˲�ʱ��Դ
    uint32_t	LVD_FilterTime;   // ����˲�ʱ��
}LVD_InitTypeDef;

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
//ʹ��NVIC��LVD�ж�
void LVD_EnableNvic(uint8_t intPriority);
//��ֹNVIC��LVD�ж�
void LVD_DisableNvic(void);
//����LVD�ж�/ϵͳ��λ������ʽ
void LVD_TrigConfig(uint16_t LVD_TRIG, FunctionalState NewState);
//ʹ��LVD�ж�
void LVD_EnableIrq(uint8_t intPriority);
//��ֹLVD�ж�
void LVD_DisableIrq(void);

//���LVD�жϱ�־
void LVD_ClearIrq(void);
//��ȡLVD�жϱ�־
boolean_t LVD_GetIrqStatus(void);
//��ȡLVDָ����״̬λ
FlagStatus LVD_GetFlagStatus(uint16_t LVD_FLAG);
//��ȡFilter���
boolean_t LVD_GetFilterResult(void);

//LVD��ʼ��
void LVD_Init(LVD_InitTypeDef* LVD_InitStruct);
//LVDȥ��ʼ��
void LVD_DeInit(void);

//ʹ��LVD
void LVD_Enable(void);
//ֹͣLVD
void LVD_Disable(void);

//@} // LvdGroup

#ifdef __cplusplus
}
#endif

#endif /* __CW32F030_LVD_H */
/******************************************************************************
 * EOF (not truncated)
 ******************************************************************************/
