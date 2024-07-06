/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
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
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C"
{
#endif

/* Includes ------------------------------------------------------------------*/
#include "cw32f003.h"
#include "cw32f003_atim.h"
#include "cw32f003_btim.h"
#include "cw32f003_flash.h"
#include "cw32f003_gpio.h"
#include "cw32f003_rcc.h"
#include "cw32f003_uart.h"
#include "interrupts_cw32f003.h"
#include "log.h"

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
void ATIM_IRQHandlerCallBack(void);

  /* Private defines -----------------------------------------------------------*/
  /* USER CODE BEGIN Private defines */
  /* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */

/************************ (C) COPYRIGHT CW *****END OF FILE****/
