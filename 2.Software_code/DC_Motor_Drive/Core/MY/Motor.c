#include "Motor.h"

/*
//order ���ڷ����ı��
void Motor_run(uint8_t order,uint8_t Duty)
{
	switch(order)
	{
		//U0  V+ W-
		case 1:
		{
			HAL_TIM_PWM_Stop(&htim1,TIM_CHANNEL_1);//U�಻����
			HAL_TIMEx_PWMN_Stop(&htim1,TIM_CHANNEL_1);
			
			TIM1->CCR2 = ((float)Duty/(float)100)*70;//�޸�ռ�ձ�
			HAL_TIM_PWM_Start(&htim1,TIM_CHANNEL_2);//V������
			
			TIM1->CCR3 = ((float)Duty/(float)100)*70;//50%��ռ�ձ�
			HAL_TIMEx_PWMN_Start(&htim1,TIM_CHANNEL_3);//W�໥����
			break;	
		}
		
		case 3:
		{
			HAL_TIM_PWM_Stop(&htim1,TIM_CHANNEL_2);//v�಻����
			HAL_TIMEx_PWMN_Stop(&htim1,TIM_CHANNEL_2);
			
			TIM1->CCR1 = ((float)Duty/(float)100)*70;//�޸�ռ�ձ�
			HAL_TIMEx_PWMN_Start(&htim1,TIM_CHANNEL_1);//V�໥����
			
			TIM1->CCR3 = ((float)Duty/(float)100)*70;//50%��ռ�ձ�
			HAL_TIM_PWM_Start(&htim1,TIM_CHANNEL_3);//W������
			break;	
		}
		
		case 2:
		{
			HAL_TIM_PWM_Stop(&htim1,TIM_CHANNEL_3);//W�಻����
			HAL_TIMEx_PWMN_Stop(&htim1,TIM_CHANNEL_3);
			
			TIM1->CCR1 = ((float)Duty/(float)100)*70;//�޸�ռ�ձ�
			HAL_TIMEx_PWMN_Start(&htim1,TIM_CHANNEL_1);//U�໥����
			
			TIM1->CCR2 = ((float)Duty/(float)100)*70;//50%��ռ�ձ�
			HAL_TIM_PWM_Start(&htim1,TIM_CHANNEL_2);//V������
			break;	
		}
		case 6:
		{
			HAL_TIM_PWM_Stop(&htim1,TIM_CHANNEL_1);//U�಻����
			HAL_TIMEx_PWMN_Stop(&htim1,TIM_CHANNEL_1);
			
			TIM1->CCR3 = ((float)Duty/(float)100)*70;//�޸�ռ�ձ�
			HAL_TIMEx_PWMN_Start(&htim1,TIM_CHANNEL_3);//U�໥����
			
			TIM1->CCR2 = ((float)Duty/(float)100)*70;//�޸�ռ�ձ�
			HAL_TIM_PWM_Start(&htim1,TIM_CHANNEL_2);//V������
			break;	
		}
		case 4:
		{
			HAL_TIM_PWM_Stop(&htim1,TIM_CHANNEL_2);//V�಻����
			HAL_TIMEx_PWMN_Stop(&htim1,TIM_CHANNEL_2);
			
			TIM1->CCR3 = ((float)Duty/(float)100)*70;//�޸�ռ�ձ�
			HAL_TIMEx_PWMN_Start(&htim1,TIM_CHANNEL_3);//W�໥����
			
			TIM1->CCR1 = ((float)Duty/(float)100)*70;//�޸�ռ�ձ�
			HAL_TIM_PWM_Start(&htim1,TIM_CHANNEL_1);//U������
			break;	
		}
		case 5:
		{
			HAL_TIM_PWM_Stop(&htim1,TIM_CHANNEL_3);//W�಻����
			HAL_TIMEx_PWMN_Stop(&htim1,TIM_CHANNEL_3);
			
			TIM1->CCR2 = ((float)Duty/(float)100)*70;//�޸�ռ�ձ�
			HAL_TIMEx_PWMN_Start(&htim1,TIM_CHANNEL_2);//V�໥����
			
			TIM1->CCR1 = ((float)Duty/(float)100)*70;//�޸�ռ�ձ�
			HAL_TIM_PWM_Start(&htim1,TIM_CHANNEL_1);//V������
			break;	
		}
		default:break;
	}
}

*/
// 120 ��HAL,�����ĵ��ֱ����������������ʣ����������Ҫ����
// ʵ�ʵ�������ʵ��ĵ�����Ӧ��ϵ�����ڸñ�����Ͻ����ʵ��޸ļ���
// �� ת
// ����#1 ����#2 ����#3		A+ 		A- 		 B+ 		B- 		C+ 		C- 		����
// 1 				0 		1 		�ر� 		�ر� 	�ر� 	��ͨ 	��ͨ 		�ر� 		��   
// 0 				0 		1 		�ر� 		��ͨ 	�ر� 	�ر� 	��ͨ 		�ر� 		��		
// 0 				1 		1 		�ر� 		��ͨ 	��ͨ 	�ر� 	�ر� 		�ر� 		��			
// 0 				1 		0 		�ر� 		�ر� 	��ͨ 	�ر� 	�ر� 		��ͨ 		��
// 1 				1 		0 		��ͨ 		�ر� 	�ر� 	�ر� 	�ر� 		��ͨ 		��
// 1 				0 		0 		��ͨ 		�ر� 	�ر� 	��ͨ 	�ر� 		�ر� 		��

// �� ת
// ����#1 ����#2 ����#3 	A+ 		A- 			B+ 		B- 		C+ 		C- 		����
// 1 				0 		1 		�ر� 		�ر� 	��ͨ 	�ر� 	�ر� 		��ͨ 		��
// 0 				0 		1 		��ͨ 		�ر� 	�ر� 	�ر� 	�ر� 		��ͨ 		��
// 0 				1 		1 		��ͨ 		�ر� 	�ر� 	��ͨ 	�ر� 		�ر� 		��
// 0 				1 		0 		�ر� 		�ر� 	�ر� 	��ͨ 	��ͨ 		�ر� 		��
// 1 				1 		0 		�ر� 		��ͨ 	�ر� 	�ر� 	��ͨ 		�ر� 		��
// 1 				0 		0 		�ر� 		��ͨ 	��ͨ 	�ر� 	�ر� 		�ر� 		��



/*
���ͣ��
*/
void Motor_Stop()
{
	//�������Ϲܣ��������¹ܣ�й�����綯��
	
	//1.���Ϲ�
	UH_OFF;VH_OFF;WH_OFF;
	HAL_Delay(1);//��ʱ�£���ֹ�Ϲ�δ��ȫ�ر� �͵�ͨ�¹ܣ��ջ�MOS
	//2.���¹�
	UL_ON;VL_ON;WL_ON;	
}



/*
���ת��Ԥ��λ
direction:ת�����򣬸���ת�����������е���
������Ԥ��λ��ȷ��ת�Ӷ�λ��׼ȷλ��
*/
void ROTOR_Pre_positioning(uint8_t direction)
{
	if(direction)//��ת
	{
			//1.��ʼ��Ԥ��λ
		for(uint8_t i = 0;i<3;i++)
		{
			UH_ON;VH_OFF;WH_OFF;//U+ W-
			UL_OFF;VL_OFF;WL_ON;
			HAL_Delay(10);
		}
			//��ʱת��Ӧ����λ��6	
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
			//1.���Ϲ�
			UH_OFF;VH_OFF;WH_OFF;
			//2.���¹�
			UL_ON;VL_ON;WL_ON;
			break;
		}
	
	}
}


/************* �������� ******************/
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
			HAL_Delay(i+1);//���1MS����һ��
		}
	}
}

/************* ������� ******************/
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

