/**
* @file cw32f030_lvd.h
* @author P&S (you@domain.com)
* @brief
* @version 0.1
* @date 2021-07-01
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

#ifndef __CW32F030_ADC_H
#define __CW32F030_ADC_H


/******************************************************************************/
/* Include files                                                              */
/******************************************************************************/
#include "base_types.h"

/* C binding of definitions if building with C++ compiler */
#ifdef __cplusplus
extern "C"
{
#endif

/**
 ******************************************************************************
 ** \defgroup AdcGroup AD Converter (ADC)
  **
 ******************************************************************************/
 
//@{

/******************************************************************************
 * Global definitions
 ******************************************************************************/
#define  ADC_INT_PRIORITY            ((uint32_t)3)    /*ADC interrupt priority (lowest by default)  */

#define COEFF_TS 		(0.0924f)
#define ADDR_TRIM_1P5	(0x0001260A)
#define ADDR_TRIM_2P5	(0x0001260C)
#define ADDR_T0			(0x00012609)
/**
  * @}
  */

/** @defgroup ADC_interrupts_definition
  * @{
  */
#define ADC_IT_READY                 ((uint16_t)0x0080)
#define ADC_IT_OVW                   ((uint16_t)0x0040)
#define ADC_IT_WDTR                  ((uint16_t)0x0020)
#define ADC_IT_WDTH                  ((uint16_t)0x0010)
#define ADC_IT_WDTL                  ((uint16_t)0x0008)
#define ADC_IT_EOA                   ((uint16_t)0x0004)
#define ADC_IT_EOS                   ((uint16_t)0x0002)
#define ADC_IT_EOC                   ((uint16_t)0x0001)

#define IS_ADC_IT(IT) ((((IT) & (uint16_t)0xFF00) == 0x00) && ((IT) != 0x00))
#define IS_ADC_GET_IT(IT) (((IT) == ADC_IT_READY) || \
                            ((IT) == ADC_IT_OVW) || \
                            ((IT) == ADC_IT_WDTR)|| \
                            ((IT) == ADC_IT_WDTH)|| \
                            ((IT) == ADC_IT_WDTL)|| \
                            ((IT) == ADC_IT_EOA)|| \
                            ((IT) == ADC_IT_EOS)|| \
                            ((IT) == ADC_IT_EOC))


/** @defgroup ADC external interrupts_definition
  * @{
  */
#define ADC_TRIG_DMA                     ((uint16_t)0x8000)
#define ADC_TRIG_I2C2                    ((uint16_t)0x4000)
#define ADC_TRIG_I2C1                    ((uint16_t)0x2000)
#define ADC_TRIG_SPI2                    ((uint16_t)0x1000)
#define ADC_TRIG_SPI1                    ((uint16_t)0x0800)
#define ADC_TRIG_UART3                   ((uint16_t)0x0400)
#define ADC_TRIG_UART2                   ((uint16_t)0x0200)
#define ADC_TRIG_UART1                   ((uint16_t)0x0100)
#define ADC_TRIG_BTIM3                   ((uint16_t)0x0080)
#define ADC_TRIG_BTIM2                   ((uint16_t)0x0040)
#define ADC_TRIG_BTIM1                   ((uint16_t)0x0020)
#define ADC_TRIG_GTIM4                   ((uint16_t)0x0010)
#define ADC_TRIG_GTIM3                   ((uint16_t)0x0008)
#define ADC_TRIG_GTIM2                   ((uint16_t)0x0004)
#define ADC_TRIG_GTIM1                   ((uint16_t)0x0002)
#define ADC_TRIG_ATIM                    ((uint16_t)0x0001)

#define IS_ADC_TRIG(TRIG) ((((TRIG) & (uint16_t)0x0000) == 0x00) && ((TRIG) != 0x00))
#define IS_ADC_GET_TRIG(TRIG) (((TRIG) == ADC_TRIG_DMA) || \
                              ((TRIG) == ADC_TRIG_I2C2) || \
                              ((TRIG) == ADC_TRIG_I2C1)|| \
                              ((TRIG) == ADC_TRIG_SPI2)|| \
                              ((TRIG) == ADC_TRIG_SPI1)|| \
                              ((TRIG) == ADC_TRIG_UART3)|| \
                              ((TRIG) == ADC_TRIG_UART2)|| \
                              ((TRIG) == ADC_TRIG_UART1) || \
                              ((TRIG) == ADC_TRIG_BTIM3)|| \
                              ((TRIG) == ADC_TRIG_BTIM2)|| \
                              ((TRIG) == ADC_TRIG_BTIM1)|| \
                              ((TRIG) == ADC_TRIG_GTIM4)|| \
                              ((TRIG) == ADC_TRIG_GTIM3)|| \
                              ((TRIG) == ADC_TRIG_GTIM2)|| \
                              ((TRIG) == ADC_TRIG_GTIM1)|| \
                              ((TRIG) == ADC_TRIG_ATIM))


/******************************************************************************
 ** Global type definitions
 *****************************************************************************/

/** @defgroup ADC_OpMode
  * @{
  */
#define ADC_SingleChOneMode				((uint32_t)0x00000000)
#define ADC_SingleChMoreMode			((uint32_t)0x00000002)
#define ADC_SingleChContinuousMode		((uint32_t)0x00000004)
#define ADC_SerialChContinuousMode		((uint32_t)0x00000006)
#define ADC_SerialChScanMode			((uint32_t)0x00000008)
#define ADC_SerialChMoreMode			((uint32_t)0x0000000A)
#define ADC_SerialChBreakMode			((uint32_t)0x0000000C)


#define IS_ADC_OP_MODE(OP_MODE)		(((OP_MODE) == ADC_SingleChOneMode)   || \
										((OP_MODE) == ADC_SingleChMoreMode)    || \
										((OP_MODE) == ADC_SingleChContinuousMode)   || \
										((OP_MODE) == ADC_SerialChContinuousMode)   || \
										((OP_MODE) == ADC_SerialChScanMode)   || \
										((OP_MODE) == ADC_SerialChMoreMode)  || \
										((OP_MODE) == ADC_SerialChBreakMode))


/** @defgroup ADC_ClkDiv
  * @{
  */
#define ADC_Clk_Div1		((uint32_t)0x00000000)
#define ADC_Clk_Div2		((uint32_t)0x00000100)
#define ADC_Clk_Div4		((uint32_t)0x00000200)
#define ADC_Clk_Div8		((uint32_t)0x00000300)
#define ADC_Clk_Div16		((uint32_t)0x00000400)
#define ADC_Clk_Div32		((uint32_t)0x00000500)
#define ADC_Clk_Div64		((uint32_t)0x00000600)
#define ADC_Clk_Div128		((uint32_t)0x00000700)

#define IS_ADC_CLK_DIV(CLK_DIV)		(((CLK_DIV) == ADC_Clk_Div1)   || \
										((CLK_DIV) == ADC_Clk_Div2)    || \
										((CLK_DIV) == ADC_Clk_Div4)   || \
										((CLK_DIV) == ADC_Clk_Div8)   || \
										((CLK_DIV) == ADC_Clk_Div16)   || \
										((CLK_DIV) == ADC_Clk_Div32)  || \
										((CLK_DIV) == ADC_Clk_Div64)  || \
										((CLK_DIV) == ADC_Clk_Div128))



/** @defgroup ADC_VrefSel
  * @{
  */
#define ADC_Vref_BGR1p5			((uint32_t)0x00000000)
#define ADC_Vref_BGR2p5			((uint32_t)0x00000040)
#define ADC_Vref_Extern1		((uint32_t)0x00000080)
#define ADC_Vref_VDDA			((uint32_t)0x000000C0)

#define IS_ADC_VREF_SEL(VREF_SEL)		(((VREF_SEL) == ADC_Vref_BGR1p5)   || \
										((VREF_SEL) == ADC_Vref_BGR2p5)    || \
										((VREF_SEL) == ADC_Vref_Extern1)   || \
										((VREF_SEL) == ADC_Vref_VDDA))



/** @defgroup ADC_ChSel
  * @{
  * ͨ��0����PA00
  * ͨ��1����PA01
  * ͨ��2����PA02
  * ͨ��3����PA03
  * ͨ��4����PA04
  * ͨ��5����PA05
  * ͨ��6����PA06
  * ͨ��7����PA07
  * ͨ��8����PB00
  * ͨ��9����PB01
  * ͨ��10����PB02
  * ͨ��11����PB10
  * ͨ��12����PB11
  * 1/3 VDDA(����ʹ����������)
  * BGR_TS(����ʹ����������)
  * Vref1P2(����ʹ����������)
  */
#define ADC_ExInputCH0		((uint32_t)0x00000000)
#define ADC_ExInputCH1		((uint32_t)0x00000001)
#define ADC_ExInputCH2		((uint32_t)0x00000002)
#define ADC_ExInputCH3		((uint32_t)0x00000003)
#define ADC_ExInputCH4		((uint32_t)0x00000004)
#define ADC_ExInputCH5		((uint32_t)0x00000005)
#define ADC_ExInputCH6		((uint32_t)0x00000006)
#define ADC_ExInputCH7		((uint32_t)0x00000007)
#define ADC_ExInputCH8		((uint32_t)0x00000008)
#define ADC_ExInputCH9		((uint32_t)0x00000009)
#define ADC_ExInputCH10		((uint32_t)0x0000000A)
#define ADC_ExInputCH11		((uint32_t)0x0000000B)
#define ADC_ExInputCH12		((uint32_t)0x0000000C)
#define ADC_VddaDiV3Input	((uint32_t)0x0000000D)
#define ADC_TsInput			((uint32_t)0x0000000E)
#define ADC_Vref1P2Input	((uint32_t)0x0000000F)

#define IS_ADC_CH_SEL(CH_SEL)		(((CH_SEL) == ADC_ExInputCH0)   || \
										((CH_SEL) == ADC_ExInputCH1)    || \
										((CH_SEL) == ADC_ExInputCH2)   || \
										((CH_SEL) == ADC_ExInputCH3)   || \
										((CH_SEL) == ADC_ExInputCH4)   || \
										((CH_SEL) == ADC_ExInputCH5)  || \
										((CH_SEL) == ADC_ExInputCH6)  || \
										((CH_SEL) == ADC_ExInputCH7)    || \
										((CH_SEL) == ADC_ExInputCH8)   || \
										((CH_SEL) == ADC_ExInputCH9)   || \
										((CH_SEL) == ADC_ExInputCH10)   || \
										((CH_SEL) == ADC_ExInputCH11)  || \
										((CH_SEL) == ADC_ExInputCH12)   || \
										((CH_SEL) == ADC_VddaDiV3Input)  || \
										((CH_SEL) == ADC_TsInput)  || \
										((CH_SEL) == ADC_Vref1P2Input))

/** @defgroup ADC_SampleTime
  * @{
  */
#define ADC_SampTime5Clk		((uint32_t)0x00000000)
#define ADC_SampTime6Clk		((uint32_t)0x00000800)
#define ADC_SampTime8Clk		((uint32_t)0x00001000)
#define ADC_SampTime10Clk		((uint32_t)0x00001800)

#define IS_ADC_SAMPLE_TIME(SAMPLE_TIME)		(((SAMPLE_TIME) == ADC_SampTime5Clk)   || \
										((SAMPLE_TIME) == ADC_SampTime6Clk)    || \
										((SAMPLE_TIME) == ADC_SampTime8Clk)   || \
										((SAMPLE_TIME) == ADC_SampTime10Clk))



/** @defgroup ADC_TrigSel
  * @{
  */
#define ADC_TrigATimerDisable		((uint32_t)0x00000000)
#define ADC_TrigATimerEnable		((uint32_t)0x00000001)

#define ADC_TrigGTimer1Disable		((uint32_t)0x00000000)
#define ADC_TrigGTimer1Enable		((uint32_t)0x00000002)

#define ADC_TrigGTimer2Disable		((uint32_t)0x00000000)
#define ADC_TrigGTimer2Enable		((uint32_t)0x00000004)

#define ADC_TrigGTimer3Disable		((uint32_t)0x00000000)
#define ADC_TrigGTimer3Enable		((uint32_t)0x00000008)

#define ADC_TrigGTimer4Disable		((uint32_t)0x00000000)
#define ADC_TrigGTimer4Enable		((uint32_t)0x00000010)

#define ADC_TrigBTimer1Disable		((uint32_t)0x00000000)
#define ADC_TrigBTimer1Enable		((uint32_t)0x00000020)

#define ADC_TrigBTimer2Disable		((uint32_t)0x00000000)
#define ADC_TrigBTimer2Enable		((uint32_t)0x00000040)

#define ADC_TrigBTimer3Disable		((uint32_t)0x00000000)
#define ADC_TrigBTimer3Enable		((uint32_t)0x00000080)

#define ADC_TrigUart1Disable		((uint32_t)0x00000000)
#define ADC_TrigUart1Enable			((uint32_t)0x00000100)

#define ADC_TrigUart2Disable		((uint32_t)0x00000000)
#define ADC_TrigUart2Enable			((uint32_t)0x00000200)

#define ADC_TrigUart3Disable		((uint32_t)0x00000000)
#define ADC_TrigUart3Enable			((uint32_t)0x00000400)

#define ADC_TrigSPI1Disable			((uint32_t)0x00000000)
#define ADC_TrigSPI1Enable			((uint32_t)0x00000800)

#define ADC_TrigSPI2Disable			((uint32_t)0x00000000)
#define ADC_TrigSPI2Enable			((uint32_t)0x00001000)

#define ADC_TrigI2C1Disable			((uint32_t)0x00000000)
#define ADC_TrigI2C1Enable			((uint32_t)0x00002000)

#define ADC_TrigI2C2Disable			((uint32_t)0x00000000)
#define ADC_TrigI2C2Enable			((uint32_t)0x00004000)

#define ADC_TrigDMADisable			((uint32_t)0x00000000)
#define ADC_TrigDMAEnable			((uint32_t)0x00008000)

#define IS_ADC_TRIG_SEL(TRIG_SEL)		(((TRIG_SEL) == ADC_TrigATimerDisable)   || \
										((TRIG_SEL) == ADC_TrigATimerEnable)     || \
										((TRIG_SEL) == ADC_TrigGTimer1Disable)   || \
										((TRIG_SEL) == ADC_TrigGTimer1Enable)    || \
										((TRIG_SEL) == ADC_TrigGTimer2Disable)   || \
										((TRIG_SEL) == ADC_TrigGTimer2Enable)    || \
										((TRIG_SEL) == ADC_TrigGTimer3Disable)   || \
										((TRIG_SEL) == ADC_TrigGTimer3Enable)    || \
										((TRIG_SEL) == ADC_TrigGTimer4Disable)   || \
										((TRIG_SEL) == ADC_TrigGTimer4Enable)    || \
										((TRIG_SEL) == ADC_TrigBTimer1Disable)   || \
										((TRIG_SEL) == ADC_TrigBTimer1Enable)    || \
										((TRIG_SEL) == ADC_TrigBTimer2Disable)   || \
										((TRIG_SEL) == ADC_TrigBTimer2Enable)    || \
										((TRIG_SEL) == ADC_TrigBTimer3Disable)   || \
										((TRIG_SEL) == ADC_TrigBTimer3Enable)    || \
										((TRIG_SEL) == ADC_TrigUart1Disable)     || \
										((TRIG_SEL) == ADC_TrigUart1Enable)      || \
										((TRIG_SEL) == ADC_TrigUart2Disable)     || \
										((TRIG_SEL) == ADC_TrigUart2Enable)   	 || \
										((TRIG_SEL) == ADC_TrigUart3Disable)     || \
										((TRIG_SEL) == ADC_TrigUart3Enable)      || \
										((TRIG_SEL) == ADC_TrigSPI1Disable)	     || \
										((TRIG_SEL) == ADC_TrigSPI1Enable)       || \
										((TRIG_SEL) == ADC_TrigSPI2Disable)      || \
										((TRIG_SEL) == ADC_TrigSPI2Enable)       || \
										((TRIG_SEL) == ADC_TrigI2C1Disable)      || \
										((TRIG_SEL) == ADC_TrigI2C1Enable)       || \
										((TRIG_SEL) == ADC_TrigI2C2Disable)      || \
										((TRIG_SEL) == ADC_TrigI2C2Enable)       || \
										((TRIG_SEL) == ADC_TrigDMADisable)       || \
										((TRIG_SEL) == ADC_TrigDMAEnable))



/** @defgroup ADC_SqrEns
  * @{
  */
#define ADC_SqrEns0			((uint32_t)0x00000000)
#define ADC_SqrEns01		((uint32_t)0x00010000)
#define ADC_SqrEns02		((uint32_t)0x00020000)
#define ADC_SqrEns03		((uint32_t)0x00030000)

#define IS_ADC_SQR_ENS(SQR_ENS)		(((SQR_ENS) == ADC_SqrEns0)   || \
									((SQR_ENS) == ADC_SqrEns01)   || \
									((SQR_ENS) == ADC_SqrEns02)   || \
									((SQR_ENS) == ADC_SqrEns03))



/** @defgroup ADC_SqrChmux
  * @{
  * ͨ��0����PA00
  * ͨ��1����PA01
  * ͨ��2����PA02
  * ͨ��3����PA03
  * ͨ��4����PA04
  * ͨ��5����PA05
  * ͨ��6����PA06
  * ͨ��7����PA07
  * ͨ��8����PB00
  * ͨ��9����PB01
  * ͨ��10����PB02
  * ͨ��11����PB10
  * ͨ��12����PB11
  * 1/3 VDDA(����ʹ����������)
  * BGR_TS(����ʹ����������)
  * Vref1P2(����ʹ����������)
  */
#define ADC_SqrCh0		((uint32_t)0x00000000)
#define ADC_SqrCh1		((uint32_t)0x00000001)
#define ADC_SqrCh2		((uint32_t)0x00000002)
#define ADC_SqrCh3		((uint32_t)0x00000003)
#define ADC_SqrCh4		((uint32_t)0x00000004)
#define ADC_SqrCh5		((uint32_t)0x00000005)
#define ADC_SqrCh6		((uint32_t)0x00000006)
#define ADC_SqrCh7		((uint32_t)0x00000007)
#define ADC_SqrCh8		((uint32_t)0x00000008)
#define ADC_SqrCh9		((uint32_t)0x00000009)
#define ADC_SqrCh10		((uint32_t)0x0000000A)
#define ADC_SqrCh11		((uint32_t)0x0000000B)
#define ADC_SqrCh12		((uint32_t)0x0000000C)
#define ADC_SqrVddaDiV3	((uint32_t)0x0000000D)
#define ADC_SqrTs		((uint32_t)0x0000000E)
#define ADC_SqrVref1P2	((uint32_t)0x0000000F)

#define IS_ADC_SQR_CH(SQR_CH)		(((SQR_CH) == ADC_SqrCh0)   		|| \
										((SQR_CH) == ADC_SqrCh1)    	|| \
										((SQR_CH) == ADC_SqrCh2)   		|| \
										((SQR_CH) == ADC_SqrCh3)   		|| \
										((SQR_CH) == ADC_SqrCh4)   		|| \
										((SQR_CH) == ADC_SqrCh5)  		|| \
										((SQR_CH) == ADC_SqrCh6)  		|| \
										((SQR_CH) == ADC_SqrCh7)    	|| \
										((SQR_CH) == ADC_SqrCh8)   		|| \
										((SQR_CH) == ADC_SqrCh9)   		|| \
										((SQR_CH) == ADC_SqrCh10)   	|| \
										((SQR_CH) == ADC_SqrCh11)  		|| \
										((SQR_CH) == ADC_SqrCh12)   	|| \
										((SQR_CH) == ADC_SqrVddaDiV3)	|| \
										((SQR_CH) == ADC_SqrTs)  		|| \
										((SQR_CH) == ADC_SqrVref1P2))



/** @defgroup ADC_WdtChmux
  * @{
  * ͨ��0����PA00
  * ͨ��1����PA01
  * ͨ��2����PA02
  * ͨ��3����PA03
  * ͨ��4����PA04
  * ͨ��5����PA05
  * ͨ��6����PA06
  * ͨ��7����PA07
  * ͨ��8����PB00
  * ͨ��9����PB01
  * ͨ��10����PB02
  * ͨ��11����PB10
  * ͨ��12����PB11
  * 1/3 VDDA(����ʹ����������)
  * BGR_TS(����ʹ����������)
  * Vref1P2(����ʹ����������)
  */
#define ADC_WdtCh0		((uint32_t)0x00000000)
#define ADC_WdtCh1		((uint32_t)0x00000100)
#define ADC_WdtCh2		((uint32_t)0x00000200)
#define ADC_WdtCh3		((uint32_t)0x00000300)
#define ADC_WdtCh4		((uint32_t)0x00000400)
#define ADC_WdtCh5		((uint32_t)0x00000500)
#define ADC_WdtCh6		((uint32_t)0x00000600)
#define ADC_WdtCh7		((uint32_t)0x00000700)
#define ADC_WdtCh8		((uint32_t)0x00000800)
#define ADC_WdtCh9		((uint32_t)0x00000900)
#define ADC_WdtCh10		((uint32_t)0x00000A00)
#define ADC_WdtCh11		((uint32_t)0x00000B00)
#define ADC_WdtCh12		((uint32_t)0x00000C00)
#define ADC_WdtVddaDiV3	((uint32_t)0x00000D00)
#define ADC_WdtTs		((uint32_t)0x00000E00)
#define ADC_WdtVref1P2	((uint32_t)0x00000F00)

#define IS_ADC_WDT_CH(WDT_CH)		(((WDT_CH) == ADC_WdtCh0)   		|| \
										((WDT_CH) == ADC_WdtCh1)    	|| \
										((WDT_CH) == ADC_WdtCh2)   		|| \
										((WDT_CH) == ADC_WdtCh3)   		|| \
										((WDT_CH) == ADC_WdtCh4)   		|| \
										((WDT_CH) == ADC_WdtCh5)  		|| \
										((WDT_CH) == ADC_WdtCh6)  		|| \
										((WDT_CH) == ADC_WdtCh7)    	|| \
										((WDT_CH) == ADC_WdtCh8)   		|| \
										((WDT_CH) == ADC_WdtCh9)   		|| \
										((WDT_CH) == ADC_WdtCh10)   	|| \
										((WDT_CH) == ADC_WdtCh11)  		|| \
										((WDT_CH) == ADC_WdtCh12)   	|| \
										((WDT_CH) == ADC_WdtVddaDiV3)	|| \
										((WDT_CH) == ADC_WdtTs)  		|| \
										((WDT_CH) == ADC_WdtVref1P2))


/** @defgroup ADC_WdtAll
  * @{
  */
#define ADC_WdtDisable		((uint32_t)0x00000000)
#define ADC_WdtEnable		((uint32_t)0x00002000)

#define IS_ADC_WDT_EN(WDT_EN)		(((WDT_EN) == ADC_WdtDisable) || \
												((WDT_EN) == ADC_WdtEnable))

/** @defgroup ADC_WdtrIrq
  * @{
  */
#define ADC_WdtrDisable		((uint32_t)0x00000000)
#define ADC_WdtrEnable		((uint32_t)0x00000020)

#define IS_ADC_WDTR_EN(WDTR_EN)		(((WDTR_EN) == ADC_WdtrDisable) || \
												((WDTR_EN) == ADC_WdtrEnable))

/** @defghoup ADC_WdthIrq
  * @{
  */
#define ADC_WdthDisable		((uint32_t)0x00000000)
#define ADC_WdthEnable		((uint32_t)0x00000010)

#define IS_ADC_WDTH_EN(WDTH_EN)		(((WDTH_EN) == ADC_WdthDisable) || \
												((WDTH_EN) == ADC_WdthEnable))

/** @defgloup ADC_WdtlIrq
  * @{
  */
#define ADC_WdtlDisable		((uint32_t)0x00000000)
#define ADC_WdtlEnable		((uint32_t)0x00000008)

#define IS_ADC_WDTL_EN(WDTL_EN)		(((WDTL_EN) == ADC_WdtlDisable) || \
												((WDTL_EN) == ADC_WdtlEnable))



/** @defgroup ADC_Align
  * @{
  */
#define ADC_AlignRight		((uint32_t)0x00000000)
#define ADC_AlignLeft		((uint32_t)0x00000040)

#define IS_ADC_DATA_ALIGN(DATA_ALIGN)		(((DATA_ALIGN) == ADC_AlignRight)   || \
											((DATA_ALIGN) == ADC_AlignLeft))



/** @defgroup ADC_DataDiscard
  * @{
  */
#define ADC_DiscardNull			((uint32_t)0x00000000)
#define ADC_DiscardEnable		((uint32_t)0x00000020)

#define IS_ADC_DATA_DISCARD(DATA_DISCARD)		(((DATA_DISCARD) == ADC_DiscardNull) || \
												((DATA_DISCARD) == ADC_DiscardEnable))



/** @defgroup ADC_TsEn
  * @{
  */
#define ADC_TsDisable		((uint32_t)0x00000000)
#define ADC_TsEnable		((uint32_t)0x00000020)

#define IS_ADC_TS_ENABLE(TS_ENABLE)		(((TS_ENABLE) == ADC_TsDisable) || \
										((TS_ENABLE) == ADC_TsEnable))

/** @defgroup ADC_InBufEn
  * @{
  */
#define ADC_BufDisable		((uint32_t)0x00000000)
#define ADC_BufEnable		((uint32_t)0x00002000)

#define IS_ADC_BUF_ENABLE(BUF_ENABLE)		(((BUF_ENABLE) == ADC_BufDisable) || \
										((BUF_ENABLE) == ADC_BufEnable))

/** @defgroup ADC_DMAEn
  * @{
  */
#define ADC_DmaDisable		((uint32_t)0x00000000)
#define ADC_DmaEnable		((uint32_t)0x00000080)

#define IS_ADC_DMA_ENABLE(DMA_ENABLE)		(((DMA_ENABLE) == ADC_DmaDisable) || \
										((DMA_ENABLE) == ADC_DmaEnable))

/** @defgroup ADC_AccEn
  * @{
  */
#define ADC_AccDisable		((uint32_t)0x00000000)
#define ADC_AccEnable		((uint32_t)0x00000100)

#define IS_ADC_ACC_ENABLE(ACC_ENABLE)		(((ACC_ENABLE) == ADC_AccDisable) || \
										((ACC_ENABLE) == ADC_AccEnable))



/** @defgroup ADC_AutoStop
  * @{
  */
#define ADC_AutoStopDisable		((uint32_t)0x00000000)
#define ADC_AutoStopEnable		((uint32_t)0x00000002)

#define IS_ADC_AUTO_STOP(AUTO_STOP)		(((AUTO_STOP) == ADC_AutoStopDisable) || \
										((AUTO_STOP) == ADC_AutoStopEnable))

/******************************************************************************
 * Extern type definitions ('typedef')                                        *
 ******************************************************************************/

/**
 ******************************************************************************
 ** @brief  ADC����
 *****************************************************************************/
typedef struct
{
    uint32_t    	ADC_OpMode;			/*ADC����ģʽ*/

    uint32_t    	ADC_ClkDiv;			/*ADCʱ��ѡ��*/

    uint32_t  		ADC_SampleTime;		/*ADC����ʱ��*/

    uint32_t   		ADC_VrefSel;	    /*ADC�ο���ѹ*/

    uint32_t   		ADC_InBufEn;		/*ADC��������ʹ��*/

    uint32_t   		ADC_TsEn;			/*�����¶ȴ�����ʹ��*/

    uint32_t   		ADC_DMAEn;			/*ADCת����ɴ���DMAʹ��*/

    uint32_t     	ADC_Align;			/*ADCת��������뷽ʽ*/

    uint32_t		ADC_AccEn;			/*ת������ۼ�ʹ��*/
}ADC_InitTypeDef;

/**
 ******************************************************************************
 ** @brief  ADCģ�⿴�Ź�����
 *****************************************************************************/
typedef struct
{
	uint32_t 			ADC_WdtCh;  /*ADCģ�⿴�Ź�ͨ��*/

	uint32_t 			ADC_WdtAll;  /*ADCģ�⿴�Ź�ʹ��*/

	uint32_t 			ADC_WdtrIrq; /*ADC����ģ�⿴�Ź�ʹ��*/

	uint32_t 			ADC_WdthIrq; /*ADC�ϳ���ģ�⿴�Ź�ʹ��*/

	uint32_t 			ADC_WdtlIrq; /*ADC�³���ģ�⿴�Ź�ʹ��*/

	uint32_t 			ADC_Vth; 	 /*ADCģ�⿴�Ź�����ֵ*/

	uint32_t 			ADC_Vtl; 	 /*ADCģ�⿴�Ź�����ֵ*/
}ADC_WdtTypeDef;

/**
 ******************************************************************************
 ** @brief  ADC��ͨ������
 *****************************************************************************/
typedef struct
{
    uint32_t 			ADC_Chmux;	/*ADC��ͨ��ת��ģʽ��ת��ͨ��*/

    uint32_t			ADC_DiscardEn;	/*��ͨ��ADCת����������������*/

    ADC_InitTypeDef  	ADC_InitStruct;	/*ADC��ʼ��*/

    ADC_WdtTypeDef   	ADC_WdtStruct;		/*ADCģ�⿴�Ź�����*/
}ADC_SingleChTypeDef;

/**
 ******************************************************************************
 ** @brief  ADC��������
 *****************************************************************************/
typedef struct
{
	uint32_t    		ADC_SqrEns;		/*ADC����ת������������*/

	uint32_t  			ADC_Sqr3Chmux;	/*ADC����3��ת��ͨ��*/

	uint32_t  			ADC_Sqr2Chmux;	/*ADC����2��ת��ͨ��*/

	uint32_t  			ADC_Sqr1Chmux;	/*ADC����1��ת��ͨ��*/

	uint32_t  			ADC_Sqr0Chmux;	/*ADC����0��ת��ͨ��*/

    ADC_InitTypeDef		ADC_InitStruct;		/*ADC��ʼ��*/
}ADC_SerialChTypeDef;


/**
 ******************************************************************************
 ** @brief  ADC�ж�����
 *****************************************************************************/
typedef struct
{
	boolean_t 	ADC_ReadyFlag;	/*ADC��ʼ����ɱ�־*/

	boolean_t 	ADC_OvwIrq;		/*ADCת���������ж�*/

	boolean_t 	ADC_WdtrIrq;		/*ADCģ�⿴�Ź������ж�*/

	boolean_t 	ADC_WdthIrq;		/*ADCģ�⿴�Ź�����ֵ�ж�*/

	boolean_t 	ADC_WdtlIrq;		/*ADCģ�⿴�Ź�����ֵ�ж�*/

	boolean_t 	ADC_EoaIrq;		/*ADC���ת������ж�*/

	boolean_t 	ADC_EosIrq;		/*ADC����ת������ж�*/

	boolean_t 	ADC_EocIrq;		/*ADC����ת������ж�*/
}ADC_IrqTypeDef;





/******************************************************************************
 * Global variable definitions ('extern')
 ******************************************************************************/

/******************************************************************************
 * Global function prototypes (definition in C source)
 ******************************************************************************/
//ADCȥ��ʼ��
void ADC_DeInit(void);
//ADC��ʼ��
void ADC_Init(ADC_InitTypeDef* ADC_InitStruct);
//ADCĬ��ֵ��ʼ��
void ADC_StructInit(ADC_InitTypeDef* ADC_InitStruct);
//ADCģ�⿴�Ź�Ĭ��ֵ��ʼ��
void ADC_WdtInit(ADC_WdtTypeDef* ADC_WdtStruct);
//ADCʹ��
void ADC_Enable(void);
//ADC����
void ADC_Disable(void);

//����DMA��ȡ����
void ADC_DMACmd(FunctionalState NewState);
//����DMA��ȡʹ��
void ADC_DMAEnable(void);
//����DMA��ȡ��ֹ
void ADC_DMADisable(void);

//ADCת�������������
void ADC_SoftwareStartConvCmd(FunctionalState NewState);
//ADC�ⲿ�жϴ���Դ����
void ADC_ExtTrigCfg(uint16_t ADC_TRIG, FunctionalState NewState);

//��ͨ��ת��ģʽ��������
void ADC_SingleChCommon(ADC_SingleChTypeDef* ADC_SingleChStruct);
//ADC��ͨ������ת��ģʽ����
void ADC_SingleChOneModeCfg(ADC_SingleChTypeDef* ADC_SingleChStruct);
//ADC��ͨ�����ת��ģʽ����
void ADC_SingleChMoreModeCfg(ADC_SingleChTypeDef* ADC_SingleChStruct, uint8_t cntAdcSample);
//ADC��ͨ������ת��ģʽ����
void ADC_SingleChContinuousModeCfg(ADC_SingleChTypeDef* ADC_SingleChStruct);
//ADC����ת��ģʽ��������
void ADC_SerialChCommon(ADC_SerialChTypeDef* ADC_SerialChStruct);
//ADC��������ת��ģʽ����
void ADC_SerialChContinuousModeCfg(ADC_SerialChTypeDef* ADC_SerialChStruct);
//ADC����ɨ��ת��ģʽ����
void ADC_SerialChScanModeCfg(ADC_SerialChTypeDef* ADC_SerialChStruct);
//ADC���ж��ת��ģʽ����
void ADC_SerialChMoreModeCfg(ADC_SerialChTypeDef* ADC_SerialChStruct, uint8_t cntAdcSample);
//ADC���ж���ת��ģʽ����
void ADC_SerialChBreakModeCfg(ADC_SerialChTypeDef* ADC_SerialChStruct);

//����SQR0ת��ͨ������
void ADC_Sqr0ChannelCfg(ADC_SerialChTypeDef* ADC_SerialChStruct);
//����SQR0/SQR1ת��ͨ������
void ADC_Sqr01ChannelCfg(ADC_SerialChTypeDef* ADC_SerialChStruct);
//����SQR0~SQR2ת��ͨ������
void ADC_Sqr02ChannelCfg(ADC_SerialChTypeDef* ADC_SerialChStruct);
//����SQR0~SQR3ת��ͨ������
void ADC_Sqr03ChannelCfg(ADC_SerialChTypeDef* ADC_SerialChStruct);

//��ͨ��ģʽ�����ø�����ʹ��
void ADC_BufEnSingleCh( uint32_t enAdcSampCh);
//����ģʽ�����ø�����ʹ��
void ADC_BufEnSerialCh( uint32_t enAdcSampCh);

//ADCģ�⿴�Ź�����
void ADC_WdtConfig(ADC_WdtTypeDef* ADC_WdtStruct);

//ADC�ж�����
void ADC_ITConfig(uint16_t ADC_IT, FunctionalState NewState);
//ADC�ж�ʹ��
void ADC_EnableIrq(uint8_t intPriority);
//ADC�жϽ�ֹ
void ADC_DisableIrq(void);
//ʹ��NVIC��ADC�ж�
void ADC_EnableNvic(uint8_t intPriority);
//����NVIC��ADC�ж�
void ADC_DisableNvic(void);
//��ȡADC�����ж�״̬
void ADC_GetITStatusAll(volatile uint8_t* pFlagAdcIrq);
//��ȡADCָ�����ж�״̬
ITStatus ADC_GetITStatus(uint16_t ADC_IT);
//���ADC�����ж�״̬
void ADC_ClearITPendingAll(void);
//���ADCָ�����ж�״̬
void ADC_ClearITPendingBit(uint16_t ADC_IT);

//��ȡ����ת������ֵ
uint16_t ADC_GetConversionValue(void);
//��ȡSQR0ͨ������ֵ
void ADC_GetSqr0Result(uint16_t* pAdcResult);
//��ȡSQR1ͨ������ֵ
void ADC_GetSqr1Result(uint16_t* pAdcResult);
//��ȡSQR2ͨ������ֵ
void ADC_GetSqr2Result(uint16_t* pAdcResult);
//��ȡSQR3ͨ������ֵ
void ADC_GetSqr3Result(uint16_t* pAdcResult);
//��ȡ�ۼӲ���ֵ
void ADC_GetAccResult(uint32_t* pAdcAccResult);
//�����ۼӲ���ֵ
void ADC_ClrAccResult(void);

//���òο���ѹ
void ADC_SetVref(uint32_t ADC_VrefSel);
//���ý�����뷽ʽ
void ADC_SetAlign(uint32_t enAlign);
//���õ�ͨ��ADCת���������������
void ADC_SetDiscard(uint32_t enDiscard);
//���������¶ȴ�����ʹ�ܿ���
void ADC_SetTs(uint32_t enTs);
//��ȡADC�ο���ѹ1.5Vʱ���¶ȴ������Ĳ����¶�
void ADC_GetTsVref1V5(float* fAdcTsDegree);
//��ȡADC�ο���ѹ2.5Vʱ���¶ȴ������Ĳ����¶�
void ADC_GetTsVref2V5(float* fAdcTsDegree);
//����ADCת�������Զ�ֹͣ
void ADC_AutoStop(uint32_t enAutoStop);
//@}
#ifdef __cplusplus
}
#endif

#endif /* __CW32F030_ADC_H */
/******************************************************************************/
/* EOF (not truncated)                                                        */
/******************************************************************************/
