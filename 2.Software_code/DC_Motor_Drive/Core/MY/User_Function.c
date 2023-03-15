/*--------------------------------------------*/
/*----文件名：User_Function.c-----------------*/
/*----功能：用户的功能代码，使用时间调度器----*/
/*----作者：周琦------------------------------*/
/*----时间：2022/09/20/14：43-----------------*/
/*--------------------------------------------*/

#include "User_Function.h"

uint8_t KEY_Value;
uint8_t Direction,Count;


void Test_KEY(void)
{
	//KEY_Value = Key_scan();
	if(KEY_Value!=0)
	{
		user_main_info("按键%d被按下\r\n",KEY_Value);
		KEY_Value = 0;
	}
		
}



