#ifndef _BLDC_H
#define _BLDC_H


#include "main.h"
//-------------------------------------
//��λ���Ŷ���
#define _ABCL0   P34=0,P36=0,P35=0
#define _ABCL1   P34=1,P36=1,P35=1
#define _AL1     P34=0,P35=0,P36=1
#define _BL1     P34=0,P36=0,P35=1
#define _CL1     P35=0,P36=0,P34=1

#define _ABCH0   PCA_PWM0 |=  2, PCA_PWM1 |=  2, PCA_PWM2 |=  2  
#define _AHpwm   PCA_PWM1 |=  2, PCA_PWM2 |=  2, PCA_PWM0 &= ~2, CCAP0H=(u8)bldc.dpwm 
#define _BHpwm   PCA_PWM0 |=  2, PCA_PWM2 |=  2, PCA_PWM1 &= ~2, CCAP1H=(u8)bldc.dpwm 
#define _CHpwm   PCA_PWM0 |=  2, PCA_PWM1 |=  2, PCA_PWM2 &= ~2, CCAP2H=(u8)bldc.dpwm  

 
#define _AH0     PCA_PWM0 |=  2
#define _AH1     PCA_PWM0 &= ~2, CCAP0H = 0x00
 
#define _BH0     PCA_PWM1 |=  2
#define _BH1     PCA_PWM1 &= ~2, CCAP1H = 0x00

#define _CH0     PCA_PWM2 |=  2
#define _CH1     PCA_PWM2 &= ~2, CCAP2H = 0x00


//-------------------------------------
//�������״̬����
typedef enum
{
    eStopState,                                                                 // 0: ͣ��״̬
    eStartState,                                                                // 1: ����״̬
    eRunState,                                                                  // 2: ����״̬
    eEabsState,                                                                 // 3: �ƶ�״̬
    
    eStudyHallState,                                                            // 4: ѧϰHall״̬
    eCheckMOS,                                                                  // 5: ���MOS��״̬
    eIPDUrge,                                                                   // 6: ��Hall����״̬
    eFault                                                                      // 7: ����  
     
}RunStatus;

// ADCͨ��
typedef enum
{
  currbufchang,
  volbufchang,                                                            
  ntcbufchang                                                                 
}AdcBufChang;

// ���õ������
typedef enum
{
  dCCW,
  dCW                                                             
}Rundirection;

//-------------------------------------
//��������
typedef struct
{
	uint8_t  dphase;           // �����λ��0~5

	uint8_t  dRunMode;		  // �������ģʽ
	uint8_t  dState;           // ���״̬
	uint8_t  dEnPhase;		  // ����ʹ�� falseʹ�� true��ֹ

	uint16_t dSpeed;			  // ����������ٶ�
	uint16_t dSpeedLas; 		  // ���б�¼��ٺ���ٶ�
	uint16_t dpwm;             // ���ת�٣�256 ~ 0  ��Ӧռ�ձ�Ϊ0~100%
	uint16_t dSpeedOut;

	uint8_t  dDir;			  // �ⲿ��������ķ���
	uint8_t  dDirLas;		  // ���ʵ�����еķ���
	uint8_t  dDirFlag;		  // �л�������

	uint8_t  dsPhaseTimeOut;   // ���೬ʱ
	uint8_t  dBkinTime;		  // ɲ��ʱ��

	uint16_t adBuf[3];         // ���ڱ���ADֵ
	uint16_t SpeedT[6];        // �ٶȼ��㻺��
	uint8_t  SpeedTindex;

}bldc_define;
extern bldc_define bldc;


extern void StepXL(void);
extern uint8_t StartMotor(void);
extern void BldcRun(void);
extern void speedCal(void);


#endif