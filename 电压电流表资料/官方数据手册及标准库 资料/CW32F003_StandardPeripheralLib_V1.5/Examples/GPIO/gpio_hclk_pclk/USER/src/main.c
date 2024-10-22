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
 ** 从PA03/PA04输出HCLK及PCLK，并翻转PA05管脚
 **
 ******************************************************************************/
int32_t main(void)
{
    CW_SYSCTRL->AHBEN_f.GPIOB = 1;    //Open GPIOB Clk
    CW_SYSCTRL->AHBEN_f.GPIOC = 1;    //Open GPIOC Clk
    
    //配置PB3,PB4,PC0为输出
    REGBITS_CLR(CW_GPIOB->ANALOG , bv3 | bv4);  //当同时操作多个管脚时建议使用REGBITS_xxx宏以提高效率
    REGBITS_CLR(CW_GPIOB->DIR    , bv3 | bv4);
    REGBITS_CLR(CW_GPIOC->ANALOG , bv0);
    REGBITS_CLR(CW_GPIOC->DIR    , bv0);  
    PB03_AFx_PCLKOUT();                                 //配置PB03输出PCLK
    PC00_AFx_HCLKOUT();                                 //配置PC00输出HCLK

    while(1)
    {
        CW_GPIOB->TOG = bv4;    //翻转PB04
    }
    
}


/******************************************************************************
 * EOF (not truncated)
 ******************************************************************************/


