/******************************************************************************/
/** \file main.c
 **
 ** A detailed description is available at
 ** @link Sample Group Some description @endlink
 **
 **   - 2021-03-12  1.0  xiebin First version for Device Driver Library of Module.
 **
 ******************************************************************************/
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
/******************************************************************************
 * Include files
 ******************************************************************************/
#include "../inc/main.h"

/******************************************************************************
 * Local pre-processor symbols/macros ('#define')
 ******************************************************************************/
#define KEY_GPIO_PORT CW_GPIOB
#define KEY_GPIO_PINS GPIO_PIN_5 | GPIO_PIN_6 
/******************************************************************************
 * Global variable definitions (declared in header file with 'extern')
 ******************************************************************************/

/******************************************************************************
 * Local type definitions ('typedef')
 ******************************************************************************/

/******************************************************************************
 * Local function prototypes ('static')
 ******************************************************************************/

/******************************************************************************
 * Local variable definitions ('static')                                      *
 ******************************************************************************/

/******************************************************************************
 * Local pre-processor symbols/macros ('#define')
 ******************************************************************************/

/*****************************************************************************
 * Function implementation - global ('extern') and local ('static')
 ******************************************************************************/

/**
 ******************************************************************************
 ** \brief  Main function of project
 **
 ** \return uint32_t return value, if needed
 **
 ** 
 **
 ******************************************************************************/
int32_t main(void)
{
    uint8_t tmp8;

    GPIO_InitTypeDef GPIO_InitStruct;

    __RCC_GPIOA_CLK_ENABLE(); // 使能GPIO的配置时钟
    __RCC_GPIOB_CLK_ENABLE();

    GPIO_InitStruct.IT = GPIO_IT_FALLING;
    GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
    GPIO_InitStruct.Pins = KEY_GPIO_PINS;
    GPIO_Init(KEY_GPIO_PORT, &GPIO_InitStruct);

    GPIO_InitStruct.IT = GPIO_IT_NONE;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Pins = GPIO_PIN_6 | GPIO_PIN_7;
    GPIO_Init(CW_GPIOA, &GPIO_InitStruct);

    //配置中断滤波为LSI，脉冲宽度小于LSI的则不会触发中断
    GPIO_ConfigFilter(CW_GPIOB, bv5 | bv6, GPIO_FLTCLK_LSI);

    PA07_SETHIGH();

    //等待KEY1所在的端口为低后才进入DEEPSLEEP，以防止芯片被锁死（不能再进行调试）
    while (PB05_GETVALUE());
    // GPIO_HighByte_Write(CW_GPIOB, 0); //从高8bit输出唤醒次数

    //清除PB05中断标志并使能NVIC    //相关程序在中断服务GPIOB_IRQHandler中进行处理
    GPIOB_INTFLAG_CLR(bv5 | bv6);
    NVIC_EnableIRQ(GPIOB_IRQn);

    tmp8 = 0x00;
    PA07_SETLOW();
    while (1)
    {
        SCB->SCR = 0x04;
        __WFI();

        tmp8++;
        PA06_TOG();
        // GPIO_HighByte_Write(CW_GPIOB, tmp8); //从高8bit输出唤醒次数
    }
}

void GPIOB_IRQHandlerCallback(void)
{
    if (CW_GPIOB->ISR_f.PIN5)
    {
        GPIOB_INTFLAG_CLR(bv5);
    }

    if (CW_GPIOB->ISR_f.PIN6)
    {
        GPIOB_INTFLAG_CLR(bv6);
    }
}

/******************************************************************************
 * EOF (not truncated)
 ******************************************************************************/
