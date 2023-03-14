#ifndef __KEY_H__
#define __KEY_H__

#include "gpio.h"
#include "main.h"

#define KEY1 HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_4)
#define KEY2 HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_5)



uint8_t Key_scan(void);

#endif


