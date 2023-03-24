#include "Motor.h"

/*
//order 用于发波的标号
void Motor_run(uint8_t order,uint8_t Duty)
{
	switch(order)
	{
		//U0  V+ W-
		case 1:
		{
			HAL_TIM_PWM_Stop(&htim1,TIM_CHANNEL_1);//U相不发波
			HAL_TIMEx_PWMN_Stop(&htim1,TIM_CHANNEL_1);
			
			TIM1->CCR2 = ((float)Duty/(float)100)*70;//修改占空比
			HAL_TIM_PWM_Start(&htim1,TIM_CHANNEL_2);//V相正波
			
			TIM1->CCR3 = ((float)Duty/(float)100)*70;//50%的占空比
			HAL_TIMEx_PWMN_Start(&htim1,TIM_CHANNEL_3);//W相互补波
			break;	
		}
		
		case 3:
		{
			HAL_TIM_PWM_Stop(&htim1,TIM_CHANNEL_2);//v相不发波
			HAL_TIMEx_PWMN_Stop(&htim1,TIM_CHANNEL_2);
			
			TIM1->CCR1 = ((float)Duty/(float)100)*70;//修改占空比
			HAL_TIMEx_PWMN_Start(&htim1,TIM_CHANNEL_1);//V相互补波
			
			TIM1->CCR3 = ((float)Duty/(float)100)*70;//50%的占空比
			HAL_TIM_PWM_Start(&htim1,TIM_CHANNEL_3);//W相正波
			break;	
		}
		
		case 2:
		{
			HAL_TIM_PWM_Stop(&htim1,TIM_CHANNEL_3);//W相不发波
			HAL_TIMEx_PWMN_Stop(&htim1,TIM_CHANNEL_3);
			
			TIM1->CCR1 = ((float)Duty/(float)100)*70;//修改占空比
			HAL_TIMEx_PWMN_Start(&htim1,TIM_CHANNEL_1);//U相互补波
			
			TIM1->CCR2 = ((float)Duty/(float)100)*70;//50%的占空比
			HAL_TIM_PWM_Start(&htim1,TIM_CHANNEL_2);//V相正波
			break;	
		}
		case 6:
		{
			HAL_TIM_PWM_Stop(&htim1,TIM_CHANNEL_1);//U相不发波
			HAL_TIMEx_PWMN_Stop(&htim1,TIM_CHANNEL_1);
			
			TIM1->CCR3 = ((float)Duty/(float)100)*70;//修改占空比
			HAL_TIMEx_PWMN_Start(&htim1,TIM_CHANNEL_3);//U相互补波
			
			TIM1->CCR2 = ((float)Duty/(float)100)*70;//修改占空比
			HAL_TIM_PWM_Start(&htim1,TIM_CHANNEL_2);//V相正波
			break;	
		}
		case 4:
		{
			HAL_TIM_PWM_Stop(&htim1,TIM_CHANNEL_2);//V相不发波
			HAL_TIMEx_PWMN_Stop(&htim1,TIM_CHANNEL_2);
			
			TIM1->CCR3 = ((float)Duty/(float)100)*70;//修改占空比
			HAL_TIMEx_PWMN_Start(&htim1,TIM_CHANNEL_3);//W相互补波
			
			TIM1->CCR1 = ((float)Duty/(float)100)*70;//修改占空比
			HAL_TIM_PWM_Start(&htim1,TIM_CHANNEL_1);//U相正波
			break;	
		}
		case 5:
		{
			HAL_TIM_PWM_Stop(&htim1,TIM_CHANNEL_3);//W相不发波
			HAL_TIMEx_PWMN_Stop(&htim1,TIM_CHANNEL_3);
			
			TIM1->CCR2 = ((float)Duty/(float)100)*70;//修改占空比
			HAL_TIMEx_PWMN_Start(&htim1,TIM_CHANNEL_2);//V相互补波
			
			TIM1->CCR1 = ((float)Duty/(float)100)*70;//修改占空比
			HAL_TIM_PWM_Start(&htim1,TIM_CHANNEL_1);//V相正波
			break;	
		}
		default:break;
	}
}

*/
// 120 度HAL,如果你的电机直接用这个表驱动有问，那你可能需要根据
// 实际电机进行适当的调整对应关系，可在该表基础上进行适当修改即可
// 正 转
// 霍尔#1 霍尔#2 霍尔#3		A+ 		A- 		 B+ 		B- 		C+ 		C- 		方向
// 1 				0 		1 		关闭 		关闭 	关闭 	开通 	开通 		关闭 		↓   
// 0 				0 		1 		关闭 		开通 	关闭 	关闭 	开通 		关闭 		↓		
// 0 				1 		1 		关闭 		开通 	开通 	关闭 	关闭 		关闭 		↓			
// 0 				1 		0 		关闭 		关闭 	开通 	关闭 	关闭 		开通 		↓
// 1 				1 		0 		开通 		关闭 	关闭 	关闭 	关闭 		开通 		↓
// 1 				0 		0 		开通 		关闭 	关闭 	开通 	关闭 		关闭 		↓

// 反 转
// 霍尔#1 霍尔#2 霍尔#3 	A+ 		A- 			B+ 		B- 		C+ 		C- 		方向
// 1 				0 		1 		关闭 		关闭 	开通 	关闭 	关闭 		开通 		↑
// 0 				0 		1 		开通 		关闭 	关闭 	关闭 	关闭 		开通 		↑
// 0 				1 		1 		开通 		关闭 	关闭 	开通 	关闭 		关闭 		↑
// 0 				1 		0 		关闭 		关闭 	关闭 	开通 	开通 		关闭 		↑
// 1 				1 		0 		关闭 		开通 	关闭 	关闭 	开通 		关闭 		↑
// 1 				0 		0 		关闭 		开通 	开通 	关闭 	关闭 		关闭 		↑



/*
电机停机
*/
void Motor_Stop()
{
	//关三个上管，开三个下管，泄除反电动势
	
	//1.关上管
	UH_OFF;VH_OFF;WH_OFF;
	HAL_Delay(1);//延时下，防止上管未完全关闭 就导通下管，烧毁MOS
	//2.开下管
	UL_ON;VL_ON;WL_ON;	
}



/*
电机转子预定位
direction:转动方向，根据转动方向来进行调整
做三次预定位，确定转子定位到准确位置
*/
void ROTOR_Pre_positioning(uint8_t direction)
{
	if(direction)//正转
	{
			//1.开始做预定位
		for(uint8_t i = 0;i<3;i++)
		{
			UH_ON;VH_OFF;WH_OFF;//U+ W-
			UL_OFF;VL_OFF;WL_ON;
			HAL_Delay(10);
		}
			//此时转自应该在位置6	
	}
}


void Six_step(uint8_t step)
{
	switch(step)
	{
		case 1:
		{
			UH_ON;VH_OFF;WH_OFF;//U+ V-
			UL_OFF;VL_ON;WL_OFF;
			break;
		}
		case 2:
		{
			UH_OFF;VH_OFF;WH_ON;//V- W+
			UL_OFF;VL_ON;WL_OFF;
			break;
		}
		case 3:
		{
			UH_OFF;VH_ON;WH_OFF;//U- V+
			UL_ON;VL_OFF;WL_OFF;
			break;
		}
		case 4:
		{
			UH_OFF;VH_ON;WH_OFF;//U- V+
			UL_ON;VL_OFF;WL_OFF;
			break;
		}
		case 5:
		{
			UH_OFF;VH_ON;WH_OFF;//V+ W-
			UL_OFF;VL_OFF;WL_ON;
			break;
		}
		case 6:
		{
			UH_ON;VH_OFF;WH_OFF;//U+ W-
			UL_OFF;VL_OFF;WL_ON;
			break;
		}
		default:
		{
			//1.关上管
			UH_OFF;VH_OFF;WH_OFF;
			//2.开下管
			UL_ON;VL_ON;WL_ON;
			break;
		}
	
	}
}


/************* 启动加速 ******************/
void Motor_Start(uint8_t direction)
{
	if(direction)
	{
		for(uint8_t i=100; i>0; i-=2)
		{
			for(uint8_t j=1; j<7; j++)
			{
				Six_step(j);
			}
			HAL_Delay(i+1);//最低1MS换相一次
		}
	}
}

/************* 电机匀速 ******************/
void Motor_Run(uint8_t direction)
{
	if(direction)
	{
			for(uint8_t j=1; j<7; j++)
			{
				Six_step(j);
				//HAL_Delay(1);
			}
	}
}

