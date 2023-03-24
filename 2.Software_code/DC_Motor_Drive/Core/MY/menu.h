#ifndef __MENU_H__
#define __MENU_H__


#include "IIC_OLED.h"
#include "main.h"


//����һ���ṹ��
typedef struct
{
	uint8_t current;//��ǰҳ��������
	uint8_t up;//���Ϸ�������
	uint8_t down;//���·�������
	uint8_t back;//����������
	uint8_t enter;//ȷ��������
	void (*current_operation)();
} key_table;

void fun_0(void);

void fun_a1(void);
void fun_b1(void);
void fun_c1(void);
void fun_d1(void);

void fun_a21(void);
void fun_a22(void);

void fun_b21(void);

void fun_c21(void);

void fun_d21(void);







#endif


