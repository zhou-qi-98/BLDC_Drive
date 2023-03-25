#ifndef __VAR_H
#define __VAR_H
#include "typedef.h"


//---------from adc.c-------------------

extern uint16_t ADC_ConvData[5];
extern uint16_t Temperature_Convert_Counter ;
extern uint16_t V0_Buf[10];
extern uint16_t V1_Buf[10];
extern uint16_t K0_Buf[10];

//---------from key.c-------------------


extern Com Com1 , Com2;

extern uint16_t T14_S;


extern tPid Pid;


//---------------------from motor.c-----------------------

extern uint16_t PWM_Duty;

extern tsMotor Motor_St;


/* ------------------------------------------ */


	
#endif
