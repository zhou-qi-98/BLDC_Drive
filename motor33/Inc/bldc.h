#ifndef __BLDC_H_
#define __BLDC_H_



/* Includes ------------------------------------------------------------------*/
#include "stm32f1xx_hal.h"


#define FULL_PWM 719
#define PMW_PERIOD 40       // pwm 周期，单位us


#define MOTOR_VOLT  				240 
#define MOTOR_MID_VOLT 			120
#define MOTOR_BEMF_OFFSET  	3
#define MOTOR_BEMF_MID      2990 // 4095*((MOTOR_MID_VOLT-MOTOR_BEMF_OFFSET)*22/122+MOTOR_BEMF_OFFSET)/33

#define MOTOR_BEMF_CROSS    200


// 电机的一些参数
#define POLE_PAIRS 1 
#define MAX_SPEED 	12000
#define MIN_SPEED 	1200

#define START_TIME  100    // 起动时间，启动时间越长，运动过程中的分段感也越明显，建议100-500间



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
	uint8_t EN;     		// bldc使能
	uint8_t Dir;     		// bldc方向
	uint8_t Hall;   		// bldc HALL 状态
	int16_t PwmRef;  	  // bldc开环速度参考
	
	int16_t SpeedRef;  	// bldc闭环速度
	int16_t SpeedBck;  	// bldc速度反馈
	uint8_t Status; 		// bldc状态
	
	uint16_t start_first_step_timeus;   // 启动时第一次换相时间
	uint16_t start_step_timeus;         // 启动时每项换相时间
	uint16_t start_step_by_step_timeus; // 启动时步进减少时间
	uint16_t start_timems;              // 启动已用时间
	uint16_t start_pwm;                 // 启动时速度
	
	uint16_t Estimated_zero_crossing;   // 预估的过零间

}BldcMotor_t;


extern BldcMotor_t mymotor;


extern volatile uint8_t pre_flag,cur_flag;
extern volatile uint8_t first;

// 用于得到HALL传感器位置
uint8_t GetBldcHall( uint8_t dir );

//  电机驱动
void BldcStart( BldcMotor_t *motor,int16_t speed );
void BldcStop( BldcMotor_t *motor );
void BldcMove( BldcMotor_t *motor );
void BldcUpdataPwm( int16_t pwm );


#endif
