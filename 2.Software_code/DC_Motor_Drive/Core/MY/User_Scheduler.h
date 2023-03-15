#ifndef __USER_SCHEDULER_H__
#define __USER_SCHEDULER_H__

#include "stm32f1xx_hal.h"
#include "gpio.h"
#include "iwdg.h"
#include "User_Function.h"
#include "key.h"
#include "Get_ADC_Value.h"

#define u8 uint8_t
#define u16 uint16_t

/* 类型定义 -------------------------------------------------------------------*/
typedef struct
{
//u8 LED_Scan_Flag;//LED任务
	u8 ANA_Scan_Flag					;//解析任务扫描标志位
	u8 ADC_Scan_Flag					;//ADC任务扫描标志位
	u8 LAG_Scan_Flag					;//延迟任务扫描标志位
	u8 IRQ_Scan_Flag					;//中断任务扫描标志位
	u8 KEY_Scan_Flag					;//按键任务扫描标志位
	u8 CTR_Scan_Flag					;//控制扫描标志位
	
	u8 CAT_Scan_Finish_Flag		;//完成一次全参数扫描标志位	
}SysScanFlag_T;

extern volatile uint8_t SYS_TIME1S_FLAG;//1MS时基标志
extern SysScanFlag_T __align(4)tSysScanFlag;//系统扫描标志位
extern uint8_t KEY_Value;//按键值

void Schedule(void);/*任务调度*/
void FuncRun(SysScanFlag_T *_tSysScanFlag);/*功能运行*/

#endif
