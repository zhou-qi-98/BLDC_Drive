#include "key.h"

//��ȡ��������
//0---->NULL;1---->KEY1;2---->KEY2

uint8_t Key_scan(void)
{
		uint8_t Key_num = 0;
		if(!KEY1||!KEY2)//������һ������������
		{
			HAL_Delay(5);//ȥ������
			if(!KEY1)
				Key_num = 1;
			else if(!KEY2)
				Key_num = 2;
			else
				Key_num = 0;
		}

		return Key_num;
}

uint8_t Key2_scan(void)
{
	static uint8_t key_up=1;//�������ɿ���־
	if(key_up&&(!KEY1||!KEY2))
	{
		HAL_Delay(10);//ȥ���� 
		key_up=0;
		if(!KEY1)return 1;
		else if(!KEY2)return 2;
	}else if(KEY1&&KEY2)key_up=1; 	    
 	return 0;// �ް�������	
}


/*�����Ǳ�����*/
void Get_EC11_Value()
{

	Direction = (uint32_t)(__HAL_TIM_IS_TIM_COUNTING_DOWN(&htim3));
	Count = (uint32_t)(__HAL_TIM_GET_COUNTER(&htim3));             //��ȡ����ֵ
	user_main_info("����%d\r\n����ֵ��%d\r\n",Direction,Count);

}

