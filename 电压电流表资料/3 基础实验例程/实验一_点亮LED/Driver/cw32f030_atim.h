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
#ifndef __CW32F030_ATIM_H
#define __CW32F030_ATIM_H

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
  uint32_t CounterDirection;        /*!< �������� */

  uint32_t CounterOPMode;           /*!< ����ģʽ�����λ��ظ� */

  uint32_t CounterAlignedMode;      /*!< ��������ģʽ: ���ػ����� */

  FunctionalState BufferState;      /*!<  ARR����ʹ�� */

  uint32_t Prescaler;               /*!< Ԥ��Ƶϵ�� */
  
  uint32_t ClockSelect;             /*!< ����ʱ��ѡ�� */            

  uint32_t ReloadValue;           /*!< ARR��ֵ��ȡֵ��Χ0x0000~0xFFFF */  

  uint32_t RepetitionCounter;     /*!< �ظ����ڼ���ֵ��RCR�Ĵ��� */

  FunctionalState UnderFlowMask; /*!< ���������ʹ�� */

  FunctionalState OverFlowMask;  /*!< ���������ʹ�� */   

 } ATIM_InitTypeDef;  

 typedef struct
{
  uint32_t ICPolarity;  /*!< ���벶���ԣ��������½���˫�� */
 
  uint32_t ICFilter;     /*!< �����˲����� */
} ATIM_ICInitTypeDef;

typedef struct
{
  uint32_t OCPolarity;  /*!< �˿ڼ���ѡ�����򡢷��� */
 
  uint32_t OCMode;     /*!< �Ƚ�ģʽ���� */

  uint32_t OCInterruptSelect;    /*!< �Ƚ��ж�ģʽ */

  FunctionalState OCDMAState;  /*!< �Ƚ�ƥ�䴥��DMAʹ��״̬ */

  FunctionalState OCInterruptState; /*!< �Ƚ�ƥ�䴥���ж�ʹ��״̬ */

  FunctionalState BufferState;    /*!< �Ƚϻ���ʹ��״̬ */
} ATIM_OCInitTypeDef;     
/******************************************************************************
 * pre-processor symbols/macros ('#define')
 ******************************************************************************/
#define ATIM_COUNTING_UP                    (0UL)
#define ATIM_COUNTING_DOWN                  (1UL << 27)
#define IS_ATIM_COUNTING_DIRECTION(DIR)     (((DIR) == ATIM_COUNTING_UP) || \
                                             ((DIR) == ATIM_COUNTING_DOWN)) 

#define ATIM_OP_MODE_SINGLE                 (1UL << 14)
#define ATIM_OP_MODE_REPETITIVE             (0UL)
#define IS_ATIM_OP_MODE(MODE)               (((MODE) == ATIM_OP_MODE_SINGLE) || \
                                              ((MODE) == ATIM_OP_MODE_REPETITIVE)) 


#define ATIM_COUNT_MODE_EDGE_ALIGN          (2UL << 12)
#define ATIM_COUNT_MODE_CENTER_ALIGN        (3UL << 12)
#define IS_ATIM_COUNT_MODE(MODE)            (((MODE) == ATIM_COUNT_MODE_EDGE_ALIGN) || \
                                             ((MODE) == ATIM_COUNT_MODE_CENTER_ALIGN))

#define ATIM_CR_IT_UNDE                        (1UL << 29)
#define ATIM_CR_IT_OVE                         (1UL << 28)
#define ATIM_CR_IT_BIE                         (1UL << 20)
#define ATIM_CR_IT_TIE                         (1UL << 19)
#define ATIM_CR_IT_UIE                         (1UL << 10)

#define ATIM_BUFFER_ENABLE                  (1UL << 7)
#define ATIM_BUFFER_DISABLE                 (0UL)

#define ATIM_Prescaler_DIV1        (0UL)
#define ATIM_Prescaler_DIV2        (1UL << 4)
#define ATIM_Prescaler_DIV4        (2UL << 4)
#define ATIM_Prescaler_DIV8        (3UL << 4)
#define ATIM_Prescaler_DIV16       (4UL << 4)
#define ATIM_Prescaler_DIV32       (5UL << 4)
#define ATIM_Prescaler_DIV64       (6UL << 4)
#define ATIM_Prescaler_DIV256      (7UL << 4)
#define IS_ATIM_PRESCALER(PRESCALER)  (((PRESCALER) == ATIM_Prescaler_DIV1)   ||\
                                       ((PRESCALER) == ATIM_Prescaler_DIV2)   ||\
                                       ((PRESCALER) == ATIM_Prescaler_DIV4)  ||\
                                       ((PRESCALER) == ATIM_Prescaler_DIV8)  ||\
                                       ((PRESCALER) == ATIM_Prescaler_DIV16)  ||\
                                       ((PRESCALER) == ATIM_Prescaler_DIV64) ||\
                                       ((PRESCALER) == ATIM_Prescaler_DIV256))

#define ATIM_CLOCK_PCLK            (0UL)
#define ATIM_CLOCK_ETR             (1UL << 2)
#define IS_ATIM_CLOCK(CLK)         (((CLK) == ATIM_CLOCK_PCLK) || \
                                    ((CLK) == ATIM_CLOCK_ETR))

#define ATIM_IT_UIF                         (1UL)
#define ATIM_IT_C1AF                        (1UL << 2)
#define ATIM_IT_C2AF                        (1UL << 3)
#define ATIM_IT_C3AF                        (1UL << 4)
#define ATIM_IT_C1BF                        (1UL << 5)
#define ATIM_IT_C2BF                        (1UL << 6)
#define ATIM_IT_C3BF                        (1UL << 7)
#define ATIM_IT_C1AE                        (1UL << 8)
#define ATIM_IT_C2AE                        (1UL << 9)
#define ATIM_IT_C3AE                        (1UL << 10)
#define ATIM_IT_C1BE                        (1UL << 11)
#define ATIM_IT_C2BE                        (1UL << 12)
#define ATIM_IT_C3BE                        (1UL << 13)
#define ATIM_IT_BIF                         (1UL << 14)
#define ATIM_IT_TIF                         (1UL << 15)
#define ATIM_IT_OVF                         (1UL << 16)
#define ATIM_IT_UNDF                        (1UL << 17)
#define ATIM_IT_C4AF                        (1UL << 18)

#define ATIM_CH_A_IC                        (1UL << 4)
#define ATIM_CH_A_OC                        (0UL)

#define ATIM_CH_B_IC                        (1UL << 5)
#define ATIM_CH_B_OC                        (0UL)

#define ATIM_CHxA_BUFF                      (1UL << 6)
#define ATIM_CHxA_CIE                       (1UL << 8)
#define ATIM_CHxA_CDE                       (1UL << 10)
#define ATIM_CHxB_BUFF                      (1UL << 7)
#define ATIM_CHxB_CIE                       (1UL << 9)
#define ATIM_CHxB_CDE                       (1UL << 11)

#define ATIM_CH4_BUFF                       (1UL)
#define ATIM_CH4_CIE                        (1UL << 1)
#define ATIM_CH4_CDE                        (1UL << 2)

#define ATIM_ICPOLOARITY_DISABLE           (0UL)
#define ATIM_ICPOLARITY_RISING             (1UL)
#define ATIM_ICPOLARITY_FALLING            (2UL)
#define ATIM_ICPOLARITY_BOTHEDGE           (3UL)
#define IS_ATIM_IC_POLARITY(POLARITY) (((POLARITY) == ATIM_ICPOLOARITY_DISABLE) || \
                                            ((POLARITY) == ATIM_ICPOLARITY_RISING) || \
                                           ((POLARITY) == ATIM_ICPOLARITY_FALLING)|| \
                                           ((POLARITY) == ATIM_ICPOLARITY_BOTHEDGE))                                      

#define ATIM_ICFILTER_NONE                  (0UL)
#define ATIM_ICFILTER_PCLK_N3               (4UL)
#define ATIM_ICFILTER_PCLKDIV4_N3           (5UL)
#define ATIM_ICFILTER_PCLKDIV16_N3          (6UL)
#define ATIM_ICFILTER_PCLKDIV64_N3          (7UL)
#define IS_ATIM_IC_FILTER(ICFILTER)         ((ICFILTER) <= 7UL)

#define ATIM_OCPOLARITY_NONINVERT           (0UL)
#define ATIM_OCPOLARITY_INVERT              (1UL)
#define IS_ATIM_OC_POLARITY(POLARITY)       (((POLARITY) ==  ATIM_OCPOLARITY_NONINVERT) || \
                                             ((POLARITY) == ATIM_OCPOLARITY_INVERT))

#define ATIM_OCMODE_FORCED_INACTIVE         (0UL)
#define ATIM_OCMODE_FORCED_ACTIVE           (1UL)
#define ATIM_OCMODE_INACTIVE                (2UL)
#define ATIM_OCMODE_ACTIVE                  (3UL)
#define ATIM_OCMODE_TOGGLE                  (4UL)
#define ATIM_OCMODE_ONE_PLUSE               (5UL)
#define ATIM_OCMODE_PWM1                    (6UL)
#define ATIM_OCMODE_PWM2                    (7UL)
#define IS_ATIM_OC_MODE(MODE)               ((MODE) <= 7UL)

#define ATIM_OC_IT_NONE                     (0UL)
#define ATIM_OC_IT_UP_COUNTER               (1UL)
#define ATIM_OC_IT_DOWN_COUNTER             (2UL)
#define ATIM_OC_IT_BOTH_COUNTER             (3UL)
#define IS_ATIM_OC_IT(SELECT)               ((SELECT) <= 3UL)

#define ATIM_ETR_POLARITY_NONINVERT         (0UL)
#define ATIM_ETR_POLARITY_INVERT            (1UL << 31)
#define IS_ATIM_ETR_POLARITY(POLARITY)      (((POLARITY) == ATIM_ETR_POLARITY_INVERT) || \
                                             ((POLARITY) == ATIM_ETR_POLARITY_NONINVERT))

#define ATIM_ETR_FILTER_NONE                (0UL)
#define ATIM_ETR_FILTER_PCLK_N3             (4UL << 28)
#define ATIM_ETR_FILTER_PCLKDIV4_N3         (5UL << 28)
#define ATIM_ETR_FILTER_PCLKDIV16_N3        (6UL << 28)
#define ATIM_ETR_FILTER_PCLKDIV64_N3        (7UL << 28)
#define IS_ATIM_ETR_FILTER(FILTER)          (((FILTER) == ATIM_ETR_FILTER_NONE) ||\
                                             ((FILTER) == ATIM_ETR_FILTER_PCLK_N3) || \
                                             ((FILTER) == ATIM_ETR_FILTER_PCLKDIV4_N3) || \
                                             ((FILTER) == ATIM_ETR_FILTER_PCLKDIV16_N3) || \
                                             ((FILTER) == ATIM_ETR_FILTER_PCLKDIV64_N3))

#define ATIM_BRAKE_POLARITY_NONINVERT       (0UL)
#define ATIM_BRAKE_POLARITY_INVERT          (1UL << 27)
#define IS_ATIM_BRAKE_POLARITY(POLARITY)     (((POLARITY) == ATIM_BRAKE_POLARITY_INVERT) || \
                                             ((POLARITY) == ATIM_BRAKE_POLARITY_NONINVERT))

#define ATIM_BRAKE_FILTER_NONE                (0UL)
#define ATIM_BRAKE_FILTER_PCLK_N3             (4UL << 24)
#define ATIM_BRAKE_FILTER_PCLKDIV4_N3         (5UL << 24)
#define ATIM_BRAKE_FILTER_PCLKDIV16_N3        (6UL << 24)
#define ATIM_BRAKE_FILTER_PCLKDIV64_N3        (7UL << 24)
#define IS_ATIM_BRAKE_FILTER(FILTER)          (((FILTER) == ATIM_BRAKE_FILTER_NONE) ||\
                                             ((FILTER) == ATIM_BRAKE_FILTER_PCLK_N3) || \
                                             ((FILTER) == ATIM_BRAKE_FILTER_PCLKDIV4_N3) || \
                                             ((FILTER) == ATIM_BRAKE_FILTER_PCLKDIV16_N3) || \
                                             ((FILTER) == ATIM_BRAKE_FILTER_PCLKDIV64_N3))

#define ATIM_ADC_TRIGGER_GLOBAL             (1UL << 7)
#define ATIM_ADC_TRIGGER_CH3B               (1UL << 6)
#define ATIM_ADC_TRIGGER_CH2B               (1UL << 5)
#define ATIM_ADC_TRIGGER_CH1B               (1UL << 4)
#define ATIM_ADC_TRIGGER_CH3A               (1UL << 3)
#define ATIM_ADC_TRIGGER_CH2A               (1UL << 2)
#define ATIM_ADC_TRIGGER_CH1A               (1UL << 1)
#define ATIM_ADC_TRIGGER_UPDATA_EVENT       (1UL)
#define IS_ATIM_ADC_TRIGGER(SOURCE)         ((SOURCE) <= 0x000000FF)

#define OCREFA_TYPE_DOUBLE                  (0UL)
#define OCREFA_TYPE_SINGLE                  (1UL << 3)
#define IS_ATIM_OCREFA_TYPE(TYPE)           ((TYPE) == OCREFA_TYPE_DOUBLE || (TYPE) == OCREFA_TYPE_SINGLE)
#define OUTPUT_TYPE_ALONE                   (0UL)
#define OUTPUT_TYPE_COMP                    (1UL << 1)
#define IS_ATIM_OUTPUT_TYPE(TYPE) ((TYPE) == OUTPUT_TYPE_ALONE || (TYPE) == OUTPUT_TYPE_COMP)
#define IS_ATIM_DEADTIME(VAL)        ((VAL)<= 0xFF)

#define ATIM_MASTER_OUTPUT_UG        0x00    // �������UG
#define ATIM_MASTER_OUTPUT_CTEN      0x01    // ��ʱ��ʹ��CTEN
#define ATIM_MASTER_OUTPUT_UEV       0x02    // ��ʱ��ʱ�����UEV
#define ATIM_MASTER_OUTPUT_CMPSO     0x03    // �Ƚ�ƥ��ѡ�����CMPSO
#define ATIM_MASTER_OUTPUT_OCREF1A   0x04    // ��ʱ���Ƚ����OCREF1A
#define ATIM_MASTER_OUTPUT_OCREF2A   0x05    // ��ʱ���Ƚ����OCREF2A
#define ATIM_MASTER_OUTPUT_OCREF3A   0x06    // ��ʱ���Ƚ����OCREF3A
#define ATIM_MASTER_OUTPUT_OCREF1B   0x07    // ��ʱ���Ƚ����OCREF1B
#define IS_ATIM_MASTER_OUTPUT(OUTPUT) ((OUTPUT) <= 0x07)

#define ATIM_SLAVER_TYPE_PCLK        0x00    // �ڲ�ʱ��
#define ATIM_SLAVER_TYPE_RESET       0x01    // ��λ����
#define ATIM_SLAVER_TYPE_TRIGGER     0x02    // ����ģʽ
#define ATIM_SLAVER_TYPE_EXT         0x03    // �ⲿʱ��
#define ATIM_SLAVER_TYPE_ENCODE1     0x04    // �����������ģʽ1
#define ATIM_SLAVER_TYPE_ENCODE2     0x05    // �����������ģʽ2
#define ATIM_SLAVER_TYPE_ENCODE3     0x06    // �����������ģʽ3
#define ATIM_SLAVER_TYPE_GATE        0x07    // �ſع���
#define IS_ATIM_SLAVER_TYPE(TYPE) ((TYPE) <= 0x07)

#define ATIM_TRIGGER_SOURCE_ETFP      0x00  // �˿�ETR���˲���λѡ�����ź�ETFP
#define ATIM_TRIGGER_SOURCE_ITR       0x01  // �ڲ������ź�ITR
#define ATIM_TRIGGER_SOURCE_CH1A      0x05  // �˿�CH1A�ı����ź�
#define ATIM_TRIGGER_SOURCE_IAFP      0x06  // �˿�CH1A���˲���λѡ�����ź�IAFP
#define ATIM_TRIGGER_SOURCE_IBFP      0x07  // �˿�CH1B���˲���λѡ�����ź�IBFP
#define IS_ATIM_TRIGGER_SOURCE(SRC) ((SRC) == ATIM_TRIGGER_SOURCE_ETFP || \
                                     (SRC) == ATIM_TRIGGER_SOURCE_ITR ||  \
                                     (SRC) == ATIM_TRIGGER_SOURCE_CH1A || \
                                     (SRC) == ATIM_TRIGGER_SOURCE_IAFP || \
                                     (SRC) == ATIM_TRIGGER_SOURCE_IBFP)

#define ATIM_UPDATE_EVENT_NORMAL      0x01  // �����/�����
#define ATIM_UPDATE_EVENT_EXTENSION   0x00  // �����/�����/�������/��ģʽ��λ
#define IS_ATIM_UPDATE_EVENT(EVENT) ((EVENT) == ATIM_UPDATE_EVENT_NORMAL || \
                                     (EVENT) == ATIM_UPDATE_EVENT_EXTENSION)
   /******************************************************************************
 * Global variable definitions (declared in header file with 'extern')
 ******************************************************************************/

   /******************************************************************************
 * Global function prototypes 
 ******************************************************************************/
   void ATIM_DeInit(void);

   void ATIM_Init(ATIM_InitTypeDef *ATIM_InitStruct);
   void ATIM_Cmd(FunctionalState NewState);

   void ATIM_ITConfig(uint32_t ATIM_IT, FunctionalState NewState);
   ITStatus ATIM_GetITStatus(uint32_t ATIM_IT);
   void ATIM_ClearITPendingBit(uint32_t ATIM_IT);
   void ATIM_SetReloadValue(uint32_t Value);

   void ATIM_CH1Config(uint32_t Function, FunctionalState NewState);
   void ATIM_CH2Config(uint32_t Function, FunctionalState NewState);
   void ATIM_CH3Config(uint32_t Function, FunctionalState NewState);
   void ATIM_CH4Config(uint32_t Function, FunctionalState NewState);

   void ATIM_IC1AInit(ATIM_ICInitTypeDef *TIM_ICInitStruct);
   void ATIM_IC1BInit(ATIM_ICInitTypeDef *TIM_ICInitStruct);
   void ATIM_IC2AInit(ATIM_ICInitTypeDef *TIM_ICInitStruct);
   void ATIM_IC2BInit(ATIM_ICInitTypeDef *TIM_ICInitStruct);
   void ATIM_IC3AInit(ATIM_ICInitTypeDef *TIM_ICInitStruct);
   void ATIM_IC3BInit(ATIM_ICInitTypeDef *TIM_ICInitStruct);

   void ATIM_OC1AInit(ATIM_OCInitTypeDef *ATIM_OCInitStruct);
   void ATIM_OC2AInit(ATIM_OCInitTypeDef *ATIM_OCInitStruct);
   void ATIM_OC3AInit(ATIM_OCInitTypeDef *ATIM_OCInitStruct);
   void ATIM_OC1BInit(ATIM_OCInitTypeDef *ATIM_OCInitStruct);
   void ATIM_OC2BInit(ATIM_OCInitTypeDef *ATIM_OCInitStruct);
   void ATIM_OC3BInit(ATIM_OCInitTypeDef *ATIM_OCInitStruct);

   void ATIM_OC4Init(FunctionalState NewState, uint32_t ITSelect, FunctionalState DMAState,
                     FunctionalState ITState, FunctionalState BufferState);
   void ATIM_PWMOutputConfig(uint32_t OCREFAType, uint32_t OutputType, int16_t Deadtime);
   void ATIM_CtrlPWMOutputs(FunctionalState NewState);
   void ATIM_ETRConfig(uint32_t ATIM_ETRPolarity, uint32_t ATIM_ETRFilter);
   void ATIM_BrakeConfig(uint32_t ATIM_BrakePolarity, uint32_t ATIM_BrakeFilter);

   void ATIM_ADCTriggerConfig(uint32_t ATIM_ADCTriggerSource, FunctionalState NewState);

   uint16_t ATIM_GetCapture1A(void);
   uint16_t ATIM_GetCapture2A(void);
   uint16_t ATIM_GetCapture3A(void);
   uint16_t ATIM_GetCapture1B(void);
   uint16_t ATIM_GetCapture2B(void);
   uint16_t ATIM_GetCapture3B(void);
   uint16_t ATIM_GetCapture4(void);

   void ATIM_SetCompare1A(uint16_t Compare);
   void ATIM_SetCompare2A(uint16_t Compare);
   void ATIM_SetCompare3A(uint16_t Compare);
   void ATIM_SetCompare1B(uint16_t Compare);
   void ATIM_SetCompare2B(uint16_t Compare);
   void ATIM_SetCompare3B(uint16_t Compare);
   void ATIM_SetCompare4(uint16_t Compare);

   void ATIM_MasterModeConfig(uint8_t ATIM_MasterOutput);
   void ATIM_SlaverModeConfig(uint8_t ATIM_SlaverType);
   void ATIM_TriggerSelect(uint8_t ATIM_TriggerSource);
   void ATIM_UpdateEventSelect(uint8_t ATIM_UpdateEvent);

#ifdef __cplusplus
}
#endif

#endif /*__CW32F030_ATIM_H */
/**
  * @}
  */ 
