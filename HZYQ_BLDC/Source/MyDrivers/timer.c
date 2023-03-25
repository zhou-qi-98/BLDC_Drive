
#include "timer.h"


uint16_t		Delay_Time = 0;

uint16_t		ms1, s1, ms2, s2;

uint16_t		Ms100;

uint16_t		T14_Counter;

uint32_t		T17_Count;

uint16_t        LED_Duty;


void Delay_Ms(uint16_t delay_ms)
{

    Delay_Time = delay_ms;

    while(Delay_Time);

}


void TIM1_PWM_Init(void) // NMOS Bridge PWM OutPut  without cc4 interrupt
{


    TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
    TIM_OCInitTypeDef TIM_OCInitStructure;

    TIM_BDTRInitTypeDef TIM1_BDTRInitStruct;

    NVIC_InitTypeDef NVIC_InitStructure;

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1, ENABLE);


    TIM_TimeBaseInitStructure.TIM_Prescaler = 0;	// 48000000/ (1+1) = 24000000 HZ

    TIM_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up;

    TIM_TimeBaseInitStructure.TIM_Period = PWM_TIM_PULSE; // 24000000/ (8000)  =  2000 HZ

    TIM_TimeBaseInitStructure.TIM_ClockDivision = TIM_CKD_DIV1;

    TIM_TimeBaseInitStructure.TIM_RepetitionCounter = 0;

    TIM_TimeBaseInit(TIM1, &TIM_TimeBaseInitStructure);


    TIM1_BDTRInitStruct.TIM_OSSRState = TIM_OSSRState_Disable;

    TIM1_BDTRInitStruct.TIM_OSSIState = TIM_OSSIState_Disable;

    TIM1_BDTRInitStruct.TIM_LOCKLevel = TIM_LOCKLevel_1;

    TIM1_BDTRInitStruct.TIM_DeadTime = 60;

    TIM1_BDTRInitStruct.TIM_Break = TIM_Break_Disable;

    TIM1_BDTRInitStruct.TIM_BreakPolarity = TIM_BreakPolarity_Low;

    TIM1_BDTRInitStruct.TIM_AutomaticOutput = TIM_AutomaticOutput_Disable;

    TIM_BDTRConfig(TIM1, &TIM1_BDTRInitStruct);


    TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;

    TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;

    TIM_OCInitStructure.TIM_OutputNState = TIM_OutputNState_Enable;

    TIM_OCInitStructure.TIM_Pulse = 0;


    TIM_OCInitStructure.TIM_OCPolarity = TIM_OCNPolarity_High;

    TIM_OCInitStructure.TIM_OCNPolarity = TIM_OCNPolarity_High;

    TIM_OCInitStructure.TIM_OCIdleState = TIM_OCIdleState_Set;

    TIM_OCInitStructure.TIM_OCNIdleState = TIM_OCIdleState_Set;

    TIM_OC1Init(TIM1, &TIM_OCInitStructure);
   
    TIM_OC2Init(TIM1, &TIM_OCInitStructure);

    TIM_OC3Init(TIM1, &TIM_OCInitStructure);

    TIM_OCInitStructure.TIM_Pulse = 240;

    TIM_OCInitStructure.TIM_OutputNState = TIM_OutputNState_Disable;

    TIM_OC4Init(TIM1, &TIM_OCInitStructure);
    
    TIM_SelectOutputTrigger(TIM1, TIM_TRGOSource_Update); 

    TIM_ITConfig(TIM1, TIM_IT_CC4, ENABLE);

    NVIC_InitStructure.NVIC_IRQChannel = TIM1_CC_IRQn;

    NVIC_InitStructure.NVIC_IRQChannelPriority = 1;

    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;

    NVIC_Init(&NVIC_InitStructure);



    TIM_Cmd(TIM1, ENABLE);


    TIM_CtrlPWMOutputs(TIM1, ENABLE);


}



void TIM14_Init(void) // Motor Start Timer	0.5ms INT
{

    TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
//    NVIC_InitTypeDef NVIC_InitStructure;

    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM14, ENABLE);
    TIM_TimeBaseInitStructure.TIM_Prescaler = 24;
    TIM_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up;
    TIM_TimeBaseInitStructure.TIM_Period = 0xffff;
    TIM_TimeBaseInitStructure.TIM_ClockDivision = TIM_CKD_DIV1;
    TIM_TimeBaseInit(TIM14, &TIM_TimeBaseInitStructure);

//    NVIC_InitStructure.NVIC_IRQChannel = TIM14_IRQn;
//    NVIC_InitStructure.NVIC_IRQChannelPriority = 3;
//    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
//    NVIC_Init(&NVIC_InitStructure);

//    TIM_ITConfig(TIM14, TIM_IT_Update, ENABLE);

	
		TIM14->CNT = 0;
    TIM_Cmd(TIM14, ENABLE);

}


void TIM14_ISR(void)
{


}

void TIM15_Init(void)
{
    TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM15, ENABLE); //open TIM3 clock.

    TIM_TimeBaseInitStructure.TIM_Prescaler = 4799; //48000000 /(4799 + 1) = 10000. 1Ms.

    TIM_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up;

    TIM_TimeBaseInitStructure.TIM_Period = 9;

    TIM_TimeBaseInitStructure.TIM_ClockDivision = TIM_CKD_DIV1;

    TIM_TimeBaseInitStructure.TIM_RepetitionCounter = 0;

    TIM_TimeBaseInit(TIM15, &TIM_TimeBaseInitStructure);
		TIM_SelectOutputTrigger(TIM15,TIM_TRGOSource_Update);//TIM15的Update事件作为外部TRGO
	
		TIM_ClearFlag(TIM15,TIM_FLAG_Update);
		
		TIM_Cmd(TIM15, ENABLE);
	
}



void TIM6_Init(void) // Caulate 60 angel;
{


    TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;

    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM6, ENABLE);

    TIM_TimeBaseInitStructure.TIM_Prescaler = 47;

    TIM_TimeBaseInitStructure.TIM_Period = 0xFFFF;

    TIM_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up;

    TIM_TimeBaseInitStructure.TIM_ClockDivision = TIM_CKD_DIV1;

    TIM_TimeBaseInitStructure.TIM_RepetitionCounter = 0;

    TIM_TimeBaseInit(TIM6, &TIM_TimeBaseInitStructure);

    TIM_Cmd(TIM6, ENABLE);


}


void TIM17_Init(void) // Switch Motor Phase
{


    TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;

    NVIC_InitTypeDef NVIC_InitStructure;

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM17, ENABLE); //open TIM3 clock.

    TIM_TimeBaseInitStructure.TIM_Prescaler = 47;	//48000000 /(4799 + 1) = 10000Hz. 1Ms.

    TIM_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up;

    TIM_TimeBaseInitStructure.TIM_Period = 0;

    TIM_TimeBaseInitStructure.TIM_ClockDivision = TIM_CKD_DIV1;

    TIM_TimeBaseInitStructure.TIM_RepetitionCounter = 0;

    TIM_TimeBaseInit(TIM17, &TIM_TimeBaseInitStructure);

    NVIC_InitStructure.NVIC_IRQChannel = TIM17_IRQn;

    NVIC_InitStructure.NVIC_IRQChannelPriority = 2;

    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;

    NVIC_Init(&NVIC_InitStructure);

    TIM_ClearITPendingBit(TIM17, TIM_IT_Update);

    TIM_ITConfig(TIM17, TIM_IT_Update, ENABLE);

    TIM_Cmd(TIM17, ENABLE);




}


void TIM17_ISR(void)
{

}







void TIM16_Init(void) // System 1ms Timer
{



    TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;

    NVIC_InitTypeDef NVIC_InitStructure;

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM16, ENABLE); //open TIM3 clock.

    TIM_TimeBaseInitStructure.TIM_Prescaler = 4799; //48000000 /(4799 + 1) = 10000Hz. 1Ms.

    TIM_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up;

    TIM_TimeBaseInitStructure.TIM_Period = 9;

    TIM_TimeBaseInitStructure.TIM_ClockDivision = TIM_CKD_DIV1;

    TIM_TimeBaseInitStructure.TIM_RepetitionCounter = 0;

    TIM_TimeBaseInit(TIM16, &TIM_TimeBaseInitStructure);

    NVIC_InitStructure.NVIC_IRQChannel = TIM16_IRQn;

    NVIC_InitStructure.NVIC_IRQChannelPriority = 0;

    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;

    NVIC_Init(&NVIC_InitStructure);

    TIM_ITConfig(TIM16, TIM_IT_Update, ENABLE);

    TIM_Cmd(TIM16, ENABLE);

}


void TIM3_PWM_Init(void) // PWM DAC OutPut
{


    TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
    TIM_OCInitTypeDef TIM_OCInitStructure;
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);


    TIM_TimeBaseInitStructure.TIM_Prescaler = 0;  // 8000000/ (1+1) = 4000000 HZ
    TIM_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up;

    TIM_TimeBaseInitStructure.TIM_Period = 2399;   // 4000000/ (4999+1)  =  800 HZ
    TIM_TimeBaseInitStructure.TIM_ClockDivision = TIM_CKD_DIV1;
    TIM_TimeBaseInitStructure.TIM_RepetitionCounter = 0;
    TIM_TimeBaseInit(TIM3, &TIM_TimeBaseInitStructure);

    TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1 ;
    TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
    TIM_OCInitStructure.TIM_OutputNState = TIM_OutputNState_Disable;
    TIM_OCInitStructure.TIM_OCPolarity = TIM_OCNPolarity_High;
    TIM_OCInitStructure.TIM_OCNPolarity = TIM_OCNPolarity_Low;
    TIM_OCInitStructure.TIM_OCIdleState = TIM_OCIdleState_Set;
    TIM_OCInitStructure.TIM_OCNIdleState = TIM_OCNIdleState_Reset;
    TIM_OCInitStructure.TIM_Pulse = 0 ;

    TIM_OC2Init(TIM3, &TIM_OCInitStructure);

    TIM_Cmd(TIM3, ENABLE);

    TIM_CtrlPWMOutputs(TIM3, ENABLE);
		
    TIM3->CCR2 = 1200;



}


uint16_t Stop_Delay = 0;


void TIM16_ISR(void)
{

    Delay_Time--;

    Ms100++;

    if(Ms100 >= 2000)
    {

        Ms100 = 0;

    }
		
		Feed_Dog();

		Motor_St.Brake_Delay++;
		
		Motor_St.Fstart_Timer++;//初次启动的计时
		Motor_St.St_Timer++;
}







void TIM_Channel_1_PWM_ALL_Stop(void)
{

    TIM1->CCER			&= ~(1 << 0);
    TIM1->CCER			&= ~(1 << 2);

}


void TIM_Channel_1_PWM_P_OutPut(void)
{

    TIM1->CCER			|= (1 << 0);
    TIM1->CCER			&= ~(1 << 2);

}


void TIM_Channel_1_PWM_N_OutPut(void)
{

    TIM1->CCER			&= ~(1 << 0);
    TIM1->CCER			|= (1 << 2);

}


void TIM_Channel_1_PWM_All_OutPut(void)
{

    TIM1->CCER			|= (1 << 0);
    TIM1->CCER			|= (1 << 2);

}


void TIM_Channel_2_PWM_ALL_Stop(void)
{

    TIM1->CCER			&= ~(1 << 4);
    TIM1->CCER			&= ~(1 << 6);


}


void TIM_Channel_2_PWM_P_OutPut(void)
{

    TIM1->CCER			|= (1 << 4);
    TIM1->CCER			&= ~(1 << 6);


}


void TIM_Channel_2_PWM_N_OutPut(void)
{

    TIM1->CCER			&= ~(1 << 4);
    TIM1->CCER			|= (1 << 6);

}


void TIM_Channel_2_PWM_All_OutPut(void)
{

    TIM1->CCER			|= (1 << 4);
    TIM1->CCER			|= (1 << 6);

}




void TIM_Channel_3_PWM_ALL_Stop(void)
{

    TIM1->CCER			&= ~(1 << 8);
    TIM1->CCER			&= ~(1 << 10);


}


void TIM_Channel_3_PWM_P_OutPut(void)
{

    TIM1->CCER			|= (1 << 8);
    TIM1->CCER			&= ~(1 << 10);


}


void TIM_Channel_3_PWM_N_OutPut(void)
{

    TIM1->CCER			&= ~(1 << 8);
    TIM1->CCER			|= (1 << 10);

}


void TIM_Channel_3_PWM_All_OutPut(void)
{

    TIM1->CCER			|= (1 << 8);
    TIM1->CCER			|= (1 << 10);

}


void Timer_Init(void)
{

    TIM1_PWM_Init();
	
	TIM3_PWM_Init();

    TIM6_Init();
	
    TIM14_Init();
	
	TIM15_Init();
	
    TIM16_Init();

}


#if 0



void TIM14_ISR(void)
{
    if(Motor.Status == Runing)
    {

        if(Motor.Boot == 1)
        {

            T14_Counter++;

            if(T14_Counter >= Motor.Boot_Time_Base)  // 20
            {
                T14_Counter = 0;

                Motor.Angle_60_Time = TIM2->CNT;

                Hall_Step++;

                if(Hall_Step >= 6)
                {

                    Hall_Step = 0;

                }

                Motor.Hall = Hall_Table[Hall_Step];

                Motor_FWD_Run();

                Motor.Hall_Next = Find_Next_Step(Motor.Hall);

                TIM2->CNT = 0;



                Motor.Angle_30_Time = Motor.Angle_60_Time >> 1; // 计算30度角度时间

                Motor.Angle_30_Time = ((Motor.Angle_30_Time * 7 / 10) + (Motor.Last_Angle_30_Time * 3 / 10)); //30度角时间RC滤波

                Motor.Last_Angle_30_Time = Motor.Angle_30_Time;  // 30度时间迭代。

                Motor.Avoid_Plus_Count = (Motor.Angle_30_Time / 50) - 4; //反电动势采用时避开的PWM脉冲个数

                Accelerate_Counter++;             //强拖次数计数

                if(Accelerate_Counter >= 500)  // 20 * 50 * 5 = 5000 us = 5ms
                {
                    Accelerate_Counter = 0;
                    Motor.Run_PWM = 240;
                    Motor.Boot = 0;
                    Motor.BEMF_Check_Flag = 1;

                    


                }

            }

        }

    }


}

#endif
























