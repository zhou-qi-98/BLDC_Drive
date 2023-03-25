#include "protect.h"


static void MotorVoltage_Protect(void);
static void MotorCurrent_Protect(void);
static void MotorCurrent_Loop(void);

SysPro_T Sys_Protect = 
{
	NormalCurrent_Status,
	NormalCurrent_Status,
	NormalVol_Status,
	0,
	
	NormalVol_Status,
	NormalCurrent_Status,
	NoCurrentLoop_Status,
	
	MotorCurrent_Protect,
	MotorVoltage_Protect,
	MotorCurrent_Loop,
};



/*
*********************************************************************************************************
*	@函 数 名: static void MotorVoltage_Protect(void)
*	@功能说明: 电机欠压+过压保护 24V-60V
*	@形    参: None
*	@返 回 值: None
*********************************************************************************************************
*/

static void MotorVoltage_Protect(void)
{
	static uint8_t Voltage_ProTimes = 0;
	if((Sys_Protect.Voltage <= Min_Voltage) || (Sys_Protect.Voltage >= MAX_Voltage))
	{
		Voltage_ProTimes++;
		if(Voltage_ProTimes >= 50)
		{
			Voltage_ProTimes = 0;
			BLDC_Motor.Stop();					//停机
			
			Sys_Protect.VolPro_Flag = UnderOverVol_Status;
			BLDC_Motor.B_Status = Stop_status;
		}
	}
	else
	{
		Voltage_ProTimes = 0;
	}
}

/*
*********************************************************************************************************
*	@函 数 名: static void MotorCurrent_Protect(void)
*	@功能说明: 电机堵转保护 - 情况1：电流过大。情况2：电流正常，但是电机转速不匹配
*	@形    参: None
*	@返 回 值: None   2000
*********************************************************************************************************
*/

static void MotorCurrent_Protect(void)
{
	if((Sys_Protect.W_Current > 3000) || (Sys_Protect.V_Current < 1000)|| (Sys_Protect.V_Current > 3000) || (Sys_Protect.W_Current < 1000))
	{
		Sys_Protect.CurrentPro_Fliter++;
		if(Sys_Protect.CurrentPro_Fliter > 300)
		{
			Sys_Protect.CurrentPro_Fliter = 0;
			BLDC_Motor.Stop();					//停机
			
			
			Sys_Protect.CurPro_Flag = OverCurrent_status;
			BLDC_Motor.B_Status = Stop_status;
		}
	}
	else
	{
		Sys_Protect.CurrentPro_Fliter = 0;
	}
}

/*
*********************************************************************************************************
*	@函 数 名: static void MotorCurrent_Loop(void)
*	@功能说明: 电机电流环
*	@形    参: None
*	@返 回 值: None
*********************************************************************************************************
*/
static void MotorCurrent_Loop(void)
{
	
}
