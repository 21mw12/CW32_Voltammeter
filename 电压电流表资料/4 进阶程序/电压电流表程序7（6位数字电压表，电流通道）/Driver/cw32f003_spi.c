/**
 * @file cw32f003_spi.c
 * @author P&S (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2021-11-05
 * 
 * @copyright Copyright (c) 2021
 * 
 */
/*******************************************************************************
*
* 代码许可和免责信息
* 武汉芯源半导体有限公司授予您使用所有编程代码示例的非专属的版权许可，您可以由此
* 生成根据您的特定需要而定制的相似功能。根据不能被排除的任何法定保证，武汉芯源半
* 导体有限公司及其程序开发商和供应商对程序或技术支持（如果有）不提供任何明示或暗
* 含的保证或条件，包括但不限于暗含的有关适销性、适用于某种特定用途和非侵权的保证
* 或条件。
* 无论何种情形，武汉芯源半导体有限公司及其程序开发商或供应商均不对下列各项负责，
* 即使被告知其发生的可能性时，也是如此：数据的丢失或损坏；直接的、特别的、附带的
* 或间接的损害，或任何后果性经济损害；或利润、业务、收入、商誉或预期可节省金额的
* 损失。
* 某些司法辖区不允许对直接的、附带的或后果性的损害有任何的排除或限制，因此某些或
* 全部上述排除或限制可能并不适用于您。
*
*******************************************************************************/

/* Includes ------------------------------------------------------------------*/
#include "cw32f003_spi.h"

/* Private_TypesDefinitions --------------------------------------------------*/

/* Private_Defines -----------------------------------------------------------*/

/* Private_Variables ---------------------------------------------------------*/

/* Private_FunctionPrototypes ------------------------------------------------*/

/* Private_Functions ---------------------------------------------------------*/

/* Public_Functions ----------------------------------------------------------*/

/**
 * @brief 通过SPI发送一个数据(4 ~ 16bit)
 * 
 * @param Data :待发送的数据
 */
void SPI_SendData(uint16_t Data)
{
    CW_SPI->DR = Data;
}

/**
 * @brief 通过SPI接收一个数据(4 ~ 16bit)
 * 
 * @return uint16_t :接收的数据
 */
uint16_t SPI_ReceiveData(void)
{
    return (uint16_t)(CW_SPI->DR); 
}

/**
 * @brief 根据SPI_InitStruct中指定的参数初始化SPI外设
 * 
 * @param SPI_InitStruct :指向SPI_InitTypeDef类型结构体的指针
 */
void SPI_Init(SPI_InitTypeDef* SPI_InitStruct)
{
    assert_param(IS_SPI_DIRECTION_MODE(SPI_InitStruct->SPI_Direction));
    assert_param(IS_SPI_MODE(SPI_InitStruct->SPI_Mode));
    assert_param(IS_SPI_DATASIZE(SPI_InitStruct->SPI_DataSize));
    assert_param(IS_SPI_CPOL(SPI_InitStruct->SPI_CPOL));
    assert_param(IS_SPI_CPHA(SPI_InitStruct->SPI_CPHA));
    assert_param(IS_SPI_NSS(SPI_InitStruct->SPI_NSS));
    assert_param(IS_SPI_BAUDRATE_PRESCALER(SPI_InitStruct->SPI_BaudRatePrescaler));
    assert_param(IS_SPI_FIRST_BIT(SPI_InitStruct->SPI_FirstBit));
    assert_param(IS_SPI_SPEED(SPI_InitStruct->SPI_Speed));

    REGBITS_MODIFY(CW_SPI->CR1, SPI_CR1_MODE_Msk |\
                                SPI_CR1_WIDTH_Msk | SPI_CR1_SSM_Msk |\
                                SPI_CR1_SMP_Msk | SPI_CR1_LSBF_Msk |\
                                SPI_CR1_BR_Msk | SPI_CR1_MSTR_Msk |\
                                SPI_CR1_CPOL_Msk | SPI_CR1_CPHA_Msk \
                                ,\
                                SPI_InitStruct->SPI_Direction |\
                                SPI_InitStruct->SPI_DataSize | SPI_InitStruct->SPI_NSS |\
                                SPI_InitStruct->SPI_Speed | SPI_InitStruct->SPI_FirstBit |\
                                SPI_InitStruct->SPI_BaudRatePrescaler | SPI_InitStruct->SPI_Mode |\
                                SPI_InitStruct->SPI_CPOL | SPI_InitStruct->SPI_CPHA);
}

/**
 * @brief 默认值赋值SPI_InitStruct结构体成员
 * 
 * @param SPI_InitStruct :指向SPI_InitTypeDef类型结构体的指针
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
 * @brief SPI去初始化
 * 
 */
void SPI_DeInit(void)
{
    CW_SYSCTRL->APBRST2_f.SPI = 0;
    CW_SYSCTRL->APBRST2_f.SPI = 1;
}

/**
 * @brief 使能或禁止SPI
 * 
 * @param NewState :ENABLE or DISABLE 
 */
void SPI_Cmd(FunctionalState NewState)
{
    assert_param(IS_FUNCTIONAL_STATE(NewState));

    CW_SPI->CR1_f.EN = NewState;
}

/**
 * @brief 使能/失能SPI中断
 * 
 * @param SPI_IT :中断源
 *   参数可以是:
 *     @arg SPI_IT_MODF:    模式错误中断
 *     @arg SPI_IT_SSERR:   从机模式下的从机选择错误中断
 *     @arg SPI_IT_OV:      接收缓冲上溢错误中断
 *     @arg SPI_IT_UD:      从机模式下发送缓冲下溢错误中断
 *     @arg SPI_IT_SSR:     从机选择输入上升沿中断
 *     @arg SPI_IT_SSF:     从机选择输入下降沿中断
 *     @arg SPI_IT_RXNE:    接收缓冲非空中断
 *     @arg SPI_IT_TXE:     发送缓冲空中断
 * @param NewState :ENABLE or DISABLE
 */
void SPI_ITConfig(uint8_t SPI_IT, FunctionalState NewState)
{
    assert_param(IS_SPI_IT(SPI_IT));
    assert_param(IS_FUNCTIONAL_STATE(NewState));

    if (NewState != DISABLE)
    {
        CW_SPI->IER |= SPI_IT;
    }
    else
    {
        CW_SPI->IER &= ~SPI_IT;
    }
}

/**
 * @brief 获取SPI中断标志位
 * 
 * @param SPI_IT :中断源
 *   参数可以是:
 *     @arg SPI_IT_MODF:    模式错误中断
 *     @arg SPI_IT_SSERR:   从机模式下的从机选择错误中断
 *     @arg SPI_IT_OV:      接收缓冲上溢错误中断
 *     @arg SPI_IT_UD:      从机模式下发送缓冲下溢错误中断
 *     @arg SPI_IT_SSR:     从机选择输入上升沿中断
 *     @arg SPI_IT_SSF:     从机选择输入下降沿中断
 *     @arg SPI_IT_RXNE:    接收缓冲非空中断
 *     @arg SPI_IT_TXE:     发送缓冲空中断
 * @return ITStatus :SPI_IT当前状态 (SET or RESET)
 */
ITStatus SPI_GetITStatus(uint8_t SPI_IT)
{   
    assert_param(IS_SPI_IT(SPI_IT));

    return ((CW_SPI->ISR & SPI_IT) ? SET : RESET);
}

/**
 * @brief 清除SPI中断标志位
 * 
 * @param SPI_IT :中断源
 *   参数可以是:
 *     @arg SPI_IT_MODF:    模式错误中断
 *     @arg SPI_IT_SSERR:   从机模式下的从机选择错误中断
 *     @arg SPI_IT_OV:      接收缓冲上溢错误中断
 *     @arg SPI_IT_UD:      从机模式下发送缓冲下溢错误中断
 *     @arg SPI_IT_SSR:     从机选择输入上升沿中断
 *     @arg SPI_IT_SSF:     从机选择输入下降沿中断
 *     @arg SPI_IT_RXNE:    接收缓冲非空中断
 * @note
 *    -TXE中断标志位只能通过写SPI_DR寄存器来清除
 */
void SPI_ClearITPendingBit(uint8_t SPI_IT)
{  
    assert_param(IS_SPI_CLEAR_IT(SPI_IT));

    CW_SPI->ICR &= ~SPI_IT;
}

/**
 * @brief 获取SPI标志位
 * 
 * @param SPI_FLAG :标志位
 *   参数可以是:
 *     @arg SPI_FLAG_SSLVL:  从机选择信号状态  
 *     @arg SPI_FLAG_BUSY:   总线忙标志
 *     @arg SPI_FLAG_MODF:   模式错误标志
 *     @arg SPI_FLAG_SSERR:  从机模式下的从机选择错误标志
 *     @arg SPI_FLAG_OV:     接收缓冲上溢错误中断
 *     @arg SPI_FLAG_UD:     从机模式下发送缓冲下溢错误标志
 *     @arg SPI_FLAG_SSR:    从机选择输入上升沿标志
 *     @arg SPI_FLAG_SSF:    从机选择输入下降沿标志
 *     @arg SPI_FLAG_RXNE:   接收缓冲非空标志
 *     @arg SPI_FLAG_TXE:    发送缓冲空标志
 * @return FlagStatus :SPI_FLAG当前状态 (SET or RESET)
 */
FlagStatus SPI_GetFlagStatus(uint16_t SPI_FLAG)
{     
    assert_param(IS_SPI_FLAG(SPI_FLAG));
  
    return ((CW_SPI->ISR & SPI_FLAG) ? SET : RESET); 
}

/**
 * @brief 清除SPI标志位
 * 
 * @param SPI_FLAG :标志位
 *   参数可以是:
 *     @arg SPI_FLAG_MODF:   模式错误标志
 *     @arg SPI_FLAG_SSERR:  从机模式下的从机选择错误标志
 *     @arg SPI_FLAG_OV:     接收缓冲上溢错误中断
 *     @arg SPI_FLAG_UD:     从机模式下发送缓冲下溢错误标志
 *     @arg SPI_FLAG_SSR:    从机选择输入上升沿标志
 *     @arg SPI_FLAG_SSF:    从机选择输入下降沿标志
 *     @arg SPI_FLAG_RXNE:   接收缓冲非空标志
 * @note
 *    -SSLVL、BUSY标志位由硬件自动设置和清除
 *    -TXE标志位只能通过写SPI_DR寄存器来清除
 *    -RXNE标志位也可以通过读SPI_DR寄存器来清除
 * @return FlagStatus :SPI_FLAG当前状态 (SET or RESET)
 */
void SPI_ClearFlag(uint16_t SPI_FLAG)
{   
    assert_param(IS_SPI_CLEAR_FLAG(SPI_FLAG));

    CW_SPI->ICR &= ~SPI_FLAG;
}

/**
 * @brief 单线半双工数据传输方向配置
 * 
 * @param SPI_Direction :发送/接收
 *   参数可以是：
 *     @arg SPI_Direction_Tx: 发送
 *     @arg SPI_Direction_Rx: 接收
 */
void SPI_BiDirectionalLineConfig(uint8_t SPI_Direction)
{
  assert_param(IS_SPI_DIRECTION(SPI_Direction));

  CW_SPI->CR2 = SPI_Direction;
}

/**
 * @brief 软件内部配置NSS
 * 
 * @param SPI_NSSInternalSoft :NSS状态
 *   参数可以是：
 *     @arg SPI_NSSInternalSoft_Set: Set NSS
 *     @arg SPI_NSSInternalSoft_Reset: Reset NSS
 * @note
 *    -SPI_CR1.SSM = 1时有效，即软件NSS(SPI_InitStruct->SPI_NSS = SPI_NSS_Soft)
 *    -主机时：0 - CS输出低     1 - CS输出高
 *    -从机时：0 - 本机被选中   1 - 本机未被选中
 */
void SPI_NSSInternalSoftwareConfig(uint8_t SPI_NSSInternalSoft)
{
    assert_param(IS_SPI_NSS_INTERNAL(SPI_NSSInternalSoft));

    CW_SPI->SSI = SPI_NSSInternalSoft;
}

/**
 * @brief 设置数据帧的位宽
 * 
 * @param SPI_DataSize :数据帧宽度
 *   参数可以是：
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
void SPI_DataSizeConfig(uint16_t SPI_DataSize)
{
    assert_param(IS_SPI_DATASIZE(SPI_DataSize));
   
    REGBITS_MODIFY(CW_SPI->CR1, SPI_CR1_WIDTH_Msk, SPI_DataSize);
}

/**
 * @brief 从模式MISO输出配置
 * 
 * @param SPI_MISOOutput :MISO输出配置
 *   参数可以是：
 *     @arg SPI_MISOOutput_HD: 从机被选中时 MISO 为 COMS 输出，未被选中时为高阻输出
 *     @arg SPI_MISOOutput_CMOS: MISO 始终为 COMS 输出
 */
void SPI_MISOOutputConfig(uint8_t SPI_MISOOutput)
{
    assert_param(IS_SPI_MISOOUTPUT(SPI_MISOOutput));

    CW_SPI->CR1_f.MISOHD = SPI_MISOOutput;
}

/**
 * @brief 清空发送缓冲区和移位寄存器
 * 
 */
void SPI_FlushSendBuff(void)
{
    CW_SPI->ICR_f.FLUSH = 0;
}





