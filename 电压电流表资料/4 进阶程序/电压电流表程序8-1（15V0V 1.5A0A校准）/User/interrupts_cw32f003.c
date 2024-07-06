/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    interrupts.c
  * @brief   Interrupt Service Routines.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2021 CW.
  * All rights reserved.</center></h2>
  *
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "interrupts_cw32f003.h"
/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
/* USER CODE END Includes */


/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN TD */
/* USER CODE END TD */


/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */ 
/* USER CODE END PD */


/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */
/* USER CODE END PM */


/* Private variables ---------------------------------------------------------*/
/* USER CODE BEGIN PV */
/* USER CODE END PV */


/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN PFP */
/* USER CODE END PFP */


/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
/* USER CODE END 0 */

/* External variables --------------------------------------------------------*/
/* USER CODE BEGIN EV */
/* USER CODE END EV */

/******************************************************************************/
/*           Cortex-M0P Processor Interruption and Exception Handlers          */ 
/******************************************************************************/
/**
  * @brief This function handles Non maskable interrupt.
  */
void NMI_Handler(void)
{
  /* USER CODE BEGIN NonMaskableInt_IRQn */

  /* USER CODE END NonMaskableInt_IRQn */
}

/**
  * @brief This function handles Hard fault interrupt.
  */
void HardFault_Handler(void)
{
  /* USER CODE BEGIN HardFault_IRQn */

  /* USER CODE END HardFault_IRQn */
  while (1)
  {
    /* USER CODE BEGIN W1_HardFault_IRQn */
	  
    /* USER CODE END W1_HardFault_IRQn */
  }
}


/**
  * @brief This function handles System service call via SWI instruction.
  */
void SVC_Handler(void)
{
  /* USER CODE BEGIN SVCall_IRQn */

  /* USER CODE END SVCall_IRQn */
}


/**
  * @brief This function handles Pendable request for system service.
  */
void PendSV_Handler(void)
{
  /* USER CODE BEGIN PendSV_IRQn */

  /* USER CODE END PendSV_IRQn */
}

//void SysTick_Handler(void)
//{
//  
//}

/******************************************************************************/
/* CW32F003 Peripheral Interrupt Handlers                                     */
/* Add here the Interrupt Handlers for the used peripherals.                  */
/* For the available peripheral interrupt handler names,                      */
/* please refer to the startup file (startup_cw32f003.s).                     */
/******************************************************************************/

/**
 * @brief This funcation handles WDT
 */
void WDT_IRQHandler(void)
{
  /* USER CODE BEGIN */
	
  /* USER CODE END */
}

/**
 * @brief This funcation handles LVD
 */
void LVD_IRQHandler(void)
{
  /* USER CODE BEGIN */

  /* USER CODE END */
}


/**
 * @brief This funcation handles FLASHRAM
 */
void FLASHRAM_IRQHandler(void)
{
  /* USER CODE BEGIN */

  /* USER CODE END */
}

/**
 * @brief This funcation handles RCC
 */
void SYSCTRL_IRQHandler(void)
{
  /* USER CODE BEGIN */

  /* USER CODE END */
}

/**
 * @brief This funcation handles GPIOA
 */
void GPIOA_IRQHandler(void)
{
  /* USER CODE BEGIN */

  /* USER CODE END */
}

/**
 * @brief This funcation handles GPIOB
 */
void GPIOB_IRQHandler(void)
{
  /* USER CODE BEGIN */

  /* USER CODE END */
}

/**
 * @brief This funcation handles GPIOC
 */
void GPIOC_IRQHandler(void)
{
  /* USER CODE BEGIN */

  /* USER CODE END */
}


/**
 * @brief This funcation handles ADC
 */
void ADC_IRQHandler(void)
{
  /* USER CODE BEGIN */
	CW_ADC->ICR = 0x00;//情况中断标志位
  /* USER CODE END */
}

/**
 * @brief This funcation handles ATIM
 */
void ATIM_IRQHandler(void)
{
  /* USER CODE BEGIN */

  /* USER CODE END */
}

/**
 * @brief This funcation handles VC1
 */
void VC1_IRQHandler(void)
{
  /* USER CODE BEGIN */

  /* USER CODE END */
}

/**
 * @brief This funcation handles VC2
 */
void VC2_IRQHandler(void)
{
  /* USER CODE BEGIN */

  /* USER CODE END */
}

/**
 * @brief This funcation handles GTIM
 */
void GTIM_IRQHandler(void)
{
  /* USER CODE BEGIN */

  /* USER CODE END */
}

extern unsigned int timecount;
/**
 * @brief This funcation handles BTIM1
 */


/**
 * @brief This funcation handles BTIM2
 */
void BTIM2_IRQHandler(void)
{
  /* USER CODE BEGIN */


  /* USER CODE END */
}

/**
 * @brief This funcation handles BTIM3
 */
void BTIM3_IRQHandler(void)
{
  /* USER CODE BEGIN */


  /* USER CODE END */
}

/**
 * @brief This funcation handles I2C
 */
void I2C_IRQHandler(void)
{
  /* USER CODE BEGIN */

  /* USER CODE END */
}

/**
 * @brief This funcation handles SPI
 */
void SPI_IRQHandler(void)
{
  /* USER CODE BEGIN */

  /* USER CODE END */
}


/**
 * @brief This funcation handles UART1
 */
void UART1_IRQHandler(void)
{
  /* USER CODE BEGIN */

  /* USER CODE END */
}

/**
 * @brief This funcation handles UART2
 */
//void UART2_IRQHandler(void)
//{
//  /* USER CODE BEGIN */
// uint8_t TxRxBuffer;
//  if(USART_GetITStatus(CW_UART2, USART_IT_RC) != RESET)
//  {
//      TxRxBuffer = USART_ReceiveData_8bit(CW_UART2);
//      //    USART_SendData_8bit(CW_UART2, TxRxBuffer);
//      USART_ClearITPendingBit(CW_UART2, USART_IT_RC);
//     // wait_spp_cmd(TxRxBuffer);
//  }
//  /* USER CODE END */
//}


/**
 * @brief This funcation handles AWT
 */
void AWT_IRQHandler(void)
{
  /* USER CODE BEGIN */

  /* USER CODE END */
}

/* USER CODE BEGIN 1 */

/* USER CODE END 1 */

/************************ (C) COPYRIGHT CW *****END OF FILE****/
