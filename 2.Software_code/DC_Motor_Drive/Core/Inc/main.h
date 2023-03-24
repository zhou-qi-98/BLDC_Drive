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
extern uint8_t KEY_Value;
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
#define KEY1_Pin GPIO_PIN_4
#define KEY1_GPIO_Port GPIOA
#define KEY2_Pin GPIO_PIN_5
#define KEY2_GPIO_Port GPIOA
#define UL_Pin GPIO_PIN_13
#define UL_GPIO_Port GPIOB
#define VL_Pin GPIO_PIN_14
#define VL_GPIO_Port GPIOB
#define WL_Pin GPIO_PIN_15
#define WL_GPIO_Port GPIOB
#define UH_Pin GPIO_PIN_8
#define UH_GPIO_Port GPIOA
#define VH_Pin GPIO_PIN_9
#define VH_GPIO_Port GPIOA
#define WH_Pin GPIO_PIN_10
#define WH_GPIO_Port GPIOA
#define IIC_SCL_Pin GPIO_PIN_15
#define IIC_SCL_GPIO_Port GPIOA
#define IIC_SDA_Pin GPIO_PIN_3
#define IIC_SDA_GPIO_Port GPIOB
#define LED0_Pin GPIO_PIN_4
#define LED0_GPIO_Port GPIOB
#define LED1_Pin GPIO_PIN_5
#define LED1_GPIO_Port GPIOB
#define BEEP1_Pin GPIO_PIN_6
#define BEEP1_GPIO_Port GPIOB
/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
