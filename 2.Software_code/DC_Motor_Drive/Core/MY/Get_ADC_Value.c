#include "Get_ADC_Value.h"
#include "main.h"
#include "adc.h"
ADC_VALUE ADC1_Value={0,0,0,0};


void get_adc_value()
{
	uint8_t i=0;
	for(i=0;i<4;i++)
	{
		HAL_ADC_Start(&hadc1);   //����û�п�������ת����ÿ��ת��ǰ��Ҫ�������adc
		HAL_ADC_PollForConversion(&hadc1,10);//��ѯ�ȴ�ADCת�����
		switch(i)//���ĸ�ͨ���Ĳ���ֵ���ڽṹ�嵱��
		{
			case 0:ADC1_Value.Driving_V=HAL_ADC_GetValue(&hadc1);break;
			case 1:ADC1_Value.Current_U=HAL_ADC_GetValue(&hadc1);break;
			case 2:ADC1_Value.Current_V=HAL_ADC_GetValue(&hadc1);break;
			case 3:ADC1_Value.Current_W=HAL_ADC_GetValue(&hadc1);break;
			default:break;
		}
	}
	HAL_ADC_Stop(&hadc1);//�ر�ADC
}
