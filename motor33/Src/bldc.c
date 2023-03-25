#include "bldc.h"
#include "stdlib.h"
#include "tim.h"
#include "adc.h"

BldcMotor_t mymotor =
{
	.start_first_step_timeus = 15000,
};


// 用于得到HALL传感器位置
uint8_t GetBldcHall( uint8_t dir )
{
	uint8_t ret = 0;
	
	static uint8_t i = 3;
	
	const static unsigned char HallBuff[8] = {0,5,1,3,2,6,4,7};  // {0,2,6,4,5,1,3,7};

	if( dir ) i = i%6 + 1;       // 正转
	else i = (i+4)%6 +1;  			 // 反转
	
	ret = HallBuff[i];

	return ret;
}


volatile uint8_t first=1;
volatile uint8_t pre_flag = 0,cur_flag = 0;
int h=0,l=0,d=0;

void MC_SixStep_ADC_Channel(uint32_t adc_ch,uint8_t flag)
{
		uint16_t i;
		int sum = 0;

		cur_flag = flag;
		
    __HAL_ADC_DISABLE(&hadc1);
		MODIFY_REG(hadc1.Instance->JSQR , ADC_JSQR_JSQ4 , ADC_JSQR_RK_JL( adc_ch, ADC_INJECTED_RANK_1,1) );
	
		// 计算平均反电动势
	  for( i = 0;i< adcwrite;i++ )
			sum += AdcBemf[i];
	
		sum /= adcwrite;
		adcwrite = 0;

#if 0  //  可以通过控制d在零附近，实现无感bldc控制，控制方法很简单，只需要电机的RUN阶段根据d的值来增减TIM2->ARR
	
		if( pre_flag == 0 )  h = sum;// (h + sum)/2;
		else l = sum; //  (l + sum)/2;
		d = (h-l); 
	  
#endif 

		pre_flag = cur_flag;
    __HAL_ADC_ENABLE(&hadc1);
		
		first = 1;
	

}


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

void six_step( BldcMotor_t *motor )
{
		static uint8_t prehall = 0;
		uint16_t Speed = abs(motor->PwmRef)* FULL_PWM / 1000;
	
		motor->Hall = GetBldcHall( motor->Dir );
	
		motor->Estimated_zero_crossing = motor->start_step_timeus/2/PMW_PERIOD;
	
		if( motor->EN )
		{
			TIM1->CCR1 = Speed;
			TIM1->CCR2 = Speed;
			TIM1->CCR3 = Speed;
		}
		else
		{
			TIM1->CCR1 = 0;
			TIM1->CCR2 = 0;
			TIM1->CCR3 = 0;
		}
	
		if( prehall != motor->Hall )
		{

			GPIOC->ODR &= ~(7<<10);

			if( motor->Dir )
			{
				switch( motor->Hall )
				{
					case 2:
						TIM1->CCER = 0x1010;
						GPIOC->ODR |= 6<<10;
						MC_SixStep_ADC_Channel(ADC_BEMF_U,0);
						break;

					case 6:
						TIM1->CCER = 0x1001;
						GPIOC->ODR |= 5<<10;
						MC_SixStep_ADC_Channel(ADC_BEMF_V,1);
						break;

					case 4:
						TIM1->CCER = 0x1001;
						GPIOC->ODR |= 3<<10;
						MC_SixStep_ADC_Channel(ADC_BEMF_W,0);
						break;

					case 5:
						TIM1->CCER = 0x1100;
						GPIOC->ODR |= 6<<10;
						MC_SixStep_ADC_Channel(ADC_BEMF_U,1);
						break;

					case 1:
						TIM1->CCER = 0x1100;
						GPIOC->ODR |= 5<<10;
						MC_SixStep_ADC_Channel(ADC_BEMF_V,0);
						break;

					case 3:
						TIM1->CCER = 0x1010;
						GPIOC->ODR |= 3<<10;
						MC_SixStep_ADC_Channel(ADC_BEMF_W,1);
						break;
					
					default:break;
				}
			}
			else
			{
				switch( motor->Hall )
				{
					case 5:
						TIM1->CCER = 0x1010;
						GPIOC->ODR |= 6<<10;
						MC_SixStep_ADC_Channel(ADC_BEMF_U,1);
						break;

					case 1:
						TIM1->CCER = 0x1001;
						GPIOC->ODR |= 5<<10;
						MC_SixStep_ADC_Channel(ADC_BEMF_V,0);
						break;

					case 3:
						TIM1->CCER = 0x1001;
						GPIOC->ODR |= 3<<10;
						MC_SixStep_ADC_Channel(ADC_BEMF_W,1);
						break;

					case 2:
						TIM1->CCER = 0x1100;
						GPIOC->ODR |= 6<<10;
						MC_SixStep_ADC_Channel(ADC_BEMF_U,0);
						break;

					case 6:
						TIM1->CCER = 0x1100;
						GPIOC->ODR |= 5<<10;
						MC_SixStep_ADC_Channel(ADC_BEMF_V,1);
						break;

					case 4:
						TIM1->CCER = 0x1010;
						GPIOC->ODR |= 3<<10;
						MC_SixStep_ADC_Channel(ADC_BEMF_W,0);
						break;

					default:break;
				}
			}
			prehall = motor->Hall;
		}
	
}


//  电机驱动
void BldcMove( BldcMotor_t *motor )
{
	static uint16_t alignval = 0;
	static uint16_t PwmBack = 0;
	static uint16_t newspeed;
		
	switch( motor->Status )
	{
		case  MOTOR_STATUS_IDLE  		: 
			TIM2->ARR = motor->start_first_step_timeus;
			TIM2->CNT = 0;
			break;
		
		case  MOTOR_STATUS_ALIGN  	: 
			alignval += 50;
			if( alignval < FULL_PWM/5 )
			{
				// 让hall状态为对齐到 3
				GPIOC->ODR &= ~(7<<10);

				TIM1->CCR1 = alignval;
				TIM1->CCR2 = 0;
				TIM1->CCR3 = 0;

				TIM1->CCER = 0x0111;
				GPIOC->ODR |= 7<<10;
			}
			else
			{
				motor->Hall = 3;
				motor->start_step_by_step_timeus = (motor->start_first_step_timeus - 60*1000*1000/MIN_SPEED/6/POLE_PAIRS) / START_TIME; 
				motor->start_timems = 0;
				motor->Status = MOTOR_STATUS_STARTUP;
				PwmBack = motor->PwmRef;
				motor->PwmRef = alignval;
				alignval = 0;
			}
			break;
		
		case  MOTOR_STATUS_STARTUP  : 
			// 以 1/5 PWM 跑起来，速度到 1/10 的满速
			motor->start_timems += motor->start_step_timeus/1000;
			if( motor->start_timems < START_TIME )
			{
				motor->start_step_timeus = motor->start_step_timeus - (motor->start_step_by_step_timeus*TIM2->ARR/1000);
				TIM2->ARR = motor->start_step_timeus;
				TIM2->CNT = 0;
			}
			else
			{
				motor->start_timems = 0;
				motor->Status = MOTOR_STATUS_RUN;
				motor->PwmRef = PwmBack;
			}
			six_step(motor);
			break; 
		
		case  MOTOR_STATUS_RUN  		:
			
			// 得到新速度 ,注意 如果电位器接触不良，在调速度过程中，电机有可能失速，这里要小心！！
			newspeed = (newspeed + (1000-100)*ADC2->JDR2/4096 + 100)/2;
			motor->PwmRef = newspeed;  

#if 0		// 和种简单地控制，让无感bldc顺利跑起来，可以将++，-- 变成 +=2 及 -=2，但这两种方式电机的响应都较慢，需要较多时间才能稳定
		
//			if( d > 100 ) motor->start_step_timeus --;
//			else if( d < -100 ) motor->start_step_timeus ++;

#endif //  将电机的反电动势可零控制在ADC中断中去实现，并由TIM3的辅助控制
		
			TIM2->ARR = motor->start_step_timeus;
			TIM2->CNT = 0;
			
			six_step(motor);
			break;
		
		case  MOTOR_STATUS_STOP  		:
			motor->Status = MOTOR_STATUS_IDLE;
			break;
		
		default:
			motor->Status = MOTOR_STATUS_IDLE;
			break;
	}

	
}




//  电机驱动
void BldcStart( BldcMotor_t *motor,int16_t speed )
{
	
#if 0
	
	TIM_SlaveConfigTypeDef SlaveConfig;
	SlaveConfig.SlaveMode =  TIM_SLAVEMODE_DISABLE;
	SlaveConfig.InputTrigger = TIM_TS_TI1F_ED;
	SlaveConfig.TriggerPolarity = TIM_TRIGGERPOLARITY_BOTHEDGE;
	HAL_TIM_SlaveConfigSynchronization(&htim2, &SlaveConfig);
	 
  HAL_TIM_IC_Start(&htim2,TIM_CHANNEL_1);
	__HAL_TIM_ENABLE(&htim2);
	
#endif	
	
	// HAL_ADC_Start(&hadc1);
	HAL_ADCEx_InjectedStart( &hadc1 );
	HAL_ADCEx_InjectedStart( &hadc2 );
	
	MODIFY_REG( hadc1.Instance->JSQR , ADC_JSQR_JL ,ADC_JSQR_JL_SHIFT(1) );
	MODIFY_REG( hadc1.Instance->JSQR , ADC_JSQR_JSQ4 , ADC_JSQR_RK_JL( ADC_CHANNEL_13, ADC_INJECTED_RANK_1,1) );
	__HAL_ADC_ENABLE(&hadc1);
	__HAL_ADC_ENABLE(&hadc2);
	
	
	if( speed > 1000 ) speed = 1000;
	else if( speed < -1000 ) speed = -1000;
	
	motor->PwmRef = speed;
	motor->Dir = speed > 0 ? 1 : 0;
	motor->EN = 1;
	
	motor->start_step_timeus = motor->start_first_step_timeus;
	
	// 如果没有对齐操作，让电机直接进入到拖动阶段 ，则后面需要更多的时间才能达到稳定，
	// 即电机的实际启动时间会更长，所以还是要加上对齐段
	motor->Status  =  MOTOR_STATUS_ALIGN; // MOTOR_STATUS_STARTUP; 

	
	
	TIM1->BDTR |= TIM_BDTR_MOE;
	TIM1->CR1  |= TIM_CR1_CEN;
}


//  电机驱动
void BldcStop( BldcMotor_t *motor )
{
	motor->PwmRef = 0;
	motor->EN = 0;
	motor->Status  =  MOTOR_STATUS_STOP;
	
	TIM1->BDTR &= ~TIM_BDTR_MOE;
	TIM1->CR1  &= ~TIM_CR1_CEN;
}



//  更新PWM值
void BldcUpdataPwm( int16_t pwm )
{
	if( pwm > 1000 ) pwm = 1000;
	else if( pwm < -1000 ) pwm = -1000;
	
	uint16_t speed = abs(pwm)* FULL_PWM/ 1000 ;
	
	mymotor.PwmRef = pwm;
	mymotor.Dir = pwm > 0 ? 1 : 0;

//	TIM1->CCR1 = speed;
//	TIM1->CCR2 = speed;
//	TIM1->CCR3 = speed;
	
	
}
