#ifndef __STEPMOTOR_H_
#define __STEPMOTOR_H_




/* Includes ------------------------------------------------------------------*/
#include "stm32f1xx_hal.h"


typedef struct
{
	uint8_t EN;     // �������ʹ��
	uint8_t Step;   // ���������ǰ�Ľ���
	uint8_t Dir;    // �����������
	uint8_t Status; // �������״̬
	__IO uint32_t *Delay; // �������������ʱ����λUS
}stepmotor_t;


extern stepmotor_t mymotor;

void setpwm(uint16_t pwm);
void step4(uint8_t step);
void step8(uint8_t step);


#endif
