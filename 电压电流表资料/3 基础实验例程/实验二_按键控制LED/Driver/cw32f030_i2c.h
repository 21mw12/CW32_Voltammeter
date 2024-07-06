/**
 * @file cw32f030_i2c.h
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2021-04-27
 * 
 * @copyright Copyright (c) 2021
 * x
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
#ifndef __CW32F03x_I2C_H
#define __CW32F03x_I2C_H

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "cw32f030.h"
#include "base_types.h"
#include "cw32f030_rcc.h"
/**
 * @brief  I2Cͨ��ѡ��
 * 
 */
 typedef enum en_i2c_channel
 {
    I2C1 = 0,///<ͨ��1
    I2C2 = 1,///<ͨ��2  
 }en_i2c_channel_t;

/**
 ******************************************************************************
 ** \brief I2C��ʼ�����ýṹ
 *****************************************************************************/
typedef struct 
{
  FunctionalState         I2C_BaudEn;    ///<�����ʼ�����ʹ�� 
  uint8_t         I2C_Baud;      ///<�����ʼ���������
  uint8_t         I2C_OwnSlaveAddr0;   ///<�ӻ���ַ0
  FunctionalState         I2C_OwnGc;   ///<�㲥��Ӧʹ��
  uint8_t         I2C_OwnSlaveAddr1;   ///<�ӻ���ַ1
  uint8_t         I2C_OwnSlaveAddr2;   ///<�ӻ���ַ2
  FunctionalState         I2C_FLT;       ///<FLT����
  FunctionalState         I2C_AA;        ///<ACK����
}I2C_InitTypeDef;

 /** @defgroup I2C_Exported_Constants
  * @{
  */
#define IS_I2C_ALL_PERIPH(PERIPH) (((PERIPH) == CW_I2C1) || \
                                   ((PERIPH) == CW_I2C2))   
#define IS_I2C_OWN_ADDRESS0(ADDRESS0) ((ADDRESS0) <= 0x7F)
#define IS_I2C_OWN_ADDRESS1(ADDRESS1) ((ADDRESS1) <= 0x7F)
#define IS_I2C_OWN_ADDRESS2(ADDRESS2) ((ADDRESS2) <= 0x7F)

#define I2C_Baud_BRR_1               ((uint8_t)0x01)
#define I2C_Baud_BRR_2               ((uint8_t)0x02)
#define I2C_Baud_BRR_3               ((uint8_t)0x03)
#define I2C_Baud_BRR_4               ((uint8_t)0x04)
#define I2C_Baud_BRR_5               ((uint8_t)0x05)
#define I2C_Baud_BRR_6               ((uint8_t)0x06)
#define I2C_Baud_BRR_7               ((uint8_t)0x07)
#define IS_I2C_Baud_BRR(PARA) (((PARA) == I2C_Baud_BRR_1) || \
                               ((PARA) == I2C_Baud_BRR_2) ||\
                                 ((PARA) == I2C_Baud_BRR_3) ||\
                                 ((PARA) == I2C_Baud_BRR_4) ||\
                                 ((PARA) == I2C_Baud_BRR_5) ||\
                                 ((PARA) == I2C_Baud_BRR_6) ||\
                                 ((PARA) == I2C_Baud_BRR_7))

/** @defgroup I2C_transfer_direction 
  * @{
  */

#define  I2C_Direction_Transmitter      ((uint8_t)0x00)
#define  I2C_Direction_Receiver         ((uint8_t)0x01)
#define  IS_I2C_DIRECTION(DIRECTION) (((DIRECTION) == I2C_Direction_Transmitter) || \
                                     ((DIRECTION) == I2C_Direction_Receiver))
//��������������ͣ����
void I2C_BaudGeneratorEnable(I2C_TypeDef* I2Cx, FunctionalState NewState);
//���ò��������üĴ���
void I2C_SetBaud(I2C_TypeDef *I2Cx, uint8_t u8TBaud);
//����START�ź�
void I2C_GenerateSTART(I2C_TypeDef* I2Cx, FunctionalState NewState);
//����STOP�ź�
void I2C_GenerateSTOP(I2C_TypeDef* I2Cx, FunctionalState NewState);
//Ack�ź�����
void I2C_AcknowledgeConfig(I2C_TypeDef* I2Cx, FunctionalState NewState);
//Filter����
void I2C_FilterConfig(I2C_TypeDef* I2Cx, FunctionalState NewState);
//���ӻ�ʱ�Ĵӻ���ַ0����
void I2C_SetOwnSlaveAddress0(I2C_TypeDef* I2Cx, uint8_t I2CSlaveAddr);
//���ӻ�ʱ�Ĵӻ���ַ1����
void I2C_SetOwnSlaveAddress1(I2C_TypeDef* I2Cx, uint8_t I2CSlaveAddr);
//���ӻ�ʱ�Ĵӻ���ַ2����
void I2C_SetOwnSlaveAddress2(I2C_TypeDef* I2Cx, uint8_t I2CSlaveAddr);
//���ӻ�ʱ�㲥��Ӧ����
void I2C_GcConfig(I2C_TypeDef* I2Cx, FunctionalState NewState);
//I2Cģ��ʹ��
void I2C_Cmd(I2C_TypeDef* I2Cx, FunctionalState NewState);
//��ȡSI�жϱ�־
ITStatus I2C_GetIrq(I2C_TypeDef *I2Cx);
//���SI�жϱ�־
void I2C_ClearIrq(I2C_TypeDef *I2Cx);
//��ȡ״̬�Ĵ���
uint8_t I2C_GetState(I2C_TypeDef *I2Cx);
//I2C MASTER��ʼ��
void I2C_Master_Init(I2C_TypeDef *I2Cx,I2C_InitTypeDef *I2C_InitStruct);
//I2C SLAVE��ʼ��
void I2C_Slave_Init(I2C_TypeDef *I2Cx,I2C_InitTypeDef *I2C_InitStruct);
//I2C1�رճ�ʼ��
void I2C1_DeInit(void);
//I2C2�رճ�ʼ��
void I2C2_DeInit(void);
//����1�ֽ�����
void I2C_SendData(I2C_TypeDef* I2Cx, uint8_t Data);
//����1�ֽ�����
uint8_t I2C_ReceiveData(I2C_TypeDef* I2Cx);
//���͵�ַ�ֽ�
void I2C_Send7bitAddress(I2C_TypeDef* I2Cx, uint8_t Address, uint8_t I2C_Direction);
//��λI2C1ģ��
void I2C1_SoftwareResetCmd(FunctionalState NewState);
//��λI2C2ģ��
void I2C2_SoftwareResetCmd(FunctionalState NewState);
//��дEEPROM����
void I2C_MasterWriteEepromData(I2C_TypeDef *I2Cx,uint8_t u8Addr,uint8_t *pu8Data,uint32_t u32Len);
//����EEPROM����
void I2C_MasterReadEepomData(I2C_TypeDef *I2Cx,uint8_t u8Addr,uint8_t *pu8Data,uint32_t u32Len);
//����������
void I2C_MasterSendDataToSlave(I2C_TypeDef *I2Cx,uint8_t *pu8Data,uint32_t u32Len);
//����������
void I2C_MasterRecDataFromSlave(I2C_TypeDef *I2Cx,uint8_t *pu8Data,uint32_t u32Len);
//�ӷ�������
void I2C_SlaveSendDataToMaster(I2C_TypeDef* I2Cx,uint8_t *pu8Data,uint32_t *u32Len);
//�ӽ�������
void I2C_SlaveRecDataFromMaster(I2C_TypeDef* I2Cx,uint8_t *pu8Data,uint32_t *pu32Len);
//�ӻ�״̬���
uint8_t I2C_MasterCheckSlaveBusy( I2C_TypeDef* I2Cx );

#ifdef __cplusplus
}
#endif

#endif /*__CW32F030_I2C_H */
