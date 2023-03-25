#ifndef __TYPEDEF_H
#define __TYPEDEF_H
#include "stdio.h"
#include "stdint.h"
typedef unsigned char    	uint8;      // 无符号8位整型变量
typedef unsigned char 	 	U8;
typedef unsigned char	 	uchar;
typedef unsigned char    	UCHAR;
typedef char                int8;
typedef signed char	     	INT8;
typedef signed char      	byte;
//typedef signed char      	BYTE;
typedef unsigned short   	uint16;     // 无符号16位整型变量
typedef unsigned short      U16;
typedef unsigned short 	 	uint;
//typedef unsigned short   	UINT;
typedef unsigned short   	word;
typedef unsigned short   	WORD;
typedef signed short     	int16;      // 有符号16位整型变量
typedef signed short     	INT16;
//typedef signed short 		INT;
typedef unsigned long       uint32;
typedef unsigned int 	    U32;
typedef unsigned int 	 	dword;
//typedef unsigned int 	 	DWORD;
typedef signed int       	int32;      // 有符号32位整型变量
typedef signed int       	INT32;
typedef signed int 		 	dint;
typedef signed int 		 	DINT;   
typedef float               fp32;       // 单精度浮点数（32位长度）
typedef float			 	real;
typedef float 			 	REAL;
typedef double              fp64;       // 双精度浮点数（64位长度）
typedef double			 	dreal;
typedef double 			 	DREAL;

#define nop()  __nop();

#ifndef TRUE
#define TRUE  0x01
#endif

#ifndef FALSE
#define FALSE 0x00
#endif



#define BackLight(x)  {\
						if(x==1)\
						GPIOA->ODR |= (1 << 7);\
						else\
						GPIOA->ODR &=~(1 << 7);} 

#define LCD_DATA(x)  {\
						if(x==1)\
						GPIOA->ODR |= (1 << 12);\
						else\
						GPIOA->ODR &=~(1 << 12);} 

#define LCD_WR(x)    {\
						if(x==1)\
						GPIOA->ODR |= (1 << 11);\
						else\
						GPIOA->ODR &=~(1 << 11);} 

						
#define LCD_CS(x)    {\
						if(x==1)\
						GPIOA->ODR |= (1 << 10);\
						else\
						GPIOA->ODR &=~(1 << 10);} 

#define AD_Power(x)  {\
						if(x==1)\
						GPIOB->ODR |= (1 << 2);\
						else\
						GPIOB->ODR &=~(1 << 2);}

#define RD(x)        {\
						if(x==1)\
						GPIOA->ODR |= (1 << 11);\
						else\
						GPIOA->ODR &=~(1 << 11);}

#define SCS(x)       {\
    					if(x==1)\
    					GPIOF->ODR |=(1 << 1);\
    					else\
    					GPIOF->ODR &=~(1 << 1);}
		
#define CS(x)       {\
    					if(x==1)\
    					GPIOF->ODR |=(1 << 1);\
    					else\
    					GPIOF->ODR &=~(1 << 1);}

#define MOSI(x)      {\
    					if(x==1)\
    					GPIOF->ODR |=(1 << 0);\
    					else\
    					GPIOF->ODR &=~(1 << 0);}

#define SCK(x)       {\
    					if(x==1)\
    					GPIOC->ODR |=(1 << 15);\
    					else\
    					GPIOC->ODR &=~(1 << 15);}


#define NRST(x)      {\
    					if(x==1)\
    					GPIOF->ODR |=(1 << 0);\
    					else\
    					GPIOF->ODR &=~(1 << 0);}

#define SCL(x)       {\
    					if(x==1)\
    					GPIOF->ODR |=(1 << 6);\
    					else\
    					GPIOF->ODR &=~(1 << 6);}

#define SDA(x)       {\
      					if(x==1)\
      					GPIOF->ODR |=(1 << 7);\
      					else\
      					GPIOF->ODR &=~(1 << 7);}


#define Relay1(x)    {\
    					if(x==1)\
    					GPIOA->ODR |=(1 << 11);\
    					else\
    					GPIOA->ODR &=~(1 << 11);}


#define Relay2(x)    {\
    					if(x==1)\
    					GPIOA->ODR |=(1 << 10);\
    					else\
    					GPIOA->ODR &=~(1 << 10);}

#define Relay3(x)    {\
    					if(x==1)\
    					GPIOA->ODR |=(1 << 11);\
    					else\
    					GPIOA->ODR &=~(1 << 11);}


#define Relay4(x)    {\
    					if(x==1)\
    					GPIOA->ODR |=(1 << 12);\
    					else\
    					GPIOA->ODR &=~(1 << 12);}

#define Relay5(x)    {\
    					if(x==1)\
    					GPIOF->ODR |=(1 << 6);\
    					else\
    					GPIOF->ODR &=~(1 << 6);}          

          
				

                        
                        
                        
#define EMF_C   (GPIOF->IDR & (1 << 6))

#define EMF_B   (GPIOA->IDR & (1 << 12))

#define EMF_A   (GPIOA->IDR & (1 << 11))   



#define AP_IN    (GPIOB->IDR & (1 << 5))                          
                        
                        
#define HALL_U  (GPIOA->IDR & (1 << 11))                        
                        
#define HALL_V  (GPIOA->IDR & (1 << 12))   

#define HALL_W  (GPIOF->IDR & (1 << 6))  



#define Err_On GPIO_SetBits(GPIOB, GPIO_Pin_2)

#define Err_Off GPIO_ResetBits(GPIOB, GPIO_Pin_2)

typedef struct
{
    uint8_t   Rx_Buf[256];
    uint8_t   Tx_Buf[256];
    uint8_t   Rx_Count;
    uint8_t   Rx_Complete;
    uint8_t   Rx_Time;
    uint8_t   Tx_Len;
    uint8_t   Tx_IDLE;
    uint16_t  Frame_Len;
    uint8_t   TxCrc_Pos;  
    uint8_t   RxCrc_Pos;
    uint8_t   ReSend;
    uint8_t   Data_Serial;
    uint16_t  Rx_Timeout;
    uint16_t  Data_Start_Addr;
    uint16_t  Data_End_Addr;
    uint16_t  Data_Count;
    uint16_t  Bitrate;
    uint16_t  StopBit;
    uint16_t  Parity; 
    uint16_t  WordLength;
    uint16_t *  Data_Point;					

}Com;

typedef struct sPid
{

    int16_t Erro;

    int16_t Erro_Next;

    int16_t Erro_Last;
    
    uint16_t Time;

    float Increment;

    float Out;

    float Kp;

    float Ki;

    float Kd;
    
    

}tPid;


typedef struct sRadio
{
    uint8_t     Tx_Buf[255];

    uint8_t     Rx_Buf[255];

    uint8_t     TxPayloadLength;

    uint8_t     RxPacketSize;

    uint8_t     Tx_Complete;

    uint8_t     Rx_Complete;

    uint8_t     Cad_Done;

    uint8_t     Resend;

    uint8_t     Registers_Start_Addr;

    uint8_t     Registers_Offset;

    uint8_t     Registers_Count;

    uint8_t *   Message_Point;

    uint16_t    Rx_Timeout;

    uint16_t *  Data_Point;

    int16_t     RxPacketSnrEstimate;

    int16_t     RxPacketRssiValue;

    uint16_t    Tx_Cost_Time;
    
    uint16_t    Original_Address;
    
    uint16_t    Destination_Address;
    
    uint16_t    Repeater_Address; 
        
    uint16_t    Channel_Address;
    
    uint16_t     Original_Mac;
		

}tRadio , * ptRadio;

typedef struct tMotor
{
	
	uint8_t	 Motor_NowPosition;
	uint8_t  Motor_OldPosition;
	
	uint16_t Pwm;
	uint8_t  Run_Status;
	uint16_t Measure_Speed;
	uint16_t Desire_Speed;
	
	
	uint16_t Brake_Delay;
	uint8_t  Brake_Key;
	
	uint16_t Fstart_Timer;
	
	uint16_t St_Timer;
	
	
}tsMotor;


typedef enum
{
	Pidopen_Status,				//pid运行状态
	Pidclose_Status,				//pid关闭状态,
}BLDC_Pid;


#endif

