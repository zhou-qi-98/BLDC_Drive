#include "key.h"

//读取按键数据
//0---->NULL;1---->KEY1;2---->KEY2

uint8_t Key_scan(void)
{
		static uint8_t Key_num = 0;
		//uint8_t Key_status;
		//Key_status = KEY1;
		if(!KEY1)
		{
			HAL_Delay(5);//去除抖动
			if(!KEY1)
				Key_num = 1;
		}
		if(!KEY2)
		{
			HAL_Delay(5);//去除抖动
			if(!KEY2)
				Key_num = 2;
		}
		return Key_num;
}

