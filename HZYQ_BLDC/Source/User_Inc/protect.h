#ifndef __PROTECT_H
#define __PROTECT_H

#include "typedef.h"
#include "adc.h"
#include "var.h"
#include "timer.h"
#include "motor.h"

#define Min_Voltage 1450 //ADCֵ - 24V
#define MAX_Voltage 3620 //ADCֵ - 60V

typedef enum
{
	OverCurrent_status = 0,				//����״̬
	NormalCurrent_Status			//����״̬
}BLDC_Current;

typedef enum
{
	UnderOverVol_Status = 0,			//Ƿѹ���ѹ״̬
	NormalVol_Status				//����״̬
}BLDC_Voltage;

typedef enum
{
	CurrentLoop_Status = 0,			    //������״̬
	NoCurrentLoop_Status			//�ǵ�����״̬	
}BLDC_CurLoop;


typedef struct
{
	uint16_t W_Current;//W�����
	uint16_t V_Current;//V����
	uint16_t Voltage;//ĸ�ߵ�ѹ
	
	uint16_t CurrentPro_Fliter;//���������˲�
	
	uint8_t VolPro_Flag; //��ѹ������־λ
	uint8_t CurPro_Flag; //����������־λ
	uint8_t CurLoop_Flag;//��������־λ
	
	void (*Current_Protect)(void);	//BLDC��������
	void (*Voltage_Protect)(void);	//BLDC��ѹ����
	void (*Currnt_Loop)(void);//BLDC������
}SysPro_T;


extern SysPro_T Sys_Protect;

#endif

