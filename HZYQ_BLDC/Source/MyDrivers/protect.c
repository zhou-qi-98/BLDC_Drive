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
*	@�� �� ��: static void MotorVoltage_Protect(void)
*	@����˵��: ���Ƿѹ+��ѹ���� 24V-60V
*	@��    ��: None
*	@�� �� ֵ: None
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
			BLDC_Motor.Stop();					//ͣ��
			
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
*	@�� �� ��: static void MotorCurrent_Protect(void)
*	@����˵��: �����ת���� - ���1�������������2���������������ǵ��ת�ٲ�ƥ��
*	@��    ��: None
*	@�� �� ֵ: None   2000
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
			BLDC_Motor.Stop();					//ͣ��
			
			
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
*	@�� �� ��: static void MotorCurrent_Loop(void)
*	@����˵��: ���������
*	@��    ��: None
*	@�� �� ֵ: None
*********************************************************************************************************
*/
static void MotorCurrent_Loop(void)
{
	
}
