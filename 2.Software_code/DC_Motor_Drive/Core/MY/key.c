#include "key.h"

//读取按键数据
//0---->NULL;1---->KEY1;2---->KEY2

uint8_t Key_scan(void)
{
		uint8_t Key_num = 0;
		if(!KEY1||!KEY2)//有其中一个按键被按下
		{
			HAL_Delay(5);//去除抖动
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
	static uint8_t key_up=1;//按键按松开标志
	if(key_up&&(!KEY1||!KEY2))
	{
		HAL_Delay(10);//去抖动 
		key_up=0;
		if(!KEY1)return 1;
		else if(!KEY2)return 2;
	}else if(KEY1&&KEY2)key_up=1; 	    
 	return 0;// 无按键按下	
}


/*下面是编码器*/
void Get_EC11_Value()
{

	Direction = (uint32_t)(__HAL_TIM_IS_TIM_COUNTING_DOWN(&htim3));
	Count = (uint32_t)(__HAL_TIM_GET_COUNTER(&htim3));             //获取计数值
	user_main_info("方向：%d\r\n计数值：%d\r\n",Direction,Count);

}

