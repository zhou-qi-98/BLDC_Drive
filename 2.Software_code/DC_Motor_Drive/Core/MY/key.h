#ifndef __KEY_H__
#define __KEY_H__

#include "gpio.h"
#include "tim.h"
#include "usart.h"
#include "User_Function.h"

#define KEY1 HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_4)
#define KEY2 HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_5)

extern uint8_t Direction,Count;

uint8_t Key_scan(void);
void Get_EC11_Value(void);

#endif


