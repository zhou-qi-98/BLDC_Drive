#ifndef __I2C_OLED_H__
#define	__I2C_OLED_H__

/* ����ͷ�ļ� ----------------------------------------------------------------*/
#include "stm32f1xx_hal.h"

/* ���Ͷ��� ------------------------------------------------------------------*/
/* �궨�� --------------------------------------------------------------------*/
#define OLED_DEV_ADDR			   0x7A

/* ��չ���� ------------------------------------------------------------------*/
/* �������� ------------------------------------------------------------------*/
void OLED_Init(void);
void OLED_SetPos(unsigned char x, unsigned char y);
void OLED_Fill(unsigned char fill_Data);
void OLED_CLS(void);
void OLED_ON(void);
void OLED_OFF(void);
void OLED_ShowStr(unsigned char x, unsigned char y, unsigned char ch[], unsigned char TextSize);
void OLED_ShowCN(unsigned char x, unsigned char y, unsigned char N);
void OLED_DrawBMP(unsigned char x0,unsigned char y0,unsigned char x1,unsigned char y1,unsigned char BMP[]);

void OLED_ShowChar(uint8_t x,uint8_t y,uint8_t chr,uint8_t Char_Size);
void OLED_ShowNum(uint8_t x,uint8_t y,uint32_t num,uint8_t len,uint8_t size);
unsigned int mypow(unsigned char m,unsigned char n);

void oled_start(void); //ϵͳ��ʼ����
void oled_mainshow(void);//ϵͳ������
void oled_come(void) ; //�����ǰ����ʿ̨

#endif /* __I2C_OLED_H__ */

/******************* (C) COPYRIGHT 2015-2020 ӲʯǶ��ʽ�����Ŷ� *****END OF FILE****/
