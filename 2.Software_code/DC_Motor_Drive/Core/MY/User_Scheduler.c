#include "User_Scheduler.h"

#include "gpio.h"
#include "Get_ADC_Value.h"

SysScanFlag_T __align(4)tSysScanFlag;//系统扫描标志位

#define u16 uint16_t

uint16_t MS_count = 0;			//毫秒计数

void Schedule(void)/*任务调度*/
{	
	if(SYS_TIME1S_FLAG)//1MS时基标志
  {
    SYS_TIME1S_FLAG = 0;
  
		MS_count ++ ;
		if(MS_count >= 60000) MS_count = 0;
    /*调度任务列表*/

		if(( MS_count % 10 ) == 0) 		tSysScanFlag.ANA_Scan_Flag = 1;//		
		if(( MS_count % 200 ) == 0) 		tSysScanFlag.KEY_Scan_Flag = 1;//	
		if(( MS_count % 400 ) == 0) 	tSysScanFlag.CTR_Scan_Flag = 1;//			
		if(( MS_count % 1000 ) == 0)  tSysScanFlag.LAG_Scan_Flag = 1;//		
	}
	
}

void FuncRun(SysScanFlag_T *_tSysScanFlag)/*功能运行*/
{
	
	if(_tSysScanFlag->ANA_Scan_Flag)				//解析任务
	{
		_tSysScanFlag->ANA_Scan_Flag = 0;
		
	}
	
	if(_tSysScanFlag->KEY_Scan_Flag)				//按键任务
	{
		_tSysScanFlag->KEY_Scan_Flag = 0;
		LED0_TOG;
		get_adc_value();

	}
	
	if(_tSysScanFlag->CTR_Scan_Flag)				//控制扫描
	{
		_tSysScanFlag->CTR_Scan_Flag = 0;
		LED1_TOG;
		
	}
	
	if(_tSysScanFlag->LAG_Scan_Flag)				//延时任务
	{
		_tSysScanFlag->LAG_Scan_Flag = 0;


	}	
}
