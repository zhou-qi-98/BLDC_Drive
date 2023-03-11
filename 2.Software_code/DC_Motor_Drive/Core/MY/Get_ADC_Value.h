#ifndef __GET_ADC_CALUE_H__
#define __GET_ADC_CALUE_H__

typedef struct
{
	int Driving_V;//驱动电压
	int Current_U;//U相电流
	int Current_V;//V相电流
	int Current_W;//W相电流
}ADC_VALUE;


void get_adc_value(void);

#endif



