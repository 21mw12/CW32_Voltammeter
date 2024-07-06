/**
 * @file cw32f003_rcc.c
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

/* Includes ------------------------------------------------------------------*/
#include "cw32f003_rcc.h"

/* Private_TypesDefinitions --------------------------------------------------*/
const uint32_t hsiprs_tbl[] = {6,6,6,6,6,6,1,3,2,4,6,8,10,12,14,16};

/* Private_Defines -----------------------------------------------------------*/

/* Private_Variables ---------------------------------------------------------*/

/* Private_FunctionPrototypes ------------------------------------------------*/

/* Private_Functions ---------------------------------------------------------*/

/* Public_Functions ----------------------------------------------------------*/

/**
 * @brief 配置SysClk 到 HCLK的分频系数
 * 
 * @param HCLKPRS ：RCC_HCLK_DIV1/2/4/8/16/32/64/128
 */
void RCC_HCLKPRS_Config(uint32_t HCLKPRS)
{
    assert_param(IS_RCC_HCLKPRS(HCLKPRS));
    CW_SYSCTRL->CR0 = ( (CW_SYSCTRL->CR0 & (~ (SYSCTRL_BYPASS_MASK | SYSCTRL_CR0_HCLKPRS_Msk))) | SYSCTRL_BYPASS | HCLKPRS );
}
/**
 * @brief 配置HCLK 到 PCLK的分频系数
 * 
 * @param PCLKPRS ：RCC_PCLK_DIV1/2/4/8
 */
void RCC_PCLKPRS_Config(uint32_t PCLKPRS)
{
    assert_param(IS_RCC_PCLKPRS(PCLKPRS));
    CW_SYSCTRL->CR0 = ( (CW_SYSCTRL->CR0 & (~ (SYSCTRL_BYPASS_MASK | SYSCTRL_CR0_PCLKPRS_Msk))) | SYSCTRL_BYPASS | PCLKPRS );
}

/**
 * @brief 配置SysClk的时钟源
 * 
 * @param SYSCLKSRC ：RCC_SYSCLKSRC_HSI RCC_SYSCLKSRC_HEX  
 *                    RCC_SYSCLKSRC_LSI 
 */
void RCC_SYSCLKSRC_Config(uint32_t SYSCLKSRC)
{
    assert_param(IS_RCC_SYSCLKSRC(SYSCLKSRC));
    CW_SYSCTRL->CR0 = ( (CW_SYSCTRL->CR0 & (~ (SYSCTRL_BYPASS_MASK | SYSCTRL_CR0_SYSCLK_Msk))) | SYSCTRL_BYPASS | SYSCLKSRC );
    RCC_SystemCoreClockUpdate( RCC_Sysctrl_GetHClkFreq() );
}

/**
 * @brief 配置CLKCCS  HEXCCS  LSECCS 功能
 * 
 * @param CCS  ：RCC_SYSCTRL_LSECCS  RCC_SYSCTRL_HEXCCS  RCC_SYSCTRL_CLKCCS
 * @param NewState  :ENABLE  DISABLE
 */
void RCC_CCS_Config(uint32_t CCS,FunctionalState NewState)
{
    assert_param(IS_RCC_CCS_STATUS(CCS));

    if (NewState != DISABLE)
    {
        CW_SYSCTRL->CR1 = ( ( (CW_SYSCTRL->CR1 & (~ SYSCTRL_BYPASS_MASK) ) | SYSCTRL_BYPASS ) | CCS );
    }
    else
    {
        CW_SYSCTRL->CR1 = ( ( (CW_SYSCTRL->CR1 & (~ SYSCTRL_BYPASS_MASK) ) | SYSCTRL_BYPASS) & (~CCS) );
    }
}

/**
 * @brief 配置LSELOCK功能：使能后软件无法关闭LSE时钟
 * 
 * @param LSELOCK ： RCC_SYSCTRL_LSELOCKEN  RCC_SYSCTRL_LSELOCKDIS
 */
void RCC_LSELOCK_Config(uint32_t LSELOCK)
{
    assert_param(IS_RCC_LSELOCK_STATUS(LSELOCK));
    CW_SYSCTRL->CR1 = ( (CW_SYSCTRL->CR1 & (~ SYSCTRL_BYPASS_MASK) ) | SYSCTRL_BYPASS | LSELOCK );
}

/**
 * @brief 配置WAKEUPCLK功能:决定从深度休眠模式唤醒后所使用的系统时钟源
 * 
 * @param WAKEUPCLK ：RCC_SYSCTRL_WAKEUPCLKEN   RCC_SYSCTRL_WAKEUPCLKDIS
 */
void RCC_WAKEUPCLK_Config(uint32_t WAKEUPCLK)
{
    assert_param(IS_RCC_WAKEUPCLK_STATUS(WAKEUPCLK));
    CW_SYSCTRL->CR2 = ( (CW_SYSCTRL->CR2 & (~ ( SYSCTRL_BYPASS_MASK | SYSCTRL_CR2_WAKEUPCLK_Msk ) ) ) | SYSCTRL_BYPASS | WAKEUPCLK );
}

/**
 * @brief 配置LOCK功能：决定异常故障后是否产生LOCKUP复位
 * 
 * @param LOCKUP ：RCC_SYSCTRL_LOCKUPEN  RCC_SYSCTRL_LOCKUPDIS
 */
void RCC_LOCKUP_Config(uint32_t LOCKUP)
{
    assert_param(IS_RCC_LOCKUP_STATUS(LOCKUP));
    CW_SYSCTRL->CR2 = ( (CW_SYSCTRL->CR2 & (~ ( SYSCTRL_BYPASS_MASK | SYSCTRL_CR2_LOCKUP_Msk ) ) ) | SYSCTRL_BYPASS | LOCKUP );
}

/**
 * @brief 配置端口SWDIO功能
 * 
 * @param SWDIO  ：RCC_SYSCTRL_SWDIOEN   RCC_SYSCTRL_SWDIODIS
 */
void RCC_SWDIO_Config(uint32_t SWDIO)
{
    assert_param(IS_RCC_SWDIO_STATUS(SWDIO));
    CW_SYSCTRL->CR2 = ( (CW_SYSCTRL->CR2 & (~ ( SYSCTRL_BYPASS_MASK | SYSCTRL_CR2_SWDIO_Msk ) ) ) | SYSCTRL_BYPASS | SWDIO );
}

/**
 * @brief 配置NRST的端口的功能
 * 
 * @param RSTIO RCC_SYSCTRL_RSTIOEN, RCC_SYSCTRL_RSTIODIS
 */
void RCC_RSTIO_Config(uint32_t RSTIO)
{
    assert_param(IS_RCC_RSTIO_STATUS(RSTIO));
    CW_SYSCTRL->CR2 = (CW_SYSCTRL->CR2 & ~SYSCTRL_CR2_RSTIO_Msk) | RSTIO;
}

/**
  * @brief  Resets the RCC clock configuration to the default reset state.
  * @param  None
  * @retval None
  * CAUTION:
  * 1、LSEEN Bit Not Changed ,so it will not affect RTC,BUT LSELOCK BIT Changed.
  * 2、Before CALL this funciton,we should set FLASH_CR2.WAIT 
  */
void RCC_DeInit(void)
{
  /* HSIEN Enable*/
  CW_SYSCTRL->CR1 = ( (CW_SYSCTRL->CR1 & (~ SYSCTRL_BYPASS_MASK) ) | SYSCTRL_BYPASS | RCC_SYSCTRL_HSIEN );  

  //Here need wait HSI STBALE
  while( (CW_SYSCTRL->HSI & SYSCTRL_HSI_STABLE_Msk) != SYSCTRL_HSI_STABLE_Msk ) //Wait stable
  {
    ;
  }

  // CW_FLASH->CR2 =  ( ((CW_FLASH->CR2) & (~ SYSCTRL_BYPASS_MASK) ) | (uint32_t)0x5A5A0001 );
  /* SWITCH TO HSI*/
  CW_SYSCTRL->CR0 = ( (CW_SYSCTRL->CR0 & (~ SYSCTRL_BYPASS_MASK) ) | SYSCTRL_BYPASS | RCC_SYSCLKSRC_HSI );    

 /* HCLKPRS SET TO 000,PCLKPRS SET TO 00*/
  CW_SYSCTRL->CR0 = ( (CW_SYSCTRL->CR0 & (~ SYSCTRL_BYPASS_MASK) ) | SYSCTRL_BYPASS | RCC_HCLK_DIV1 | \
                       RCC_PCLK_DIV1 | RCC_SYSCLKSRC_HSI ); 

  
  CW_SYSCTRL->CR1 = ( ((CW_SYSCTRL->CR1 & (~ SYSCTRL_BYPASS_MASK) ) | SYSCTRL_BYPASS | RCC_SYSCTRL_HSIEN) \
                        & (~ RCC_SYSCTRL_LSIEN) & (~ RCC_SYSCTRL_HEXEN)); 

  
  CW_SYSCTRL->CR2 =  (CW_SYSCTRL->CR2 & (~ SYSCTRL_BYPASS_MASK) ) | SYSCTRL_BYPASS | RCC_SYSCTRL_LOCKUPDIS  |\
                     RCC_SYSCTRL_SWDIODIS | RCC_SYSCTRL_RSTIODIS; 

  /* Disable all interrupts */
  CW_SYSCTRL->IER = 0x5A5AFE00;      //IER have KEY attribute

  /* Clear all pending bits  */
  CW_SYSCTRL->ICR &= 0xFFFFFE00;

  //外设时钟和复位寄存器设置 ??

}

/**
 * @brief 
 * 
 * @param NewFreq 
 */
void RCC_SystemCoreClockUpdate(uint32_t NewFreq)
{
    SystemCoreClock = NewFreq;
}

/**
 * @brief 获得系统时钟（HCLK）频率值
 * 
 * @return uint32_t   HCLK频率值(Hz)
 */
uint32_t RCC_Sysctrl_GetHClkFreq(void)
{
    uint32_t u32rtnVal = 0;
    uint32_t sysclksource = 0;
    uint32_t hsiprs = 0;
   
    sysclksource = CW_SYSCTRL->CR0_f.SYSCLK;
    hsiprs = CW_SYSCTRL->HSI_f.DIV;
   

    switch (sysclksource)
    {
        case 0x00:  /* HSI used as system clock */
            u32rtnVal = ( HSIOSC_VALUE / hsiprs_tbl[hsiprs] );
        break;
        case 0x01:  /* HEX used as system clock */
            u32rtnVal = HEX_VALUE;
        break;
        case 0x03:  /* LSI used as system clock */
            u32rtnVal = LSI_VALUE;
        break;      
        default:
            u32rtnVal = ( HSIOSC_VALUE / hsiprs_tbl[hsiprs] ) ;
        break;
    }
    u32rtnVal = ( u32rtnVal >> CW_SYSCTRL->CR0_f.HCLKPRS ) ;
    return u32rtnVal;
}

/**
 * @brief 获得外设时钟（PCLK）频率值
 * 
 * @return uint32_t    PCLK频率值(Hz)
 */
uint32_t RCC_Sysctrl_GetPClkFreq(void)
{
    uint32_t u32Val = 0;

    u32Val = RCC_Sysctrl_GetHClkFreq();
    u32Val = ( u32Val >> (CW_SYSCTRL->CR0_f.PCLKPRS) );
    return u32Val;
}

/**
* @brief  Enable HSI
* @param  HSIDiv:
*			RCC_HSIOSC_DIV1
*			RCC_HSIOSC_DIV2
*			RCC_HSIOSC_DIV3
*			RCC_HSIOSC_DIV4
*			RCC_HSIOSC_DIV6
*			RCC_HSIOSC_DIV8
*			RCC_HSIOSC_DIV10
*			RCC_HSIOSC_DIV12
*			RCC_HSIOSC_DIV14
*			RCC_HSIOSC_DIV16
*
* @retval None
*/
void RCC_HSI_Enable(uint32_t HSIDiv )
{
    assert_param(IS_RCC_HSIOSC_DIV(HSIDiv));
    
    CW_SYSCTRL->HSI  = ( HSIDiv << SYSCTRL_HSI_DIV_Pos ) | ( *((volatile uint16_t *)RCC_HSI_TRIMCODEADDR) ) ;        //正式版芯片才需要加载Trim值
    CW_SYSCTRL->CR1 |= SYSCTRL_BYPASS | SYSCTRL_CR1_HSIEN_Msk ;                   //Enable HSI
    while( (CW_SYSCTRL->HSI & SYSCTRL_HSI_STABLE_Msk) != SYSCTRL_HSI_STABLE_Msk ) //Wait stable
    {
        ;
    }
}

/**
* @brief  Disable HSI
* @param  None.
* @retval None.
*/
void RCC_HSI_Disable(void)
{	
    CW_SYSCTRL->CR1 = ( ( (CW_SYSCTRL->CR1 & (~ SYSCTRL_BYPASS_MASK) ) | SYSCTRL_BYPASS ) & \
                      (~SYSCTRL_CR1_HSIEN_Msk) );    	
}


/**
* @brief  Enable LSI
* @param  None:
* @retval None
*/
void RCC_LSI_Enable(void)
{
	CW_SYSCTRL->LSI  = *((uint16_t *)RCC_LSI_TRIMCODEADDR);                       //
    CW_SYSCTRL->LSI |= RCC_LSI_WAITCYCLE_258;                                     //WaitCycle = 258
    CW_SYSCTRL->CR1 |= SYSCTRL_BYPASS | SYSCTRL_CR1_LSIEN_Msk;                    //Enable LSI
    while( (CW_SYSCTRL->LSI & SYSCTRL_LSI_STABLE_Msk) != SYSCTRL_LSI_STABLE_Msk ) //Wait stable
    {
	    ;
    }
}

/**
* @brief  Disable LSI
* @param  None.
* @retval None.
*/
void RCC_LSI_Disable(void)
{
    CW_SYSCTRL->CR1 = ( ( (CW_SYSCTRL->CR1 & (~ SYSCTRL_BYPASS_MASK) ) | SYSCTRL_BYPASS ) & \
                      (~SYSCTRL_CR1_LSIEN_Msk) );
}

/**
 * @brief 允许外部时钟输入
 * 
 * @param PINMUX RCC_HEX_PINMUX_PB00， RCC_HEX_PINMUX_PB01
 */
void RCC_HEX_Enable(uint32_t PINMUX)
{    
    //参数断言
    assert_param(IS_RCC_HEX_PINMUX_MODE(PINMUX));    
    
    //根据HEX模式设置IO口功能
    CW_SYSCTRL->AHBEN |= SYSCTRL_AHBEN_GPIOB_Msk; //Open GPIOB Clk
    if (PINMUX == RCC_HEX_PINMUX_PB00)
    {
        CW_GPIOB->ANALOG &= ~bv0;                    // Digital
        CW_GPIOB->DIR    |= bv0;                     // INPUT
        CW_GPIOB->PUR    &= ~bv0;
        CW_GPIOB->PDR    |= bv0;
    }
    if (PINMUX == RCC_HEX_PINMUX_PB01)
    {
        CW_GPIOB->ANALOG &= ~bv1; // Digital
        CW_GPIOB->DIR    |= bv1;     // INPUT
        CW_GPIOB->PUR    &= ~bv1;
        CW_GPIOB->PDR    |= bv1;
    }

    CW_SYSCTRL->HEX = (CW_SYSCTRL->HEX & ~(SYSCTRL_HEX_PINMUX_Msk | SYSCTRL_HEX_PINEN_Msk)) | PINMUX | RCC_HEX_PINEN;

    //使能HEX
    CW_SYSCTRL->CR1 |= SYSCTRL_BYPASS | SYSCTRL_CR1_HEXEN_Msk;  //Enable HEX
		
    //等待HEX稳定
    while( (CW_SYSCTRL->HEX & SYSCTRL_HEX_STABLE_Msk) != SYSCTRL_HEX_STABLE_Msk )        //Wait stable
    {
        ;
    }
}

/**
* @brief  Disable HEX
* @param  None.
* @retval None.
*/
void RCC_HEX_Disable(void)
{
    CW_SYSCTRL->CR1 = ( ( (CW_SYSCTRL->CR1 & (~ SYSCTRL_BYPASS_MASK) ) | SYSCTRL_BYPASS ) & \
                      (~SYSCTRL_CR1_HEXEN_Msk) );
}


/**
* @brief  CLKSRC switch
* @param  NewClk:
*                RCC_SYSCLKSRC_HSI,
*                RCC_SYSCLKSRC_HEX,                
*                RCC_SYSCLKSRC_LSI                
* @retval 0: PASS, 1: Fail
*
* NOTE:调用此函数之前需要保证新时钟源已经使能（ENABLE函数中已包含等待时钟稳定过程）。
*/

uint8_t RCC_SysClk_Switch(uint32_t NewClk)
{	
    assert_param(IS_RCC_SYSCLKSRC(NewClk));
	
    CW_SYSCTRL->CR0 = ( (((CW_SYSCTRL->CR0 & (~ SYSCTRL_BYPASS_MASK) ) | SYSCTRL_BYPASS) & (~SYSCTRL_CR0_SYSCLK_Msk)) | (NewClk) );
    
    RCC_SystemCoreClockUpdate( RCC_Sysctrl_GetHClkFreq() );

    return ( ((CW_SYSCTRL->CR0 & SYSCTRL_CR0_SYSCLK_Msk) == NewClk) ? 0U : 1U );
}

/**
 * @brief RCC中断配置
 * 
 * @param RCC_IT ：RCC_IT_LSIRDY
 *                 RCC_IT_HEXRDY
 *                 RCC_IT_HSIRDY
 * @param NewState  :ENABLE  DISABLE
 */
void RCC_ITConfig(uint32_t RCC_IT, FunctionalState NewState)
{
    assert_param(IS_RCC_IT(RCC_IT));
    assert_param(IS_FUNCTIONAL_STATE(NewState));
   
    if (NewState != DISABLE)     //IER have KEY attribute
    {
        CW_SYSCTRL->IER = ((CW_SYSCTRL->IER & (~ SYSCTRL_BYPASS_MASK) ) | SYSCTRL_BYPASS) | RCC_IT;
    }
    else                         //IER have KEY attribute
    {
        CW_SYSCTRL->IER = ((CW_SYSCTRL->IER & (~ SYSCTRL_BYPASS_MASK) ) | SYSCTRL_BYPASS) & (~RCC_IT);
    }
}

/**
 * @brief 获取RCC指定中断状态
 * 
 * @param RCC_IT   RCC_IT_LSIRDY
 *                 RCC_IT_HEXRDY
 *                 RCC_IT_HSIRDY
 * @return ITStatus  : SET   RESET
 */
ITStatus RCC_GetITStatus(uint32_t RCC_IT)
{
    assert_param(IS_RCC_GET_IT(RCC_IT));

    return (CW_SYSCTRL->ISR & RCC_IT) ? SET : RESET;
}


/**
 * @brief 清除RCC指定中断标志
 * 
 * @param RCC_IT ：RCC_IT_LSIRDY
 *                 RCC_IT_HEXRDY
 *                 RCC_IT_HSIRDY
 */
void RCC_ClearITPendingBit(uint32_t RCC_IT)
{
    assert_param(IS_RCC_GET_IT(RCC_IT));

    CW_SYSCTRL->ICR &= (~RCC_IT);
}

/**
 * @brief 获取指定时钟源稳定标志
 * 
 * @param RCC_STABLEFLAG ：RCC_FLAG_HSISTABLE  RCC_FLAG_HEXSTABLE                         
 *                         RCC_FLAG_LSISTABLE
 * @return FlagStatus ：SET   RESET
 */
FlagStatus RCC_GetStableFlag(uint32_t RCC_STABLEFLAG)
{
    assert_param(IS_RCC_STABLEFLAG(RCC_STABLEFLAG));

    return( ((CW_SYSCTRL->ISR) & RCC_STABLEFLAG) ?  SET : RESET); 
}

/**
 * @brief  获取所有时钟源稳定标志
 * 
 * @return uint32_t ：返回ISR寄存器内容
 */
uint32_t RCC_GetAllStableFlag( void )
{
    return( CW_SYSCTRL->ISR ); 
}


/**
 * @brief AHB外设时钟设置
 * 
 * @param Periph  ：RCC_AHB_PERIPH_GPIOC
 *                  RCC_AHB_PERIPH_GPIOB   RCC_AHB_PERIPH_GPIOA
 *                  RCC_AHB_PERIPH_CRC     RCC_AHB_PERIPH_FLASH
 *                  
 * @param NewState  ENABLE  DISABLE
 */
void RCC_AHBPeriphClk_Enable(uint32_t Periph,FunctionalState NewState)
{
    assert_param(IS_RCC_AHB_PERIPH(Periph)); 

    if (NewState != DISABLE)
    {
        CW_SYSCTRL->AHBEN |= Periph;
    }
    else
    {
        CW_SYSCTRL->AHBEN &= (~Periph);
    }
}

/**
 * @brief APB外设时钟设置1
 * 
 * @param Periph   ：  RCC_APB1_PERIPH_I2C
 *                     RCC_APB1_PERIPH_UART2
 *                     RCC_APB1_PERIPH_IWDT
 *                     RCC_APB1_PERIPH_WWDT   
 *                     RCC_APB1_PERIPH_GTIM
 * @param NewState  ENABLE  DISABLE
 */
void RCC_APBPeriphClk_Enable1(uint32_t Periph,FunctionalState NewState)
{
    assert_param(IS_RCC_APB1_PERIPH(Periph)); 

    if (NewState != DISABLE)
    {
        CW_SYSCTRL->APBEN1 |= Periph;
    }
    else
    {
        CW_SYSCTRL->APBEN1 &= (~Periph);
    }
}

/**
 * @brief APB外设时钟设置2
 * 
 * @param Periph ：  RCC_APB2_PERIPH_AWT       RCC_APB2_PERIPH_BTIM                   
 *                   RCC_APB2_PERIPH_UART1     RCC_APB2_PERIPH_SPI
 *                   RCC_APB2_PERIPH_ATIM      RCC_APB2_PERIPH_VC
 *                   RCC_APB2_PERIPH_ADC
 * @param NewState :  ENABLE  DISABLE
 */
void RCC_APBPeriphClk_Enable2(uint32_t Periph,FunctionalState NewState)
{
    assert_param(IS_RCC_APB1_PERIPH(Periph)); 

    if (NewState != DISABLE)
    {
        CW_SYSCTRL->APBEN2 |= Periph;
    }
    else
    {
        CW_SYSCTRL->APBEN2 &= (~Periph);
    }
}

/**
 * @brief AHB外设复位设置
 * 
 * @param Periph  ：RCC_AHB_PERIPH_GPIOC
 *                  RCC_AHB_PERIPH_GPIOB   RCC_AHB_PERIPH_GPIOA
 *                  RCC_AHB_PERIPH_CRC     RCC_AHB_PERIPH_FLASH
 *                  
 * @param NewState  : ENABLE  DISABLE
 */
void RCC_AHBPeriphReset(uint32_t Periph,FunctionalState NewState)
{
    assert_param(IS_RCC_AHB_PERIPH(Periph)); 

    if (NewState != DISABLE)
    {
        CW_SYSCTRL->AHBRST |= Periph;
    }
    else
    {
        CW_SYSCTRL->AHBRST &= (~Periph);
    }
}

/**
 * @brief APB外设复位设置1
 * 
 * @param Periph   ：  RCC_APB1_PERIPH_I2C
 *                     RCC_APB1_PERIPH_UART2
 *                     RCC_APB1_PERIPH_IWDT
 *                     RCC_APB1_PERIPH_WWDT   
 *                     RCC_APB1_PERIPH_GTIM
 * @param NewState  : ENABLE  DISABLE
 */
void RCC_APBPeriphReset1(uint32_t Periph,FunctionalState NewState)
{
    assert_param(IS_RCC_APB1_PERIPH(Periph)); 

    if (NewState != DISABLE)
    {
        CW_SYSCTRL->APBRST1 |= Periph;
    }
    else
    {
        CW_SYSCTRL->APBRST1 &= (~Periph);
    }
}

/**
 * @brief APB外设复位设置2
 * 
 * @param Periph ：  RCC_APB2_PERIPH_AWT       RCC_APB2_PERIPH_BTIM
 *                   RCC_APB2_PERIPH_UART1     RCC_APB2_PERIPH_SPI
 *                   RCC_APB2_PERIPH_ATIM      RCC_APB2_PERIPH_VC
 *                   RCC_APB2_PERIPH_ADC
 * @param NewState : ENABLE  DISABLE
 */
void RCC_APBPeriphReset2(uint32_t Periph,FunctionalState NewState)
{
    assert_param(IS_RCC_APB1_PERIPH(Periph)); 

    if (NewState != DISABLE)
    {
        CW_SYSCTRL->APBRST2 |= Periph;
    }
    else
    {
        CW_SYSCTRL->APBRST2 &= (~Periph);
    }
}

/**
 * @brief 获取指定的系统复位标志
 * 
 * @param RCC_RSTFLAG  ：RCC_RESTFLAG_SYSRESETREQ 
 *                       RCC_RESTFLAG_LOCKUP      
 *                       RCC_RESTFLAG_RSTB        
 *                       RCC_RESTFLAG_WWDT        
 *                       RCC_RESTFLAG_IWDT        
 *                       RCC_RESTFLAG_LVD         
 *                       RCC_RESTFLAG_POR
 * @return FlagStatus  SET RESET
 */
FlagStatus RCC_GetRstFlag(uint32_t RCC_RSTFLAG)
{
    assert_param(IS_RCC_RESTFLAG(RCC_RSTFLAG));

    return( ((CW_SYSCTRL->RESETFLAG) & RCC_RSTFLAG) ?  SET : RESET); 
}

/**
 * @brief 获取复位标志寄存器内容
 * 
 * @return uint32_t 
 */
uint32_t RCC_GetAllRstFlag( void )
{
    return( CW_SYSCTRL->RESETFLAG ); 
}

/**
 * @brief 清除指定或者全部复位标志
 * 
 * @param RCC_RSTFLAG  ：RCC_RESTFLAG_SYSRESETREQ 
 *                       RCC_RESTFLAG_LOCKUP      
 *                       RCC_RESTFLAG_RSTB        
 *                       RCC_RESTFLAG_WWDT        
 *                       RCC_RESTFLAG_IWDT        
 *                       RCC_RESTFLAG_LVD         
 *                       RCC_RESTFLAG_POR
 *                       RCC_RESTFLAG_ALL 
 * @return 
 */
void RCC_ClearRstFlag(uint32_t RCC_RSTFLAG)
{
    assert_param(IS_RCC_RESTFLAG(RCC_RSTFLAG));
    CW_SYSCTRL->RESETFLAG &= (~RCC_RSTFLAG); 
}

/**
 * @brief 配置HCLK_OUT引脚输出HCLK时钟
 *  
 */
void RCC_HCLK_OUT(void)
{  //PB6
    CW_SYSCTRL->AHBEN |= SYSCTRL_AHBEN_GPIOB_Msk;
    CW_GPIOB->ANALOG_f.PIN6 = 0U;
    CW_GPIOB->DIR_f.PIN6 = 0U;
    CW_GPIOB->AFRL_f.AFR6 = 7U;
}

/**
 * @brief 配置PCLK_OUT引脚输出PCLK时钟
 * PB3
 */
void RCC_PCLK_OUT(void)
{  // PB3
    CW_SYSCTRL->AHBEN |= SYSCTRL_AHBEN_GPIOB_Msk;
    CW_GPIOB->ANALOG_f.PIN3 = 0U;
    CW_GPIOB->DIR_f.PIN3 = 0U;
    CW_GPIOB->AFRL_f.AFR3 = 3U;
}


/**
 * @brief  配置MCO_OUT引脚输出指定的时钟源及分频比
 * 
 * @param Source  ：RCC_MCO_SRC_NONE    RCC_MCO_SRC_HCLK
 *                  RCC_MCO_SRC_PCLK    RCC_MCO_SRC_HSIOSC
 *                  RCC_MCO_SRC_LSI     RCC_MCO_SRC_HEX                 
 *                  RCC_MCO_SRC_RC150K  RCC_MCO_SRC_RC10K
 * @param Div     ：RCC_MCO_DIV1/2/8/64/128/256/512/1024
 */
void RCC_MCO_OUT(uint8_t Source, uint8_t Div)
{  //PA1
    assert_param(IS_RCC_MCO_SRC(Source));
    assert_param(IS_RCC_MCO_DIV(Div));

    CW_SYSCTRL->AHBEN |= SYSCTRL_AHBEN_GPIOA_Msk; //Open GPIOA clk

    CW_GPIOA->ANALOG_f.PIN1  = 0U;  //Digit
    CW_GPIOA->AFRL_f.AFR1 = 7U;
    CW_GPIOA->DIR_f.PIN1 = 0U;      //Output
    CW_SYSCTRL->MCO    = (uint32_t)(Source | Div);
}

/**
 * @brief 配置在debug模式下计数器的工作模式
 * 
 * @param Periph      RCC_DEBUG_WWDT 
 *                    RCC_DEBUG_IWDT 
 *                    RCC_DEBUG_AWT 
 *                    RCC_DEBUG_BTIM123 
 *                    RCC_DEBUG_GTIM
 *                    RCC_DEBUG_ATIM 
 * 
 */
void RCC_DEBUG_Config(uint32_t Periph, FunctionalState NewState)
{
    assert_param(IS_RCC_DEBUG(Periph));
    NewState ? (CW_SYSCTRL->DEBUG |= Periph) : (CW_SYSCTRL->DEBUG &= (~Periph));
}

/**
 * @brief 配置BTIM3的ITR来源
 * 
 * @param Source RCC_TIMITR_BTIM1 RCC_TIMITR_BTIM2
 *               RCC_TIMITR_GTIM
 *               RCC_TIMITR_ATIM
 */
void RCC_BTIM3ITRSelect(uint32_t Source)
{
    assert_param(IS_RCC_TIMITR_SOURCE(Source));

    CW_SYSCTRL->TIMITR_f.BTIM3ITR = Source;
}

/**
 * @brief 配置BTIM2的ITR来源
 * 
 * @param Source RCC_TIMITR_BTIM1 RCC_TIMITR_BTIM3
 *               RCC_TIMITR_GTIM
 *               RCC_TIMITR_ATIM
 */
void RCC_BTIM2ITRSelect(uint32_t Source)
{
    assert_param(IS_RCC_TIMITR_SOURCE(Source));

    CW_SYSCTRL->TIMITR_f.BTIM2ITR = Source;
}

/**
 * @brief 配置BTIM1的ITR来源
 * 
 * @param Source RCC_TIMITR_BTIM2 RCC_TIMITR_BTIM3
 *               RCC_TIMITR_GTIM
 *               RCC_TIMITR_ATIM
 */
void RCC_BTIM1ITRSelect(uint32_t Source)
{
    assert_param(IS_RCC_TIMITR_SOURCE(Source));

    CW_SYSCTRL->TIMITR_f.BTIM1ITR = Source;
}

/**
 * @brief 配置GTIM的ITR来源
 * 
 * @param Source RCC_TIMITR_BTIM1 RCC_TIMITR_BTIM2 RCC_TIMITR_BTIM3                
 *               RCC_TIMITR_ATIM
 */
void RCC_GTIMITRSelect(uint32_t Source)
{
    assert_param(IS_RCC_TIMITR_SOURCE(Source));

    CW_SYSCTRL->TIMITR_f.GTIMITR = Source;
}

/**
 * @brief 配置ATIM的ITR来源
 * 
 * @param Source RCC_TIMITR_BTIM1 RCC_TIMITR_BTIM2 RCC_TIMITR_BTIM3
 *               RCC_TIMITR_GTIM
 *               
 */
void RCC_ATIMITRSelect(uint32_t Source)
{
    assert_param(IS_RCC_TIMITR_SOURCE(Source));

    CW_SYSCTRL->TIMITR_f.ATIMITR = Source;
}
