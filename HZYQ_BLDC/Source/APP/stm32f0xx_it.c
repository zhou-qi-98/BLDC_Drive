#include "stm32f0xx.h"
#include "timer.h"
#include "typedef.h"
#include "adc.h"
#include "var.h"

#include "stm32f0xx_usart.h"
#include "stm32f0xx_tim.h"
#include "stm32f0xx_dma.h"
#include "stm32f0xx_exti.h"
#include "usart.h"
#include "motor.h"
#include "iwdg.h"
#include "bsp.h"
#include "control.h"
#include "protect.h"

void NMI_Handler(void)
{


}


void HardFault_Handler(void)
{

    while(1)
    {


    }


}


void SVC_Handler(void)
{
}


void PendSV_Handler(void)
{
}


void SysTick_Handler(void)
{

}



void TIM1_CC_IRQHandler(void)
{

    if(TIM_GetITStatus(TIM1, TIM_IT_CC4) != RESET)
    {

        TIM_ClearITPendingBit(TIM1, TIM_IT_CC4);
				
				Read_Holl_Speed();
		


		
				/*	电机启动状态，停止状态不执行 */
				if(BLDC_Motor.B_Status == Start_status)
				{
					/*	电机PID状态，其他状态不执行 */
					if(ES_Struct.PID_Flag == Pidopen_Status)
					{
						ES_Struct.PID_Eliminate++;
						if(ES_Struct.PID_Eliminate > 50)
						{
							ES_Struct.PID_Eliminate = 0;
							
							ES_Struct.PID_Dat = PID_Function(Motor_St.Desire_Speed,Motor_St.Measure_Speed);

							Motor_St.Pwm += ES_Struct.PID_Dat;
							if(Motor_St.Pwm > 2800)
							{
								Motor_St.Pwm = 2800;
							}
							else if(Motor_St.Pwm < 200)
							{
								Motor_St.Pwm = 200;
							}
						}
					}
				}					
    }

}

void TIM3_IRQHandler(void)
{
    if(TIM_GetITStatus(TIM3, TIM_IT_Update) != RESET)
    {

        TIM_ClearITPendingBit(TIM3, TIM_IT_Update);


    }


}

void TIM14_IRQHandler(void)
{
    if(TIM_GetITStatus(TIM14, TIM_IT_Update) != RESET)
    {
        TIM_ClearITPendingBit(TIM14, TIM_IT_Update);

        TIM14_ISR();
    }


}

void TIM15_IRQHandler(void)
{

    if(TIM_GetFlagStatus(TIM15, TIM_IT_Update) != RESET)
    {
        TIM_ClearFlag(TIM15, TIM_IT_Update);
    }


}

void TIM16_IRQHandler(void)
{
    if(TIM_GetITStatus(TIM16, TIM_IT_Update) != RESET)
    {
        TIM_ClearITPendingBit(TIM16, TIM_IT_Update);

        TIM16_ISR();
    }


}

void TIM17_IRQHandler(void)
{

    if(TIM_GetITStatus(TIM17, TIM_IT_Update) != RESET)
    {
        TIM_ClearITPendingBit(TIM17, TIM_IT_Update);

        TIM17_ISR();


    }


}

void ADC1_IRQHandler(void)
{

    if(ADC_GetITStatus(ADC1, ADC_IT_EOC) != RESET)
    {
        ADC_ClearITPendingBit(ADC1, ADC_IT_EOC);

//        ADC_ISR();

    }

}


void DMA1_Channel1_IRQHandler(void)
{
    if(DMA_GetITStatus(DMA1_FLAG_TC1) != RESET)
    {

				DMA_ClearITPendingBit(DMA1_FLAG_TC1);

				//PID速度算法补偿
//				Motor_St.Desire_Speed = ADC_ConvData[0] * (-1.22) + 2304.2;
//				Motor_St.Desire_Speed = ADC_ConvData[0] * (-1.1) + 2048;
				Motor_St.Desire_Speed = ADC_ConvData[0] * (-0.714) + 1305.28;
//				Motor_St.Desire_Speed = ADC_ConvData[0] * (-1) + 1780;
				Sys_Protect.Voltage = ADC_ConvData[2];
				Sys_Protect.W_Current = ADC_ConvData[3];
				Sys_Protect.V_Current = ADC_ConvData[4];

    }

}

void DMA1_Channel2_3_IRQHandler(void)
{
    if(DMA_GetFlagStatus(DMA_IT_TC) != RESET)
    {




    }



}



void DMA1_Channel4_5_IRQHandler(void)
{
    if(DMA_GetITStatus(DMA1_IT_TC4) != RESET)
    {
        //Com2.Tx_IDLE = 0;
        //DMA_ITConfig(DMA1_Channel4,DMA_IT_TC,DISABLE);
        //DMA_Cmd(DMA1_Channel4,DISABLE);
        //DMA_ClearITPendingBit(DMA1_IT_TC4);
    }
    if(DMA_GetFlagStatus(DMA1_IT_TC4) != RESET)
    {
        //Com2.Tx_IDLE = 0;

    }
}

void USART1_IRQHandler(void)
{
    if(USART_GetITStatus(USART1, USART_IT_IDLE) != RESET)
    {
        Usart1_Isr();
        USART_ClearITPendingBit(USART1, USART_IT_IDLE);
    }

}

void USART2_IRQHandler(void)
{
    if(USART_GetITStatus(USART2, USART_IT_IDLE) != RESET)
    {
        //Usart2_Isr();
        //USART_ClearITPendingBit(USART2,USART_IT_IDLE);
    }
}



void EXTI4_15_IRQHandler(void)
{

}

#if 0
void EXTI2_3_IRQHandler(void)
{


    if(EXTI_GetITStatus(EXTI_Line3) != RESET)
    {

        LED_Counter++;


        EXTI_ClearFlag(EXTI_Line3);

    }






}

#endif











