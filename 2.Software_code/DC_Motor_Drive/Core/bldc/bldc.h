#ifndef _BLDC_H
#define _BLDC_H


#include "main.h"
//-------------------------------------
//相位引脚定义
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
//电机运行状态定义
typedef enum
{
    eStopState,                                                                 // 0: 停车状态
    eStartState,                                                                // 1: 启动状态
    eRunState,                                                                  // 2: 运行状态
    eEabsState,                                                                 // 3: 制动状态
    
    eStudyHallState,                                                            // 4: 学习Hall状态
    eCheckMOS,                                                                  // 5: 检测MOS管状态
    eIPDUrge,                                                                   // 6: 无Hall激励状态
    eFault                                                                      // 7: 故障  
     
}RunStatus;

// ADC通道
typedef enum
{
  currbufchang,
  volbufchang,                                                            
  ntcbufchang                                                                 
}AdcBufChang;

// 设置电机方向
typedef enum
{
  dCCW,
  dCW                                                             
}Rundirection;

//-------------------------------------
//变量定义
typedef struct
{
	uint8_t  dphase;           // 电机相位，0~5

	uint8_t  dRunMode;		  // 电机运行模式
	uint8_t  dState;           // 电机状态
	uint8_t  dEnPhase;		  // 换相使能 false使能 true禁止

	uint16_t dSpeed;			  // 给定电机的速度
	uint16_t dSpeedLas; 		  // 电机斜坡加速后的速度
	uint16_t dpwm;             // 电机转速，256 ~ 0  对应占空比为0~100%
	uint16_t dSpeedOut;

	uint8_t  dDir;			  // 外部给定电机的方向
	uint8_t  dDirLas;		  // 电机实际运行的方向
	uint8_t  dDirFlag;		  // 切换方向标记

	uint8_t  dsPhaseTimeOut;   // 换相超时
	uint8_t  dBkinTime;		  // 刹车时间

	uint16_t adBuf[3];         // 用于保存AD值
	uint16_t SpeedT[6];        // 速度计算缓存
	uint8_t  SpeedTindex;

}bldc_define;
extern bldc_define bldc;


extern void StepXL(void);
extern uint8_t StartMotor(void);
extern void BldcRun(void);
extern void speedCal(void);


#endif