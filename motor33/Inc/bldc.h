#ifndef __BLDC_H_
#define __BLDC_H_



/* Includes ------------------------------------------------------------------*/
#include "stm32f1xx_hal.h"


#define FULL_PWM 719
#define PMW_PERIOD 40       // pwm ���ڣ���λus


#define MOTOR_VOLT  				240 
#define MOTOR_MID_VOLT 			120
#define MOTOR_BEMF_OFFSET  	3
#define MOTOR_BEMF_MID      2990 // 4095*((MOTOR_MID_VOLT-MOTOR_BEMF_OFFSET)*22/122+MOTOR_BEMF_OFFSET)/33

#define MOTOR_BEMF_CROSS    200


// �����һЩ����
#define POLE_PAIRS 1 
#define MAX_SPEED 	12000
#define MIN_SPEED 	1200

#define START_TIME  100    // ��ʱ�䣬����ʱ��Խ�����˶������еķֶθ�ҲԽ���ԣ�����100-500��



#define ADC_BEMF_U ADC_CHANNEL_13
#define ADC_BEMF_V ADC_CHANNEL_8
#define ADC_BEMF_W ADC_CHANNEL_7

#define MOTOR_STATUS_IDLE  		0
#define MOTOR_STATUS_ALIGN  	1
#define MOTOR_STATUS_STARTUP  2 
#define MOTOR_STATUS_RUN  		3
#define MOTOR_STATUS_STOP  		4


typedef struct
{
	uint8_t EN;     		// bldcʹ��
	uint8_t Dir;     		// bldc����
	uint8_t Hall;   		// bldc HALL ״̬
	int16_t PwmRef;  	  // bldc�����ٶȲο�
	
	int16_t SpeedRef;  	// bldc�ջ��ٶ�
	int16_t SpeedBck;  	// bldc�ٶȷ���
	uint8_t Status; 		// bldc״̬
	
	uint16_t start_first_step_timeus;   // ����ʱ��һ�λ���ʱ��
	uint16_t start_step_timeus;         // ����ʱÿ���ʱ��
	uint16_t start_step_by_step_timeus; // ����ʱ��������ʱ��
	uint16_t start_timems;              // ��������ʱ��
	uint16_t start_pwm;                 // ����ʱ�ٶ�
	
	uint16_t Estimated_zero_crossing;   // Ԥ���Ĺ����

}BldcMotor_t;


extern BldcMotor_t mymotor;


extern volatile uint8_t pre_flag,cur_flag;
extern volatile uint8_t first;

// ���ڵõ�HALL������λ��
uint8_t GetBldcHall( uint8_t dir );

//  �������
void BldcStart( BldcMotor_t *motor,int16_t speed );
void BldcStop( BldcMotor_t *motor );
void BldcMove( BldcMotor_t *motor );
void BldcUpdataPwm( int16_t pwm );


#endif
