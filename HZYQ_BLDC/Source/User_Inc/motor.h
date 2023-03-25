#ifndef __MOTOR_H
#define __MOTOR_H

#include "stm32f0xx_gpio.h"
#include "stm32f0xx_tim.h"
#include "var.h"
#include "typedef.h"
#include "timer.h"

#define MinDuty  300

#define MAXDuty  2800

/* BLDC电机当前状态 */
typedef enum
{
	Start_status, 				    //启动
	Stop_status	 				    //停止
}BLDC_st;

/* BLDC电机转动方向 */
typedef enum
{
	Forward_Status,    			    //正转
	Reverse_Status     				//反转
}BLDC_Dircetion;



typedef struct
{
	uint8_t B_Status;				//BLDC状态
	uint8_t B_Direction;			//BLDC转动方向
	
	void (*Start)(void);			//BLDC启动
	void (*Stop)(void);				//BLDC停机
	void (*Motor_Cw)(void);			//BLDC正转
	void (*Motor_CCw)(void);		//BLDC反转
	void (*GetRunDeriction)(void);	//BLDC获取电机运动方向
	void (*Direction_Adjust)(BLDC_Dircetion BLDC_Dir);	//BLDC方向调整
}BLDC_T;


extern BLDC_T BLDC_Motor;


void Read_Holl_Speed(void);



#endif




