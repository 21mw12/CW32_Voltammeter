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
#ifndef __CW32F030_IWDT_H
#define __CW32F030_IWDT_H

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
  uint32_t IWDT_Prescaler;         /* Ԥ����ϵ����ȡֵ��Χ2��n���ݣ�n=2,3..9  */

  uint32_t IWDT_OverFlowAction;    /* �����Ķ���                           */

  FunctionalState IWDT_ITState;    /* ���Ź��ж�״̬��ȡֵ��ΧENABLE��DISABLE */

  uint32_t IWDT_Pause;             /* Deepsleepģʽ��IWDT��ͣ����            */

  uint32_t IWDT_ReloadValue;       /* ���Ź�����ֵ��ȡֵ��ΧС�ڵ���0x0FFF    */

  uint32_t IWDT_WindowValue;       /* ���ڱȽ����Ƚ�ֵ,ȡֵ��ΧС�ڵ���0x0FFF  */
} IWDT_InitTypeDef;       
/******************************************************************************
 * pre-processor symbols/macros ('#define')
 ******************************************************************************/
#define IWDT_FREQ                  10000UL

#define IWDT_Prescaler_DIV4        ((uint32_t)0x00000000)
#define IWDT_Prescaler_DIV8        ((uint32_t)0x00000001)
#define IWDT_Prescaler_DIV16       ((uint32_t)0x00000002)
#define IWDT_Prescaler_DIV32       ((uint32_t)0x00000003)
#define IWDT_Prescaler_DIV64       ((uint32_t)0x00000004)
#define IWDT_Prescaler_DIV128      ((uint32_t)0x00000005)
#define IWDT_Prescaler_DIV256      ((uint32_t)0x00000006)
#define IWDT_Prescaler_DIV512      ((uint32_t)0x00000007)
#define IS_IWDT_PRESCALER(PRESCALER)  (((PRESCALER) == IWDT_Prescaler_DIV4)   ||\
                                       ((PRESCALER) == IWDT_Prescaler_DIV8)   ||\
                                       ((PRESCALER) == IWDT_Prescaler_DIV16)  ||\
                                       ((PRESCALER) == IWDT_Prescaler_DIV32)  ||\
                                       ((PRESCALER) == IWDT_Prescaler_DIV64)  ||\
                                       ((PRESCALER) == IWDT_Prescaler_DIV128) ||\
                                       ((PRESCALER) == IWDT_Prescaler_DIV512))
#define IS_IWDT_WINDOW_VALUE(VALUE) ((VALUE) <= 0xFFF)
#define IS_IWDT_RELOAD(COUNTER) ((COUNTER) <= 0xFFF)

#define IWDT_UNLOCK_KEY             0x5555
#define IWDT_LOCK_KEY               0x6666
#define IWDT_RUN_KEY                0xCCCC
#define IWDT_REFRESH_KEY            0xAAAA
#define IWDT_STOP_KEY1              0x5A5A
#define IWDT_STOP_KEY2              0xA5A5

#define IWDT_OVERFLOW_ACTION_RESET  0
#define IWDT_OVERFLOW_ACTION_INT    IWDT_CR_ACTION_Msk
#define IS_IWDT_ACTION(ACTION)      ((ACTION) == IWDT_OVERFLOW_ACTION_RESET || \
                                     (ACTION) == IWDT_OVERFLOW_ACTION_INT) 
#define IWDT_SLEEP_PAUSE            IWDT_CR_PAUSE_Msk
#define IWDT_SLEEP_CONTINUE         0
#define IS_IWDT_SLEEP_MODE(MODE)   ((MODE) == IWDT_SLEEP_PAUSE || \
                                    (MODE) == IWDT_SLEEP_CONTINUE)

#define __IWDT_RUN()            (CW_IWDT->KR = IWDT_RUN_KEY)
#define __IWDT_REFRESH()        (CW_IWDT->KR = IWDT_REFRESH_KEY)
#define __IWDT_STOP()           do{                              \
                                    CW_IWDT->KR = IWDT_STOP_KEY1;\
                                    CW_IWDT->KR = IWDT_STOP_KEY2;\
                                } while(0)
#define __IWDT_UNLOCK()         (CW_IWDT->KR = IWDT_UNLOCK_KEY)
#define __IWDT_LOCK()           (CW_IWDT->KR = IWDT_LOCK_KEY)


 /******************************************************************************
 * Global variable definitions (declared in header file with 'extern')
 ******************************************************************************/
 
 
 /******************************************************************************
 * Global function prototypes 
 ******************************************************************************/
void IWDT_DeInit(void);
void IWDT_Init(IWDT_InitTypeDef *IWDT_InitStruct);

void IWDT_Cmd(void);
void IWDT_Refresh(void);

void IWDT_Unlock(void);
void IWDT_Lock(void);
void IWDT_Stop(void);

void IWDT_SetPrescaler(uint32_t WWDT_Prescaler);
void IWDT_SetWindowValue(uint32_t WindowValue);
void IWDT_SetReloadValue(uint32_t ReloadValue);
void IWDT_ITConfig(FunctionalState NewState);
FlagStatus IWDT_GetFlagStatus(uint32_t StatusBit);
void IWDT_ClearOVFlag(void);
uint32_t IWDT_GetCounterValue(void);

#ifdef __cplusplus
}
#endif

#endif /*__CW32F030_IWDT_H */
/**
  * @}
  */ 
