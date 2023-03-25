#include "bsp.h"

typedef struct{
	float Kp;
	float Ki;
	uint32_t PreError;//�ϴε������
	int8_t Pid_Dat;
}tsPID;

tsPID Speed_PID;


/*desir_speed�����ٶ�  measure_speed�����ٶ� */
/*����ֵPID�����Ƶ�ʱ仯������*/
int PID_Function(uint16_t desir_speed, uint16_t measure_speed)
{
	int32_t Error,Dat;//Error��������ʵ�ʵ����ֵ��Dat��PID������������
	Error = desir_speed - measure_speed;
	
	Dat = Speed_PID.Kp * (Error - Speed_PID.PreError) +
				Speed_PID.Ki * Error;//����ʽPID���㹫ʽ
	if(Dat > 10)
	{
		Dat = 10;
	}
	else if(Dat < -10)
	{
		Dat = -10;
	}
	Speed_PID.PreError = Error;//��ǰ������һ�����
	
	return Dat;
}


void PID_Init(void)
{
	Speed_PID.Ki = 0.1;
	Speed_PID.Kp = 0.0;
	Speed_PID.PreError = 0;
}
