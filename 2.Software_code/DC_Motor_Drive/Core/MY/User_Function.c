/*--------------------------------------------*/
/*----文件名：User_Function.c-----------------*/
/*----功能：用户的功能代码，使用时间调度器----*/
/*----作者：周琦------------------------------*/
/*----时间：2022/09/20/14：43-----------------*/
/*--------------------------------------------*/

#include "User_Function.h"

uint8_t KEY_Value = 0;
uint8_t Direction,Count;

extern key_table table[];
void (*current_operation_index)(); //定义一个函数指针 用于控制屏幕的显示
uint8_t index= 0;//页面索引


uint8_t Speed = 50;

void Mune(void)
{
	KEY_Value = Key_scan();
	switch (KEY_Value)
	{
	case 1:
		KEY_Value = 0;
		index = table[index].back;
		display_UI(index);
		break;
	case 2:
		KEY_Value = 0;
		index = table[index].enter;
		display_UI(index);
		break;
	case 3:
		KEY_Value = 0;
		index = table[index].down;
		display_UI(index);
	break;
	case 4:
		KEY_Value = 0;
		index = table[index].up;
		display_UI(index);
	break;
	
	default:
		KEY_Value = 0;
		break;
	}

	if(KEY_Value!=0)
	{
		//user_main_info("按键%d被按下\r\n",KEY_Value);
		KEY_Value = 0;
	}
		
}

/*根据EC11的差值来确定上翻还是下翻*/
/*直接给KEY_Value进行赋值*/
/*
void EC11_Fun()
{
	int D_value;
	D_value = Get_EC11_D_value(EC11_oldnum,EC11_newnum);



}
*/


void display_UI(uint8_t index)
{
	current_operation_index = table[index].current_operation;
	OLED_CLS();//清屏
	(*current_operation_index)();//执行当前操作函数
}



