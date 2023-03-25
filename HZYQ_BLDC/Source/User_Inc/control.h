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
	teStart Event_Start;//״̬��
	
	tePrepare Event_Prepare;
	
	uint8_t H1_Flag;//����1��״̬
	uint8_t H2_Flag;//����2��״̬
	int     PID_Dat;//PID��ÿ�μ���ֵ
	uint8_t PID_Flag;
	uint8_t PID_Eliminate;//PID��������
}tsEStruct;

extern tsEStruct ES_Struct;	

void EventHandle(void);

#endif

