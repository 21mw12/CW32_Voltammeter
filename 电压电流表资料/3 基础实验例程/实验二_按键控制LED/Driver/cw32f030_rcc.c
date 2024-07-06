/**
 * @file cw32f030_rcc.c
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
#include "cw32f030_rcc.h"

/* Private_TypesDefinitions --------------------------------------------------*/
const uint32_t hsiprs_tbl[] = {6,6,6,6,6,6,1,3,2,4,6,8,10,12,14,16};

/* Private_Defines -----------------------------------------------------------*/

/* Private_Variables ---------------------------------------------------------*/

/* Private_FunctionPrototypes ------------------------------------------------*/

/* Private_Functions ---------------------------------------------------------*/

/* Public_Functions ----------------------------------------------------------*/

/**
 * @brief ����SysClk �� HCLK�ķ�Ƶϵ��
 * 
 * @param HCLKPRS ��RCC_HCLK_DIV1/2/4/8/16/32/64/128
 */
void RCC_HCLKPRS_Config(uint32_t HCLKPRS)
{
    assert_param(IS_RCC_HCLKPRS(HCLKPRS));
    CW_SYSCTRL->CR0 = ( (CW_SYSCTRL->CR0 & (~ (SYSCTRL_BYPASS_MASK | SYSCTRL_CR0_HCLKPRS_Msk))) | SYSCTRL_BYPASS | HCLKPRS );
}
/**
 * @brief ����HCLK �� PCLK�ķ�Ƶϵ��
 * 
 * @param PCLKPRS ��RCC_PCLK_DIV1/2/4/8
 */
void RCC_PCLKPRS_Config(uint32_t PCLKPRS)
{
    assert_param(IS_RCC_HCLKPRS(PCLKPRS));
    CW_SYSCTRL->CR0 = ( (CW_SYSCTRL->CR0 & (~ (SYSCTRL_BYPASS_MASK | SYSCTRL_CR0_PCLKPRS_Msk))) | SYSCTRL_BYPASS | PCLKPRS );
}

/**
 * @brief ����SysClk��ʱ��Դ
 * 
 * @param SYSCLKSRC ��RCC_SYSCLKSRC_HSI RCC_SYSCLKSRC_HSE  RCC_SYSCLKSRC_PLL
 *                    RCC_SYSCLKSRC_LSI RCC_SYSCLKSRC_LSE
 */
void RCC_SYSCLKSRC_Config(uint32_t SYSCLKSRC)
{
    assert_param(IS_RCC_SYSCLKSRC(SYSCLKSRC));
    CW_SYSCTRL->CR0 = ( (CW_SYSCTRL->CR0 & (~ (SYSCTRL_BYPASS_MASK | SYSCTRL_CR0_SYSCLK_Msk))) | SYSCTRL_BYPASS | SYSCLKSRC );
    RCC_SystemCoreClockUpdate( RCC_Sysctrl_GetHClkFreq() );
}

/**
 * @brief ����CLKCCS  HSECCS  LSECCS ����
 * 
 * @param CCS  ��RCC_SYSCTRL_LSECCS  RCC_SYSCTRL_HSECCS  RCC_SYSCTRL_CLKCCS
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
 * @brief ����LSELOCK���ܣ�ʹ�ܺ�����޷��ر�LSEʱ��
 * 
 * @param LSELOCK �� RCC_SYSCTRL_LSELOCKEN  RCC_SYSCTRL_LSELOCKDIS
 */
void RCC_LSELOCK_Config(uint32_t LSELOCK)
{
    assert_param(IS_RCC_LSELOCK_STATUS(LSELOCK));
    CW_SYSCTRL->CR1 = ( (CW_SYSCTRL->CR1 & (~ SYSCTRL_BYPASS_MASK) ) | SYSCTRL_BYPASS | LSELOCK );
}

/**
 * @brief ����WAKEUPCLK����:�������������ģʽ���Ѻ���ʹ�õ�ϵͳʱ��Դ
 * 
 * @param WAKEUPCLK ��RCC_SYSCTRL_WAKEUPCLKEN   RCC_SYSCTRL_WAKEUPCLKDIS
 */
void RCC_WAKEUPCLK_Config(uint32_t WAKEUPCLK)
{
    assert_param(IS_RCC_WAKEUPCLK_STATUS(WAKEUPCLK));
    CW_SYSCTRL->CR2 = ( (CW_SYSCTRL->CR2 & (~ ( SYSCTRL_BYPASS_MASK | SYSCTRL_CR2_WAKEUPCLK_Msk ) ) ) | SYSCTRL_BYPASS | WAKEUPCLK );
}

/**
 * @brief ����LOCK���ܣ������쳣���Ϻ��Ƿ����LOCKUP��λ
 * 
 * @param LOCKUP ��RCC_SYSCTRL_LOCKUPEN  RCC_SYSCTRL_LOCKUPDIS
 */
void RCC_LOCKUP_Config(uint32_t LOCKUP)
{
    assert_param(IS_RCC_LOCKUP_STATUS(LOCKUP));
    CW_SYSCTRL->CR2 = ( (CW_SYSCTRL->CR2 & (~ ( SYSCTRL_BYPASS_MASK | SYSCTRL_CR2_LOCKUP_Msk ) ) ) | SYSCTRL_BYPASS | LOCKUP );
}

/**
 * @brief ���ö˿�SWDIO����
 * 
 * @param SWDIO  ��RCC_SYSCTRL_SWDIOEN   RCC_SYSCTRL_SWDIODIS
 */
void RCC_SWDIO_Config(uint32_t SWDIO)
{
    assert_param(IS_RCC_SWDIO_STATUS(SWDIO));
    CW_SYSCTRL->CR2 = ( (CW_SYSCTRL->CR2 & (~ ( SYSCTRL_BYPASS_MASK | SYSCTRL_CR2_SWDIO_Msk ) ) ) | SYSCTRL_BYPASS | SWDIO );
}

/**
  * @brief  Resets the RCC clock configuration to the default reset state.
  * @param  None
  * @retval None
  * CAUTION:
  * 1��LSEEN Bit Not Changed ,so it will not affect RTC,BUT LSELOCK BIT Changed.
  * 2��Before CALL this funciton,we should set FLASH_CR2.WAIT 
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

  /* CLKCCS/HSECCS/LSECCS/LSELOCK/LSIEN/PLLEN/HSEEN Disable   CLKCCS / LSEEN NO CHANGE*/
  CW_SYSCTRL->CR1 = ( ((CW_SYSCTRL->CR1 & (~ SYSCTRL_BYPASS_MASK) ) | SYSCTRL_BYPASS | RCC_SYSCTRL_HSIEN) \
                        & (~ RCC_SYSCTRL_CLKCCS)  & (~ RCC_SYSCTRL_HSECCS)  & (~ RCC_SYSCTRL_LSECCS) \
                        & (~ RCC_SYSCTRL_LSELOCKEN) & (~ RCC_SYSCTRL_LSIEN) & (~ RCC_SYSCTRL_PLLEN) \
                        & (~ RCC_SYSCTRL_HSEEN) ); 

  /* SWDIO Enable,LOCKUP/WAKEUPCLK Disable*/
  CW_SYSCTRL->CR2 = ( ( ( ( (CW_SYSCTRL->CR2 & (~ SYSCTRL_BYPASS_MASK) ) | SYSCTRL_BYPASS ) \
                    & (~ RCC_SYSCTRL_SWDIOEN) )  & (~ RCC_SYSCTRL_LOCKUPEN) )  & (~ RCC_SYSCTRL_WAKEUPCLKEN)  ); 

  /* Disable all interrupts */
  CW_SYSCTRL->IER = 0x5A5AFE00;      //IER have KEY attribute

  /* Clear all pending bits  */
  CW_SYSCTRL->ICR &= 0xFFFFFE00;

  //����ʱ�Ӻ͸�λ�Ĵ������� ??

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
 * @brief ���ϵͳʱ�ӣ�HCLK��Ƶ��ֵ
 * 
 * @return uint32_t   HCLKƵ��ֵ(Hz)
 */
uint32_t RCC_Sysctrl_GetHClkFreq(void)
{
    uint32_t u32rtnVal = 0;
    uint32_t sysclksource = 0;
    uint32_t hsiprs = 0;
    uint32_t pllmul = 0;
    uint32_t pllrefclk = 0;

    sysclksource = CW_SYSCTRL->CR0_f.SYSCLK;
    hsiprs = CW_SYSCTRL->HSI_f.DIV;
    pllrefclk = CW_SYSCTRL->PLL_f.SOURCE;
    pllmul = CW_SYSCTRL->PLL_f.MUL;

    switch (sysclksource)
    {
        case 0x00:  /* HSI used as system clock */
            u32rtnVal = ( HSIOSC_VALUE / hsiprs_tbl[hsiprs] );
        break;
        case 0x01:  /* HSE used as system clock */
            u32rtnVal = HSE_VALUE;
        break;
        case 0x03:  /* LSI used as system clock */
            u32rtnVal = LSI_VALUE;
        break;
        case 0x04:  /* LSE used as system clock */
            u32rtnVal = LSE_VALUE;
        break;
        case 0x02:  /* PLL used as system clock */
            switch (pllrefclk)
            {  
                case 0x00:  /* HSEOSC used as pll refclk */
                case 0x01:  /* HSEIN used as pll refclk */
                    u32rtnVal =  ( HSE_VALUE * pllmul ) ;
                break;  
                case 0x03:  /* HSI used as pll refclk */
                    u32rtnVal =  ( ( HSIOSC_VALUE / hsiprs_tbl[hsiprs] ) * pllmul ) ;
                break;
                default:
                    u32rtnVal =  ( ( HSIOSC_VALUE / hsiprs_tbl[hsiprs] ) * pllmul ) ;
                break;  
            }
        break;
        default:
            u32rtnVal = ( HSIOSC_VALUE / hsiprs_tbl[hsiprs] ) ;
        break;
    }
    u32rtnVal = ( u32rtnVal >> CW_SYSCTRL->CR0_f.HCLKPRS ) ;
    return u32rtnVal;
}

/**
 * @brief �������ʱ�ӣ�PCLK��Ƶ��ֵ
 * 
 * @return uint32_t    PCLKƵ��ֵ(Hz)
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

    //CW_SYSCTRL->HSI_f.DIV = HSIDiv;
    CW_SYSCTRL->HSI  = ( HSIDiv << SYSCTRL_HSI_DIV_Pos ) | ( *((volatile uint16_t *)RCC_HSI_TRIMCODEADDR) ) ;        //��ʽ��оƬ����Ҫ����Trimֵ
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
	CW_SYSCTRL->LSI  = *((uint16_t *)RCC_LSI_TRIMCODEADDR);                       //��ʽ��оƬ����Ҫ����Trimֵ
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
* @brief  Enable HSE
* @param  Mode:   RCC_HSE_MODE_OSC: Oscillator, 
*                 RCC_HSE_MODE_CLK: Input Clk
*
* @param  FreqIn: 4000000Hz ~ 32000000Hz
*
* @param  Driver: RCC_HSE_DRIVER_LEAST,
*                 RCC_HSE_DRIVER_SMALL,
*                 RCC_HSE_DRIVER_NORMAL, (default)
*                 RCC_HSE_DRIVER_LARGER
*
* @param  Flt: RCC_HSE_FLT_OPEN,    
*              RCC_HSE_FLT_CLOSE
*
* @retval None

16M�������ý��飺
Range:  ��������Ϊ2
Driver����������Ϊ1����2

24M�������ý��飺
Range:  ��������Ϊ3
Driver����������Ϊ1

32M�������ý��飺
Range:  ��������Ϊ3
Driver����������Ϊ2

ע�⣺1��ѡ���ص���С�ľ������������
2��Flt: ǿ���Ż�����,һ�㲻��
*/
void RCC_HSE_Enable(uint32_t Mode, uint32_t FreqIn, uint8_t Driver,uint32_t Flt)
{
    uint8_t freqRange = 0;

    //��������
    assert_param(IS_RCC_HSE_MODE(Mode));
    assert_param(IS_RCC_HSE_FREQIN(FreqIn));  //FPGA����ע�͵�����ʽ���
    assert_param(IS_RCC_HSE_DRIVER(Driver));
    assert_param(IS_RCC_HSE_FLT(Flt));
    
    //����HSEģʽ����IO�ڹ���
    CW_SYSCTRL->AHBEN |= SYSCTRL_AHBEN_GPIOF_Msk; //Open GPIOF Clk
    if( Mode == RCC_HSE_MODE_OSC )                //Oscillator 
    {
        CW_GPIOF->ANALOG |= ( bv0 | bv1 );        //PF00 PF01 as analog pin
    }
    else                                          //Input clk
    {
        CW_GPIOF->ANALOG &= ~bv0;                 //PF00 as input clk pin
        CW_GPIOF->DIR    |=  bv0;                 //PF00 input
        CW_GPIOF->PUR    &= ~bv0;
        CW_GPIOF->PDR    |=  bv0;
    }

    //��������Ƶ�ʲ����õ���Ӧ����ֵ
    freqRange = ( FreqIn == 32000000 ) ? 0x3UL : ( FreqIn / 8000000 );

    //����HSE����
    CW_SYSCTRL->HSE = (( 8000000000/FreqIn ) << 8 )                     | \
		              ( Mode                                            | \
                      ( RCC_HSE_WAITCYCLE_131072 )                      | \
                      ( ((uint32_t)freqRange << SYSCTRL_HSE_FREQ_Pos) ) | \
                      ( Driver ) |\
                      ( Flt ) );

    //ʹ��HSE,ͬʱʹ��CLKCCS��HSECCS��ʹ��ʱ��ʧЧ�л�
    CW_SYSCTRL->CR1 |= SYSCTRL_BYPASS | RCC_SYSCTRL_CLKCCS | SYSCTRL_CR1_HSECCS_Msk | SYSCTRL_CR1_HSEEN_Msk;  //Enable HSE
		
    //�ȴ�HSE�ȶ�
    while( (CW_SYSCTRL->HSE & SYSCTRL_HSE_STABLE_Msk) != SYSCTRL_HSE_STABLE_Msk )        //Wait stable
    {
        ;
    }
}

/**
* @brief  Disable HSE
* @param  None.
* @retval None.
*/
void RCC_HSE_Disable(void)
{
    CW_SYSCTRL->CR1 = ( ( (CW_SYSCTRL->CR1 & (~ SYSCTRL_BYPASS_MASK) ) | SYSCTRL_BYPASS ) & \
                      (~SYSCTRL_CR1_HSEEN_Msk) );
}

/**
* @brief  Enable LSE
* @param  Mode:   RCC_LSE_MODE_OSC: Oscillator, 
*                 RCC_LSE_MODE_CLK: Input Clk
* @param  Amp:    RCC_LSE_AMP_LEAST, RCC_LSE_AMP_SMALL
*                 RCC_LSE_AMP_NORMAL��RCC_LSE_AMP_LARGER
* @param  Driver: RCC_LSE_DRIVER_LEAST, RCC_LSE_DRIVER_SMALL
*                 RCC_LSE_DRIVER_NORMAL��RCC_LSE_DRIVER_LARGER
*
* @retval None

�������ý��飺
AMP:    ��������Ϊ2��RCC_LSE_AMP_NORMAL����3��RCC_LSE_AMP_LARGER��
Driver����������Ϊ3��RCC_LSE_DRIVER_LARGER��
*/   
void RCC_LSE_Enable(uint32_t Mode,uint8_t Amp,uint8_t Driver)
{
    //��������
    assert_param(IS_RCC_LSE_MODE(Mode));
    assert_param(IS_RCC_LSE_AMP(Amp));
    assert_param(IS_RCC_LSE_DRIVER(Driver));

    //����LSEģʽ������IO����
    CW_SYSCTRL->AHBEN |= SYSCTRL_AHBEN_GPIOC_Msk; //Open GPIOC clk
    if( Mode == RCC_LSE_MODE_OSC )                //Oscillator 
    {
        CW_GPIOC->ANALOG |= ( bv13 | bv14 );      //PC13 PC14 as analog pin
    }
    else                                          //Input clk
    {
        CW_GPIOC->ANALOG &= ~bv14;                //PC14 as input clk pin
        CW_GPIOC->DIR    |=  bv14;                //PC14 input
        CW_GPIOC->PUR    &=  bv14;
        CW_GPIOC->PDR    |=  bv14;
    }

   //����LSE����
    CW_SYSCTRL->LSE = ((Mode)                    | \
                       (RCC_LSE_WAITCYCLE_16384) | \
                       (Amp)                     | \
                       (Driver));

    //LSEʹ��,ͬʱʹ��CLKCCS��LSECCS��ʹ��ʱ��ʧЧ�л�
    CW_SYSCTRL->CR1 |= SYSCTRL_BYPASS | RCC_SYSCTRL_CLKCCS | SYSCTRL_CR1_LSECCS_Msk | SYSCTRL_CR1_LSEEN_Msk;                    //Enable LSE
    
    //�ȴ�LSE�ȶ�
    while( (CW_SYSCTRL->LSE & SYSCTRL_LSE_STABLE_Msk) != SYSCTRL_LSE_STABLE_Msk ) //Wait stable
    {
        ;
    }
}

/**
* @brief  Disable LSE
* @param  None
* @retval None
*/
void RCC_LSE_Disable(void)
{
    CW_SYSCTRL->CR1 = ( ( (CW_SYSCTRL->CR1 & (~ SYSCTRL_BYPASS_MASK) ) | SYSCTRL_BYPASS ) & \
                      (~SYSCTRL_CR1_LSEEN_Msk) );
}

/**
* @brief  Enable PLL
* @param  PLLSource:    
                     RCC_PLLSOURCE_HSEOSC,
                     RCC_PLLSOURCE_HSECLK,
                     RCC_PLLSOURCE_HSI
* @param  FreqIn:    4000000Hz ~ 24000000Hz
* @param  PLLMul:    2~12
* @retval  None
*/
void RCC_PLL_Enable(uint32_t PLLSource, uint32_t FreqIn, uint32_t PLLMul)
{
    uint8_t  i = 0;
    uint32_t freqInMsk = 0;
    uint32_t freqOutMsk = 0;
    uint32_t freqInTable[4]  = { 6000000 , 12000000, 20000000, 24000001 };
    //uint32_t freqInTable[4]  = { 6000000 , 12000000, 20000000, 32000001 }; //FPGA���Դ�
    uint32_t freqOutTable[5] = { 18000000, 24000000, 36000000, 48000000, 72000001 };

    //��������
    assert_param(IS_RCC_PLLSOURCE(PLLSource));
    assert_param(IS_RCC_PLL_FREQIN(FreqIn));  //FPGA����ע�͵�����ʽ���
    assert_param(IS_RCC_PLL_MUL(PLLMul));

    //����FREQIN����ֵ
    for( i = 0; i < (sizeof(freqInTable)/sizeof(freqInTable[0])); i++ )
    {
        if( FreqIn < freqInTable[i] )
        {
            freqInMsk = i;
            break;
        }
    }

    ////����FREQOUT����ֵ
    freqOutMsk = FreqIn * PLLMul;
    for( i = 0; i < (sizeof(freqOutTable)/sizeof(freqOutTable[0])); i++ )
    {
        if( freqOutMsk < freqOutTable[i] )
        {
             freqOutMsk = i;
             break;
        }
    }

    //����PLL����
    CW_SYSCTRL->PLL = ( RCC_PLL_WAITCYCLE_16384                                | \
                      ((uint32_t)( freqOutMsk << SYSCTRL_PLL_FREQOUT_Pos   ))  | \
                      ((uint32_t)( PLLMul     << SYSCTRL_PLL_MUL_Pos       ))  | \
                      ((uint32_t)( freqInMsk  << SYSCTRL_PLL_FREQIN_Pos    ))  | \
                      ((uint32_t)( PLLSource  << SYSCTRL_PLL_SOURCE_Pos    )));

    //ʹ��PLL
    CW_SYSCTRL->CR1 |= SYSCTRL_BYPASS | SYSCTRL_CR1_PLLEN_Msk;     //Enable PLL

    //�ȴ�PLLʱ���ȶ�
    while( (CW_SYSCTRL->PLL & SYSCTRL_PLL_STABLE_Msk) != SYSCTRL_PLL_STABLE_Msk )
    {
        ;
    }
}

/**
* @brief  Disable PLL
* @param  None
* @retval None
*/
void RCC_PLL_Disable(void)
{
    CW_SYSCTRL->CR1 = ( ( (CW_SYSCTRL->CR1  & (~ SYSCTRL_BYPASS_MASK) ) | SYSCTRL_BYPASS ) & \
                      (~SYSCTRL_CR1_PLLEN_Msk) );
}

/**
* @brief  CLKSRC switch
* @param  NewClk:
*                RCC_SYSCLKSRC_HSI,
*                RCC_SYSCLKSRC_HSE,
*                RCC_SYSCLKSRC_PLL,
*                RCC_SYSCLKSRC_LSI,
*                RCC_SYSCLKSRC_LSE
* @retval 0: PASS, 1: Fail
*
* NOTE:���ô˺���֮ǰ��Ҫ��֤��ʱ��Դ�Ѿ�ʹ�ܣ�ENABLE�������Ѱ����ȴ�ʱ���ȶ����̣���
*/

uint8_t RCC_SysClk_Switch(uint32_t NewClk)
{	
    assert_param(IS_RCC_SYSCLKSRC(NewClk));
	
    CW_SYSCTRL->CR0 = ( (((CW_SYSCTRL->CR0 & (~ SYSCTRL_BYPASS_MASK) ) | SYSCTRL_BYPASS) & (~SYSCTRL_CR0_SYSCLK_Msk)) | (NewClk) );
    
    RCC_SystemCoreClockUpdate( RCC_Sysctrl_GetHClkFreq() );

    return ( ((CW_SYSCTRL->CR0 & SYSCTRL_CR0_SYSCLK_Msk) == NewClk) ? 0U : 1U );
}

/**
 * @brief RCC�ж�����
 * 
 * @param RCC_IT ��RCC_IT_HSEFAULT   RCC_IT_LSEFAULT
 *                 RCC_IT_HSEFAIL    RCC_IT_LSEFAIL
 *                 RCC_IT_LSERDY     RCC_IT_LSIRDY
 *                 RCC_IT_PLLRDY     RCC_IT_HSERDY
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
 * @brief ��ȡRCCָ���ж�״̬
 * 
 * @param RCC_IT ��RCC_IT_HSEFAULT   RCC_IT_LSEFAULT
 *                 RCC_IT_HSEFAIL    RCC_IT_LSEFAIL
 *                 RCC_IT_LSERDY     RCC_IT_LSIRDY
 *                 RCC_IT_PLLRDY     RCC_IT_HSERDY
 *                 RCC_IT_HSIRDY
 * @return ITStatus  : SET   RESET
 */
ITStatus RCC_GetITStatus(uint32_t RCC_IT)
{
    assert_param(IS_RCC_GET_IT(RCC_IT));

    return (CW_SYSCTRL->ISR & RCC_IT) ? SET : RESET;
}


/**
 * @brief ���RCCָ���жϱ�־
 * 
 * @param RCC_IT ��RCC_IT_HSEFAULT   RCC_IT_LSEFAULT
 *                 RCC_IT_HSEFAIL    RCC_IT_LSEFAIL
 *                 RCC_IT_LSERDY     RCC_IT_LSIRDY
 *                 RCC_IT_PLLRDY     RCC_IT_HSERDY
 *                 RCC_IT_HSIRDY
 */
void RCC_ClearITPendingBit(uint32_t RCC_IT)
{
    assert_param(IS_RCC_GET_IT(RCC_IT));

    CW_SYSCTRL->ICR &= (~RCC_IT);
}

/**
 * @brief ��ȡָ��ʱ��Դ�ȶ���־
 * 
 * @param RCC_STABLEFLAG ��RCC_FLAG_HSISTABLE  RCC_FLAG_HSESTABLE
 *                         RCC_FLAG_PLLSTABLE  RCC_FLAG_LSESTABLE
 *                         RCC_FLAG_LSISTABLE
 * @return FlagStatus ��SET   RESET
 */
FlagStatus RCC_GetStableFlag(uint32_t RCC_STABLEFLAG)
{
    assert_param(IS_RCC_STABLEFLAG(RCC_STABLEFLAG));

    return( ((CW_SYSCTRL->ISR) & RCC_STABLEFLAG) ?  SET : RESET); 
}

/**
 * @brief  ��ȡ����ʱ��Դ�ȶ���־
 * 
 * @return uint32_t ������ISR�Ĵ�������
 */
uint32_t RCC_GetAllStableFlag( void )
{
    return( CW_SYSCTRL->ISR ); 
}


/**
 * @brief AHB����ʱ������
 * 
 * @param Periph  ��RCC_AHB_PERIPH_GPIOF   RCC_AHB_PERIPH_GPIOC
 *                  RCC_AHB_PERIPH_GPIOB   RCC_AHB_PERIPH_GPIOA
 *                  RCC_AHB_PERIPH_CRC     RCC_AHB_PERIPH_FLASH
 *                  RCC_AHB_PERIPH_DMA
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
 * @brief APB����ʱ������1
 * 
 * @param Periph   ��  RCC_APB1_PERIPH_I2C2   RCC_APB1_PERIPH_I2C1
 *                     RCC_APB1_PERIPH_UART3  RCC_APB1_PERIPH_UART2
 *                     RCC_APB1_PERIPH_SPI2   RCC_APB1_PERIPH_IWDT
 *                     RCC_APB1_PERIPH_WWDT   RCC_APB1_PERIPH_RTC
 *                     RCC_APB1_PERIPH_GTIM2  RCC_APB1_PERIPH_GTIM1
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
 * @brief APB����ʱ������2
 * 
 * @param Periph ��  RCC_APB2_PERIPH_AWT       RCC_APB2_PERIPH_BTIM
 *                   RCC_APB2_PERIPH_GTIM4     RCC_APB2_PERIPH_GTIM3
 *                   RCC_APB2_PERIPH_UART1     RCC_APB2_PERIPH_SPI1
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
 * @brief AHB���踴λ����
 * 
 * @param Periph  ��RCC_AHB_PERIPH_GPIOF   RCC_AHB_PERIPH_GPIOC
 *                  RCC_AHB_PERIPH_GPIOB   RCC_AHB_PERIPH_GPIOA
 *                  RCC_AHB_PERIPH_CRC     RCC_AHB_PERIPH_FLASH
 *                  RCC_AHB_PERIPH_DMA
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
 * @brief APB���踴λ����1
 * 
 * @param Periph   ��  RCC_APB1_PERIPH_I2C2   RCC_APB1_PERIPH_I2C1
 *                     RCC_APB1_PERIPH_UART3  RCC_APB1_PERIPH_UART2
 *                     RCC_APB1_PERIPH_SPI2   RCC_APB1_PERIPH_IWDT
 *                     RCC_APB1_PERIPH_WWDT   RCC_APB1_PERIPH_RTC
 *                     RCC_APB1_PERIPH_GTIM2  RCC_APB1_PERIPH_GTIM1
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
 * @brief APB���踴λ����2
 * 
 * @param Periph ��  RCC_APB2_PERIPH_AWT       RCC_APB2_PERIPH_BTIM
 *                   RCC_APB2_PERIPH_GTIM4     RCC_APB2_PERIPH_GTIM3
 *                   RCC_APB2_PERIPH_UART1     RCC_APB2_PERIPH_SPI1
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
 * @brief ��ȡָ����ϵͳ��λ��־
 * 
 * @param RCC_RSTFLAG  ��RCC_FLAG_PINRST   RCC_FLAG_PORRST
 *                       RCC_FLAG_LVDRST   RCC_FLAG_LOCKUPRST
 *                       RCC_FLAG_IWDTRST  RCC_FLAG_WWDTRST
 *                       RCC_FLAG_SYSRESETREQRST
 * @return FlagStatus  SET RESET
 */
FlagStatus RCC_GetRstFlag(uint32_t RCC_RSTFLAG)
{
    assert_param(IS_RCC_RSTFLAG(RCC_RSTFLAG));

    return( ((CW_SYSCTRL->RESETFLAG) & RCC_RSTFLAG) ?  SET : RESET); 
}

/**
 * @brief ��ȡ��λ��־�Ĵ�������
 * 
 * @return uint32_t 
 */
uint32_t RCC_GetAllRstFlag( void )
{
    return( CW_SYSCTRL->RESETFLAG ); 
}

/**
 * @brief ���ָ������ȫ����λ��־
 * 
 * @param RCC_RSTFLAG  ��RCC_FLAG_PINRST   RCC_FLAG_PORRST
 *                       RCC_FLAG_LVDRST   RCC_FLAG_LOCKUPRST
 *                       RCC_FLAG_IWDTRST  RCC_FLAG_WWDTRST
 *                       RCC_FLAG_SYSRESETREQRST  RCC_FLAG_ALLRST
 * @return 
 */
void RCC_ClearRstFlag(uint32_t RCC_RSTFLAG)
{
    assert_param(IS_RCC_RSTFLAG(RCC_RSTFLAG));
    CW_SYSCTRL->RESETFLAG &= (~RCC_RSTFLAG); 
}

/**
 * @brief ����HCLK_OUT�������HCLKʱ��
 * 
 */
void RCC_HCLK_OUT(void)
{
    CW_SYSCTRL->AHBEN |= SYSCTRL_AHBEN_GPIOA_Msk;
    CW_GPIOA->ANALOG_f.PIN4 = 0U;
    CW_GPIOA->DIR_f.PIN4 = 0U;
    CW_GPIOA->AFRL_f.AFR4 = 4U;
}

/**
 * @brief ����PCLK_OUT�������PCLKʱ��
 * 
 */
void RCC_PCLK_OUT(void)
{
    CW_SYSCTRL->AHBEN |= SYSCTRL_AHBEN_GPIOA_Msk;
    CW_GPIOA->ANALOG_f.PIN3 = 0U;
    CW_GPIOA->DIR_f.PIN3 = 0U;
    CW_GPIOA->AFRL_f.AFR3 = 4U;
}

/**
 * @brief ����HSE_OUT�������HSEʱ��
 * 
 */
void RCC_HSE_OUT(void)
{
    CW_SYSCTRL->AHBEN |= SYSCTRL_AHBEN_GPIOB_Msk;
    CW_GPIOB->ANALOG_f.PIN2 = 0U;
    CW_GPIOB->DIR_f.PIN2 = 0U;
    CW_GPIOB->AFRL_f.AFR2 = 3U;
}

/**
 * @brief ����HSI_OUT�������HSIOSCʱ��
 * 
 */
void RCC_HSI_OUT(void)
{
    CW_SYSCTRL->AHBEN |= SYSCTRL_AHBEN_GPIOB_Msk;
    CW_GPIOB->ANALOG_f.PIN0 = 0U;
    CW_GPIOB->DIR_f.PIN0 = 0U;
    CW_GPIOB->AFRL_f.AFR0 = 5U;
}

/**
 * @brief ����LSE_OUT�������LSEʱ��
 * 
 */
void RCC_LSE_OUT(void)
{
    CW_SYSCTRL->AHBEN |= SYSCTRL_AHBEN_GPIOB_Msk;
    CW_GPIOB->ANALOG_f.PIN12 = 0U;
    CW_GPIOB->DIR_f.PIN12 = 0U;
    CW_GPIOB->AFRH_f.AFR12 = 3U;
}

/**
 * @brief ����LSI_OUT�������LSIʱ��
 * 
 */
void RCC_LSI_OUT(void)
{
    CW_SYSCTRL->AHBEN |= SYSCTRL_AHBEN_GPIOB_Msk;
    CW_GPIOB->ANALOG_f.PIN11 = 0U;
    CW_GPIOB->DIR_f.PIN11 = 0U;
    CW_GPIOB->AFRH_f.AFR11 = 1U;
}
/**
 * @brief ����PLL_OUT�������PLLʱ��
 * 
 */
void RCC_PLL_OUT(void)
{
    CW_SYSCTRL->AHBEN |= SYSCTRL_AHBEN_GPIOC_Msk;
    CW_GPIOC->ANALOG_f.PIN13 = 0U;
    CW_GPIOC->DIR_f.PIN13 = 0U;
    CW_GPIOC->AFRH_f.AFR13 = 1U;
}

/**
 * @brief  ����MCO_OUT�������ָ����ʱ��Դ����Ƶ��
 * 
 * @param Source  ��RCC_MCO_SRC_NONE    RCC_MCO_SRC_HCLK
 *                  RCC_MCO_SRC_PCLK    RCC_MCO_SRC_HSI
 *                  RCC_MCO_SRC_LSI     RCC_MCO_SRC_HSE
 *                  RCC_MCO_SRC_LSE     RCC_MCO_SRC_PLL
 *                  RCC_MCO_SRC_RC150K  RCC_MCO_SRC_RC10K
 * @param Div     ��RCC_MCO_DIV1/2/8/64/128/256/512/1024
 */
void RCC_MCO_OUT(uint8_t Source, uint8_t Div)
{
    assert_param(IS_RCC_MCO_SRC(Source));
    assert_param(IS_RCC_MCO_DIV(Div));

    CW_SYSCTRL->AHBEN |= SYSCTRL_AHBEN_GPIOA_Msk; //Open GPIOA clk

    CW_GPIOA->ANALOG  &= ~GPIOx_ANALOG_PIN8_Msk;  //Digit
    CW_GPIOA->AFRH     = ((CW_GPIOA->AFRH) & (~(uint32_t)(GPIOx_AFRH_AFR8_Msk))) | (uint32_t)(0x4U << GPIOx_AFRH_AFR8_Pos);
    CW_GPIOA->DIR     &= ~GPIOx_DIR_PIN8_Msk;     //Output

    CW_SYSCTRL->MCO    = (uint32_t)(Source | Div);
}

/**
 * @brief ����BTIM3��ITR��Դ
 * 
 * @param Source RCC_TIMITR_BTIM1 RCC_TIMITR_BTIM2
 *               RCC_TIMITR_GTIM1 RCC_TIMITR_GTIM2 RCC_TIMITR_GTIM3 RCC_TIMITR_GTIM4
 *               RCC_TIMITR_ATIM
 */
void RCC_BTIM3ITRSelect(uint32_t Source)
{
    assert_param(IS_RCC_TIMITR_SOURCE(Source));

    CW_SYSCTRL->TIMITR_f.BTIM3ITR = Source;
}

/**
 * @brief ����BTIM2��ITR��Դ
 * 
 * @param Source RCC_TIMITR_BTIM1 RCC_TIMITR_BTIM3
 *               RCC_TIMITR_GTIM1 RCC_TIMITR_GTIM2 RCC_TIMITR_GTIM3 RCC_TIMITR_GTIM4
 *               RCC_TIMITR_ATIM
 */
void RCC_BTIM2ITRSelect(uint32_t Source)
{
    assert_param(IS_RCC_TIMITR_SOURCE(Source));

    CW_SYSCTRL->TIMITR_f.BTIM2ITR = Source;
}

/**
 * @brief ����BTIM1��ITR��Դ
 * 
 * @param Source RCC_TIMITR_BTIM2 RCC_TIMITR_BTIM3
 *               RCC_TIMITR_GTIM1 RCC_TIMITR_GTIM2 RCC_TIMITR_GTIM3 RCC_TIMITR_GTIM4
 *               RCC_TIMITR_ATIM
 */
void RCC_BTIM1ITRSelect(uint32_t Source)
{
    assert_param(IS_RCC_TIMITR_SOURCE(Source));

    CW_SYSCTRL->TIMITR_f.BTIM1ITR = Source;
}

/**
 * @brief ����GTIM1��ITR��Դ
 * 
 * @param Source RCC_TIMITR_BTIM1 RCC_TIMITR_BTIM2 RCC_TIMITR_BTIM3
 *               RCC_TIMITR_GTIM2 RCC_TIMITR_GTIM3 RCC_TIMITR_GTIM4
 *               RCC_TIMITR_ATIM
 */
void RCC_GTIM1ITRSelect(uint32_t Source)
{
    assert_param(IS_RCC_TIMITR_SOURCE(Source));

    CW_SYSCTRL->TIMITR_f.GTIM1ITR = Source;
}

/**
 * @brief ����GTIM2��ITR��Դ
 * 
 * @param Source RCC_TIMITR_BTIM1 RCC_TIMITR_BTIM2 RCC_TIMITR_BTIM3
 *               RCC_TIMITR_GTIM1 RCC_TIMITR_GTIM3 RCC_TIMITR_GTIM4
 *               RCC_TIMITR_ATIM
 */
void RCC_GTIM2ITRSelect(uint32_t Source)
{
    assert_param(IS_RCC_TIMITR_SOURCE(Source));

    CW_SYSCTRL->TIMITR_f.GTIM2ITR = Source;
}

/**
 * @brief ����GTIM3��ITR��Դ
 * 
 * @param Source RCC_TIMITR_BTIM1 RCC_TIMITR_BTIM2 RCC_TIMITR_BTIM3
 *               RCC_TIMITR_GTIM1 RCC_TIMITR_GTIM2 RCC_TIMITR_GTIM4
 *               RCC_TIMITR_ATIM
 */
void RCC_GTIM3ITRSelect(uint32_t Source)
{
    assert_param(IS_RCC_TIMITR_SOURCE(Source));

    CW_SYSCTRL->TIMITR_f.GTIM3ITR = Source;
}

/**
 * @brief ����GTIM4��ITR��Դ
 * 
 * @param Source RCC_TIMITR_BTIM1 RCC_TIMITR_BTIM2 RCC_TIMITR_BTIM3
 *               RCC_TIMITR_GTIM1 RCC_TIMITR_GTIM2 RCC_TIMITR_GTIM3 
 *               RCC_TIMITR_ATIM
 */
void RCC_GTIM4ITRSelect(uint32_t Source)
{
    assert_param(IS_RCC_TIMITR_SOURCE(Source));

    CW_SYSCTRL->TIMITR_f.GTIM4ITR = Source;
}

/**
 * @brief ����ATIM��ITR��Դ
 * 
 * @param Source RCC_TIMITR_BTIM1 RCC_TIMITR_BTIM2 RCC_TIMITR_BTIM3
 *               RCC_TIMITR_GTIM1 RCC_TIMITR_GTIM2 RCC_TIMITR_GTIM3 
 *               
 */
void RCC_ATIMITRSelect(uint32_t Source)
{
    assert_param(IS_RCC_TIMITR_SOURCE(Source));

    CW_SYSCTRL->TIMITR_f.ATIMITR = Source;
}





