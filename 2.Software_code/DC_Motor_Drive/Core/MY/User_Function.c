/*--------------------------------------------*/
/*----�ļ�����User_Function.c-----------------*/
/*----���ܣ��û��Ĺ��ܴ��룬ʹ��ʱ�������----*/
/*----���ߣ�����------------------------------*/
/*----ʱ�䣺2022/09/20/14��43-----------------*/
/*--------------------------------------------*/

#include "User_Function.h"

uint8_t KEY_Value = 0;
uint8_t Direction,Count;

extern key_table table[];
void (*current_operation_index)(); //����һ������ָ�� ���ڿ�����Ļ����ʾ
uint8_t index= 0;//ҳ������


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
		//user_main_info("����%d������\r\n",KEY_Value);
		KEY_Value = 0;
	}
		
}

/*����EC11�Ĳ�ֵ��ȷ���Ϸ������·�*/
/*ֱ�Ӹ�KEY_Value���и�ֵ*/
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
	OLED_CLS();//����
	(*current_operation_index)();//ִ�е�ǰ��������
}



