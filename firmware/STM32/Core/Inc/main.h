/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2023 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f3xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

#include "epc_conf.h"

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
void Error_Handler(void);

/* USER CODE BEGIN EFP */
#ifdef EPC_CONF_USE_CUSTOM_HAL
void SystemClock_Config(void);
#endif
/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define Ext_Tmp_1_Pin GPIO_PIN_0
#define Ext_Tmp_1_GPIO_Port GPIOA
#define Ext_Tmp_2_Pin GPIO_PIN_1
#define Ext_Tmp_2_GPIO_Port GPIOA
#define Ls_Curr_Pin GPIO_PIN_4
#define Ls_Curr_GPIO_Port GPIOA
#define Ls_Volt_Pin GPIO_PIN_5
#define Ls_Volt_GPIO_Port GPIOA
#define Ls_Volt_Ext_Pin GPIO_PIN_6
#define Ls_Volt_Ext_GPIO_Port GPIOA
#define Hs_Volt_Pin GPIO_PIN_7
#define Hs_Volt_GPIO_Port GPIOA
#define Led0_Pin GPIO_PIN_4
#define Led0_GPIO_Port GPIOC
#define Led1_Pin GPIO_PIN_5
#define Led1_GPIO_Port GPIOC
#define Led2_Pin GPIO_PIN_0
#define Led2_GPIO_Port GPIOB
#define Led3_Pin GPIO_PIN_1
#define Led3_GPIO_Port GPIOB
#define Status_3v3_Pin GPIO_PIN_14
#define Status_3v3_GPIO_Port GPIOB
#define Status_5v0_Pin GPIO_PIN_15
#define Status_5v0_GPIO_Port GPIOB
#define Pwm_Out_Pin GPIO_PIN_8
#define Pwm_Out_GPIO_Port GPIOA
#define Out_Disable_Pin GPIO_PIN_9
#define Out_Disable_GPIO_Port GPIOA
#define Thermal_Warn_Pin GPIO_PIN_10
#define Thermal_Warn_GPIO_Port GPIOA
#define SCL_Pin GPIO_PIN_6
#define SCL_GPIO_Port GPIOB
#define SDA_Pin GPIO_PIN_7
#define SDA_GPIO_Port GPIOB

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
