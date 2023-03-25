#include "stm32f0xx_gpio.h"
#include "stm32f0xx_tim.h"
#include "gpio.h"
#include "var.h"
#include "typedef.h"
#include "timer.h"
#include "motor.h"
#include "adc.h"

static void Motor_Stop(void);
static void Motor_Start(void);
static void BLDC_ReadyStart(void);
static void Motor_GetRunDeriction(void);
static void Motor_DerictionAdjsut(BLDC_Dircetion BLDC_Dir);
static void Motor_CW(void);
static void Motor_CCW(void);

tsMotor Motor_St;

BLDC_T BLDC_Motor = 
{
	Stop_status,
	Reverse_Status,
	
	Motor_Start,
	Motor_Stop,
	Motor_CW,
	Motor_CCW,
	Motor_GetRunDeriction,
	Motor_DerictionAdjsut,
	
};

/*
*********************************************************************************************************
*	@函 数 名: static void BLDC_ReadyStart(void)
*	@功能说明: 电机预启动
*	@形    参: None
*	@返 回 值: None
*********************************************************************************************************
*/
static void BLDC_ReadyStart(void)
{
	uint8_t Hu, Hv, Hw;
	
	/***电机启动前需要给自举电容充电***/
	/*三个上管不输出*/
	/*三个下管输出*/
	TIM_Channel_1_PWM_ALL_Stop();
	TIM_Channel_2_PWM_ALL_Stop();
	TIM_Channel_3_PWM_ALL_Stop();

	TIM_Channel_1_PWM_N_OutPut();  
	TIM_Channel_2_PWM_N_OutPut();
	TIM_Channel_3_PWM_N_OutPut();
	
	TIM1->CCR1 = PWM_TIM_PULSE;
	TIM1->CCR2 = PWM_TIM_PULSE;
	TIM1->CCR3 = PWM_TIM_PULSE;
	
	Delay_Ms(60);
	
	Motor_St.Pwm = MinDuty;
	
	/*	读取霍尔	*/ 
	Hu = GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_11);
	Hv = GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_12);
	Hw = GPIO_ReadInputDataBit(GPIOF, GPIO_Pin_6);

	//Motor_St.Motor_NowPosition = (Hu << 2) + (Hv << 1) + Hw;
	Motor_St.Motor_NowPosition = (Hw << 2) + (Hv << 1) + Hu;
	
	
}

/*
*********************************************************************************************************
*	@函 数 名: void Motor_Start(void)
*	@功能说明: 电机启动
*	@形    参: None
*	@返 回 值: None
*********************************************************************************************************
*/
static void Motor_Start(void)
{

	BLDC_ReadyStart();
	
	BLDC_Motor.Motor_Cw();
	
	Motor_St.Motor_OldPosition = Motor_St.Motor_NowPosition;
	
	BLDC_Motor.B_Status = Start_status;
	
}

/*
*********************************************************************************************************
*	@函 数 名: void Motor_Stop(void)
*	@功能说明: 电机停止
*	@形    参: None
*	@返 回 值: None
*********************************************************************************************************
*/
static void Motor_Stop(void)
{

	TIM_Channel_1_PWM_ALL_Stop();
	TIM_Channel_2_PWM_ALL_Stop();
	TIM_Channel_3_PWM_ALL_Stop();
	
	
	TIM1->CCR1 = 0;
	TIM1->CCR2 = 0;
	TIM1->CCR3 = 0;
	
	BLDC_Motor.B_Status = Stop_status;
	Motor_St.Pwm = MinDuty;//设置启动占空比
}

/*
*********************************************************************************************************
*	@函 数 名: void Motor_DerictionAdjsut(BLDC_Dircetion BLDC_Dir)
*	@功能说明: BLDC调整转动方向
*	@形    参: None
*	@返 回 值: None
*********************************************************************************************************
*/
static void Motor_DerictionAdjsut(BLDC_Dircetion BLDC_Dir)
{
	if(BLDC_Dir == Forward_Status)
	{
		BLDC_Motor.B_Direction = Forward_Status;
	}
	else
	{
		BLDC_Motor.B_Direction = Reverse_Status;
	}
}
/*
*********************************************************************************************************
*	@函 数 名: void Motor_GetRunDeriction(void)
*	@功能说明: BLDC获取电机运动方向
*	@形    参: None
*	@返 回 值: None
*********************************************************************************************************
*/
static void Motor_GetRunDeriction(void)
{
	if(BLDC_Motor.B_Direction == Forward_Status)
	{
		BLDC_Motor.Motor_Cw();
	}
	else
	{
		BLDC_Motor.Motor_CCw();
	}
}


/*
*********************************************************************************************************
*	@函 数 名: void Array_Sort(uint32_t *data, uint8_t len)
*	@功能说明: 数据数据从小到大排序
*	@形    参: *data-需要排序的数组数据 len-排序数据的长度
*	@返 回 值: None
*********************************************************************************************************
*/
void Array_Sort(uint32_t *data, uint8_t len)
{
	uint8_t i,j;
	
	uint32_t temp;
	for(i = 0; i < len; i++)
	{
		for(j = 0; j < len - 1 - i; j++)
		{
			if(*(data + j) > *(data +j + 1))
			{
				temp  = *(data + j);
				*(data + j) = *(data +j + 1);
				*(data +j + 1) = temp;
			}
		}
	}
}
uint8_t Phase_Count = 0;

uint8_t Phase_ChangeNum = 0;


/*
*********************************************************************************************************
*	@函 数 名: void Read_Holl_Speed(void)
*	@功能说明: 获取霍尔的速度和位置
*	@形    参: None
*	@返 回 值: None
*********************************************************************************************************
*/
void Read_Holl_Speed(void)
{
	uint8_t Hv,	Hu,	Hw;
	float MeasureTimer_60;//60度电角度所需的时间
	/*普通的IO口测量，不是中断方式，不准，需要读取10次数值，求平均*/
	static uint32_t Speed[10] = {0};//建立一个数组，放10次读取的数值
	static uint8_t  SpeedTimer = 0;
	static uint8_t LostPositionTimer = 0;//定义一个中间变量，判断电机是否停止

	Hu = GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_11);
	Hv = GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_12);
	Hw = GPIO_ReadInputDataBit(GPIOF, GPIO_Pin_6);
	
	//Motor_St.Motor_NowPosition = (Hu << 2) + (Hv << 1) + Hw;
	Motor_St.Motor_NowPosition = (Hw << 2) + (Hv << 1) + Hu;

	/*判断电机是否发生转动*/
	if(Motor_St.Motor_NowPosition != Motor_St.Motor_OldPosition)
	{
		//电机发生转动
		if(BLDC_Motor.B_Status == Start_status)
		{
			
				LostPositionTimer = 0;
				MeasureTimer_60 = TIM14->CNT;
				Speed[SpeedTimer++] = MeasureTimer_60;
				if(SpeedTimer >= 4)
				{
					SpeedTimer = 0;
					Array_Sort(Speed, 4);
					MeasureTimer_60 = (Speed[1] + Speed[2]) << 1;
					Motor_St.Measure_Speed = (unsigned int)(2500000 / MeasureTimer_60);
				}
				TIM14->CNT = 0;
			
			Phase_Count++;
			if(Phase_Count > Phase_ChangeNum)
			{

				Phase_Count = 0;
				BLDC_Motor.GetRunDeriction();
				Motor_St.Motor_OldPosition = Motor_St.Motor_NowPosition;	
			}		
				
			
		}
	}
}


 
static void Motor_CW(void)
{
	switch(Motor_St.Motor_NowPosition)
	{
        case 1: //C+ B-
            TIM_Channel_1_PWM_ALL_Stop();
            TIM_Channel_3_PWM_N_OutPut();
            TIM_Channel_2_PWM_All_OutPut();
				
            TIM1->CCR1 = Motor_St.Pwm;
            TIM1->CCR2 = Motor_St.Pwm;
            TIM1->CCR3 = PWM_TIM_PULSE;
            break;
        case 2: //B+ A-
            TIM_Channel_3_PWM_ALL_Stop();
            TIM_Channel_2_PWM_N_OutPut();
            TIM_Channel_1_PWM_All_OutPut();

            TIM1->CCR1 = Motor_St.Pwm;
            TIM1->CCR2 = PWM_TIM_PULSE;
            TIM1->CCR3 = Motor_St.Pwm;
            break;
        case 3: //C+ A-  
            TIM_Channel_2_PWM_ALL_Stop();
            TIM_Channel_3_PWM_N_OutPut();
            TIM_Channel_1_PWM_All_OutPut();

            TIM1->CCR1 = Motor_St.Pwm;
            TIM1->CCR2 = Motor_St.Pwm;
            TIM1->CCR3 = PWM_TIM_PULSE;
            break;
        case 4: //A+ C-
            TIM_Channel_2_PWM_ALL_Stop();
            TIM_Channel_1_PWM_N_OutPut();
            TIM_Channel_3_PWM_All_OutPut();
				
            TIM1->CCR1 = PWM_TIM_PULSE;
            TIM1->CCR2 = Motor_St.Pwm;
            TIM1->CCR3 = Motor_St.Pwm;
            break;
        case 5: //A+ B-
            TIM_Channel_3_PWM_ALL_Stop();
            TIM_Channel_1_PWM_N_OutPut();
            TIM_Channel_2_PWM_All_OutPut();

            TIM1->CCR1 = PWM_TIM_PULSE;
            TIM1->CCR2 = Motor_St.Pwm;
            TIM1->CCR3 = Motor_St.Pwm;
            break;
        case 6: //B+ C-
            TIM_Channel_1_PWM_ALL_Stop();
            TIM_Channel_2_PWM_N_OutPut();
            TIM_Channel_3_PWM_All_OutPut();

            TIM1->CCR1 = Motor_St.Pwm;
            TIM1->CCR2 = PWM_TIM_PULSE;
            TIM1->CCR3 = Motor_St.Pwm;
            break;
		default: break;
		
	}
}

static void Motor_CCW(void)
{
	switch(Motor_St.Motor_NowPosition)
	{
        case 1: //C+ B-
            TIM_Channel_1_PWM_ALL_Stop();
            TIM_Channel_2_PWM_N_OutPut();
            TIM_Channel_3_PWM_All_OutPut();

            TIM1->CCR1 = Motor_St.Pwm;
            TIM1->CCR2 = PWM_TIM_PULSE;
            TIM1->CCR3 = Motor_St.Pwm;
            break;
        case 2: //B+ A-
            TIM_Channel_3_PWM_ALL_Stop();
            TIM_Channel_1_PWM_N_OutPut();
            TIM_Channel_2_PWM_All_OutPut();

            TIM1->CCR1 = PWM_TIM_PULSE;
            TIM1->CCR2 = Motor_St.Pwm;
            TIM1->CCR3 = Motor_St.Pwm;
            break;
        case 3: //C+ A-  
            TIM_Channel_2_PWM_ALL_Stop();
            TIM_Channel_1_PWM_N_OutPut();
            TIM_Channel_3_PWM_All_OutPut();
				
            TIM1->CCR1 = PWM_TIM_PULSE;
            TIM1->CCR2 = Motor_St.Pwm;
            TIM1->CCR3 = Motor_St.Pwm;
            break;
        case 4: //A+ C-
            TIM_Channel_2_PWM_ALL_Stop();
            TIM_Channel_3_PWM_N_OutPut();
            TIM_Channel_1_PWM_All_OutPut();

            TIM1->CCR1 = Motor_St.Pwm;
            TIM1->CCR2 = Motor_St.Pwm;
            TIM1->CCR3 = PWM_TIM_PULSE;
            break;
        case 5: //A+ B-
            TIM_Channel_3_PWM_ALL_Stop();
            TIM_Channel_2_PWM_N_OutPut();
            TIM_Channel_1_PWM_All_OutPut();

            TIM1->CCR1 = Motor_St.Pwm;
            TIM1->CCR2 = PWM_TIM_PULSE;
            TIM1->CCR3 = Motor_St.Pwm;
            break;
        case 6: //B+ C-
            TIM_Channel_1_PWM_ALL_Stop();
            TIM_Channel_3_PWM_N_OutPut();
            TIM_Channel_2_PWM_All_OutPut();
				
            TIM1->CCR1 = Motor_St.Pwm;
            TIM1->CCR2 = Motor_St.Pwm;
            TIM1->CCR3 = PWM_TIM_PULSE;
            break;
		default: break;
		
	}
}















