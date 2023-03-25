#ifndef __USART_H
#define __USART_H	

#include <stdio.h>
#include "typedef.h"



#include "typedef.h"
#include "stm32f0xx_usart.h"
#include "var.h"
#include "gpio.h"
#include "usart.h"
#include "stm32f0xx_gpio.h"
#include "stm32f0xx_misc.h"
#include "stm32f0xx_rcc.h"
#include "stm32f0xx_dma.h"
#include "stm32f0xx_dma.h"
#include "timer.h"

int fputc(int ch, FILE *f);
int ferror(FILE *f) ;
void _sys_exit(int return_code);
void USART1_Init(void);//串口初始化函数
void USART2_Init(void);
void USART1_DMA_TxInit(void);
void USART1_DMA_RxInit(void);

void USART2_DMA_TxInit(void);
void USART2_DMA_RxInit(void);
void Usart1_Send_Data(uint8_t * buf, uint16_t len);
void Usart2_Send_Data(uint8_t * buf, uint16_t len);
void Usart1_Isr(void);
void Usart2_Isr(void);
void Usart1_Receive_Close(void);
void Usart1_Receive_Open(void);
void Usart2_Receive_Close(void);
void Usart2_Receive_Open(void);
void Usart_test(void);
void Usart_Init(void);
void Usart_Scanf(void);






#endif 






