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
#ifndef __CW32F030_SPI_H
#define __CW32F030_SPI_H

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
  uint16_t SPI_Direction;              /*!< ����ͨ��ģʽ��ȫ˫���������������������գ����߰�˫�� 
                                            ����ȡֵ @ref SPI_Data_Direction */

  uint16_t SPI_Mode;                   /*!< SPI����ģʽ
                                            ����ȡֵ @ref SPI_Mode */

  uint16_t SPI_DataSize;               /*!< ��֡���ݿ��
                                            ����ȡֵ @ref SPI_Data_Size */

  uint16_t SPI_CPOL;                   /*!< ����ʱ�Ӵ�������
                                            ����ȡֵ @ref SPI_Clock_Polarity */

  uint16_t SPI_CPHA;                   /*!< ����ʱ����λ����
                                            ����ȡֵ @ref SPI_Clock_Phase */

  uint16_t SPI_NSS;                    /*!< CS�ܽ�����
                                            ����ȡֵ @ref SPI_Slave_Select_Management */

  uint16_t SPI_BaudRatePrescaler;      /*!< ����ģʽ��SCK����������
                                            ����ȡֵ @ref SPI_BaudRate_Prescaler */

  uint16_t SPI_FirstBit;               /*!< ����֡�ߵ�λ˳��ѡ��
                                            ����ȡֵ @ref SPI_MSB_LSB_Transmission */

  uint16_t SPI_Speed;                  /*!< ����SPI�Ĳ����Ƿ��Ӻ󣬸������Ӻ������²����Ӻ�
                                            ����ȡֵ @ref SPI_Speed */
} SPI_InitTypeDef;

/******************************************************************************
 * pre-processor symbols/macros ('#define')
 ******************************************************************************/

/** @defgroup SPI_Data_Direction 
  * @{
  */

#define SPI_Direction_2Lines_FullDuplex     ((uint16_t)0x0000) //˫��ȫ˫��
#define SPI_Direction_1Line_TxOnly          ((uint16_t)0x4000) //��������
#define SPI_Direction_1Line_RxOnly          ((uint16_t)0x8000) //��������
#define SPI_Direction_1Lines_HalfDuplex     ((uint16_t)0xC000) //���߰�˫��
#define IS_SPI_DIRECTION_MODE(MODE) (((MODE) == SPI_Direction_2Lines_FullDuplex) || \
                                     ((MODE) == SPI_Direction_1Lines_HalfDuplex) || \
                                     ((MODE) == SPI_Direction_1Line_TxOnly) || \
                                     ((MODE) == SPI_Direction_1Line_RxOnly))

/** @defgroup SPI_Mode 
  * @{
  */

#define SPI_Mode_Master                      ((uint16_t)0x0004)
#define SPI_Mode_Slave                       ((uint16_t)0x0000)
#define IS_SPI_MODE(MODE) (((MODE) == SPI_Mode_Master) || \
                           ((MODE) == SPI_Mode_Slave))

/** @defgroup SPI_Data_Size 
  * @{
  */

#define SPI_DataSize_4b                      ((uint16_t)0x0C00)
#define SPI_DataSize_5b                      ((uint16_t)0x1000)
#define SPI_DataSize_6b                      ((uint16_t)0x1400)
#define SPI_DataSize_7b                      ((uint16_t)0x1800)
#define SPI_DataSize_8b                      ((uint16_t)0x1C00)
#define SPI_DataSize_9b                      ((uint16_t)0x2000)
#define SPI_DataSize_10b                     ((uint16_t)0x2400)
#define SPI_DataSize_11b                     ((uint16_t)0x2800)
#define SPI_DataSize_12b                     ((uint16_t)0x2C00)
#define SPI_DataSize_13b                     ((uint16_t)0x3000)
#define SPI_DataSize_14b                     ((uint16_t)0x3400)
#define SPI_DataSize_15b                     ((uint16_t)0x3800)
#define SPI_DataSize_16b                     ((uint16_t)0x3C00)
#define IS_SPI_DATASIZE(DATASIZE) (((DATASIZE) == SPI_DataSize_4b) || \
                                   ((DATASIZE) == SPI_DataSize_5b) || \
                                   ((DATASIZE) == SPI_DataSize_6b) || \
                                   ((DATASIZE) == SPI_DataSize_7b) || \
                                   ((DATASIZE) == SPI_DataSize_8b) || \
                                   ((DATASIZE) == SPI_DataSize_9b) || \
                                   ((DATASIZE) == SPI_DataSize_10b) || \
                                   ((DATASIZE) == SPI_DataSize_11b) || \
                                   ((DATASIZE) == SPI_DataSize_12b) || \
                                   ((DATASIZE) == SPI_DataSize_13b) || \
                                   ((DATASIZE) == SPI_DataSize_14b) || \
                                   ((DATASIZE) == SPI_DataSize_15b) ||\
                                   ((DATASIZE) == SPI_DataSize_16b))

/** @defgroup SPI_Clock_Polarity 
  * @{
  */

#define SPI_CPOL_Low                          ((uint16_t)0x0000)
#define SPI_CPOL_High                         ((uint16_t)0x0002)
#define IS_SPI_CPOL(CPOL) (((CPOL) == SPI_CPOL_Low) || \
                           ((CPOL) == SPI_CPOL_High))

/** @defgroup SPI_Clock_Phase 
  * @{
  */

#define SPI_CPHA_1Edge                         ((uint16_t)0x0000)
#define SPI_CPHA_2Edge                         ((uint16_t)0x0001)
#define IS_SPI_CPHA(CPHA) (((CPHA) == SPI_CPHA_1Edge) || \
                           ((CPHA) == SPI_CPHA_2Edge))

/** @defgroup SPI_Slave_Select_Management 
  * @{
  */

#define SPI_NSS_Soft                            ((uint16_t)0x0200)
#define SPI_NSS_Hard                            ((uint16_t)0x0000)
#define IS_SPI_NSS(NSS) (((NSS) == SPI_NSS_Soft) || \
                         ((NSS) == SPI_NSS_Hard))                           

/** @defgroup SPI_BaudRate_Prescaler 
  * @{
  */

#define SPI_BaudRatePrescaler_2                 ((uint16_t)0x0000)
#define SPI_BaudRatePrescaler_4                 ((uint16_t)0x0008)
#define SPI_BaudRatePrescaler_8                 ((uint16_t)0x0010)
#define SPI_BaudRatePrescaler_16                ((uint16_t)0x0018)
#define SPI_BaudRatePrescaler_32                ((uint16_t)0x0020)
#define SPI_BaudRatePrescaler_64                ((uint16_t)0x0028)
#define SPI_BaudRatePrescaler_128               ((uint16_t)0x0030)
#define IS_SPI_BAUDRATE_PRESCALER(PRESCALER) (((PRESCALER) == SPI_BaudRatePrescaler_2) || \
                                              ((PRESCALER) == SPI_BaudRatePrescaler_4) || \
                                              ((PRESCALER) == SPI_BaudRatePrescaler_8) || \
                                              ((PRESCALER) == SPI_BaudRatePrescaler_16) || \
                                              ((PRESCALER) == SPI_BaudRatePrescaler_32) || \
                                              ((PRESCALER) == SPI_BaudRatePrescaler_64) || \
                                              ((PRESCALER) == SPI_BaudRatePrescaler_128))

/** @defgroup SPI_MSB_LSB_Transmission 
  * @{
  */

#define SPI_FirstBit_MSB                        ((uint16_t)0x0000)
#define SPI_FirstBit_LSB                        ((uint16_t)0x0080)
#define IS_SPI_FIRST_BIT(BIT) (((BIT) == SPI_FirstBit_MSB) || \
                               ((BIT) == SPI_FirstBit_LSB))

/** @defgroup SPI_Speed 
  * @{
  */

#define SPI_Speed_Low                           ((uint16_t)0x0000)
#define SPI_Speed_High                          ((uint16_t)0x0100)
#define IS_SPI_SPEED(SPEED) (((SPEED) == SPI_Speed_Low) || \
                             ((SPEED) == SPI_Speed_High)) 

/** @defgroup SPI_Direction_Transmit_Receive 
  * @{
  */

#define SPI_Direction_Tx                        ((uint8_t)0x01)
#define SPI_Direction_Rx                        ((uint8_t)0x00)
#define IS_SPI_DIRECTION(DIRECTION) (((DIRECTION) == SPI_Direction_Tx) || \
                                     ((DIRECTION) == SPI_Direction_Rx))

/** @defgroup SPI_DMA_Requests
  * @{
  */

#define SPI_DMAReq_Tx                          ((uint32_t)0x00020000)
#define SPI_DMAReq_Rx                          ((uint32_t)0x00010000)
#define IS_SPI_DMAREQ(DMAREQ) (((DMAREQ) == SPI_DMAReq_Tx) || \
                               ((DMAREQ) == SPI_DMAReq_Rx) || \
                               ((DMAREQ) == (SPI_DMAReq_Tx | SPI_DMAReq_Rx)))

/** @defgroup SPI_NSS_Internal_Software_Management 
  * @{
  */

#define SPI_NSSInternalSoft_Set                 ((uint8_t)0x01)
#define SPI_NSSInternalSoft_Reset               ((uint8_t)0x00)
#define IS_SPI_NSS_INTERNAL(INTERNAL) (((INTERNAL) == SPI_NSSInternalSoft_Set) || \
                                       ((INTERNAL) == SPI_NSSInternalSoft_Reset))

/** @defgroup SPI_MISO_Output_config
  * @{
  */

#define SPI_MISOOutput_HD                        ((uint8_t)0x01)
#define SPI_MISOOutput_CMOS                      ((uint8_t)0x00)
#define IS_SPI_MISOOUTPUT(MISOOUTPUT) (((MISOOUTPUT) == SPI_MISOOutput_HD) || \
                                       ((MISOOUTPUT) == SPI_MISOOutput_CMOS))

/** @defgroup SPI_Interrupts
  * @{
  */

#define SPI_IT_MODF                             ((uint8_t)0x80)
#define SPI_IT_SSERR                            ((uint8_t)0x40)
#define SPI_IT_OV                               ((uint8_t)0x20)
#define SPI_IT_UD                               ((uint8_t)0x10)
#define SPI_IT_SSR                              ((uint8_t)0x08)
#define SPI_IT_SSF                              ((uint8_t)0x04)
#define SPI_IT_RXNE                             ((uint8_t)0x02)
#define SPI_IT_TXE                              ((uint8_t)0x01)
#define IS_SPI_IT(IT)                           ((IT) <= 0xFF && ((IT) != (uint8_t)0x00))
#define IS_SPI_CLEAR_IT(IT) ((((IT) & (uint8_t)0x01) == 0x00) && ((IT) != (uint8_t)0x00))

/** @defgroup SPI_Flags
  * @{
  */

#define SPI_FLAG_SSLVL                          ((uint16_t)0x0200)
#define SPI_FLAG_BUSY                           ((uint16_t)0x0100)
#define SPI_FLAG_MODF                           ((uint16_t)0x0080)
#define SPI_FLAG_SSERR                          ((uint16_t)0x0040)
#define SPI_FLAG_OV                             ((uint16_t)0x0020)
#define SPI_FLAG_UD                             ((uint16_t)0x0010)
#define SPI_FLAG_SSR                            ((uint16_t)0x0008)
#define SPI_FLAG_SSF                            ((uint16_t)0x0004)
#define SPI_FLAG_RXNE                           ((uint16_t)0x0002)
#define SPI_FLAG_TXE                            ((uint16_t)0x0001)
#define IS_SPI_FLAG(FLAG) ((((FLAG) & (uint16_t)0xFC00) == 0x00) && ((FLAG) != (uint16_t)0x00))
#define IS_SPI_CLEAR_FLAG(FLAG) ((((FLAG) & (uint16_t)0xFF01) == 0x00) && ((FLAG) != (uint16_t)0x00)) 

#define IS_SPI_ALL_PERIPH(PERIPH) (((PERIPH) == CW_SPI1) || \
                                   ((PERIPH) == CW_SPI2))

 /******************************************************************************
 * Global variable definitions (declared in header file with 'extern')
 ******************************************************************************/
 
 
 /******************************************************************************
 * Global function prototypes 
 ******************************************************************************/

/* �����շ� */
void SPI_SendData(SPI_TypeDef* SPIx, uint16_t Data);
uint16_t SPI_ReceiveData(SPI_TypeDef* SPIx);

/* ��ʼ�� */
void SPI_Init(SPI_TypeDef* SPIx, SPI_InitTypeDef* SPI_InitStruct);
void SPI_StructInit(SPI_InitTypeDef* SPI_InitStruct);
void SPI1_DeInit(void);
void SPI2_DeInit(void);

/* ʹ�ܻ��ֹSPIx */
void SPI_Cmd(SPI_TypeDef* SPIx, FunctionalState NewState);

/* �жϼ���־ */
void SPI_ITConfig(SPI_TypeDef* SPIx, uint8_t SPI_I2S_IT, FunctionalState NewState);
ITStatus SPI_GetITStatus(SPI_TypeDef* SPIx, uint8_t SPI_I2S_IT);
void SPI_ClearITPendingBit(SPI_TypeDef* SPIx, uint8_t SPI_I2S_IT);
FlagStatus SPI_GetFlagStatus(SPI_TypeDef* SPIx, uint16_t SPI_FLAG);
void SPI_ClearFlag(SPI_TypeDef* SPIx, uint16_t SPI_FLAG);

/* ���߰�˫�����ݴ��䷽������ */
void SPI_BiDirectionalLineConfig(SPI_TypeDef* SPIx, uint8_t SPI_Direction);

/* DMA */
void SPI_DMACmd(SPI_TypeDef* SPIx, uint32_t SPI_DMAReq, FunctionalState NewState);

/* ����ڲ�����NSS */
void SPI_NSSInternalSoftwareConfig(SPI_TypeDef* SPIx, uint8_t SPI_NSSInternalSoft);

/* ��������֡��λ�� */
void SPI_DataSizeConfig(SPI_TypeDef* SPIx, uint16_t SPI_DataSize);

/* ��ģʽMISO�������*/
void SPI_MISOOutputConfig(SPI_TypeDef* SPIx, uint8_t SPI_MISOOutput);

/* ��շ��ͻ���������λ�Ĵ��� */
void SPI_FlushSendBuff(SPI_TypeDef* SPIx);

#ifdef __cplusplus
}
#endif

#endif /*__CW32F030_SPI_H */

