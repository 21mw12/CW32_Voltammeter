/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    interrupts_cw32f003.h
  * @brief   This file contains the headers of the interrupt handlers.
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

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __INTERRUPTS_CW32F003_H
#define __INTERRUPTS_CW32F003_H

#ifdef __cplusplus
 extern "C" {
#endif 

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */


/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */

/* USER CODE END ET */


/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

/* USER CODE END EC */


/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */


/* Exported functions prototypes ---------------------------------------------*/

extern void NMI_Handler(void);
extern void HardFault_Handler(void);
extern void SVC_Handler(void);
extern void PendSV_Handler(void);
extern void WDT_IRQHandler(void);
extern void LVD_IRQHandler(void);

extern void FLASHRAM_IRQHandler(void);
extern void SYSCTRL_IRQHandler(void);
extern void GPIOA_IRQHandler(void);
extern void GPIOB_IRQHandler(void);
extern void GPIOC_IRQHandler(void);


extern void ADC_IRQHandler(void);
extern void ATIM_IRQHandler(void);
extern void VC1_IRQHandler(void);
extern void VC2_IRQHandler(void);
extern void GTIM_IRQHandler(void);

extern void BTIM1_IRQHandler(void);
extern void BTIM2_IRQHandler(void);
extern void BTIM3_IRQHandler(void);
extern void I2C_IRQHandler(void);

extern void SPI_IRQHandler(void);

extern void UART1_IRQHandler(void);
extern void UART2_IRQHandler(void);

extern void AWT_IRQHandler(void);


/* USER CODE BEGIN EFP */

/* USER CODE END EFP */


#ifdef __cplusplus
}
#endif

#endif /* __INTERRUPTS_CW32F003_H */

/************************ (C) COPYRIGHT CW *****END OF FILE****/
