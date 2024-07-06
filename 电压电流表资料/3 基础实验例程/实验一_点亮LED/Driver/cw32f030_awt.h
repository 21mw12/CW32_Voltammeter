/**
 * @file cw32f030_awt.h
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2021-05-18
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
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __CW32F030_AWT_H
#define __CW32F030_AWT_H

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "cw32f030.h"

typedef struct
{
  uint32_t AWT_ClkSource;         /* ʱ��Դѡ������ֵ0 - 4 */
  uint32_t AWT_Prescaler;         /* Ԥ����ϵ��������ֵ1 - 15����Ӧȡֵ��Χ2��n���ݣ�n=1,2��15 */
  uint32_t AWT_Period;            /* �����������ڣ�ȡֵ��Χ0x0000 �� 0xFFFF.  */ 
  uint32_t AWT_Mode;              /* AWT����ģʽ���̶�Ϊ11  */ 
} AWT_TimeCntInitTypeDef;       

#define AWT_CLKSOURCE_HSIOSC  ( uint32_t )(0x00UL << 8)
#define AWT_CLKSOURCE_LSI     ( uint32_t )(0x01UL << 8)
#define AWT_CLKSOURCE_HSE     ( uint32_t )(0x02UL << 8)
#define AWT_CLKSOURCE_LSE     ( uint32_t )(0x03UL << 8)
#define AWT_CLKSOURCE_ETR     ( uint32_t )(0x04UL << 8)
#define IS_AWT_CLKSOURCE(SOURCE) (((SOURCE) == AWT_CLKSOURCE_HSIOSC) || \
                                  ((SOURCE) == AWT_CLKSOURCE_LSI) || \
                                  ((SOURCE) == AWT_CLKSOURCE_HSE) || \
                                  ((SOURCE) == AWT_CLKSOURCE_LSE) || \
                                  ((SOURCE) == AWT_CLKSOURCE_ETR))

#define AWT_PRS_DIV2                       ( uint32_t )(0x01UL << 4)
#define AWT_PRS_DIV4                       ( uint32_t )(0x02UL << 4)
#define AWT_PRS_DIV8                       ( uint32_t )(0x03UL << 4)
#define AWT_PRS_DIV16                      ( uint32_t )(0x04UL << 4)
#define AWT_PRS_DIV32                      ( uint32_t )(0x05UL << 4)
#define AWT_PRS_DIV64                      ( uint32_t )(0x06UL << 4)
#define AWT_PRS_DIV128                     ( uint32_t )(0x07UL << 4)
#define AWT_PRS_DIV256                     ( uint32_t )(0x08UL << 4)
#define AWT_PRS_DIV512                     ( uint32_t )(0x09UL << 4)
#define AWT_PRS_DIV1024                    ( uint32_t )(0x0AUL << 4)
#define AWT_PRS_DIV2048                    ( uint32_t )(0x0BUL << 4)
#define AWT_PRS_DIV4096                    ( uint32_t )(0x0CUL << 4)
#define AWT_PRS_DIV8192                    ( uint32_t )(0x0DUL << 4)
#define AWT_PRS_DIV16384                   ( uint32_t )(0x0EUL << 4)
#define AWT_PRS_DIV32768                   ( uint32_t )(0x0FUL << 4)
#define IS_AWT_PRS_DIV(DIV)  (((DIV) == AWT_PRS_DIV2) || \
                              ((DIV) == AWT_PRS_DIV4) || \
                              ((DIV) == AWT_PRS_DIV8) || \
                              ((DIV) == AWT_PRS_DIV16) || \
                              ((DIV) == AWT_PRS_DIV32) || \
                              ((DIV) == AWT_PRS_DIV64) || \
                              ((DIV) == AWT_PRS_DIV128) || \
                              ((DIV) == AWT_PRS_DIV256) || \
                              ((DIV) == AWT_PRS_DIV512) || \
                              ((DIV) == AWT_PRS_DIV1024) || \
                              ((DIV) == AWT_PRS_DIV2048) || \
                              ((DIV) == AWT_PRS_DIV4096) || \
                              ((DIV) == AWT_PRS_DIV8192) || \
                              ((DIV) == AWT_PRS_DIV16384) || \
                              ((DIV) == AWT_PRS_DIV32768))                        

#define AWT_MODE_TIMECNT      ( uint32_t )(0x03UL << 1)
#define IS_AWT_MODE(MODE)     ((MODE) == AWT_MODE_TIMECNT) 
#define AWT_CR_EN             bv0

#define IS_AWT_ARR(ARR)       ((ARR) <= 65535) 

#define AWT_IT_UD             ((uint32_t)0x08)
#define IS_AWT_IT(IT)         ((((IT) & (uint32_t)0xFFFFFFF7) == 0x0000) && ((IT) != 0x0000))
#define IS_AWT_GET_IT(IT)     (((IT) == AWT_IT_UD)
 

void AWT_DeInit(void);
void AWT_TimeCntInit(AWT_TimeCntInitTypeDef* AWT_TimeCntInitStruct);
void AWT_TimeCntStructInit(AWT_TimeCntInitTypeDef* AWT_TimeCntInitStruct);
void AWT_Cmd(FunctionalState NewState);
void AWT_ITConfig(uint32_t AWT_IT, FunctionalState NewState);
ITStatus AWT_GetITStatus(uint32_t AWT_IT);
void AWT_ClearITPendingBit(uint32_t AWT_IT);
void AWT_ClkSourceConfig(uint32_t AWT_ClkSource);
void AWT_PrescalerConfig(uint32_t AWT_Prescaler);
uint16_t AWT_GetCounter(void);
uint16_t AWT_GetAutoreload(void);
uint32_t AWT_GetClkSource(void);
uint32_t AWT_GetPrescaler(void);


#ifdef __cplusplus
}
#endif

#endif 

