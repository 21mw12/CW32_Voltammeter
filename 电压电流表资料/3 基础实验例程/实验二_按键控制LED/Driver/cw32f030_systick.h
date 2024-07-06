/**
 * @file cw32f030_systick.h
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2021-05-13
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
#ifndef __CW32F030_HAL_H
#define __CW32F030_HAL_H

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "base_types.h"
#include "cw32f030.h"

/* Exported types ------------------------------------------------------------*/

typedef enum
{
  TICK_FREQ_10HZ         = 100U,
  TICK_FREQ_100HZ        = 10U,
  TICK_FREQ_1KHZ         = 1U,
  TICK_FREQ_DEFAULT      = TICK_FREQ_1KHZ
} TickFreqTypeDef;

#define  TICK_INT_PRIORITY            ((uint32_t)0)    /*!< tick interrupt priority (lowest by default)  */            
#define MAX_SYSTICK_DELAY      0xFFFFFFFFU
#define IS_TICKFREQ(FREQ) (((FREQ) == TICK_FREQ_10HZ)  || \
                           ((FREQ) == TICK_FREQ_100HZ) || \
                           ((FREQ) == TICK_FREQ_1KHZ))

/* Exported functions --------------------------------------------------------*/
void   InitTick(uint32_t HclkFreq);
void                SysTickDelay(uint32_t Delay);
uint32_t            GetTick(void);
void                SuspendTick(void);
void                ResumeTick(void);

/* Exported variables ---------------------------------------------------------*/
extern __IO uint32_t uwTick;
extern uint32_t uwTickPrio;
extern TickFreqTypeDef uwTickFreq;



#ifdef __cplusplus
}
#endif

#endif /* __CW32F030_HAL_H */

/************************ (C) COPYRIGHT CW *****END OF FILE****/
