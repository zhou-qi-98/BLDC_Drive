#ifndef __GET_ADC_CALUE_H__
#define __GET_ADC_CALUE_H__

typedef struct
{
	int Driving_V;//������ѹ
	int Current_U;//U�����
	int Current_V;//V�����
	int Current_W;//W�����
}ADC_VALUE;


void get_adc_value(void);

#endif



