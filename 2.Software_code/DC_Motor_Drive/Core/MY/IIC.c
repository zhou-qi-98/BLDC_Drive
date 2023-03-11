#include "IIC.h"

/* ˽�����Ͷ��� --------------------------------------------------------------*/
/* ˽�к궨�� ----------------------------------------------------------------*/
/* ˽�б��� ------------------------------------------------------------------*/
/* ��չ���� ------------------------------------------------------------------*/
/* ˽�к���ԭ�� --------------------------------------------------------------*/
/* ������ --------------------------------------------------------------------*/
/**
  * ��������: I2C����λ�ӳ٣����400KHz
  * �������: ��
  * �� �� ֵ: ��
  * ˵    ������
  */
static void I2C_Delay(void)
{
	uint8_t i;

	/*��
	 	�����ʱ����ͨ���߼������ǲ��Եõ��ġ�
		CPU��Ƶ72MHzʱ�����ڲ�Flash����, MDK���̲��Ż�
		ѭ������Ϊ10ʱ��SCLƵ�� = 205KHz 
		ѭ������Ϊ7ʱ��SCLƵ�� = 347KHz�� SCL�ߵ�ƽʱ��1.5us��SCL�͵�ƽʱ��2.87us 
	 	ѭ������Ϊ5ʱ��SCLƵ�� = 421KHz�� SCL�ߵ�ƽʱ��1.25us��SCL�͵�ƽʱ��2.375us 
        
    IAR���̱���Ч�ʸߣ���������Ϊ7
	*/
	for (i = 0; i < 10; i++);
}

/**
  * ��������: CPU����I2C���������ź�
  * �������: ��
  * �� �� ֵ: ��
  * ˵    ������
  */
void I2C_Start(void)
{
	/* ��SCL�ߵ�ƽʱ��SDA����һ�������ر�ʾI2C���������ź� */
	I2C_SDA_HIGH();
	I2C_SCL_HIGH();
	I2C_Delay();
	I2C_SDA_LOW();
	I2C_Delay();
	I2C_SCL_LOW();
	I2C_Delay();
}

/**
  * ��������: CPU����I2C����ֹͣ�ź�
  * �������: ��
  * �� �� ֵ: ��
  * ˵    ������
  */
void I2C_Stop(void)
{
	/* ��SCL�ߵ�ƽʱ��SDA����һ�������ر�ʾI2C����ֹͣ�ź� */
	I2C_SDA_LOW();
	I2C_SCL_HIGH();
	I2C_Delay();
	I2C_SDA_HIGH();
}

/**
  * ��������: CPU��I2C�����豸����8bit����
  * �������: Byte �� �ȴ����͵��ֽ�
  * �� �� ֵ: ��
  * ˵    ������
  */
void I2C_SendByte(uint8_t Byte)
{
	uint8_t i;

	/* �ȷ����ֽڵĸ�λbit7 */
	for (i = 0; i < 8; i++)
	{		
		if (Byte & 0x80)
		{
			I2C_SDA_HIGH();
		}
		else
		{
			I2C_SDA_LOW();
		}
		I2C_Delay();
		I2C_SCL_HIGH();
		I2C_Delay();	
		I2C_SCL_LOW();
		if (i == 7)
		{
			I2C_SDA_HIGH(); // �ͷ�����
		}
		Byte <<= 1;	/* ����һ��bit */
		I2C_Delay();
	}
}


/**
  * ��������: CPU��I2C�����豸��ȡ8bit����
  * �������: ��
  * �� �� ֵ: ����������
  * ˵    ������
  */
uint8_t I2C_ReadByte(void)
{
	uint8_t i;
	uint8_t value;

	/* ������1��bitΪ���ݵ�bit7 */
	value = 0;
	for (i = 0; i < 8; i++)
	{
		value <<= 1;
		I2C_SCL_HIGH();
		I2C_Delay();
		if (I2C_SDA_READ())
		{
			value++;
		}
		I2C_SCL_LOW();
		I2C_Delay();
	}
	return value;
}

/**
  * ��������: CPU����һ��ʱ�ӣ�����ȡ������ACKӦ���ź�
  * �������: ��
  * �� �� ֵ: ����0��ʾ��ȷӦ��1��ʾ��������Ӧ
  * ˵    ������
  */
uint8_t I2C_WaitAck(void)
{
	uint8_t re;

	I2C_SDA_HIGH();	/* CPU�ͷ�SDA���� */
	I2C_Delay();
	I2C_SCL_HIGH();	/* CPU����SCL = 1, ��ʱ�����᷵��ACKӦ�� */
	I2C_Delay();
	if (I2C_SDA_READ())	/* CPU��ȡSDA����״̬ */
	{
		re = 1;
	}
	else
	{
		re = 0;
	}
	I2C_SCL_LOW();
	I2C_Delay();
	return re;
}

/**
  * ��������: CPU����һ��ACK�ź�
  * �������: ��
  * �� �� ֵ: ��
  * ˵    ������
  */
void I2C_Ack(void)
{
	I2C_SDA_LOW();	/* CPU����SDA = 0 */
	I2C_Delay();
	I2C_SCL_HIGH();	/* CPU����1��ʱ�� */
	I2C_Delay();
	I2C_SCL_LOW();
	I2C_Delay();
	I2C_SDA_HIGH();	/* CPU�ͷ�SDA���� */
}

/**
  * ��������: CPU����1��NACK�ź�
  * �������: ��
  * �� �� ֵ: ��
  * ˵    ������
  */
void I2C_NAck(void)
{
	I2C_SDA_HIGH();	/* CPU����SDA = 1 */
	I2C_Delay();
	I2C_SCL_HIGH();	/* CPU����1��ʱ�� */
	I2C_Delay();
	I2C_SCL_LOW();
	I2C_Delay();	
}

/**
  * ��������: ����I2C���ߵ�GPIO������ģ��IO�ķ�ʽʵ��
  * �������: ��
  * �� �� ֵ: ��
  * ˵    ������
  */
void I2C_InitGPIO(void)
{
  GPIO_InitTypeDef GPIO_InitStruct;
  
  /* ��GPIOʱ�� */
	I2C_GPIO_CLK_ENABLE();

  GPIO_InitStruct.Pin = I2C_SCL_PIN;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_OD;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_MEDIUM;
  HAL_GPIO_Init(I2C_SCL_PORT, &GPIO_InitStruct);
	//�������������ֲ
	GPIO_InitStruct.Pin = I2C_SDA_PIN;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_OD;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_MEDIUM;
  HAL_GPIO_Init(I2C_SDA_PORT, &GPIO_InitStruct);
	//I2C_SDA_PORT

  /* ��һ��ֹͣ�ź�, ��λI2C�����ϵ������豸������ģʽ */
  I2C_Stop();
}

/**
  * ��������: д�����ݵ�i2c
  * �������: ��
  * �� �� ֵ: ��
  * ˵    ������
  */
void write_i2c(uint8_t device,uint8_t addr,uint8_t dat)
{
	I2C_Start();
	I2C_SendByte(device);
	I2C_WaitAck();
	I2C_SendByte(addr);
	I2C_WaitAck();
	I2C_SendByte(dat);
	I2C_WaitAck();
	I2C_Stop();
}

/**
  * ��������: ��i2c��ȡ����
  * �������: ��
  * �� �� ֵ: ��
  * ˵    ������
  */
uint8_t read_i2c(uint8_t device,uint8_t addr)
{
	uint8_t dat;
	I2C_Start();
	I2C_SendByte(device);
	I2C_WaitAck();
	I2C_SendByte(addr);
	I2C_WaitAck();
	I2C_Start();
	I2C_SendByte(device+0x01);
	I2C_WaitAck();
	dat=I2C_ReadByte();
	I2C_NAck();
	I2C_Stop();
	return dat;
}

/******************* (C) COPYRIGHT 2015-2020 ӲʯǶ��ʽ�����Ŷ� *****END OF FILE****/
