#ifndef __CONTROL_H_
#define __CONTROL_H_

#include "timer.h"
#include "bsp.h"


#define H_Stop  1
#define H_Ok    0

#define H_Normal  0
#define H_Error   1

typedef enum
{
	FStart_status,
	Wait_status,
	PID_status,
	Err_status
	
}teStart;

typedef enum
{
	First_status,
	Second_status,
	Error_status,
	Default_status,
}tePrepare;


typedef struct sEStruct
{
	teStart Event_Start;//状态机
	
	tePrepare Event_Prepare;
	
	uint8_t H1_Flag;//霍尔1的状态
	uint8_t H2_Flag;//霍尔2的状态
	int     PID_Dat;//PID的每次计算值
	uint8_t PID_Flag;
	uint8_t PID_Eliminate;//PID消除抖动
}tsEStruct;

extern tsEStruct ES_Struct;	

void EventHandle(void);

#endif

