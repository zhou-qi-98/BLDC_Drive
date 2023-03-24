/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    gpio.h
  * @brief   This file contains all the function prototypes for
  *          the gpio.c file
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
#ifndef __GPIO_H__
#define __GPIO_H__

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* USER CODE BEGIN Private defines */
#define LED0_OFF HAL_GPIO_WritePin(GPIOB, GPIO_PIN_4, GPIO_PIN_SET);
#define LED0_ON HAL_GPIO_WritePin(GPIOB, GPIO_PIN_4, GPIO_PIN_RESET);
#define LED0_TOG HAL_GPIO_TogglePin(GPIOB, GPIO_PIN_4);
#define LED1_OFF HAL_GPIO_WritePin(GPIOB, GPIO_PIN_5, GPIO_PIN_SET);
#define LED1_ON HAL_GPIO_WritePin(GPIOB, GPIO_PIN_5, GPIO_PIN_RESET);
#define LED1_TOG HAL_GPIO_TogglePin(GPIOB, GPIO_PIN_5);
#define BEEP_OFF HAL_GPIO_WritePin(GPIOB, GPIO_PIN_6, GPIO_PIN_RESET);
#define BEEP_ON HAL_GPIO_WritePin(GPIOB, GPIO_PIN_6, GPIO_PIN_SET);
#define BEPP_TOG HAL_GPIO_TogglePin(GPIOB, GPIO_PIN_6);

/*下面开始宏定义六个MOS管*/
#define UH_ON HAL_GPIO_WritePin(GPIOA, GPIO_PIN_8,GPIO_PIN_SET);
#define UH_OFF HAL_GPIO_WritePin(GPIOA, GPIO_PIN_8,GPIO_PIN_RESET);

#define VH_ON HAL_GPIO_WritePin(GPIOA, GPIO_PIN_9,GPIO_PIN_SET);
#define VH_OFF HAL_GPIO_WritePin(GPIOA, GPIO_PIN_9,GPIO_PIN_RESET);

#define WH_ON HAL_GPIO_WritePin(GPIOA, GPIO_PIN_10,GPIO_PIN_SET);
#define WH_OFF HAL_GPIO_WritePin(GPIOA, GPIO_PIN_10,GPIO_PIN_RESET);

#define UL_ON HAL_GPIO_WritePin(GPIOB, GPIO_PIN_13,GPIO_PIN_SET);
#define UL_OFF HAL_GPIO_WritePin(GPIOB, GPIO_PIN_13,GPIO_PIN_RESET);

#define VL_ON HAL_GPIO_WritePin(GPIOB, GPIO_PIN_14,GPIO_PIN_SET);
#define VL_OFF HAL_GPIO_WritePin(GPIOB, GPIO_PIN_14,GPIO_PIN_RESET);

#define WL_ON HAL_GPIO_WritePin(GPIOB, GPIO_PIN_15,GPIO_PIN_SET);
#define WL_OFF HAL_GPIO_WritePin(GPIOB, GPIO_PIN_15,GPIO_PIN_RESET);

/* USER CODE END Private defines */

void MX_GPIO_Init(void);

/* USER CODE BEGIN Prototypes */

/* USER CODE END Prototypes */

#ifdef __cplusplus
}
#endif
#endif /*__ GPIO_H__ */

