#include "control.h"

tsEStruct ES_Struct = 
{
	FStart_status,
	First_status,
	H_Ok,
	H_Error,
	0,
	Pidclose_Status, 
	0
};

/*
*********************************************************************************************************
*	@�� �� ��: uint8_t H1_GetStatus(void)
*	@����˵��: ����ADC��ֵ��Χ�����ֹͣ���������ж�
*	@��    ��: None
*	@�� �� ֵ: H_Stop - ֹͣ��H_Ok - ����
*********************************************************************************************************
*/
static uint8_t H1_GetStatus(void)
{
	if(ADC_ConvData[0] > 1800)
	{
		return H_Stop;
	}
	else
	{
		return H_Ok;
	}
}
/*
*********************************************************************************************************
*	@�� �� ��: uint8_t H2_GetStatus(void)
*	@����˵��: ����ADC��ֵ��Χ�������������ϵ��ж�
*	@��    ��: None
*	@�� �� ֵ: H_Normal - ������H_Error - ����
*********************************************************************************************************
*/
static uint8_t H2_GetStatus(void)
{
	if(ADC_ConvData[1] <2500)
	{
		return H_Normal;
	}
	else
	{
		return H_Error;
	}
}

static void Event_PrepareHandle(void)
{
	switch(ES_Struct.Event_Prepare)
	{
		case First_status:
			
			if(Motor_St.Fstart_Timer < 8000)
			{
				if(ES_Struct.H2_Flag == H_Normal)
				{
					ES_Struct.Event_Prepare = Second_status;
				}
			}
			else
			{
				ES_Struct.Event_Prepare = Error_status;
			}
			break;
		case Second_status:
			
			if(Motor_St.Fstart_Timer < 8000)
			{
				if(ES_Struct.H1_Flag == H_Stop)
				{
					BLDC_Motor.Stop();
					
					ES_Struct.Event_Prepare = Default_status;
					ES_Struct.Event_Start = Wait_status;
				}
			}
			else
			{
				ES_Struct.Event_Prepare = Error_status;
			}
			break;
		case Error_status:
			
			Err_On;
			
			BLDC_Motor.Stop();
			
			break;
		default:break;
	}
}	
/*
*********************************************************************************************************
*	@�� �� ��: void EventHandle(void)
*	@����˵��: �¼�������
*	@��    ��: None
*	@�� �� ֵ: None
*********************************************************************************************************
*/

void EventHandle(void)
{
	switch(ES_Struct.Event_Start)
	{
		case FStart_status:
			
			
			
			ES_Struct.H1_Flag = H1_GetStatus();
		
			ES_Struct.H2_Flag = H2_GetStatus();
		
			Event_PrepareHandle();
		
			break;
		case Wait_status:
			
			ES_Struct.H1_Flag = H1_GetStatus();
		
			ES_Struct.H2_Flag = H2_GetStatus();
		
			if(ES_Struct.H2_Flag == H_Error)
			{
				ES_Struct.Event_Start = Err_status;
			}
			
			if(ES_Struct.H1_Flag != H_Ok)
			{		
				if(Motor_St.Brake_Delay >= 50)
				{
					Motor_St.Brake_Delay = 0;
					if(Motor_St.Pwm > 350)
					{
						Motor_St.Pwm -= 350;
					}
				}
				if(Motor_St.Pwm <= 350)
				{
					BLDC_Motor.Stop();
					
					BLDC_Motor.B_Status = Stop_status;
				}
//				if(Motor_St.Brake_Delay > 300)
//				{

//				}
			}
			else
			{
				BLDC_Motor.Start();
//				Delay_Ms(50);
				
				Motor_St.St_Timer = 0;
				
				ES_Struct.Event_Start = PID_status;
			}
			
			break;
		case PID_status:
			
			ES_Struct.H1_Flag = H1_GetStatus();
		
			ES_Struct.H2_Flag = H2_GetStatus();
		
			if(ES_Struct.H2_Flag == H_Error)
			{
				ES_Struct.Event_Start = Err_status;
			}
			
			if(ES_Struct.H1_Flag != H_Ok)
			{
				if(Motor_St.St_Timer > 50)
				{
					Motor_St.St_Timer = 0;
					
					if(ES_Struct.H1_Flag != H_Ok)
					{
						ES_Struct.PID_Flag = Pidclose_Status;
						Motor_St.Brake_Delay = 0;
//						Motor_St.Pwm = 600;
						ES_Struct.Event_Start = Wait_status;
					}
				}
			}
			else
			{
				if(Motor_St.St_Timer > 30)
				{

					Motor_St.St_Timer = 0;
					
					if(ES_Struct.H1_Flag == H_Ok)
					{
						ES_Struct.PID_Flag = Pidopen_Status;
					}
				}
			}
			
			break;
			
		case Err_status:
			
			Err_On;
			
			BLDC_Motor.Stop();
		
			break;
		default:break;
	}
}
