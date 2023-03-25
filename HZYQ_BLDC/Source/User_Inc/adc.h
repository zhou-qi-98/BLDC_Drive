#ifndef __ADC_H
#define __ADC_H	

#include "typedef.h"

#define ADC_CHSELR_CONFIG_U 0x000002a0			//AN5-U  AN7-CURRENT  AN9-Voltage  
#define ADC_CHSELR_CONFIG_V 0x00000290			//AN4-V  AN7-CURRENT  AN9-Voltage
#define ADC_CHSELR_CONFIG_W 0x00000282		    //AN1-W  AN7-CURRENT  AN9-Voltage

void ADC1_Init(void);

void ADC1_DMA_Init(void);

void Sort_Data(uint * ad_buf, uchar n);

uint32_t Average_Data(uint16_t * ad_buf, uint8_t n);

uint32 Filter (uint32 new_data,uint32 old_data,uint k);

uint32_t Get_Sample_Average(uint16_t * buf, uint8_t num);

void ADC_ISR(void);

void ADC_Config(void);

void ADC_Task(void);


#endif 
