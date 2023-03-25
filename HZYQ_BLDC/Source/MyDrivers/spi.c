#include "spi.h"
#include "stm32f0xx_gpio.h"


void Spi_SendByte(uint8_t byte)
{
	uint8_t i;
	SCK(0);

	for(i = 0; i < 8; i++)
	{
//		CLK = 0;

		if(byte & 0x80)
		{
			MOSI(1);
		}
		else
		{
			MOSI(0);
		}
		byte <<= 1;
		
		SCK(0);   
		SCK(1);
	}
}

void Spi_SendData(void)
{
	CS(0);

	Spi_SendByte(0xff);//0x67
	//Begin cmd is 0x03
	/*Test cmd
		0x06
	*/
	 
	CS(1);
}
