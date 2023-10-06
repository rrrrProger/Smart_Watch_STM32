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
#include "stm32f1xx_hal.h"

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
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define LED_Pin GPIO_PIN_13
#define LED_GPIO_Port GPIOC
#define Button3_Pin GPIO_PIN_2
#define Button3_GPIO_Port GPIOA
#define Button2_Pin GPIO_PIN_3
#define Button2_GPIO_Port GPIOA
#define Button2_EXTI_IRQn EXTI3_IRQn
#define CS_Pin GPIO_PIN_4
#define CS_GPIO_Port GPIOA
#define Button1_Pin GPIO_PIN_5
#define Button1_GPIO_Port GPIOA
#define SD_CS_Pin GPIO_PIN_0
#define SD_CS_GPIO_Port GPIOB
#define T_CS_Pin GPIO_PIN_12
#define T_CS_GPIO_Port GPIOB
#define RESET_Pin GPIO_PIN_8
#define RESET_GPIO_Port GPIOA
#define A0_Pin GPIO_PIN_11
#define A0_GPIO_Port GPIOA
#define T_IRQ_Pin GPIO_PIN_12
#define T_IRQ_GPIO_Port GPIOA
#define T_IRQ_EXTI_IRQn EXTI15_10_IRQn
#define ESP0_Pin GPIO_PIN_8
#define ESP0_GPIO_Port GPIOB
#define ESP2_Pin GPIO_PIN_9
#define ESP2_GPIO_Port GPIOB

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
