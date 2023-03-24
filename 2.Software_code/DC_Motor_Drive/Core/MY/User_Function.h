#ifndef __USER_FUNCTION_H__
#define __USER_FUNCTION_H__

#include "stdio.h"
#include "gpio.h"
#include "usart.h"
#include "key.h"
#include "menu.h"


/*���ÿɱ���������¶����ӡ��Ϣ*/
#define USER_MAIN_DEBUG
#ifdef USER_MAIN_DEBUG
#define user_main_printf(format, ...) printf( format "", ##__VA_ARGS__)
#define user_main_info(format, ...) printf("[main]info:" format "\r\n", ##__VA_ARGS__)//��ͨ��Ϣ
#define user_main_debug(format, ...) printf("[main]debug:" format "\r\n", ##__VA_ARGS__)//������Ϣ
#define user_main_error(format, ...) printf("[main]error:" format "\r\n",##__VA_ARGS__)//������Ϣ
#else
#define user_main_printf(format, ...)
#define user_main_info(format, ...)
#define user_main_debug(format, ...)
#define user_main_error(format, ...)
#endif



extern int fputc(int ch, FILE *f);


void Test_KEY(void);
void display_UI(uint8_t index);

#endif
