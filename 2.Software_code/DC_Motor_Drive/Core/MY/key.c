#include "key.h"

extern uint8_t KEY_Value;
//��ȡ��������
//0---->NULL;1---->KEY1;2---->KEY2

uint8_t Key_scan(void)
{
	uint8_t Key_num = 0;
	if(KEY_Value==0)
	{
		if(!KEY1||!KEY2)//������һ������������
		{
			HAL_Delay(5);//ȥ������
			if(!KEY1)
			{
				Key_num = 1;
				while(!KEY1);//���ּ��
			}
			else if(!KEY2)
			{
				Key_num = 2;
				while(!KEY2);//���ּ��
			}	
			else
				Key_num = 0;
		}
		return Key_num;
	}
}

