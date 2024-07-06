/*
 * cw32f003_pwr_modes.c
 *
 *  Created on: 2021年12月20日
 *      Author: Socrates
 */

/**
  ******************************************************************************
  * @file    PWR/PWR_CurrentConsumption/cw32f003_pwr_modes.c
  * @author  MCD Application Team
  * @brief   This file provides firmware functions to manage the following
  *          functionalities of the CW32F030 Low Power Modes:
  *           - Sleep Mode
  *           - DeepSleep mode with or without RTC
  ******************************************************************************/



/* Includes ------------------------------------------------------------------*/
#include "cw32f003_pwr_modes.h"
#include "main.h"
#include "cw32f003_pwr.h"
#include "cw32f003_gpio.h"
#include "cw32f003_systick.h"
#include "cw32f003_rcc.h"
#include "cw32f003_flash.h"
#include "cw32f003_vc.h"
#include "cw32f003_adc.h"

/** @addtogroup CW32F030_HAL_Examples
  * @{
  */

/** @addtogroup PWR_CurrentConsumption
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* RTC handler declaration */
//RTC_HandleTypeDef RTCHandle;

/* Private function prototypes -----------------------------------------------*/
static void SYSCLKConfig_DeepSleep(void);

/* Private functions ---------------------------------------------------------*/

/* External variables --------------------------------------------------------*/
/* USER CODE BEGIN EV */
extern volatile uint8_t gKeyStatus;
/* USER CODE END EV */

/**
  * @brief  This function configures the system to enter Sleep mode for
  *         current consumption measurement purpose.
  *         Sleep Mode
  *         ==========
  *            - System Running at HSI (24 MHz)
  *            - Code running from Internal FLASH
  *            - All peripherals disabled.
  *            - Wakeup using EXTI Line (User push-button)
  * @param  None
  * @return None
  */
void SleepModeTest(void)
{
  GPIO_InitTypeDef GPIO_InitStructure;
  PWR_InitTypeDef PWR_InitStructure;

  /* Configure all GPIO as analog to reduce current consumption on non used IOs */
  /* Enable GPIOs clock */
  /* Warning : Reconfiguring all GPIO will close the connexion with the debugger */
  //打开GPIO时钟
  REGBITS_SET( CW_SYSCTRL->AHBEN, SYSCTRL_AHBEN_GPIOA_Msk | SYSCTRL_AHBEN_GPIOB_Msk |\
    		  SYSCTRL_AHBEN_GPIOC_Msk );

  GPIO_InitStructure.Mode = GPIO_MODE_ANALOG;
  
  GPIO_InitStructure.IT = GPIO_IT_NONE;
  GPIO_InitStructure.Pins = GPIO_PIN_All;
  GPIO_Init(CW_GPIOA, &GPIO_InitStructure);
  GPIO_Init(CW_GPIOB, &GPIO_InitStructure);
  GPIO_Init(CW_GPIOC, &GPIO_InitStructure);
  

  /* Disable GPIOs clock */
  REGBITS_CLR( CW_SYSCTRL->AHBEN, SYSCTRL_AHBEN_GPIOA_Msk | SYSCTRL_AHBEN_GPIOB_Msk |\
    		  SYSCTRL_AHBEN_GPIOC_Msk );

  /* Configure User push-button as external interrupt generator */
  BSP_PB_Init();

  /*Suspend Tick increment to prevent wakeup by Systick interrupt.
    Otherwise the Systick interrupt will wake up the device within 1ms (HAL time base)*/
  SuspendTick();

  /* Request to enter SLEEP mode */
  //HAL_PWR_EnterSLEEPMode(PWR_MAINREGULATOR_ON, PWR_SLEEPENTRY_WFI);
  PWR_InitStructure.PWR_Sevonpend = PWR_Sevonpend_Disable;
  PWR_InitStructure.PWR_SleepDeep = PWR_SleepDeep_Disable;
  PWR_InitStructure.PWR_SleepOnExit = PWR_SleepOnExit_Disable;
  PWR_Config(&PWR_InitStructure);
  PWR_GotoLpmMode();

  /* Resume Tick interrupt if disabled prior to sleep mode entry*/
  ResumeTick();

  /* Initialize led */
  LED_Init();
}

/**
  * @brief  This function configures the system to enter Deep-Sleep mode
  *         for current consumption measurement purpose.
  *         Deep-Sleep Mode
  *         ==========
  *           - No IWDG
  *           - Wakeup using EXTI Line (User push-button)
  * @param  None
  * @return None
  */
void DeepSleepModeTest(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	PWR_InitTypeDef PWR_InitStructure;

	/* Configure all GPIO as analog to reduce current consumption on non used IOs */
	/* Warning : Reconfiguring all GPIO will close the connexion with the debugger */
	/* Enable GPIOs clock */
	//打开GPIO时钟
	REGBITS_SET( CW_SYSCTRL->AHBEN, SYSCTRL_AHBEN_GPIOA_Msk | SYSCTRL_AHBEN_GPIOB_Msk |\
			  SYSCTRL_AHBEN_GPIOC_Msk );

	GPIO_InitStructure.Mode = GPIO_MODE_ANALOG;
	
	GPIO_InitStructure.IT = GPIO_IT_NONE;
	GPIO_InitStructure.Pins = GPIO_PIN_All;
	GPIO_Init(CW_GPIOA, &GPIO_InitStructure);
	GPIO_Init(CW_GPIOB, &GPIO_InitStructure);
	GPIO_Init(CW_GPIOC, &GPIO_InitStructure);
	

	//关闭GPIO时钟
	REGBITS_CLR( CW_SYSCTRL->AHBEN, SYSCTRL_AHBEN_GPIOA_Msk | SYSCTRL_AHBEN_GPIOB_Msk |\
			  SYSCTRL_AHBEN_GPIOC_Msk );

	/* Configure User Button */
	BSP_PB_Init();

	//如果使能了VC,则应等待VC_SR.READY置1后方可进入DeepSleep模式
	//打开VC时钟
	RCC_APBPeriphClk_Enable2(RCC_APB2_PERIPH_VC, ENABLE);
	if(VC1_GetEnableStatus() == SET)
	{
		//等待VC1稳定
		while(!(VC1_GetFlagStatus(VC_FLAG_READY)))
		{
			;
		}

		if(VC2_GetEnableStatus() == SET)
		{
			//等待VC2稳定
			while(!(VC2_GetFlagStatus(VC_FLAG_READY)))
			{
				;
			}
		}
	}
	else if(VC2_GetEnableStatus() == SET)
	{
		//等待VC2稳定
		while(!(VC2_GetFlagStatus(VC_FLAG_READY)))
		{
			;
		}
	}
	else
	{
		//关闭VC时钟
		RCC_APBPeriphClk_Enable2(RCC_APB2_PERIPH_VC, DISABLE);
	}

	/* Enter Stop Mode */
	PWR_InitStructure.PWR_Sevonpend = PWR_Sevonpend_Disable;
	PWR_InitStructure.PWR_SleepDeep = PWR_SleepDeep_Enable;
	PWR_InitStructure.PWR_SleepOnExit = PWR_SleepOnExit_Disable;
	PWR_Config(&PWR_InitStructure);

	//打开FLASH时钟
	REGBITS_SET( CW_SYSCTRL->AHBEN, SYSCTRL_AHBEN_FLASH_Msk);
	REGBITS_SET(CW_FLASH->CR1, FLASH_CR1_STANDBY_Msk); //打开FLASH低功耗使能控制
	//关闭FLASH时钟
	REGBITS_CLR( CW_SYSCTRL->AHBEN, SYSCTRL_AHBEN_FLASH_Msk);

	//进入深度休眠模式前应当将HCLK的时钟频率修改为不大于4MHz
	RCC_HSI_Enable( RCC_HSIOSC_DIV12); //配置系统时钟为HSI 4M

	PWR_GotoLpmMode();

	/* Configures system clock after wake-up from DeepSleep: enable HSI and PLL with HSI as source*/
	SYSCLKConfig_DeepSleep();

	/* Initialize LED on the board */
	LED_Init();

	/* Inserted Delay */
	SysTickDelay(200);

	/* Turn LED1 On */
	PA07_SETHIGH();
}


/**
  * @brief  Configures system clock after wake-up from DeepSleep: enable HSE, PLL
  *         and select PLL as system clock source.
  * @param  None
  * @return None
  */
static void SYSCLKConfig_DeepSleep(void)
{
	FirmwareDelay( 1000ul );
	//打开FLASH时钟
	REGBITS_SET( CW_SYSCTRL->AHBEN, SYSCTRL_AHBEN_FLASH_Msk);
	FLASH_SetLatency( FLASH_Latency_2 ); //系统时钟大于24M需要配置FlashWait
	//关闭FLASH时钟
	REGBITS_CLR( CW_SYSCTRL->AHBEN, SYSCTRL_AHBEN_FLASH_Msk);

	RCC_HSI_Enable( RCC_HSIOSC_DIV1); //配置系统时钟为HSI 48M

	/* Configure the HCLK and PCLK1 clocks dividers */
	RCC_HCLKPRS_Config(RCC_HCLK_DIV1);
	RCC_PCLKPRS_Config(RCC_PCLK_DIV1);
	RCC_SYSCLKSRC_Config(RCC_SYSCLKSRC_HSI);
}

/**
 * @brief 系统时钟测试
 * 
 */
void HclkOutTest(void)
{
    //打开GPIO时钟
    REGBITS_SET( CW_SYSCTRL->AHBEN, SYSCTRL_AHBEN_GPIOB_Msk | SYSCTRL_AHBEN_GPIOC_Msk );
    //配置PB3,PC00为输出
	REGBITS_CLR( CW_GPIOB->ANALOG , bv3 );
	REGBITS_CLR( CW_GPIOB->DIR    , bv3 );
	PB03_AFx_PCLKOUT(); //配置PB03输出PCLK
	REGBITS_CLR( CW_GPIOC->ANALOG , bv0 );
	REGBITS_CLR( CW_GPIOC->DIR    , bv0 );
	PC00_AFx_HCLKOUT(); //配置PC00输出HCLK
}
/**
  * @}
  */

/**
  * @}
  */

/*****************************END OF FILE****/



