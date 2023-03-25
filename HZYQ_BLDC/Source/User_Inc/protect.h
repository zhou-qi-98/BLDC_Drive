#ifndef __PROTECT_H
#define __PROTECT_H

#include "typedef.h"
#include "adc.h"
#include "var.h"
#include "timer.h"
#include "motor.h"

#define Min_Voltage 1450 //ADC值 - 24V
#define MAX_Voltage 3620 //ADC值 - 60V

typedef enum
{
	OverCurrent_status = 0,				//过流状态
	NormalCurrent_Status			//正常状态
}BLDC_Current;

typedef enum
{
	UnderOverVol_Status = 0,			//欠压或过压状态
	NormalVol_Status				//正常状态
}BLDC_Voltage;

typedef enum
{
	CurrentLoop_Status = 0,			    //电流环状态
	NoCurrentLoop_Status			//非电流环状态	
}BLDC_CurLoop;


typedef struct
{
	uint16_t W_Current;//W相电流
	uint16_t V_Current;//V电流
	uint16_t Voltage;//母线电压
	
	uint16_t CurrentPro_Fliter;//电流保护滤波
	
	uint8_t VolPro_Flag; //电压保护标志位
	uint8_t CurPro_Flag; //电流保护标志位
	uint8_t CurLoop_Flag;//电流环标志位
	
	void (*Current_Protect)(void);	//BLDC过流保护
	void (*Voltage_Protect)(void);	//BLDC电压保护
	void (*Currnt_Loop)(void);//BLDC电流环
}SysPro_T;


extern SysPro_T Sys_Protect;

#endif

