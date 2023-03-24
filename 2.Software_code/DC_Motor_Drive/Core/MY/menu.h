#ifndef __MENU_H__
#define __MENU_H__


#include "IIC_OLED.h"
#include "main.h"


//定义一个结构体
typedef struct
{
	uint8_t current;//当前页面索引号
	uint8_t up;//向上翻索引号
	uint8_t down;//向下翻索引号
	uint8_t back;//返回索引号
	uint8_t enter;//确认索引号
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


