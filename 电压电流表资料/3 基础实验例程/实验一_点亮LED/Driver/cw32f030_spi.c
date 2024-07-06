/**
 * @file cw32f030_spi.c
 * @author P&S (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2021-06-26
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

/* Includes ------------------------------------------------------------------*/
#include "cw32f030_spi.h"

/* Private_TypesDefinitions --------------------------------------------------*/

/* Private_Defines -----------------------------------------------------------*/

/* Private_Variables ---------------------------------------------------------*/

/* Private_FunctionPrototypes ------------------------------------------------*/

/* Private_Functions ---------------------------------------------------------*/

/* Public_Functions ----------------------------------------------------------*/

/**
 * @brief ͨ��SPIx����һ������(4 ~ 16bit)
 * 
 * @param SPIx :SPIx����
 *        ����������:
 *           CW_SPI1��CW_SPI2
 * @param Data :�����͵�����
 */
void SPI_SendData(SPI_TypeDef* SPIx, uint16_t Data)
{
    assert_param(IS_SPI_ALL_PERIPH(SPIx));

    SPIx->DR = Data;
}

/**
 * @brief ͨ��SPIx����һ������(4 ~ 16bit)
 * 
 * @param SPIx :SPIx����
 *        ����������:
 *           CW_SPI1��CW_SPI2
 * @return uint16_t :���յ�����
 */
uint16_t SPI_ReceiveData(SPI_TypeDef* SPIx)
{
    assert_param(IS_SPI_ALL_PERIPH(SPIx));

    return (uint16_t)(SPIx->DR); 
}

/**
 * @brief ����SPI_InitStruct��ָ���Ĳ�����ʼ��SPIx����
 * 
 * @param SPIx :SPIx����
 *        ����������:
 *           CW_SPI1��CW_SPI2
 * @param SPI_InitStruct :ָ��SPI_InitTypeDef���ͽṹ���ָ��
 */
void SPI_Init(SPI_TypeDef* SPIx, SPI_InitTypeDef* SPI_InitStruct)
{
    assert_param(IS_SPI_ALL_PERIPH(SPIx));
    assert_param(IS_SPI_DIRECTION_MODE(SPI_InitStruct->SPI_Direction));
    assert_param(IS_SPI_MODE(SPI_InitStruct->SPI_Mode));
    assert_param(IS_SPI_DATASIZE(SPI_InitStruct->SPI_DataSize));
    assert_param(IS_SPI_CPOL(SPI_InitStruct->SPI_CPOL));
    assert_param(IS_SPI_CPHA(SPI_InitStruct->SPI_CPHA));
    assert_param(IS_SPI_NSS(SPI_InitStruct->SPI_NSS));
    assert_param(IS_SPI_BAUDRATE_PRESCALER(SPI_InitStruct->SPI_BaudRatePrescaler));
    assert_param(IS_SPI_FIRST_BIT(SPI_InitStruct->SPI_FirstBit));
    assert_param(IS_SPI_SPEED(SPI_InitStruct->SPI_Speed));

    REGBITS_MODIFY(SPIx->CR1, SPIx_CR1_MODE_Msk |\
                              SPIx_CR1_WIDTH_Msk | SPIx_CR1_SSM_Msk |\
                              SPIx_CR1_SMP_Msk | SPIx_CR1_LSBF_Msk |\
                              SPIx_CR1_BR_Msk | SPIx_CR1_MSTR_Msk |\
                              SPIx_CR1_CPOL_Msk | SPIx_CR1_CPHA_Msk \
                              ,\
                              SPI_InitStruct->SPI_Direction |\
                              SPI_InitStruct->SPI_DataSize | SPI_InitStruct->SPI_NSS |\
                              SPI_InitStruct->SPI_Speed | SPI_InitStruct->SPI_FirstBit |\
                              SPI_InitStruct->SPI_BaudRatePrescaler | SPI_InitStruct->SPI_Mode |\
                              SPI_InitStruct->SPI_CPOL | SPI_InitStruct->SPI_CPHA);
}

/**
 * @brief Ĭ��ֵ��ֵSPI_InitStruct�ṹ���Ա
 * 
 * @param SPI_InitStruct :ָ��SPI_InitTypeDef���ͽṹ���ָ��
 */
void SPI_StructInit(SPI_InitTypeDef* SPI_InitStruct)
{
    /* SPI_InitStruct members default value */
    SPI_InitStruct->SPI_Direction = SPI_Direction_2Lines_FullDuplex;
    SPI_InitStruct->SPI_Mode = SPI_Mode_Slave;
    SPI_InitStruct->SPI_DataSize = SPI_DataSize_8b;
    SPI_InitStruct->SPI_CPOL = SPI_CPOL_Low;
    SPI_InitStruct->SPI_CPHA = SPI_CPHA_1Edge;
    SPI_InitStruct->SPI_NSS = SPI_NSS_Hard;
    SPI_InitStruct->SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_2;
    SPI_InitStruct->SPI_FirstBit = SPI_FirstBit_MSB;
    SPI_InitStruct->SPI_Speed = SPI_Speed_Low;
}

/**
 * @brief SPI1ȥ��ʼ��
 * 
 */
void SPI1_DeInit(void)
{
    CW_SYSCTRL->APBRST2_f.SPI1 = 0;
    CW_SYSCTRL->APBRST2_f.SPI1 = 1;
}

/**
 * @brief SPI2ȥ��ʼ��
 * 
 */
void SPI2_DeInit(void)
{
    CW_SYSCTRL->APBRST1_f.SPI2 = 0;
    CW_SYSCTRL->APBRST1_f.SPI2 = 1;  
}

/**
 * @brief ʹ�ܻ��ֹSPIx
 * 
 * @param SPIx :SPIx����
 *        ����������:
 *           CW_SPI1��CW_SPI2
 * @param NewState :ENABLE or DISABLE 
 */
void SPI_Cmd(SPI_TypeDef* SPIx, FunctionalState NewState)
{
    assert_param(IS_SPI_ALL_PERIPH(SPIx));
    assert_param(IS_FUNCTIONAL_STATE(NewState));

    SPIx->CR1_f.EN = NewState;
}

/**
 * @brief ʹ��/ʧ��SPIx�ж�
 * 
 * @param SPIx :SPIx����
 *        ����������:
 *           CW_SPI1��CW_SPI2
 * @param SPI_IT :�ж�Դ
 *   ����������:
 *     @arg SPI_IT_MODF:    ģʽ�����ж�
 *     @arg SPI_IT_SSERR:   �ӻ�ģʽ�µĴӻ�ѡ������ж�
 *     @arg SPI_IT_OV:      ���ջ�����������ж�
 *     @arg SPI_IT_UD:      �ӻ�ģʽ�·��ͻ�����������ж�
 *     @arg SPI_IT_SSR:     �ӻ�ѡ�������������ж�
 *     @arg SPI_IT_SSF:     �ӻ�ѡ�������½����ж�
 *     @arg SPI_IT_RXNE:    ���ջ���ǿ��ж�
 *     @arg SPI_IT_TXE:     ���ͻ�����ж�
 * @param NewState :ENABLE or DISABLE
 */
void SPI_ITConfig(SPI_TypeDef* SPIx, uint8_t SPI_IT, FunctionalState NewState)
{
    assert_param(IS_SPI_ALL_PERIPH(SPIx));
    assert_param(IS_SPI_IT(SPI_IT));
    assert_param(IS_FUNCTIONAL_STATE(NewState));

    if (NewState != DISABLE)
    {
        SPIx->IER |= SPI_IT;
    }
    else
    {
        SPIx->IER &= ~SPI_IT;
    }
}

/**
 * @brief ��ȡSPIx�жϱ�־λ
 * 
 * @param SPIx :SPIx����
 *        ����������:
 *           CW_SPI1��CW_SPI2
 * @param SPI_IT :�ж�Դ
 *   ����������:
 *     @arg SPI_IT_MODF:    ģʽ�����ж�
 *     @arg SPI_IT_SSERR:   �ӻ�ģʽ�µĴӻ�ѡ������ж�
 *     @arg SPI_IT_OV:      ���ջ�����������ж�
 *     @arg SPI_IT_UD:      �ӻ�ģʽ�·��ͻ�����������ж�
 *     @arg SPI_IT_SSR:     �ӻ�ѡ�������������ж�
 *     @arg SPI_IT_SSF:     �ӻ�ѡ�������½����ж�
 *     @arg SPI_IT_RXNE:    ���ջ���ǿ��ж�
 *     @arg SPI_IT_TXE:     ���ͻ�����ж�
 * @return ITStatus :SPI_IT��ǰ״̬ (SET or RESET)
 */
ITStatus SPI_GetITStatus(SPI_TypeDef* SPIx, uint8_t SPI_IT)
{
    assert_param(IS_SPI_ALL_PERIPH(SPIx));    
    assert_param(IS_SPI_IT(SPI_IT));

    return ((SPIx->ISR & SPI_IT) ? SET : RESET);
}

/**
 * @brief ���SPIx�жϱ�־λ
 * 
 * @param SPIx :SPIx����
 *        ����������:
 *           CW_SPI1��CW_SPI2
 * @param SPI_IT :�ж�Դ
 *   ����������:
 *     @arg SPI_IT_MODF:    ģʽ�����ж�
 *     @arg SPI_IT_SSERR:   �ӻ�ģʽ�µĴӻ�ѡ������ж�
 *     @arg SPI_IT_OV:      ���ջ�����������ж�
 *     @arg SPI_IT_UD:      �ӻ�ģʽ�·��ͻ�����������ж�
 *     @arg SPI_IT_SSR:     �ӻ�ѡ�������������ж�
 *     @arg SPI_IT_SSF:     �ӻ�ѡ�������½����ж�
 *     @arg SPI_IT_RXNE:    ���ջ���ǿ��ж�
 * @note
 *    -TXE�жϱ�־λֻ��ͨ��дSPIx_DR�Ĵ��������
 */
void SPI_ClearITPendingBit(SPI_TypeDef* SPIx, uint8_t SPI_IT)
{
    assert_param(IS_SPI_ALL_PERIPH(SPIx));    
    assert_param(IS_SPI_CLEAR_IT(SPI_IT));

    SPIx->ICR &= ~SPI_IT;
}

/**
 * @brief ��ȡSPIx��־λ
 * 
 * @param SPIx :SPIx����
 *        ����������:
 *           CW_SPI1��CW_SPI2
 * @param SPI_FLAG :��־λ
 *   ����������:
 *     @arg SPI_FLAG_SSLVL:  �ӻ�ѡ���ź�״̬  
 *     @arg SPI_FLAG_BUSY:   ����æ��־
 *     @arg SPI_FLAG_MODF:   ģʽ�����־
 *     @arg SPI_FLAG_SSERR:  �ӻ�ģʽ�µĴӻ�ѡ������־
 *     @arg SPI_FLAG_OV:     ���ջ�����������ж�
 *     @arg SPI_FLAG_UD:     �ӻ�ģʽ�·��ͻ�����������־
 *     @arg SPI_FLAG_SSR:    �ӻ�ѡ�����������ر�־
 *     @arg SPI_FLAG_SSF:    �ӻ�ѡ�������½��ر�־
 *     @arg SPI_FLAG_RXNE:   ���ջ���ǿձ�־
 *     @arg SPI_FLAG_TXE:    ���ͻ���ձ�־
 * @return FlagStatus :SPI_FLAG��ǰ״̬ (SET or RESET)
 */
FlagStatus SPI_GetFlagStatus(SPI_TypeDef* SPIx, uint16_t SPI_FLAG)
{  
    assert_param(IS_SPI_ALL_PERIPH(SPIx));    
    assert_param(IS_SPI_FLAG(SPI_FLAG));
  
    return ((SPIx->ISR & SPI_FLAG) ? SET : RESET); 
}

/**
 * @brief ���SPIx��־λ
 * 
 * @param SPIx :SPIx����
 *        ����������:
 *           CW_SPI1��CW_SPI2
 * @param SPI_FLAG :��־λ
 *   ����������:
 *     @arg SPI_FLAG_MODF:   ģʽ�����־
 *     @arg SPI_FLAG_SSERR:  �ӻ�ģʽ�µĴӻ�ѡ������־
 *     @arg SPI_FLAG_OV:     ���ջ�����������ж�
 *     @arg SPI_FLAG_UD:     �ӻ�ģʽ�·��ͻ�����������־
 *     @arg SPI_FLAG_SSR:    �ӻ�ѡ�����������ر�־
 *     @arg SPI_FLAG_SSF:    �ӻ�ѡ�������½��ر�־
 *     @arg SPI_FLAG_RXNE:   ���ջ���ǿձ�־
 * @note
 *    -SSLVL��BUSY��־λ��Ӳ���Զ����ú����
 *    -TXE��־λֻ��ͨ��дSPIx_DR�Ĵ��������
 *    -RXNE��־λҲ����ͨ����SPIx_DR�Ĵ��������
 * @return FlagStatus :SPI_FLAG��ǰ״̬ (SET or RESET)
 */
void SPI_ClearFlag(SPI_TypeDef* SPIx, uint16_t SPI_FLAG)
{
    assert_param(IS_SPI_ALL_PERIPH(SPIx));    
    assert_param(IS_SPI_CLEAR_FLAG(SPI_FLAG));

    SPIx->ICR &= ~SPI_FLAG;
}

/**
 * @brief ���߰�˫�����ݴ��䷽������
 * 
 * @param SPIx :SPIx����
 *        ����������:
 *           CW_SPI1��CW_SPI2
 * @param SPI_Direction :����/����
 *   ���������ǣ�
 *     @arg SPI_Direction_Tx: ����
 *     @arg SPI_Direction_Rx: ����
 */
void SPI_BiDirectionalLineConfig(SPI_TypeDef* SPIx, uint8_t SPI_Direction)
{
  assert_param(IS_SPI_ALL_PERIPH(SPIx));
  assert_param(IS_SPI_DIRECTION(SPI_Direction));

  SPIx->CR2 = SPI_Direction;
}

/**
 * @brief ʹ��/ʧ��SPIx DMA
 * 
 * @param SPIx :SPIx����
 *        ����������:
 *           CW_SPI1��CW_SPI2
 * @param SPI_DMAReq :DMA����
 *   ���������ǣ�
 *     @arg SPI_DMAReq_Tx: DMA��������
 *     @arg SPI_DMAReq_Rx: DMA��������
 * @param NewState :ENABLE or DISABLE
 */
void SPI_DMACmd(SPI_TypeDef* SPIx, uint32_t SPI_DMAReq, FunctionalState NewState)
{
    assert_param(IS_SPI_ALL_PERIPH(SPIx));
    assert_param(IS_SPI_DMAREQ(SPI_DMAReq));
    assert_param(IS_FUNCTIONAL_STATE(NewState));

    if (NewState != DISABLE)
    {
        SPIx->CR1 |= SPI_DMAReq;
    }
    else
    {
        SPIx->CR1 &= ~SPI_DMAReq;
    }
}

/**
 * @brief ����ڲ�����NSS
 * 
 * @param SPIx :SPIx����
 *        ����������:
 *           CW_SPI1��CW_SPI2
 * @param SPI_NSSInternalSoft :NSS״̬
 *   ���������ǣ�
 *     @arg SPI_NSSInternalSoft_Set: Set NSS
 *     @arg SPI_NSSInternalSoft_Reset: Reset NSS
 * @note
 *    -SPIx_CR1.SSM = 1ʱ��Ч�������NSS(SPI_InitStruct->SPI_NSS = SPI_NSS_Soft)
 *    -����ʱ��0 - CS�����     1 - CS�����
 *    -�ӻ�ʱ��0 - ������ѡ��   1 - ����δ��ѡ��
 */
void SPI_NSSInternalSoftwareConfig(SPI_TypeDef* SPIx, uint8_t SPI_NSSInternalSoft)
{
    assert_param(IS_SPI_ALL_PERIPH(SPIx));
    assert_param(IS_SPI_NSS_INTERNAL(SPI_NSSInternalSoft));

    SPIx->SSI = SPI_NSSInternalSoft;
}

/**
 * @brief ��������֡��λ��
 * 
 * @param SPIx :SPIx����
 *        ����������:
 *           CW_SPI1��CW_SPI2
 * @param SPI_DataSize :����֡���
 *   ���������ǣ�
 *     @arg SPI_DataSize_4b
 *     @arg SPI_DataSize_5b
 *     @arg SPI_DataSize_6b
 *     @arg SPI_DataSize_7b
 *     @arg SPI_DataSize_8b
 *     @arg SPI_DataSize_9b
 *     @arg SPI_DataSize_10b
 *     @arg SPI_DataSize_11b
 *     @arg SPI_DataSize_12b
 *     @arg SPI_DataSize_13b
 *     @arg SPI_DataSize_14b
 *     @arg SPI_DataSize_15b
 *     @arg SPI_DataSize_16b
 */
void SPI_DataSizeConfig(SPI_TypeDef* SPIx, uint16_t SPI_DataSize)
{
    assert_param(IS_SPI_ALL_PERIPH(SPIx));
    assert_param(IS_SPI_DATASIZE(SPI_DataSize));
   
    REGBITS_MODIFY(SPIx->CR1, SPIx_CR1_WIDTH_Msk, SPI_DataSize);
}

/**
 * @brief ��ģʽMISO�������
 * 
 * @param SPIx :SPIx����
 *        ����������:
 *           CW_SPI1��CW_SPI2
 * @param SPI_MISOOutput :MISO�������
 *   ���������ǣ�
 *     @arg SPI_MISOOutput_HD: �ӻ���ѡ��ʱ MISO Ϊ COMS �����δ��ѡ��ʱΪ�������
 *     @arg SPI_MISOOutput_CMOS: MISO ʼ��Ϊ COMS ���
 */
void SPI_MISOOutputConfig(SPI_TypeDef* SPIx, uint8_t SPI_MISOOutput)
{
    assert_param(IS_SPI_ALL_PERIPH(SPIx));
    assert_param(IS_SPI_MISOOUTPUT(SPI_MISOOutput));

    SPIx->CR1_f.MISOHD = SPI_MISOOutput;
}

/**
 * @brief ��շ��ͻ���������λ�Ĵ���
 * 
 * @param SPIx :SPIx����
 *        ����������:
 *           CW_SPI1��CW_SPI2
 */
void SPI_FlushSendBuff(SPI_TypeDef* SPIx)
{
    assert_param(IS_SPI_ALL_PERIPH(SPIx));

    SPIx->ICR_f.FLUSH = 0;
}





