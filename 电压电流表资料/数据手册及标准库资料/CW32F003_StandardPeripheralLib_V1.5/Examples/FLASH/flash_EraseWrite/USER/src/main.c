/**
 * @file main.c
 * @author your name (you@domain.com)
 * @brief
 * @version 0.1
 * @date 2021-06-25
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
 /******************************************************************************
  * Include files
  ******************************************************************************/
#include "../inc/main.h"
#include "../inc/interrupts_cw32f003.h"
#include "cw32f003_rcc.h"
#include "cw32f003_flash.h"
#include "cw32f003_gpio.h"
/******************************************************************************
 * Local pre-processor symbols/macros ('#define')
 ******************************************************************************/

/******************************************************************************
 * Global variable definitions (declared in header file with 'extern')
 ******************************************************************************/
uint8_t AddrBuf[256];

/******************************************************************************
 * Local type definitions ('typedef')
 ******************************************************************************/

/******************************************************************************
 * Local function prototypes ('static')
 ******************************************************************************/
void RCC_Configuration(void);
void GPIO_Configuration(void);

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
* @brief Main function of project
* //对PAGE39进行擦除，并验证。
* //对PAGE39进行写入，并验证。
* @return int32_t
*/
int32_t main(void)
{
    uint8_t  Flag, tmp8;
    uint16_t i;

    //时钟初始化
    RCC_Configuration();
    // GPIO初始化
    GPIO_Configuration();

    //erase
    FLASH_UnlockPages(512 * 39, 512 * 40 -1);  //解锁最后一个页面
    Flag = FLASH_ErasePages(512 * 39, 512 * 40-1);  //擦除最后一个页面
    FLASH_LockAllPages();
    if (Flag)
    {
        while (1);  //擦除失败
    }
    for (i = 0; i <= 255; i++)
    {
        tmp8 = *((volatile uint8_t*)(512 * 39 + i));
        if (tmp8 != 0xFF)
        {
            while (1);  //对擦除后的结果进行验证失败
        }
    }


    //write
    for (i = 0; i <= 255; i++)
    {
        AddrBuf[i] = i;
    }
    FLASH_UnlockPages(512 * 39, 512 * 40-1);  //解锁最后一个页面
    Flag = FLASH_WirteBytes(512 * 39, AddrBuf, 256);
    FLASH_LockAllPages();
    if (Flag)
    {
        while (1);  //写入失败
    }

    //read
    for (i = 0; i <= 255; i++)
    {
        tmp8 = *((volatile uint8_t*)(512 * 39 + i));
        if (tmp8 != i)
        {
            while (1);  //对写入的数据进行验证失败
        }
    }

    //结束
    while (1)
    {
        PA07_TOG();
        PA06_TOG();
        FirmwareDelay(1000000);
    }

}

/**
  * @brief  Configures the different system clocks.
  * @param  None
  * @retval None
  */
void RCC_Configuration(void)
{
    RCC_HSI_Enable(RCC_HSIOSC_DIV6);
    
    CW_SYSCTRL->AHBEN |= SYSCTRL_AHBEN_FLASH_Msk | SYSCTRL_AHBEN_GPIOA_Msk | SYSCTRL_AHBEN_GPIOB_Msk;
}

/**
 * @brief GPIO 初始化
 * 
 */
void GPIO_Configuration(void)
{
    GPIO_InitTypeDef GPIO_InitStruct;

    GPIO_InitStruct.IT = GPIO_IT_NONE;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Pins = GPIO_PIN_6 | GPIO_PIN_7;   // LED1和LED2
    GPIO_Init(CW_GPIOA, &GPIO_InitStruct);
    PA07_SETHIGH();
    PA06_SETHIGH();
}

/******************************************************************************
 * EOF (not truncated)
 ******************************************************************************/


