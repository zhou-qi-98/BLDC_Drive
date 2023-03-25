#include "bsp.h"

typedef struct{
	float Kp;
	float Ki;
	uint32_t PreError;//上次的误差量
	int8_t Pid_Dat;
}tsPID;

tsPID Speed_PID;


/*desir_speed期望速度  measure_speed测量速度 */
/*返回值PID计算出频率变化的增量*/
int PID_Function(uint16_t desir_speed, uint16_t measure_speed)
{
	int32_t Error,Dat;//Error是期望和实际的误差值，Dat是PID计算结果的增量
	Error = desir_speed - measure_speed;
	
	Dat = Speed_PID.Kp * (Error - Speed_PID.PreError) +
				Speed_PID.Ki * Error;//增量式PID计算公式
	if(Dat > 10)
	{
		Dat = 10;
	}
	else if(Dat < -10)
	{
		Dat = -10;
	}
	Speed_PID.PreError = Error;//当前误差传给上一次误差
	
	return Dat;
}


void PID_Init(void)
{
	Speed_PID.Ki = 0.1;
	Speed_PID.Kp = 0.0;
	Speed_PID.PreError = 0;
}
