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
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __CW32F030_WWDT_H
#define __CW32F030_WWDT_H

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "cw32f030.h"

/******************************************************************************
 * type definitions ('typedef')
 ******************************************************************************/ 
typedef struct
{
  uint32_t WWDT_Prescaler;         /* Ԥ����ϵ����ȡֵ��Χ2��n���ݣ�n=12,13..19 */

  uint32_t WWDT_WindowValue;       /* ���Ź�����ֵ��ȡֵ��ΧС��0x80*/

  uint8_t WWDT_CounterValue;      /* ���Ź���������ֵ��ȡֵ��Χ0x40 �� 0x7F.  */
  
  FunctionalState WWDT_ITState;   /* ���Ź��ж�״̬��ȡֵ��ΧENABLE��DISABLE */  
} WWDT_InitTypeDef;       
/******************************************************************************
 * pre-processor symbols/macros ('#define')
 ******************************************************************************/
#define WWDT_Prescaler_DIV4096        ((uint32_t)0x00000000)
#define WWDT_Prescaler_DIV8192        ((uint32_t)0x00000080)
#define WWDT_Prescaler_DIV16384       ((uint32_t)0x00000100)
#define WWDT_Prescaler_DIV32768       ((uint32_t)0x00000180)
#define WWDT_Prescaler_DIV65536       ((uint32_t)0x00000200)
#define WWDT_Prescaler_DIV131072      ((uint32_t)0x00000280)
#define WWDT_Prescaler_DIV262144      ((uint32_t)0x00000300)
#define WWDT_Prescaler_DIV524288      ((uint32_t)0x00000380)
#define IS_WWDT_PRESCALER(PRESCALER)  (((PRESCALER) == WWDT_Prescaler_DIV4096) || \
                                       ((PRESCALER) == WWDT_Prescaler_DIV8192) || \
                                       ((PRESCALER) == WWDT_Prescaler_DIV16384) || \
                                       ((PRESCALER) == WWDT_Prescaler_DIV32768) || \
                                       ((PRESCALER) == WWDT_Prescaler_DIV65536) || \
                                       ((PRESCALER) == WWDT_Prescaler_DIV131072) || \
                                       ((PRESCALER) == WWDT_Prescaler_DIV262144) || \
                                       ((PRESCALER) == WWDT_Prescaler_DIV524288))
#define IS_WWDT_WINDOW_VALUE(VALUE) ((VALUE) <= 0x7F)
#define IS_WWDT_COUNTER(COUNTER) (((COUNTER) >= 0x40) && ((COUNTER) <= 0x7F))


#define WWDT_GET_POV_STATUS(VALUE)        {(VALUE) = (FlagStatus)(CW_WWDT->SR);}
#define WWDT_CLR_POV_STATUS()             {REGBITS_CLR(CW_WWDT->SR, WWDT_SR_POV_Msk);}
#define WWDT_ENABLE_IT()                  {REGBITS_SET(CW_WWDT->CR1,WWDT_CR1_IE_Msk);}
#define WWDT_FEED(VALUE)                  {REGBITS_MODIFY(CW_WWDT->CR0, WWDT_CR0_WCNT_Msk,(VALUE));}

 /******************************************************************************
 * Global variable definitions (declared in header file with 'extern')
 ******************************************************************************/
 
 
 /******************************************************************************
 * Global function prototypes 
 ******************************************************************************/
void WWDT_DeInit(void);
void WWDT_Init(WWDT_InitTypeDef* WWDT_InitStruct);
void WWDT_Refresh(uint8_t Counter);


void WWDT_Cmd(void);
void WWDT_SetPrescaler(uint32_t WWDT_Prescaler);
void WWDT_SetWindowValue(uint8_t WindowValue);
uint8_t WWDT_GetCounterValue(void);
uint8_t WWDT_GetWindowValue(void);
void WWDT_EnableIT(void);
FlagStatus WWDT_GetFlagStatus(void);
void WWDT_ClearFlag(void);


#ifdef __cplusplus
}
#endif

#endif /*__CW32F030_WWDT_H */
/**
  * @}
  */ 
