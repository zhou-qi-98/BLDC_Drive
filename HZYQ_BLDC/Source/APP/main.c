#include "typedef.h"
#include "var.h"
#include "timer.h"
#include "gpio.h"
#include "adc.h"
#include "usart.h"
#include "iwdg.h"
#include "motor.h"
#include "stdio.h"
#include "bsp.h"
#include "control.h"
#include "spi.h"
#include "protect.h"

void SysVariable_Init(void)
{
	Motor_St.Desire_Speed = 0;
	Motor_St.Measure_Speed = 0;
	Motor_St.Motor_NowPosition = 0;
	Motor_St.Motor_OldPosition = 0;
	Motor_St.Run_Status = 0;
	Motor_St.Pwm = MinDuty;
	
	Motor_St.Fstart_Timer = 0;
	Motor_St.St_Timer = 0;
	
}

uint8_t Erro_St = 0;


int main(void)
{
		ADC_Config();
	
		ADC1_DMA_Init();
	
		SysVariable_Init(); 
		
		Gpio_Init();	
		 
		PID_Init();
	
		Timer_Init();

		WDG_Init();
	
		BLDC_Motor.Start();
	
	
//		Erro_St = GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_2);
		
    while(1)  
    {
		
//				Sys_Protect.Voltage_Protect(); //过欠压保护
//				Sys_Protect.Current_Protect(); //堵转保护
//				if((Sys_Protect.VolPro_Flag == UnderOverVol_Status) || (Sys_Protect.CurPro_Flag == OverCurrent_status))
//				{
//					ES_Struct.Event_Start = Err_status;
//				}
//				EventHandle();

    }
}






