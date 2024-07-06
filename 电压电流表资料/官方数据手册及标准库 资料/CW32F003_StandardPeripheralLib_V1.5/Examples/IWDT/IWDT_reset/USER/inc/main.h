/**
 * @file main.h
 * @author P&S (you@domain.com)
 * @brief Header for main.c file.
 *        This file contains the common defines of the application.
 * @version 0.1
 * @date 2021-04-22
 * 
 * @copyright Copyright (c) 2021
 * 
 */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
//#include "device.h"
#include "base_types.h"
#include "cw32f003.h"
#include "system_cw32f003.h"
#include "interrupts_cw32f003.h"
#include "cw32f003_iwdt.h"
#include "cw32f003_gpio.h"
#include "cw32f003_rcc.h"
#include "cw32f003e4p7_startkit.h"
#include "cw32f003_flash.h"


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
/* USER CODE BEGIN EFP */
void SysTick_HandlerCallback(void);
void WDT_IRQHandlerCallback(void);
/* USER CODE END EFP */


/* Private defines -----------------------------------------------------------*/
/* USER CODE BEGIN Private defines */
/* USER CODE END Private defines */


#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */

/************************ (C) COPYRIGHT CW *****END OF FILE****/
