#ifndef __TIME_H
#define __TIME_H
#include "typedef.h"
#include "typedef.h"
#include "stm32f0xx_tim.h"
#include "var.h"

#include "stm32f0xx_misc.h"
#include "stm32f0xx_rcc.h"
#include "stm32f0xx_gpio.h"
#include "iwdg.h"
#include "motor.h"


#define PWM_TIM_CLOCK       48000000

#define PWM_TIM_FREQ       16000       //  20KHZ

#define PWM_TIM_PULSE      (PWM_TIM_CLOCK/(PWM_TIM_FREQ))

void Delay_Ms(uint ms);

void TIM1_PWM_Init(void);

void TIM3_PWM_Init(void);

void TIM6_Init(void); // Caulate 60 angel;


void TIM16_Init(void);

void TIM14_Init(void);

void TIM16_ISR(void);

void TIM14_ISR(void);

void TIM17_ISR(void);

void TIM_Channel_1_PWM_ALL_Stop(void);

void TIM_Channel_1_PWM_P_OutPut(void);

void TIM_Channel_1_PWM_N_OutPut(void);

void TIM_Channel_1_PWM_All_OutPut(void);

void TIM_Channel_2_PWM_ALL_Stop(void);

void TIM_Channel_2_PWM_P_OutPut(void);

void TIM_Channel_2_PWM_N_OutPut(void);

void TIM_Channel_2_PWM_All_OutPut(void);

void TIM_Channel_3_PWM_ALL_Stop(void);

void TIM_Channel_3_PWM_P_OutPut(void);

void TIM_Channel_3_PWM_N_OutPut(void);

void TIM_Channel_3_PWM_All_OutPut(void);

void Timer_Init(void);

void Test_TIM17_ISR(void);




#endif


