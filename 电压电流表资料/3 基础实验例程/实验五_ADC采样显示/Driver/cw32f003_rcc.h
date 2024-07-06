/**
 * @file cw32f003_rcc.h
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2021-05-13
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

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __CW32F003_RCC_H
#define __CW32F003_RCC_H
                        
#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "cw32f003.h"


//==================================================================================

#define HSIOSC_VALUE                             ((uint32_t)48000000)/*!<ValueoftheInternaloscillatorinHz*/
#define HEX_VALUE                                ((uint32_t)16000000)/*!<ValueoftheExternaloscillatorinHz*/
#define LSI_VALUE                                ((uint32_t)32800)/*!<ValueoftheExternaloscillatorinHz*/

/* SYSCTRL CR0 --------------------------------------------------------*/
#define SYSCTRL_BYPASS                           (0x5A5A0000U)
#define SYSCTRL_BYPASS_MASK                      (0xFFFF0000U)

#define RCC_HCLK_DIV1                            (0x0UL<<SYSCTRL_CR0_HCLKPRS_Pos)/*!<SYSCLKnotdivided*/
#define RCC_HCLK_DIV2                            (0x1UL<<SYSCTRL_CR0_HCLKPRS_Pos)/*!<SYSCLKdividedby2*/
#define RCC_HCLK_DIV4                            (0x2UL<<SYSCTRL_CR0_HCLKPRS_Pos)/*!<SYSCLKdividedby4*/
#define RCC_HCLK_DIV8                            (0x3UL<<SYSCTRL_CR0_HCLKPRS_Pos)/*!<SYSCLKdividedby8*/
#define RCC_HCLK_DIV16                           (0x4UL<<SYSCTRL_CR0_HCLKPRS_Pos)/*!<SYSCLKdividedby16*/
#define RCC_HCLK_DIV32                           (0x5UL<<SYSCTRL_CR0_HCLKPRS_Pos)/*!<SYSCLKdividedby32*/
#define RCC_HCLK_DIV64                           (0x6UL<<SYSCTRL_CR0_HCLKPRS_Pos)/*!<SYSCLKdividedby64*/
#define RCC_HCLK_DIV128                          (0x7ul<<SYSCTRL_CR0_HCLKPRS_Pos)/*!<SYSCLKdividedby128*/
#define IS_RCC_HCLKPRS(INSTANCE)                 (((INSTANCE)==RCC_HCLK_DIV1)||\
                                                 ((INSTANCE) == RCC_HCLK_DIV2)       ||\
                                                 ((INSTANCE) == RCC_HCLK_DIV4)       ||\
                                                 ((INSTANCE) == RCC_HCLK_DIV8)       ||\
                                                 ((INSTANCE) == RCC_HCLK_DIV16)      ||\
                                                 ((INSTANCE) == RCC_HCLK_DIV32)      ||\
                                                 ((INSTANCE) == RCC_HCLK_DIV64)      ||\
                                                 ((INSTANCE) == RCC_HCLK_DIV128))

#define RCC_PCLK_DIV1                            (0x0UL<<SYSCTRL_CR0_PCLKPRS_Pos)/*!<HCLKnotdivided*/
#define RCC_PCLK_DIV2                            (0x1UL<<SYSCTRL_CR0_PCLKPRS_Pos)/*!<HCLKdividedby2*/
#define RCC_PCLK_DIV4                            (0x2UL<<SYSCTRL_CR0_PCLKPRS_Pos)/*!<HCLKdividedby4*/
#define RCC_PCLK_DIV8                            (0x3UL<<SYSCTRL_CR0_PCLKPRS_Pos)/*!<HCLKdividedby8*/
#define IS_RCC_PCLKPRS(INSTANCE)                 (((INSTANCE)==RCC_PCLK_DIV1)||\
                                                 ((INSTANCE) == RCC_PCLK_DIV2)       ||\
                                                 ((INSTANCE) == RCC_PCLK_DIV4)       ||\
                                                 ((INSTANCE) == RCC_PCLK_DIV8)   

#define RCC_SYSCLKSRC_HSI                        (0x00000000U)/*!<HSIselectedassystemclock*/
#define RCC_SYSCLKSRC_HEX                        (0x00000001U)/*!<HEXselectedassystemclock*/
#define RCC_SYSCLKSRC_LSI                        (0x00000003U)/*!<LSIselectedassystemclock*/
#define IS_RCC_SYSCLKSRC(INSTANCE)               (((INSTANCE)==RCC_SYSCLKSRC_HSI)||\
                                                 ((INSTANCE) == RCC_SYSCLKSRC_HEX)   ||\
                                                 ((INSTANCE) == RCC_SYSCLKSRC_LSE))

/* SYSCTRL CR1 --------------------------------------------------------*/
#define RCC_SYSCTRL_HSIEN                        bv0
#define RCC_SYSCTRL_HEXEN                        bv1
#define RCC_SYSCTRL_LSIEN                        bv3

/* SYSCTRL CR2 --------------------------------------------------------*/
#define RCC_SYSCTRL_RSTIOEN                      0x00UL
#define RCC_SYSCTRL_RSTIODIS                     bv0
#define IS_RCC_RSTIO_STATUS(INSTANCE)            (((INSTANCE)==RCC_SYSCTRL_RSTIOEN)||\
                                                 ((INSTANCE) == RCC_SYSCTRL_RSTIODIS))
   
#define RCC_SYSCTRL_SWDIOEN                      0x00UL
#define RCC_SYSCTRL_SWDIODIS                     bv1
#define IS_RCC_SWDIO_STATUS(INSTANCE)            (((INSTANCE)==RCC_SYSCTRL_SWDIOEN)||\
                                                 ((INSTANCE) == RCC_SYSCTRL_SWDIODIS))
   
#define RCC_SYSCTRL_LOCKUPEN                     bv2
#define RCC_SYSCTRL_LOCKUPDIS                    0x00UL
#define IS_RCC_LOCKUP_STATUS(INSTANCE)           (((INSTANCE)==RCC_SYSCTRL_LOCKUPEN)||\
                                                 ((INSTANCE) == RCC_SYSCTRL_LOCKUPDIS))

#define RCC_SYSCTRL_WAKEUPCLKEN                  bv3
#define RCC_SYSCTRL_WAKEUPCLKDIS                 0x00UL
#define IS_RCC_WAKEUPCLK_STATUS(INSTANCE)        (((INSTANCE)==RCC_SYSCTRL_WAKEUPCLKEN)||\
                                                 ((INSTANCE) == RCC_SYSCTRL_WAKEUPCLKDIS))               

/* SYSCTRL HSI --------------------------------------------------------*/
#define RCC_HSI_TRIMCODEADDR                     (0x001007B8U)//

#define RCC_HSIOSC_DIV6                          (0x5U)
#define RCC_HSIOSC_DIV1                          (0x6U)
#define RCC_HSIOSC_DIV2                          (0x8U)
#define RCC_HSIOSC_DIV4                          (0x9U)
#define RCC_HSIOSC_DIV8                          (0xBU)
#define RCC_HSIOSC_DIV10                         (0xCU)
#define RCC_HSIOSC_DIV12                         (0xDU)
#define RCC_HSIOSC_DIV14                         (0xEU)
#define RCC_HSIOSC_DIV16                         (0xFU)

#define IS_RCC_HSIOSC_DIV(INSTANCE)              (((INSTANCE)==RCC_HSIOSC_DIV1)||\
                                                 ((INSTANCE) == RCC_HSIOSC_DIV2)          ||\
                                                 ((INSTANCE) == RCC_HSIOSC_DIV4)          ||\
                                                 ((INSTANCE) == RCC_HSIOSC_DIV6)          ||\
                                                 ((INSTANCE) == RCC_HSIOSC_DIV8)          ||\
                                                 ((INSTANCE) == RCC_HSIOSC_DIV10)         ||\
                                                 ((INSTANCE) == RCC_HSIOSC_DIV12)         ||\
                                                 ((INSTANCE) == RCC_HSIOSC_DIV14)         ||\
                                                 ((INSTANCE) == RCC_HSIOSC_DIV16))

/* SYSCTRL LSI --------------------------------------------------------*/
#define RCC_LSI_TRIMCODEADDR                     (0x001007BAU)
   
#define RCC_LSI_WAITCYCLE_6                      ((uint32_t)(0x0UL<<SYSCTRL_LSI_WAITCYCLE_Pos))
#define RCC_LSI_WAITCYCLE_18                     ((uint32_t)(0x1UL<<SYSCTRL_LSI_WAITCYCLE_Pos))
#define RCC_LSI_WAITCYCLE_66                     ((uint32_t)(0x2UL<<SYSCTRL_LSI_WAITCYCLE_Pos))
#define RCC_LSI_WAITCYCLE_258                    ((uint32_t)(0x3UL<<SYSCTRL_LSI_WAITCYCLE_Pos))


/* SYSCTRL HEX --------------------------------------------------------*/
#define RCC_HEX_PINEN                            bv6
#define RCC_HEX_PINDIS                           0x0U
#define IS_RCC_HEX_PIN_MODE(INSTANCE)            (((INSTANCE)==RCC_HEX_PINEN)||\
                                                 ((INSTANCE) == RCC_HEX_PINDIS))

#define RCC_HEX_PINMUX_PB00                      0x0U
#define RCC_HEX_PINMUX_PB01                      bv7
#define IS_RCC_HEX_PINMUX_MODE(INSTANCE)         (((INSTANCE)==RCC_HEX_PINMUX_PB00)||\
                                                 ((INSTANCE) == RCC_HEX_PINMUX_PB01))
    
/* SYSCTRL IER --------------------------------------------------------*/
#define RCC_IT_LSIRDY                            (bv3)
#define RCC_IT_HEXRDY                            (bv1)
#define RCC_IT_HSIRDY                            (bv0)
#define IS_RCC_IT(IT)                            (((IT)&0xFFFFFFE0==0x0UL)&&((IT)!=0x0UL))
#define IS_RCC_GET_IT(IT)                        (((IT)==RCC_IT_LSIRDY)||\
                                                 ((IT) == RCC_IT_HEXRDY) ||\
                                                 ((IT) == RCC_IT_HSIRDY))

/* SYSCTRL ISR --------------------------------------------------------*/
#define RCC_FLAG_HSISTABLE                       bv11
#define RCC_FLAG_HEXSTABLE                       bv12
#define RCC_FLAG_LSISTABLE                       bv14
#define IS_RCC_STABLEFLAG(FLAG)                  (((FLAG)==RCC_FLAG_HSISTABLE)||((FLAG)==RCC_FLAG_HEXSTABLE)||\
                                                 ((FLAG) == RCC_FLAG_LSISTABLE))

/* SYSCTRL AHBEN --------------------------------------------------------*/
#define RCC_AHB_PERIPH_GPIOC                     bv6
#define RCC_AHB_PERIPH_GPIOB                     bv5
#define RCC_AHB_PERIPH_GPIOA                     bv4
#define RCC_AHB_PERIPH_CRC                       bv2
#define RCC_AHB_PERIPH_FLASH                     bv1
#define IS_RCC_AHB_PERIPH(PERIPH)                ((((PERIPH)&0xFFFFFFF8)==0x00)&&((PERIPH)!=0x00))


#define __RCC_GPIOC_CLK_ENABLE()                 REGBITS_SET(CW_SYSCTRL->AHBEN,RCC_AHB_PERIPH_GPIOC)
#define __RCC_GPIOB_CLK_ENABLE()                 REGBITS_SET(CW_SYSCTRL->AHBEN,RCC_AHB_PERIPH_GPIOB)
#define __RCC_GPIOA_CLK_ENABLE()                 REGBITS_SET(CW_SYSCTRL->AHBEN,RCC_AHB_PERIPH_GPIOA)
#define __RCC_CRC_CLK_ENABLE()                   REGBITS_SET(CW_SYSCTRL->AHBEN,RCC_AHB_PERIPH_CRC)
#define __RCC_FLASH_CLK_ENABLE()                 REGBITS_SET(CW_SYSCTRL->AHBEN,RCC_AHB_PERIPH_FLASH)

#define __RCC_GPIOC_CLK_DISABLE()                (CW_SYSCTRL->AHBEN&=~(RCC_AHB_PERIPH_GPIOC))
#define __RCC_GPIOB_CLK_DISABLE()                (CW_SYSCTRL->AHBEN&=~(RCC_AHB_PERIPH_GPIOB))
#define __RCC_GPIOA_CLK_DISABLE()                (CW_SYSCTRL->AHBEN&=~(RCC_AHB_PERIPH_GPIOA))
#define __RCC_CRC_CLK_DISABLE()                  (CW_SYSCTRL->AHBEN&=~(RCC_AHB_PERIPH_CRC))
#define __RCC_FLASH_CLK_DISABLE()                (CW_SYSCTRL->AHBEN&=~(RCC_AHB_PERIPH_FLASH))

/* SYSCTRL AHPEN1 --------------------------------------------------------*/
#define RCC_APB1_PERIPH_I2C                      bv11
#define RCC_APB1_PERIPH_UART2                    bv7
#define RCC_APB1_PERIPH_IWDT                     bv5
#define RCC_APB1_PERIPH_WWDT                     bv4
#define RCC_APB1_PERIPH_GTIM                     bv1
#define IS_RCC_APB1_PERIPH(PERIPH)               ((((PERIPH)&0xFFFFF74D)==0x00)&&((PERIPH)!=0x00))

#define __RCC_I2C_CLK_ENABLE()                   REGBITS_SET(CW_SYSCTRL->APBEN1,RCC_APB1_PERIPH_I2C)
#define __RCC_UART2_CLK_ENABLE()                 REGBITS_SET(CW_SYSCTRL->APBEN1,RCC_APB1_PERIPH_UART2)
#define __RCC_IWDT_CLK_ENABLE()                  REGBITS_SET(CW_SYSCTRL->APBEN1,RCC_APB1_PERIPH_IWDT)
#define __RCC_WWDT_CLK_ENABLE()                  REGBITS_SET(CW_SYSCTRL->APBEN1,RCC_APB1_PERIPH_WWDT)
#define __RCC_GTIM_CLK_ENABLE()                  REGBITS_SET(CW_SYSCTRL->APBEN1,RCC_APB1_PERIPH_GTIM)

#define __RCC_I2C_CLK_DISABLE()                  (CW_SYSCTRL->APBEN1&=~(RCC_APB1_PERIPH_I2C))
#define __RCC_UART2_CLK_DISABLE()                (CW_SYSCTRL->APBEN1&=~(RCC_APB1_PERIPH_UART2))
#define __RCC_IWDT_CLK_DISABLE()                 (CW_SYSCTRL->APBEN1&=~(RCC_APB1_PERIPH_IWDT))
#define __RCC_WWDT_CLK_DISABLE()                 (CW_SYSCTRL->APBEN1&=~(RCC_APB1_PERIPH_WWDT))
#define __RCC_GTIM_CLK_DISABLE()                 (CW_SYSCTRL->APBEN1&=~(RCC_APB1_PERIPH_GTIM))

/* SYSCTRL AHPEN1 --------------------------------------------------------*/
#define RCC_APB2_PERIPH_AWT                      bv13
#define RCC_APB2_PERIPH_BTIM                     bv12
#define RCC_APB2_PERIPH_UART1                    bv9
#define RCC_APB2_PERIPH_SPI                      bv8
#define RCC_APB2_PERIPH_ATIM                     bv7
#define RCC_APB2_PERIPH_VC                       bv4
#define RCC_APB2_PERIPH_ADC                      bv2
#define IS_RCC_APB2_PERIPH(PERIPH)               ((((PERIPH)&0xFFFFCC63)==0x00)&&((PERIPH)!=0x00))

#define __RCC_AWT_CLK_ENABLE()                   REGBITS_SET(CW_SYSCTRL->APBEN2,RCC_APB2_PERIPH_AWT)
#define __RCC_BTIM_CLK_ENABLE()                  REGBITS_SET(CW_SYSCTRL->APBEN2,RCC_APB2_PERIPH_BTIM)
#define __RCC_UART1_CLK_ENABLE()                 REGBITS_SET(CW_SYSCTRL->APBEN2,RCC_APB2_PERIPH_UART1)
#define __RCC_SPI_CLK_ENABLE()                   REGBITS_SET(CW_SYSCTRL->APBEN2,RCC_APB2_PERIPH_SPI)
#define __RCC_ATIM_CLK_ENABLE()                  REGBITS_SET(CW_SYSCTRL->APBEN2,RCC_APB2_PERIPH_ATIM)
#define __RCC_VC_CLK_ENABLE()                    REGBITS_SET(CW_SYSCTRL->APBEN2,RCC_APB2_PERIPH_VC)
#define __RCC_ADC_CLK_ENABLE()                   REGBITS_SET(CW_SYSCTRL->APBEN2,RCC_APB2_PERIPH_ADC)

#define __RCC_AWT_CLK_DISABLE()                  (CW_SYSCTRL->APBEN2&=~(RCC_APB2_PERIPH_AWT))
#define __RCC_BTIM_CLK_DISABLE()                 (CW_SYSCTRL->APBEN2&=~(RCC_APB2_PERIPH_BTIM))
#define __RCC_UART1_CLK_DISABLE()                (CW_SYSCTRL->APBEN2&=~(RCC_APB2_PERIPH_UART1))
#define __RCC_SPI_CLK_DISABLE()                  (CW_SYSCTRL->APBEN2&=~(RCC_APB2_PERIPH_SPI))
#define __RCC_ATIM_CLK_DISABLE()                 (CW_SYSCTRL->APBEN2&=~(RCC_APB2_PERIPH_ATIM))
#define __RCC_VC_CLK_DISABLE()                   (CW_SYSCTRL->APBEN2&=~(RCC_APB2_PERIPH_VC))
#define __RCC_ADC_CLK_DISABLE()                  (CW_SYSCTRL->APBEN2&=~(RCC_APB2_PERIPH_ADC))

/* SYSCTRL AHBRST --------------------------------------------------------*/
#define RCC_AHBRST_GPIOC                         bv6
#define RCC_AHBRST_GPIOB                         bv5
#define RCC_AHBRST_GPIOA                         bv4
#define RCC_AHBRST_CRC                           bv2
#define RCC_AHBRST_FLASH                         bv1
#define RCC_AHBRST_ALL                           ((uint32_t)0x00000076)
#define IS_RCC_AHBRST(PERIPH)                    ((((PERIPH)&0xFFFFFF89)==0x00)&&((PERIPH)!=0x00))

/* SYSCTRL APBRST1 --------------------------------------------------------*/
#define RCC_APBRST1_I2C                          bv11
#define RCC_APBRST1_UART2                        bv7
#define RCC_APBRST1_IWDT                         bv5
#define RCC_APBRST1_WWDT                         bv4
#define RCC_APBRST1_GTIM                         bv1
#define RCC_APBRST1_ALL                          ((uint32_t)0x000008B2)
#define IS_RCC_APBRST1(PERIPH)                   ((((PERIPH)&0xFFFFF74D)==0x00)&&((PERIPH)!=0x00))

/* SYSCTRL APBRST2 --------------------------------------------------------*/
#define RCC_APBRST2_AWT                          bv13
#define RCC_APBRST2_BTIM                         bv12
#define RCC_APBRST2_UART1                        bv9
#define RCC_APBRST2_SPI                          bv8
#define RCC_APBRST2_ATIM                         bv7
#define RCC_APBRST2_VC                           bv4
#define RCC_APBRST2_ADC                          bv2
#define RCC_APBRST2_ALL                          ((uint32_t)0x00003394)
#define IS_RCC_APBRST2(PERIPH)                   ((((PERIPH)&0xFFFFCC6B)==0x00)&&((PERIPH)!=0x00))

/* SYSCTRL RESTFLAG --------------------------------------------------------*/
#define RCC_RESTFLAG_SYSRESETREQ                 bv9
#define RCC_RESTFLAG_LOCKUP                      bv8
#define RCC_RESTFLAG_RSTB                        bv6
#define RCC_RESTFLAG_WWDT                        bv5
#define RCC_RESTFLAG_IWDT                        bv4
#define RCC_RESTFLAG_LVD                         bv3
#define RCC_RESTFLAG_POR                         bv0
#define RCC_RESTFLAG_ALL                         ((uint32_t)0xFFFFFFFF)
#define IS_RCC_RESTFLAG(FLAG)                    (((FLAG)==RCC_RESTFLAG_SYSRESETREQ)||\
                                                 ((FLAG) == RCC_RESTFLAG_LOCKUP) ||      \
                                                 ((FLAG) == RCC_RESTFLAG_RSTB) ||        \
                                                 ((FLAG) == RCC_RESTFLAG_WWDT) ||        \
                                                 ((FLAG) == RCC_RESTFLAG_IWDT) ||        \
                                                 ((FLAG) == RCC_RESTFLAG_LVD) ||         \
                                                 ((FLAG) == RCC_RESTFLAG_POR) ||         \
                                                 ((FLAG) == RCC_RESTFLAG_ALL))

/* SYSCTRL DEBUG --------------------------------------------------------*/
#define RCC_DEBUG_WWDT                           bv10
#define RCC_DEBUG_IWDT                           bv9
#define RCC_DEBUG_AWT                            bv6
#define RCC_DEBUG_BTIM123                        bv5
#define RCC_DEBUG_GTIM                           bv1
#define RCC_DEBUG_ATIM                           bv0
#define IS_RCC_DEBUG(PERIPH)                     (((PERIPH)==RCC_DEBUG_WWDT)||\
                                                 ((PERIPH) == RCC_DEBUG_IWDT) ||    \
                                                 ((PERIPH) == RCC_DEBUG_AWT) ||     \
                                                 ((PERIPH) == RCC_DEBUG_BTIM123) || \
                                                 ((PERIPH) == RCC_DEBUG_GTIM) ||    \
                                                 ((PERIPH) == RCC_DEBUG_ATIM))

/* SYSCTRL GTIMCAP --------------------------------------------------------*/
#define GTIM_CAP_GPIO                            (0x00UL)
#define GTIM_CAP_RXD1                            (0x01UL)
#define GTIM_CAP_RXD2                            (0x02UL)
#define GTIM_CAP_VCO1                            (0x04UL)
#define GTIM_CAP_VCO2                            (0x05UL)
#define GTIM_CAP_LVDO                            (0x06UL)
#define IS_GTIM_CAP_INPUT(IN)                    (((IN)==GTIM_CAP_GPIO)||\
                                                 ((IN) == GTIM_CAP_RXD1) ||\
                                                 ((IN) == GTIM_CAP_RXD2) ||\
                                                 ((IN) == GTIM_CAP_VCO1) ||\
                                                 ((IN) == GTIM_CAP_VCO2) ||\
                                                 ((IN) == GTIM_CAP_LVDO))

/* SYSCTRL ATIMETR --------------------------------------------------------*/
#define ATIM_ETR_GPIO                            (0x00UL)
#define ATIM_ETR_RXD1                            (0x01UL)
#define ATIM_ETR_RXD2                            (0x02UL)
#define ATIM_ETR_VCO1                            (0x04UL)
#define ATIM_ETR_VCO2                            (0x05UL)
#define ATIM_ETR_LVDO                            (0x06UL)
#define IS_ATIM_ETR_INPUT(IN)                    (((IN)==ATIM_ETR_GPIO)||\
                                                 ((IN) == ATIM_ETR_RXD1) || \
                                                 ((IN) == ATIM_ETR_RXD2) || \
                                                 ((IN) == ATIM_ETR_VCO1) || \
                                                 ((IN) == ATIM_ETR_VCO2) || \
                                                 ((IN) == ATIM_ETR_LVDO))

/* SYSCTRL GTIMETR --------------------------------------------------------*/
#define GTIM_ETR_GPIO                            (0x00UL)
#define GTIM_ETR_RXD1                            (0x01UL)
#define GTIM_ETR_RXD2                            (0x02UL)
#define GTIM_ETR_VCO1                            (0x04UL)
#define GTIM_ETR_VCO2                            (0x05UL)
#define GTIM_ETR_LVDO                            (0x06UL)
#define IS_GTIM_ETR_INPUT(IN)                    (((IN)==GTIM_ETR_GPIO)||\
                                                 ((IN) == GTIM_ETR_RXD1) || \
                                                 ((IN) == GTIM_ETR_RXD2) || \
                                                 ((IN) == GTIM_ETR_VCO1) || \
                                                 ((IN) == GTIM_ETR_VCO2) || \
                                                 ((IN) == GTIM_ETR_LVDO))

/* SYSCTRL TIMITR --------------------------------------------------------*/
#define RCC_TIMITR_BTIM1                         (0UL)
#define RCC_TIMITR_BTIM2                         (1UL)
#define RCC_TIMITR_BTIM3                         (2UL)
#define RCC_TIMITR_GTIM                          (3UL)
#define RCC_TIMITR_ATIM                          (7UL)
#define IS_RCC_TIMITR_SOURCE(SRC)                ((SRC)<4||(SRC)==RCC_TIMITR_ATIM)

/* SYSCTRL MCO --------------------------------------------------------*/
#define RCC_MCO_DIV1                             (0x00U)
#define RCC_MCO_DIV2                             ((uint8_t)(0x01U<<SYSCTRL_MCO_DIV_Pos))
#define RCC_MCO_DIV8                             ((uint8_t)(0x02U<<SYSCTRL_MCO_DIV_Pos))
#define RCC_MCO_DIV64                            ((uint8_t)(0x03U<<SYSCTRL_MCO_DIV_Pos))
#define RCC_MCO_DIV128                           ((uint8_t)(0x04U<<SYSCTRL_MCO_DIV_Pos))
#define RCC_MCO_DIV256                           ((uint8_t)(0x05U<<SYSCTRL_MCO_DIV_Pos))
#define RCC_MCO_DIV512                           ((uint8_t)(0x06U<<SYSCTRL_MCO_DIV_Pos))
#define RCC_MCO_DIV1024                          ((uint8_t)(0x07U<<SYSCTRL_MCO_DIV_Pos))

#define IS_RCC_MCO_DIV(INSTANCE)                 (((INSTANCE)==RCC_MCO_DIV1)||\
                                                 ((INSTANCE) == RCC_MCO_DIV2)          ||\
                                                 ((INSTANCE) == RCC_MCO_DIV8)          ||\
                                                 ((INSTANCE) == RCC_MCO_DIV64)         ||\
                                                 ((INSTANCE) == RCC_MCO_DIV128)        ||\
                                                 ((INSTANCE) == RCC_MCO_DIV256)        ||\
                                                 ((INSTANCE) == RCC_MCO_DIV512)        ||\
                                                 ((INSTANCE) == RCC_MCO_DIV1024)) 

#define RCC_MCO_SRC_NONE                         (0x00U)
#define RCC_MCO_SRC_HCLK                         (0x01U)
#define RCC_MCO_SRC_PCLK                         (0x02U)
#define RCC_MCO_SRC_HSI                          (0x03U)
#define RCC_MCO_SRC_LSI                          (0x04U)
#define RCC_MCO_SRC_HEX                          (0x05U)
#define RCC_MCO_SRC_RC150K                       (0x08U)
#define RCC_MCO_SRC_RC10K                        (0x09U)

#define IS_RCC_MCO_SRC(INSTANCE)                 (((INSTANCE)==RCC_MCO_SRC_NONE)||\
                                                 ((INSTANCE) == RCC_MCO_SRC_HCLK)       || \
                                                 ((INSTANCE) == RCC_MCO_SRC_PCLK)       || \
                                                 ((INSTANCE) == RCC_MCO_SRC_HSI)        || \
                                                 ((INSTANCE) == RCC_MCO_SRC_LSI)        || \
                                                 ((INSTANCE) == RCC_MCO_SRC_HEX)        || \
                                                 ((INSTANCE) == RCC_MCO_SRC_RC150K)     || \
                                                 ((INSTANCE) == RCC_MCO_SRC_RC10K))



//==================================================================================
extern void RCC_HCLKPRS_Config(uint32_t HCLKPRS);
extern void RCC_PCLKPRS_Config(uint32_t PCLKPRS);
extern void RCC_SYSCLKSRC_Config(uint32_t SYSCLKSRC);
extern void RCC_LSI_Enable(void);
extern void RCC_LSI_Disable(void);
extern void RCC_HEX_Enable(uint32_t PINMUX);
extern void RCC_HEX_Disable(void);
extern void RCC_HSI_Enable(uint32_t HSIDiv);
extern void RCC_HSI_Disable(void);
extern void RCC_WAKEUPCLK_Config(uint32_t WAKEUPCLK);
extern void RCC_LOCKUP_Config(uint32_t LOCKUP);
extern void RCC_SWDIO_Config(uint32_t SWDIO);
extern void RCC_RSTIO_Config(uint32_t RSTIO);
extern void RCC_DeInit(void);
extern void RCC_SystemCoreClockUpdate(uint32_t NewFreq);
extern uint8_t RCC_SysClk_Switch(uint32_t NewClk);
extern void RCC_ITConfig(uint32_t RCC_IT, FunctionalState NewState);
extern ITStatus RCC_GetITStatus(uint32_t RCC_IT);
extern void RCC_ClearITPendingBit(uint32_t RCC_IT);
extern FlagStatus RCC_GetStableFlag(uint32_t RCC_STABLEFLAG);
extern uint32_t RCC_GetAllStableFlag( void );
extern void RCC_AHBPeriphClk_Enable(uint32_t Periph,FunctionalState NewState);
extern void RCC_APBPeriphClk_Enable1(uint32_t Periph,FunctionalState NewState);
extern void RCC_APBPeriphClk_Enable2(uint32_t Periph,FunctionalState NewState);
extern void RCC_AHBPeriphReset(uint32_t Periph,FunctionalState NewState);
extern void RCC_APBPeriphReset1(uint32_t Periph,FunctionalState NewState);
extern void RCC_APBPeriphReset2(uint32_t Periph,FunctionalState NewState);
extern FlagStatus RCC_GetRstFlag(uint32_t RCC_RSTFLAG);
extern uint32_t RCC_GetAllRstFlag( void );
extern void RCC_ClearRstFlag(uint32_t RCC_RSTFLAG);
extern void RCC_HCLK_OUT(void);
extern void RCC_PCLK_OUT(void);
extern void RCC_MCO_OUT(uint8_t Source, uint8_t Div);
extern void RCC_DEBUG_Config(uint32_t Periph, FunctionalState NewState);

extern uint32_t RCC_Sysctrl_GetHClkFreq(void);
extern uint32_t RCC_Sysctrl_GetPClkFreq(void);

void RCC_BTIM3ITRSelect(uint32_t Source);
void RCC_BTIM2ITRSelect(uint32_t Source);
void RCC_BTIM1ITRSelect(uint32_t Source);
void RCC_GTIMITRSelect(uint32_t Source);
void RCC_ATIMITRSelect(uint32_t Source);

#ifdef __cplusplus
}
#endif

#endif /* __CW32F003_RCC_H */
