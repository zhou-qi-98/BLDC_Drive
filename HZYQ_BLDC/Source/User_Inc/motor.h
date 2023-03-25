#ifndef __MOTOR_H
#define __MOTOR_H

#include "stm32f0xx_gpio.h"
#include "stm32f0xx_tim.h"
#include "var.h"
#include "typedef.h"
#include "timer.h"

#define MinDuty  300

#define MAXDuty  2800

/* BLDC�����ǰ״̬ */
typedef enum
{
	Start_status, 				    //����
	Stop_status	 				    //ֹͣ
}BLDC_st;

/* BLDC���ת������ */
typedef enum
{
	Forward_Status,    			    //��ת
	Reverse_Status     				//��ת
}BLDC_Dircetion;



typedef struct
{
	uint8_t B_Status;				//BLDC״̬
	uint8_t B_Direction;			//BLDCת������
	
	void (*Start)(void);			//BLDC����
	void (*Stop)(void);				//BLDCͣ��
	void (*Motor_Cw)(void);			//BLDC��ת
	void (*Motor_CCw)(void);		//BLDC��ת
	void (*GetRunDeriction)(void);	//BLDC��ȡ����˶�����
	void (*Direction_Adjust)(BLDC_Dircetion BLDC_Dir);	//BLDC�������
}BLDC_T;


extern BLDC_T BLDC_Motor;


void Read_Holl_Speed(void);



#endif




