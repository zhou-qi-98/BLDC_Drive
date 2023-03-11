#include "Get_ADC_Value.h"
#include "main.h"
#include "adc.h"
ADC_VALUE ADC1_Value={0,0,0,0};


void get_adc_value()
{
	uint8_t i=0;
	for(i=0;i<4;i++)
	{
		HAL_ADC_Start(&hadc1);   //由于没有开启连续转换，每次转换前需要软件开启adc
		HAL_ADC_PollForConversion(&hadc1,10);//轮询等待ADC转换完成
		switch(i)//将四个通道的采样值存在结构体当中
		{
			case 0:ADC1_Value.Driving_V=HAL_ADC_GetValue(&hadc1);break;
			case 1:ADC1_Value.Current_U=HAL_ADC_GetValue(&hadc1);break;
			case 2:ADC1_Value.Current_V=HAL_ADC_GetValue(&hadc1);break;
			case 3:ADC1_Value.Current_W=HAL_ADC_GetValue(&hadc1);break;
			default:break;
		}
	}
	HAL_ADC_Stop(&hadc1);//关闭ADC
}
