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

/* ���Ͷ��� -------------------------------------------------------------------*/
typedef struct
{
//u8 LED_Scan_Flag;//LED����
	u8 ANA_Scan_Flag					;//��������ɨ���־λ
	u8 ADC_Scan_Flag					;//ADC����ɨ���־λ
	u8 LAG_Scan_Flag					;//�ӳ�����ɨ���־λ
	u8 IRQ_Scan_Flag					;//�ж�����ɨ���־λ
	u8 KEY_Scan_Flag					;//��������ɨ���־λ
	u8 CTR_Scan_Flag					;//����ɨ���־λ
	
	u8 CAT_Scan_Finish_Flag		;//���һ��ȫ����ɨ���־λ	
}SysScanFlag_T;

extern volatile uint8_t SYS_TIME1S_FLAG;//1MSʱ����־
extern SysScanFlag_T __align(4)tSysScanFlag;//ϵͳɨ���־λ
extern uint8_t KEY_Value;//����ֵ

void Schedule(void);/*�������*/
void FuncRun(SysScanFlag_T *_tSysScanFlag);/*��������*/

#endif
