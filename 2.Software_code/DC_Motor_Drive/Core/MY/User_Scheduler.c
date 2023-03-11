#include "User_Scheduler.h"

#include "gpio.h"
#include "Get_ADC_Value.h"

SysScanFlag_T __align(4)tSysScanFlag;//ϵͳɨ���־λ

#define u16 uint16_t

uint16_t MS_count = 0;			//�������

void Schedule(void)/*�������*/
{	
	if(SYS_TIME1S_FLAG)//1MSʱ����־
  {
    SYS_TIME1S_FLAG = 0;
  
		MS_count ++ ;
		if(MS_count >= 60000) MS_count = 0;
    /*���������б�*/

		if(( MS_count % 10 ) == 0) 		tSysScanFlag.ANA_Scan_Flag = 1;//		
		if(( MS_count % 200 ) == 0) 		tSysScanFlag.KEY_Scan_Flag = 1;//	
		if(( MS_count % 400 ) == 0) 	tSysScanFlag.CTR_Scan_Flag = 1;//			
		if(( MS_count % 1000 ) == 0)  tSysScanFlag.LAG_Scan_Flag = 1;//		
	}
	
}

void FuncRun(SysScanFlag_T *_tSysScanFlag)/*��������*/
{
	
	if(_tSysScanFlag->ANA_Scan_Flag)				//��������
	{
		_tSysScanFlag->ANA_Scan_Flag = 0;
		
	}
	
	if(_tSysScanFlag->KEY_Scan_Flag)				//��������
	{
		_tSysScanFlag->KEY_Scan_Flag = 0;
		LED0_TOG;
		get_adc_value();

	}
	
	if(_tSysScanFlag->CTR_Scan_Flag)				//����ɨ��
	{
		_tSysScanFlag->CTR_Scan_Flag = 0;
		LED1_TOG;
		
	}
	
	if(_tSysScanFlag->LAG_Scan_Flag)				//��ʱ����
	{
		_tSysScanFlag->LAG_Scan_Flag = 0;


	}	
}