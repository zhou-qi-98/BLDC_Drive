#ifndef __MOTOR_H__
#define __MOTOR_H__


#include "main.h"
#include "gpio.h"
/*
void Motor_run(uint8_t order,uint8_t Duty);
*/


void Motor_Stop(void);
void ROTOR_Pre_positioning(uint8_t direction);//电机转子预定位
void Six_step(uint8_t step);
void Motor_Start(uint8_t direction);
void Motor_Run(uint8_t direction);

#endif


