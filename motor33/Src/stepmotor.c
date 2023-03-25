#include "stepmotor.h"

stepmotor_t mymotor;



// �������ԣ�ʾ��ʹ�����ķ�ʽ�պ���400������һȦ���ʲ������ 360/400 = 0.9 ��
// ���򲽾�� = 180/(����*ת�Ӽ�����),ǰ����ʵ����ò����������Ϊ2 ����֪��ת�Ӽ�����Ϊ100
// ����������ʽΪ����������ʽ��1/2ϸ���������ڸ�������ʽ�£���ʱ���ÿ��ת�� 1/2 ����Ǽ�0.45��
// ����Ҫ800�����Ĳ�������һȦ


// 
void setpwm(uint16_t pwm)
{
	 if( pwm > 1199 ) pwm = 1199;
	 TIM1->CCR1 = pwm; 
	 TIM1->CCR2 = pwm; 
	 TIM1->CCR3 = pwm; 
	 TIM1->CCR4 = pwm; 
}


#if 1

	
// ��1�����ģ�A 1000��A- 0010,   B 0100,  B- 0001.
void step4(uint8_t step)
{
	TIM1->CCER &= 0xeeee;
	switch(step)
	{
		case 0: TIM1->CCER |= 0x0001; break;
		case 1: TIM1->CCER |= 0x0100; break;
		case 2: TIM1->CCER |= 0x0010; break;
		case 3: TIM1->CCER |= 0x1000; break;
		
		default:break;
	}
}

// ��2�����ģ�A 1000��AA- 1010,A- 0010,A-B 0110,B 0100,BB- 0101,B- 0001,B-A 1001.


void step8(uint8_t step)
{
	TIM1->CCER &= 0xeeee;
	switch(step)
	{
		case 0: TIM1->CCER |= 0x0001; break;
		case 1: TIM1->CCER |= 0x0101; break;
		case 2: TIM1->CCER |= 0x0100; break;
		case 3: TIM1->CCER |= 0x0110; break;
		case 4: TIM1->CCER |= 0x0010; break;
		case 5: TIM1->CCER |= 0x1010; break;
		case 6: TIM1->CCER |= 0x1000; break;
		case 7: TIM1->CCER |= 0x1001; break;	
		default:break;
		}
}


#else


// ��1�����ģ�A 1000��A- 0010,   B 0100,  B- 0001.
void step4(uint8_t step)
{
	
//	HAL_GPIO_WritePin(GPIOA,GPIO_PIN_0,GPIO_PIN_RESET);
//	HAL_GPIO_WritePin(GPIOA,GPIO_PIN_1,GPIO_PIN_RESET);
//	HAL_GPIO_WritePin(GPIOA,GPIO_PIN_4,GPIO_PIN_RESET);
//	HAL_GPIO_WritePin(GPIOB,GPIO_PIN_0,GPIO_PIN_RESET);
	
	
	switch(step)
	{
		case 0:
			HAL_GPIO_WritePin(GPIOA,GPIO_PIN_0,GPIO_PIN_SET);
			HAL_GPIO_WritePin(GPIOA,GPIO_PIN_1,GPIO_PIN_RESET);
			HAL_GPIO_WritePin(GPIOA,GPIO_PIN_4,GPIO_PIN_RESET);
			HAL_GPIO_WritePin(GPIOB,GPIO_PIN_0,GPIO_PIN_RESET);
			break;
		
		case 1:
			HAL_GPIO_WritePin(GPIOA,GPIO_PIN_0,GPIO_PIN_RESET);
			HAL_GPIO_WritePin(GPIOA,GPIO_PIN_1,GPIO_PIN_RESET);
			HAL_GPIO_WritePin(GPIOA,GPIO_PIN_4,GPIO_PIN_SET);
			HAL_GPIO_WritePin(GPIOB,GPIO_PIN_0,GPIO_PIN_RESET);
			break;
		
		case 2:
			HAL_GPIO_WritePin(GPIOA,GPIO_PIN_0,GPIO_PIN_RESET);
			HAL_GPIO_WritePin(GPIOA,GPIO_PIN_1,GPIO_PIN_SET);
			HAL_GPIO_WritePin(GPIOA,GPIO_PIN_4,GPIO_PIN_RESET);
			HAL_GPIO_WritePin(GPIOB,GPIO_PIN_0,GPIO_PIN_RESET);
			break;
		
		case 3:
			HAL_GPIO_WritePin(GPIOA,GPIO_PIN_0,GPIO_PIN_RESET);
			HAL_GPIO_WritePin(GPIOA,GPIO_PIN_1,GPIO_PIN_RESET);
			HAL_GPIO_WritePin(GPIOA,GPIO_PIN_4,GPIO_PIN_RESET);
			HAL_GPIO_WritePin(GPIOB,GPIO_PIN_0,GPIO_PIN_SET);
			break;
		
		default:break;
	}
}

// ��2�����ģ�A 1000��AA- 1010,A- 0010,A-B 0110,B 0100,BB- 0101,B- 0001,B-A 1001.


void step8(uint8_t step)
{
	
//		HAL_GPIO_WritePin(GPIOA,GPIO_PIN_0,GPIO_PIN_RESET);
//		HAL_GPIO_WritePin(GPIOA,GPIO_PIN_1,GPIO_PIN_RESET);
//		HAL_GPIO_WritePin(GPIOA,GPIO_PIN_4,GPIO_PIN_RESET);
//		HAL_GPIO_WritePin(GPIOB,GPIO_PIN_0,GPIO_PIN_RESET);
	
		switch(step)
		{
		case 0:
			HAL_GPIO_WritePin(GPIOA,GPIO_PIN_0,GPIO_PIN_SET);
			HAL_GPIO_WritePin(GPIOA,GPIO_PIN_1,GPIO_PIN_RESET);
			HAL_GPIO_WritePin(GPIOA,GPIO_PIN_4,GPIO_PIN_RESET);
			HAL_GPIO_WritePin(GPIOB,GPIO_PIN_0,GPIO_PIN_RESET);
			break;
		
		case 1:
			HAL_GPIO_WritePin(GPIOA,GPIO_PIN_0,GPIO_PIN_SET);
			HAL_GPIO_WritePin(GPIOA,GPIO_PIN_1,GPIO_PIN_RESET);
			HAL_GPIO_WritePin(GPIOA,GPIO_PIN_4,GPIO_PIN_SET);
			HAL_GPIO_WritePin(GPIOB,GPIO_PIN_0,GPIO_PIN_RESET);
			break;
		
		case 2:
			HAL_GPIO_WritePin(GPIOA,GPIO_PIN_0,GPIO_PIN_RESET);
			HAL_GPIO_WritePin(GPIOA,GPIO_PIN_1,GPIO_PIN_RESET);
			HAL_GPIO_WritePin(GPIOA,GPIO_PIN_4,GPIO_PIN_SET);
			HAL_GPIO_WritePin(GPIOB,GPIO_PIN_0,GPIO_PIN_RESET);
			break;
		
		case 3:
			HAL_GPIO_WritePin(GPIOA,GPIO_PIN_0,GPIO_PIN_RESET);
			HAL_GPIO_WritePin(GPIOA,GPIO_PIN_1,GPIO_PIN_SET);
			HAL_GPIO_WritePin(GPIOA,GPIO_PIN_4,GPIO_PIN_SET);
			HAL_GPIO_WritePin(GPIOB,GPIO_PIN_0,GPIO_PIN_RESET);
			break;
		
		case 4:
			HAL_GPIO_WritePin(GPIOA,GPIO_PIN_0,GPIO_PIN_RESET);
			HAL_GPIO_WritePin(GPIOA,GPIO_PIN_1,GPIO_PIN_SET);
			HAL_GPIO_WritePin(GPIOA,GPIO_PIN_4,GPIO_PIN_RESET);
			HAL_GPIO_WritePin(GPIOB,GPIO_PIN_0,GPIO_PIN_RESET);
			break;
		
		case 5:
			HAL_GPIO_WritePin(GPIOA,GPIO_PIN_0,GPIO_PIN_RESET);
			HAL_GPIO_WritePin(GPIOA,GPIO_PIN_1,GPIO_PIN_SET);
			HAL_GPIO_WritePin(GPIOA,GPIO_PIN_4,GPIO_PIN_RESET);
			HAL_GPIO_WritePin(GPIOB,GPIO_PIN_0,GPIO_PIN_SET);
			break;
		
		case 6:
			HAL_GPIO_WritePin(GPIOA,GPIO_PIN_0,GPIO_PIN_RESET);
			HAL_GPIO_WritePin(GPIOA,GPIO_PIN_1,GPIO_PIN_RESET);
			HAL_GPIO_WritePin(GPIOA,GPIO_PIN_4,GPIO_PIN_RESET);
			HAL_GPIO_WritePin(GPIOB,GPIO_PIN_0,GPIO_PIN_SET);
			break;
		
		case 7:
			HAL_GPIO_WritePin(GPIOA,GPIO_PIN_0,GPIO_PIN_SET);
			HAL_GPIO_WritePin(GPIOA,GPIO_PIN_1,GPIO_PIN_RESET);
			HAL_GPIO_WritePin(GPIOA,GPIO_PIN_4,GPIO_PIN_RESET);
			HAL_GPIO_WritePin(GPIOB,GPIO_PIN_0,GPIO_PIN_SET);
			break;
		
		default:break;
		}
}


#endif 