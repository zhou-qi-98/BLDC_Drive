#include "stm32f0xx_dma.h"
#include "stm32f0xx_tim.h"
#include "stm32f0xx_adc.h"
#include "typedef.h"
#include "var.h"
#include "adc.h"

#define ADC1_DR_Address    0x40012440

uint16_t Vref_Cal;

uint16_t ADC_ConvData[5];

uint16_t AD_IT_Counter;

uint16_t Avoid_Counter = 0;

uint16_t Bemf_Temp;

uint16_t Adc_Complete = 0;


void ADC_Config(void)  // ADC + DMA OK
{

    ADC_InitTypeDef     ADC_InitStructure;

    ADC_JitterCmd(ADC1, ADC_JitterOff_PCLKDiv4, ENABLE);

    RCC_ADCCLKConfig(RCC_ADCCLK_PCLK_Div4);

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1, ENABLE);

    ADC_DeInit(ADC1);

    ADC_StructInit(&ADC_InitStructure);


    ADC_InitStructure.ADC_Resolution = ADC_Resolution_12b;

    ADC_InitStructure.ADC_ContinuousConvMode = DISABLE;//连续模式禁止，定时器触发

    ADC_InitStructure.ADC_ExternalTrigConvEdge = ADC_ExternalTrigConvEdge_Rising;//上升沿触发

    ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_T1_CC4;//触发源

    ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;


    ADC_InitStructure.ADC_ScanDirection = ADC_ScanDirection_Upward;

    ADC_Init(ADC1, &ADC_InitStructure);

    ADC_OverrunModeCmd(ADC1, ENABLE); //数据覆盖方式，只保留最新的转换数据

    ADC_ChannelConfig(ADC1, ADC_Channel_5, ADC_SampleTime_239_5Cycles);
    ADC_ChannelConfig(ADC1, ADC_Channel_6, ADC_SampleTime_239_5Cycles);
	/* ADC_Channel7 - VBUS */
    ADC_ChannelConfig(ADC1, ADC_Channel_7, ADC_SampleTime_239_5Cycles);
	
	/* ADC_Channel8 - W_Current ADC_Channel9 - V_Current*/
	ADC_ChannelConfig(ADC1, ADC_Channel_8, ADC_SampleTime_239_5Cycles);
	ADC_ChannelConfig(ADC1, ADC_Channel_9, ADC_SampleTime_239_5Cycles);

    ADC_GetCalibrationFactor(ADC1);




    ADC_Cmd(ADC1, ENABLE);

    while(ADC_GetFlagStatus(ADC1, ADC_FLAG_ADEN) == RESET); /* 等待ADC准备好 */

    ADC_DMACmd(ADC1, ENABLE);
    
    ADC_DMARequestModeConfig(ADC1, ADC_DMAMode_Circular);


    ADC_StartOfConversion(ADC1);
 
  
}

void ADC1_DMA_Init(void)
{
    DMA_InitTypeDef   DMA_InitStructure;

    NVIC_InitTypeDef  NVIC_InitStructure;

    RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1, ENABLE);

    DMA_DeInit(DMA1_Channel1);

    DMA_InitStructure.DMA_PeripheralBaseAddr = (uint32_t)ADC1_DR_Address;

    DMA_InitStructure.DMA_MemoryBaseAddr = (uint32_t)&ADC_ConvData;

    DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralSRC;

    DMA_InitStructure.DMA_BufferSize = 5;

    DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;

    DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;

    DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_HalfWord;

    DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_HalfWord;

    DMA_InitStructure.DMA_Mode = DMA_Mode_Circular;

    DMA_InitStructure.DMA_Priority = DMA_Priority_High;

    DMA_InitStructure.DMA_M2M = DMA_M2M_Disable;

    DMA_Init(DMA1_Channel1, &DMA_InitStructure);



    DMA_ClearITPendingBit(DMA1_IT_TC1);
    
    DMA_ClearFlag(DMA1_FLAG_TC1);

    DMA_ITConfig(DMA1_Channel1, DMA1_IT_TC1, ENABLE);

    DMA_Cmd(DMA1_Channel1, ENABLE);

    NVIC_InitStructure.NVIC_IRQChannel = DMA1_Channel1_IRQn;


    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;

    NVIC_InitStructure.NVIC_IRQChannelPriority = 3;

    NVIC_Init(&NVIC_InitStructure);
}




#if 0


void ADC1_Init(void)
{
    ADC_InitTypeDef     ADC_InitStructure;

    NVIC_InitTypeDef  NVIC_InitStructure;

    ADC_JitterCmd(ADC1, ADC_JitterOff_PCLKDiv4, ENABLE);

    RCC_ADCCLKConfig(RCC_ADCCLK_PCLK_Div4);

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1, ENABLE);

    ADC_DeInit(ADC1);

    ADC_StructInit(&ADC_InitStructure);

    ADC_InitStructure.ADC_Resolution = ADC_Resolution_12b;

    ADC_InitStructure.ADC_ContinuousConvMode = DISABLE;

    ADC_InitStructure.ADC_ExternalTrigConvEdge = ADC_ExternalTrigConvEdge_Falling;

    ADC_InitStructure.ADC_ExternalTrigConv =  ADC_ExternalTrigConv_T1_CC4;

    ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;

    ADC_InitStructure.ADC_ScanDirection = ADC_ScanDirection_Backward;

    ADC_Init(ADC1, &ADC_InitStructure);

    ADC1->CHSELR = ADC_CHSELR_CONFIG_U;	            //ADC channel Set																	//根据当前开通相限去切换此值		2.4us启动时间		  28.5 + 12.5 = 3.41us

    ADC1->SMPR =  0x00000003;                       // ADC SPEED SET

    ADC_ITConfig(ADC1, ADC_IT_EOC, DISABLE);

    ADC_GetCalibrationFactor(ADC1);

    NVIC_InitStructure.NVIC_IRQChannel = ADC1_COMP_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPriority = 1;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);
    ADC_Cmd(ADC1, ENABLE);

    while(!ADC_GetFlagStatus(ADC1, ADC_FLAG_ADRDY));

    ADC_StartOfConversion(ADC1);

    //ADC_ITConfig(ADC1, ADC_IT_EOC, ENABLE);

    //AD_IT_Counter = 0;


}


void ADC_ISR(void)
{


    if(AD_IT_Counter == 0)
    {


        Motor.BEFM_Voltage = ADC1->DR;

        AD_IT_Counter = 1;

    }
    else if(AD_IT_Counter == 1)
    {


        Motor.Current =  ADC1->DR;

        AD_IT_Counter = 2;

    }
    else if(AD_IT_Counter == 2)
    {


        Motor.Bus_Voltage = ADC1->DR;

        AD_IT_Counter = 0;

        if(Motor.BEMF_Check_Flag == 1)
        {

            if(Motor.BEMF_Avoid_Flag == 1)
            {

                if(Avoid_Counter < Motor.Avoid_Plus_Count)  
                {

                    Avoid_Counter++;
                }
                else
                {
                    Avoid_Counter = 0;

                    Motor.BEMF_Check_Success_Flag = 0;
                    Motor.BEMF_Avoid_Flag = 0;
                }


            }
            else
            {

                if(Motor.BEMF_Check_Success_Flag == 0)
                {

                    Bemf_Temp = (2 * Motor.BEFM_Voltage) +200 ;
                   
                    

                
                    if(Bemf_Temp >=Motor.Bus_Voltage )
                    {

                       
                        Motor.Boot = 0;
                        
                        Motor.In_Loop_Flag = 1;

                        Motor.BEMF_Check_Success_Flag = 1;

                    }
                }

            }


        }



    }



}

#endif




void Sort_Data(uint * ad_buf, uchar n)
{
    uchar j, k;
    uint temp;
    for(j = 0; j < (n - 1); j++)
    {
        for(k = 0; k < (n - 1 - j); k++)
        {
            if(ad_buf[k] < ad_buf[k + 1])
            {
                temp = ad_buf[k];
                ad_buf[k] = ad_buf[k + 1];
                ad_buf[k + 1] = temp;
            }
        }
    }
}

uint32_t Average_Data(uint16_t * ad_buf, uint8_t n)
{
    uint16_t i;

    uint32_t temp = 0;

    //temp = 0;

    for(i = 1; i < (n - 1) ; i++)
    {
        temp = (temp + (ad_buf[i]));

    }

    temp = ((temp * 100) / 8);

   

    return temp; 
}

uint32 Filter(uint32 new_data, uint32 old_data, uint k)
{
    int32 result;

    if(new_data < old_data)
    {
        result = old_data - new_data;
        result = result * k;
        result = result + 128;
        result = result / 256;
        result = old_data - result;

    }
    else if(new_data > old_data)
    {
        result = new_data - old_data;
        result = result * k;
        result = result + 128;
        result = result / 256;
        result = old_data + result;

    }
    else
    {

        result = old_data;

    }
    return  result;

}


uint32_t Get_Sample_Average(uint16_t * buf, uint8_t num)
{
    uint8_t count, i, j;
    uint16_t value_buf[10] = {0};
    uint32_t sum = 0;
    uint16_t temp;

    for(count = 0 ; count < num ; count++)
    {
        value_buf[count] = buf[count];
    }
    for(j = 0 ; j < num - 1 ; j++)
    {
        for(i = 0 ; i < num - 1 - j ; i++)
        {
            if(value_buf[i] > value_buf[i + 1])
            {
                temp = value_buf[i];
                value_buf[i] = value_buf[i + 1] ;
                value_buf[i + 1] = temp;
            }
        }
    }
    for(count = 1 ; count < num - 1 ; count++)
    {
        sum += value_buf[count] ;
    }
    return (uint16_t)(sum * 1000 / 8);
}



#if 0
void ADC_Config(void)  // ADC + DMA OK
{

    ADC_InitTypeDef     ADC_InitStructure;

    ADC_JitterCmd(ADC1, ADC_JitterOff_PCLKDiv4, ENABLE)

    RCC_ADCCLKConfig(RCC_ADCCLK_PCLK_Div4);

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1, ENABLE);

    ADC_DeInit(ADC1);

    ADC_StructInit(&ADC_InitStructure);


    ADC_InitStructure.ADC_Resolution = ADC_Resolution_12b;

    ADC_InitStructure.ADC_ContinuousConvMode = ENABLE;

    ADC_InitStructure.ADC_ExternalTrigConvEdge = ADC_ExternalTrigConvEdge_None;

    ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;

    ADC_InitStructure.ADC_ScanDirection = ADC_ScanDirection_Upward;

    ADC_Init(ADC1, &ADC_InitStructure);

    ADC_ChannelConfig(ADC1, ADC_Channel_0 | ADC_Channel_1 | ADC_Channel_4 | ADC_Channel_5 | ADC_Channel_9, ADC_SampleTime_7_5Cycles);


    ADC_GetCalibrationFactor(ADC1);

    DMA_Cmd(DMA1_Channel1, ENABLE);

    ADC_DMACmd(ADC1, ENABLE);

    ADC_Cmd(ADC1, ENABLE);

    ADC_StartOfConversion(ADC1);


}

void ADC1_DMA_Init(void)
{
    DMA_InitTypeDef   DMA_InitStructure;

    NVIC_InitTypeDef  NVIC_InitStructure;

    RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1, ENABLE);                          

    DMA_DeInit(DMA1_Channel1);                                                 

    DMA_InitStructure.DMA_PeripheralBaseAddr = (uint32_t)ADC1_DR_Address;      

    DMA_InitStructure.DMA_MemoryBaseAddr = (uint32_t)&ADC_ConvData;             

    DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralSRC;                         

    DMA_InitStructure.DMA_BufferSize = 5;                                      

    DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;           

    DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;                     

    DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_HalfWord; 

    DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_HalfWord;         

    DMA_InitStructure.DMA_Mode = DMA_Mode_Circular;                            

    DMA_InitStructure.DMA_Priority = DMA_Priority_High;                        

    DMA_InitStructure.DMA_M2M = DMA_M2M_Disable;                               

    DMA_Init(DMA1_Channel1, &DMA_InitStructure);                              

    ADC_DMARequestModeConfig(ADC1, ADC_DMAMode_Circular);

    DMA_ClearITPendingBit(DMA1_IT_TC1);                                         


    DMA_ITConfig(DMA1_Channel1, DMA1_IT_TC1, ENABLE);                           


    NVIC_InitStructure.NVIC_IRQChannel = DMA1_Channel1_IRQn;                    


    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;                              

    NVIC_InitStructure.NVIC_IRQChannelPriority = 3;                             


    NVIC_Init(&NVIC_InitStructure);                                             

}

#endif







