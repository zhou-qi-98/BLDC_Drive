#include "typedef.h"
#include "stm32f0xx_usart.h"
#include "var.h"
#include "gpio.h"
#include "usart.h"
#include "stm32f0xx_gpio.h"
#include "stm32f0xx_misc.h"
#include "stm32f0xx_rcc.h"
#include "stm32f0xx_dma.h"
#include "stm32f0xx_dma.h"
#include "timer.h"

Com Com1 ,Com2;



#if 1
#pragma import(__use_no_semihosting)             
//标准库需要的支持函数                 

struct __FILE 
{ 
	int handle; 

}; 

FILE __stdout;       

//重定义fputc函数 
 
int fputc(int ch, FILE *f)
{
    USART_SendData(USART1,(uint8_t)ch);
    while (!USART_GetFlagStatus(USART1, USART_FLAG_TXE));
    return (ch);
}


#endif

int ferror(FILE *f) {                            // Your implementation of ferror

  return EOF;

}

void _sys_exit(int return_code) {

label:  goto label;           // endless loop

}

void USART1_Init(void)//串口初始化函数
{  
      
    USART_InitTypeDef USART_InitStructure;

    NVIC_InitTypeDef	NVIC_InitStructure;

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1 , ENABLE );
    USART_InitStructure.USART_BaudRate = 9600;//设置串口波特率
    USART_InitStructure.USART_WordLength = USART_WordLength_8b;//设置数据位
    USART_InitStructure.USART_StopBits = USART_StopBits_1;//设置停止位
    USART_InitStructure.USART_Parity = USART_Parity_No;//设置效验位
    USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//设置流控制
    USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;//设置工作模式
    USART_Init(USART1, &USART_InitStructure); //配置入结构体

    USART_ITConfig(USART1,USART_IT_IDLE,ENABLE);			

    USART_DMACmd(USART1,USART_DMAReq_Tx,ENABLE);

    USART_DMACmd(USART1,USART_DMAReq_Rx,ENABLE);

    USART_Cmd(USART1, ENABLE);//使能串口1
    		
    USART_ClearFlag(USART1,USART_FLAG_TC);

    NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;	
    NVIC_InitStructure.NVIC_IRQChannelPriority = 6;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);		

    
}

void USART2_Init(void)
{

    USART_InitTypeDef USART_InitStructure;
    NVIC_InitTypeDef	NVIC_InitStructure;
	
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2 , ENABLE );
    USART_InitStructure.USART_BaudRate = 9600;
    USART_InitStructure.USART_WordLength = USART_WordLength_8b;
    USART_InitStructure.USART_StopBits = USART_StopBits_1;
    USART_InitStructure.USART_Parity = USART_Parity_No;
    USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
    USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
    USART_Init(USART2, &USART_InitStructure);
    
    USART_ITConfig(USART2,USART_IT_IDLE,ENABLE);
    USART_DMACmd(USART2,USART_DMAReq_Tx,ENABLE);
    USART_DMACmd(USART2,USART_DMAReq_Rx,ENABLE);
		    
    USART_Cmd(USART2, ENABLE);
    USART_ClearFlag(USART2,USART_FLAG_TC);	
	
    USART_ClearFlag(USART2,USART_FLAG_IDLE);
    USART_ClearITPendingBit(USART2,USART_IT_IDLE); 


    NVIC_InitStructure.NVIC_IRQChannel = USART2_IRQn;	
    NVIC_InitStructure.NVIC_IRQChannelPriority = 2;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);


}

void USART1_DMA_TxInit(void)
{
	DMA_InitTypeDef DMA_InitStructure ;

    NVIC_InitTypeDef	NVIC_InitStructure;
	
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1,ENABLE);
		
	DMA_InitStructure.DMA_PeripheralBaseAddr = (uint32_t)(&USART1->TDR);
	DMA_InitStructure.DMA_MemoryBaseAddr = (uint32_t)Com1.Tx_Buf ;
	DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralDST;
	DMA_InitStructure.DMA_BufferSize = 255;
	DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
	DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;
	DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;
	DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte;
	DMA_InitStructure.DMA_Mode = DMA_Mode_Normal;
	DMA_InitStructure.DMA_Priority = DMA_Priority_High;
	DMA_InitStructure.DMA_M2M = DMA_M2M_Disable;
	DMA_Init(DMA1_Channel2,&DMA_InitStructure);	
    DMA_ITConfig(DMA1_Channel2,DMA_IT_TC,ENABLE);

    DMA_ClearFlag(DMA_IT_TC);

    NVIC_InitStructure.NVIC_IRQChannel = DMA1_Channel2_3_IRQn;	 
    NVIC_InitStructure.NVIC_IRQChannelPriority = 2;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);
}

void USART1_DMA_RxInit(void)
{
	DMA_InitTypeDef DMA_InitStructure ;
    
    NVIC_InitTypeDef	NVIC_InitStructure;	
	
    RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1,ENABLE);
	
	DMA_InitStructure.DMA_PeripheralBaseAddr = (uint32_t)(&USART1->RDR);
	DMA_InitStructure.DMA_MemoryBaseAddr = (uint32_t)Com1.Rx_Buf ;
	DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralSRC;
	DMA_InitStructure.DMA_BufferSize = 255;
	DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
	DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;
	DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;
	DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte;
	DMA_InitStructure.DMA_Mode = DMA_Mode_Normal;
	DMA_InitStructure.DMA_Priority = DMA_Priority_High;
	DMA_InitStructure.DMA_M2M = DMA_M2M_Disable;
	DMA_Init(DMA1_Channel3,&DMA_InitStructure);	
    DMA_Cmd(DMA1_Channel3,ENABLE);

    NVIC_InitStructure.NVIC_IRQChannel = DMA1_Channel2_3_IRQn;	 
    NVIC_InitStructure.NVIC_IRQChannelPriority = 2;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);
}


void USART2_DMA_TxInit(void)
{
	DMA_InitTypeDef DMA_InitStructure ;	
    NVIC_InitTypeDef NVIC_InitStructure;
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1,ENABLE);
		
	DMA_InitStructure.DMA_PeripheralBaseAddr = (uint32_t)(&USART2->TDR);
	DMA_InitStructure.DMA_MemoryBaseAddr = (uint32_t)Com2.Tx_Buf ;
	DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralDST;
	DMA_InitStructure.DMA_BufferSize = 255;
	DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
	DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;
	DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;
	DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte;
	DMA_InitStructure.DMA_Mode = DMA_Mode_Normal;
	DMA_InitStructure.DMA_Priority = DMA_Priority_High;
	DMA_InitStructure.DMA_M2M = DMA_M2M_Disable;
	DMA_Init(DMA1_Channel4,&DMA_InitStructure);	
    DMA_ITConfig(DMA1_Channel4,DMA_IT_TC,ENABLE);
    DMA_ClearFlag(DMA_IT_TC);

    			

    NVIC_InitStructure.NVIC_IRQChannel = DMA1_Channel4_5_IRQn;	 
    NVIC_InitStructure.NVIC_IRQChannelPriority = 3;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);    
}

void USART2_DMA_RxInit(void)
{
    DMA_InitTypeDef DMA_Initstructure;  
    NVIC_InitTypeDef NVIC_InitStructure;
    RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1,ENABLE);
    
    DMA_Initstructure.DMA_PeripheralBaseAddr =  (uint32_t)(&USART2->RDR);
    DMA_Initstructure.DMA_MemoryBaseAddr      = (uint32_t)Com2.Rx_Buf;
    DMA_Initstructure.DMA_DIR = DMA_DIR_PeripheralSRC;
    DMA_Initstructure.DMA_BufferSize = 255;
    DMA_Initstructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
    DMA_Initstructure.DMA_MemoryInc = DMA_MemoryInc_Enable;
    DMA_Initstructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;
    DMA_Initstructure.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte;
    DMA_Initstructure.DMA_Mode = DMA_Mode_Normal;
    DMA_Initstructure.DMA_Priority = DMA_Priority_High;
    DMA_Initstructure.DMA_M2M = DMA_M2M_Disable;
    DMA_Init(DMA1_Channel5,&DMA_Initstructure);
    DMA_Cmd(DMA1_Channel5,ENABLE);

    NVIC_InitStructure.NVIC_IRQChannel = DMA1_Channel4_5_IRQn;	 
    NVIC_InitStructure.NVIC_IRQChannelPriority = 3;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);

}



void Usart1_Send_Data(uint8_t * buf, uint16_t len)
{   
    uint8_t i;	
    for( i = 0;i < len ; i++)
    {
        Com1.Tx_Buf[i] = *buf ;
        buf++;
    }

    DMA_Cmd(DMA1_Channel2, DISABLE); 
    DMA1_Channel2->CNDTR = len;
    DMA_ITConfig(DMA1_Channel2,DMA_IT_TC,ENABLE);	
    DMA_Cmd(DMA1_Channel2, ENABLE);		
    			
}

void Usart2_Send_Data(uint8_t * buf, uint16_t len)
{     
    uint i = 0;
    for( i = 0;i < len ; i++)
	{
		Com2.Tx_Buf[i] = *buf ;
		buf++;
	}
			
	DMA_Cmd(DMA1_Channel4, DISABLE); 
	DMA1_Channel4->CNDTR = len;
	DMA_ITConfig(DMA1_Channel4,DMA_IT_TC,ENABLE);	
	DMA_Cmd(DMA1_Channel4, ENABLE);		

}

void Usart1_Isr(void)
{
    uint8_t num = 0;
	
    num = USART1->ISR;
    num = USART1->RDR;		      
    num = DMA1_Channel3->CNDTR;
    num = 255 -  num;
    Com1.Frame_Len = num;
    Com1.Rx_Buf[num] = 0x00;
    Com1.Rx_Complete = 1;    
}

void Usart2_Isr(void)
{
    uint8_t num = 0;
	
	num = USART2->ISR;
	num = USART2->RDR;		      
    num = DMA1_Channel5->CNDTR;
    num = 255 -  num;
    Com2.Frame_Len = num;
    Com2.Rx_Buf[num] = 0x00;
    Com2.Rx_Complete = 1;    
}




void Usart1_Receive_Close(void)
{	

	 USART_ITConfig(USART1, USART_IT_IDLE, DISABLE);
	 DMA_Cmd(DMA1_Channel3,DISABLE);
}

void Usart1_Receive_Open(void)
{
    USART_ITConfig(USART1, USART_IT_IDLE, ENABLE);
    //DMA_Cmd(DMA1_Channel3,DISABLE);
    DMA1_Channel3->CNDTR = 255; 
    DMA_Cmd(DMA1_Channel3,ENABLE);
    Com1.Rx_Complete = 0;
    Com1.Rx_Timeout = 0;
}

void Usart2_Receive_Close(void)
{	        
    USART_ITConfig(USART2, USART_IT_IDLE, DISABLE);
    DMA_Cmd(DMA1_Channel5,DISABLE);
}

void Usart2_Receive_Open(void)
{
    USART_ITConfig(USART2, USART_IT_IDLE, ENABLE);
    DMA1_Channel5->CNDTR = 255; 
    DMA_Cmd(DMA1_Channel5,ENABLE);
    Com2.Rx_Complete = 0;
    Com2.Rx_Timeout = 0;
}

void Usart_test(void)
{
    uint16_t i;
    if(Com1.Rx_Complete == 1)
    {                       
        Usart1_Receive_Close();
        Usart1_Send_Data(Com1.Rx_Buf, Com1.Frame_Len);
        Usart1_Receive_Open();
    }
    
	
	
	if(Com2.Rx_Complete == 1)
	{
		
		Usart2_Receive_Close();
    
		for(i = 0; i < Com2.Frame_Len; i++)
		{
			Com2.Tx_Buf[i] = Com2.Rx_Buf[i];			
		}
		
		Usart2_Send_Data(Com2.Tx_Buf,Com2.Frame_Len);
		
		
		Com2.Rx_Complete = 0;
		Usart2_Receive_Open();	  
	}    
    

}

void Usart_Init(void)
{
	USART1_Init();
	USART1_DMA_TxInit();
	USART1_DMA_RxInit();
    Usart1_Receive_Open();  
//	USART2_Init();
//	USART2_DMA_TxInit();
//	USART2_DMA_RxInit();
//  Usart2_Receive_Open();  
	
}



void Usart_Scanf(void)
{
    if(Com1.Rx_Complete == 1)
    {
        Usart1_Receive_Close();
        
        if(Com1.Rx_Buf[0] != 0)
        {
        
            
        
        }
        
      
        Usart1_Receive_Open();	
        Com1.Rx_Complete = 0;
    }

}

