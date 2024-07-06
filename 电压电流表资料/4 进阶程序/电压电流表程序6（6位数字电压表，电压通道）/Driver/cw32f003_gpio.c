/**
 * @file cw32f003_gpio.c
 * @author P&S (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2021-10-25
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
#include "cw32f003_gpio.h"

/* Private_TypesDefinitions --------------------------------------------------*/

/* Private_Defines -----------------------------------------------------------*/

/* Private_Variables ---------------------------------------------------------*/

/* Private_FunctionPrototypes ------------------------------------------------*/

/* Private_Functions ---------------------------------------------------------*/

/* Public_Functions ----------------------------------------------------------*/

/**
 * @brief GPIO 初始化，可同时设置多个引脚或单个引脚
 * 
 * @param GPIOx 参数为下列参数之一：
 *        @arg CW_GPIOA CW_GPIOB CW_GPIOC
 * @param GPIO_Init 参见GPIO_InitTypeDef的定义
 */
void GPIO_Init(GPIO_TypeDef *GPIOx, GPIO_InitTypeDef *GPIO_Init)
{
    if( GPIO_Init->Mode == GPIO_MODE_ANALOG )                        //模拟功能
    {
       REGBITS_SET( GPIOx->ANALOG , GPIO_Init->Pins );
    }
    else
    {
        REGBITS_CLR( GPIOx->ANALOG , GPIO_Init->Pins );               //数字功能
        if( (GPIO_Init->Mode & GPIO_MODE_INPUT) == GPIO_MODE_INPUT )  //输入模式
        {
           REGBITS_SET( GPIOx->DIR , GPIO_Init->Pins );
           if( GPIO_Init->Mode == GPIO_MODE_INPUT_PULLUP )
           {
               REGBITS_SET( GPIOx->PUR , GPIO_Init->Pins );
               REGBITS_CLR( GPIOx->PDR , GPIO_Init->Pins );
           }
           if( GPIO_Init->Mode == GPIO_MODE_INPUT_PULLDOWN )
           {
               REGBITS_SET( GPIOx->PDR , GPIO_Init->Pins );
               REGBITS_CLR( GPIOx->PUR , GPIO_Init->Pins );
           }
           
           REGBITS_CLR( GPIOx->RISEIE , GPIO_Init->Pins );
           REGBITS_CLR( GPIOx->FALLIE , GPIO_Init->Pins );
           REGBITS_CLR( GPIOx->HIGHIE , GPIO_Init->Pins );
           REGBITS_CLR( GPIOx->LOWIE  , GPIO_Init->Pins );
           if( ( GPIO_Init->IT & GPIO_IT_RISING ) == GPIO_IT_RISING ) 
           {
               REGBITS_SET( GPIOx->RISEIE , GPIO_Init->Pins );
           }
           if( ( GPIO_Init->IT & GPIO_IT_FALLING ) == GPIO_IT_FALLING ) 
           {
               REGBITS_SET( GPIOx->FALLIE , GPIO_Init->Pins );
           }
           if( ( GPIO_Init->IT & GPIO_IT_HIGH ) == GPIO_IT_HIGH ) 
           {
               REGBITS_SET( GPIOx->HIGHIE , GPIO_Init->Pins );
           }
           if( ( GPIO_Init->IT & GPIO_IT_LOW ) == GPIO_IT_LOW ) 
           {
               REGBITS_SET( GPIOx->LOWIE , GPIO_Init->Pins );
           }
        }
        else                                                           //输出模式
        {
            REGBITS_CLR( GPIOx->DIR , GPIO_Init->Pins );
            if( GPIO_Init->Mode == GPIO_MODE_OUTPUT_PP )
            {
                REGBITS_CLR( GPIOx->OPENDRAIN , GPIO_Init->Pins );
            }
            else
            {
                REGBITS_SET( GPIOx->OPENDRAIN , GPIO_Init->Pins );
            }
        }
    }
}

//=============================================================================
//GPIO 反初始化， 多个引脚
/**
 * @brief GPIO 去初始化，可同时设置多个引脚或单个引脚
 * 
 * @param GPIOx 参数为下列参数之一：
 *        @arg CW_GPIOA CW_GPIOB CW_GPIOC
 * 
 * @param GPIO_Pins 参数取值如下
 *        @arg GPIO_PIN_0/1/2.../7/ALL 可通过与运算同时操作多个引脚
 */
void GPIO_DeInit(GPIO_TypeDef  *GPIOx, uint32_t GPIO_Pins)
{ 
    REGBITS_SET( GPIOx->ANALOG , GPIO_Pins );
    REGBITS_SET( GPIOx->DIR    , GPIO_Pins );
    REGBITS_CLR( GPIOx->PUR    , GPIO_Pins );
    REGBITS_CLR( GPIOx->PDR    , GPIO_Pins );
    REGBITS_CLR( GPIOx->RISEIE , GPIO_Pins );
    REGBITS_CLR( GPIOx->FALLIE , GPIO_Pins );
    REGBITS_CLR( GPIOx->HIGHIE , GPIO_Pins );
    REGBITS_CLR( GPIOx->LOWIE  , GPIO_Pins );
    REGBITS_CLR( GPIOx->OPENDRAIN , GPIO_Pins );
}
//=============================================================================
//获取指定引脚电平，一个引脚
//注意：建议采用宏函数来获取引脚电平，例PA00_GETVALUE()
/**
 * @brief 获取一个引脚的电平
 * 
 * @param GPIOx 参数为下列参数之一：
 *        @arg CW_GPIOA CW_GPIOB CW_GPIOC
 * @param GPIO_Pin 参数取值如下
 *        @arg GPIO_PIN_0/1/2.../7
 * @return GPIO_PinState 取值如下:
 *        @arg GPIO_Pin_SET
 *        @arg GPIO_Pin_RESET
 */
GPIO_PinState GPIO_ReadPin(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin)
{
    if( GPIOx->IDR & GPIO_Pin )
    {
        return( GPIO_Pin_SET );
    }
    
    return( GPIO_Pin_RESET );
}

//=============================================================================
//设置指定引脚电平，多个引脚
//注意：如只操作一只引脚，建议采用宏函数，例PA00_SETHIGH(), PA00_SETLOW()
/**
 * @brief 设置指定引脚电平，可同时设置多个引脚
 * 
 * @param GPIOx GPIOx 参数为下列参数之一：
 *        @arg CW_GPIOA CW_GPIOB CW_GPIOC
 * @param GPIO_Pins 参数取值如下
 *        @arg GPIO_PIN_0/1/2.../7/ALL;
 * @param PinState 取值如下:
 *        @arg GPIO_Pin_SET
 *        @arg GPIO_Pin_RESET
 */
void GPIO_WritePin(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pins, GPIO_PinState PinState)
{
    if( PinState == GPIO_Pin_SET )
    {
        GPIOx->BSRR = GPIO_Pins;
    }
    else
    {
        GPIOx->BRR = GPIO_Pins;
    }
}

//=============================================================================
//设置端口低字节（B0-B7）引脚电平
/**
 * @brief 设置端口低字节（B0-B7）引脚电平
 * 
 * @param GPIOx 参数为下列参数之一：
 *        @arg CW_GPIOA CW_GPIOB CW_GPIOC
 * @param Value 取值范围：0x00~0xFF
 */
// void GPIO_LowByte_Write(GPIO_TypeDef* GPIOx, uint8_t Value )
// {
//     GPIOx->ODRLOWBYTE = Value;
// }

//=============================================================================
//翻转指定引脚电平，多个引脚
//注意：如只操作一只引脚，建议采用宏函数，例PA00_TOG()
/**
 * @brief 翻转指定引脚电平，可同时设置多个引脚
 * 
 * @param GPIOx 参数为下列参数之一：
 *        @arg CW_GPIOA CW_GPIOB CW_GPIOC
 * @param GPIO_Pins 
 */
void GPIO_TogglePin(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pins)
{
    GPIOx->TOG = GPIO_Pins;
}

//=============================================================================
//将PA02/PA05设置成GPIO
/**
 * @brief 将PA02/PA05设置成GPIO
 * 
 */
void GPIO_SWD2GPIO( void )
{
    CW_SYSCTRL->CR2 =  CW_SYSCTRL->CR2 | ( 0x5A5A0000 | bv1 );
}

//=============================================================================
//将PA02/PA05设置成SWD
/**
 * @brief 将PA02/PA05设置成SWD，PA02/SWDIO PA05/SWCLK
 * 
 */
void GPIO_GPIO2SWD( void )
{
    CW_SYSCTRL->CR2 =  0x5A5A0000 | ( CW_SYSCTRL->CR2 & (~(bv1)) );
}

//=============================================================================
//将PC05设置成GPIO
/**
 * @brief 将PC05设置成GPIO
 * 
 */
void GPIO_NRST2GPIO( void )
{
    CW_SYSCTRL->CR2 =  CW_SYSCTRL->CR2 | ( 0x5A5A0000 | bv0 );
}

//=============================================================================
//将PC05设置成NRST
/**
 * @brief 将PC05设置成NRST
 * 
 */
void GPIO_GPIO2NRST( void )
{
    CW_SYSCTRL->CR2 =  0x5A5A0000 | ( CW_SYSCTRL->CR2 & (~(bv0)) );
}

//=============================================================================
//配置端口滤波
// FltClk 只能是宏定义中定义的参数
/**
 * @brief 配置端口滤波
 * 
 * @param GPIOx 参数为下列参数之一：
 *        @arg CW_GPIOA CW_GPIOB CW_GPIOC
 * @param GPIO_Pins 
 * @param FltClk 只能是宏定义中定义的参数 GPIO_FLTCLK_xxx
 */
void GPIO_ConfigFilter( GPIO_TypeDef* GPIOx, uint16_t GPIO_Pins, uint32_t FltClk )
{
    GPIOx->FILTER = FltClk | GPIO_Pins;
}

//=============================================================================
//配置端口辅助功能
//请使用cw32f003_gpio.h中的宏定义来配置每个端口的辅助功能

