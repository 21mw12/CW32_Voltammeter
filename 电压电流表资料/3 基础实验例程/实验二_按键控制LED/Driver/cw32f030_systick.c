/**
 * @file cw32f030_systick.c
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
#include "cw32f030_systick.h"

/* Private_TypesDefinitions --------------------------------------------------*/

/* Private_Defines -----------------------------------------------------------*/

/* Private_Variables ---------------------------------------------------------*/
__IO uint32_t uwTick;
uint32_t uwTickPrio   = (1UL << __NVIC_PRIO_BITS); /* Invalid PRIO */
TickFreqTypeDef uwTickFreq = TICK_FREQ_DEFAULT;  /* 1KHz */

/* Private_FunctionPrototypes ------------------------------------------------*/

/* Private_Functions ---------------------------------------------------------*/

/* Public_Functions ----------------------------------------------------------*/

/**
  * @brief This function configures the source of the time base. 
  *        The time source is configured  to have 1ms time base with a dedicated 
  *        Tick interrupt priority.
  * @note This function is called  automatically at the beginning of program after
  *       reset by HAL_Init() or at any time when clock is reconfigured  by HAL_RCC_ClockConfig(). 
  * @note In the default implementation, SysTick timer is the source of time base. 
  *       It is used to generate interrupts at regular time intervals. 
  *       Care must be taken if HAL_Delay() is called from a peripheral ISR process, 
  *       The SysTick interrupt must have higher priority (numerically lower) 
  *       than the peripheral interrupt. Otherwise the caller ISR process will be blocked.
  *       The function is declared as __Weak  to be overwritten  in case of other
  *       implementation  in user file.
  * @param system hclk freq.
  * @retval HAL status
  */
__weak void InitTick(uint32_t HclkFreq)
{
	
  /*Configure the SysTick to have interrupt in 1ms time basis*/
  if (SysTick_Config(HclkFreq / (1000U / uwTickFreq)) > 0U)
  {
    return ;
  }

  /* Configure the SysTick IRQ priority */
  if (TICK_INT_PRIORITY < (1UL << __NVIC_PRIO_BITS))
  {
	  NVIC_SetPriority(SysTick_IRQn, TICK_INT_PRIORITY);
    uwTickPrio = TICK_INT_PRIORITY;
  }
  else
  {
    return ;
  }

}


/**
  * @brief  Provides a tick value in millisecond.
  * @note   This function is declared as __weak  to be overwritten  in case of other 
  *       implementations in user file.
  * @retval tick value
  */
__weak uint32_t GetTick(void)
{
  return uwTick;
}


/**
  * @brief This function provides accurate delay (in milliseconds) based 
  *        on variable incremented.
  * @note In the default implementation , SysTick timer is the source of time base.
  *       It is used to generate interrupts at regular time intervals where uwTick
  *       is incremented.
  * @note ThiS function is declared as __weak to be overwritten in case of other
  *       implementations in user file.
  * @param Delay specifies the delay time length, in milliseconds.
  * @retval None
  */
__weak void SysTickDelay(uint32_t Delay)
{
  uint32_t tickstart = GetTick();
  uint32_t wait = Delay;
  
  /* Add a freq to guarantee minimum wait */
  if (wait < MAX_SYSTICK_DELAY)
  {
    wait += (uint32_t)(uwTickFreq);
  }
  
  while((GetTick() - tickstart) < wait)
  {
  }
}


/**
  * @brief Suspend Tick increment.
  * @note In the default implementation , SysTick timer is the source of time base. It is
  *       used to generate interrupts at regular time intervals. Once HAL_SuspendTick()
  *       is called, the the SysTick interrupt will be disabled and so Tick increment 
  *       is suspended.
  * @note This function is declared as __weak to be overwritten in case of other
  *       implementations in user file.
  * @retval None
  */
__weak void SuspendTick(void)

{
  /* Disable SysTick Interrupt */
  REGBITS_CLR(SysTick->CTRL, SysTick_CTRL_TICKINT_Msk);
}


/**
  * @brief Resume Tick increment.
  * @note In the default implementation , SysTick timer is the source of time base. It is
  *       used to generate interrupts at regular time intervals. Once HAL_ResumeTick()
  *       is called, the the SysTick interrupt will be enabled and so Tick increment 
  *       is resumed.
  * @note This function is declared as __weak  to be overwritten  in case of other
  *       implementations in user file.
  * @retval None
  */
__weak void ResumeTick(void)
{
  /* Enable SysTick Interrupt */
  REGBITS_SET(SysTick->CTRL, SysTick_CTRL_TICKINT_Msk);
}


/**
  * @brief This function handles System tick timer.
  */
void SysTick_Handler(void)
{
  /* USER CODE BEGIN SysTick_IRQn */
  uwTick += uwTickFreq;
  /* USER CODE END SysTick_IRQn */
}
