
/*---------------------------------------------------------------------*/
/* --- STC MCU International Limited ----------------------------------*/
/* --- STC 1T Series MCU Demo Programme -------------------------------*/
/* --- Mobile: 13922805190 --------------------------------------------*/
/* --- Fax: 0513-55012956,55012947,55012969 ---------------------------*/
/* --- Tel: 0513-55012928,55012929,55012966 ---------------------------*/
/* --- Web: www.GXWMCU.com   www.stcmcu.com ---------------------------*/
/* --- QQ:  800003751 -------------------------------------------------*/
/* ���Ҫ�ڳ�����ʹ�ô˴���,���ڳ�����ע��ʹ���˺꾧�Ƽ������ϼ�����   */
/*---------------------------------------------------------------------*/


/*************	����˵��	**************

����������ʹ��STC15W401AS-35I-SOP16<RMB1.6>��������ģ�õ��޴�������ˢ����ֱ�����.

������ο������ϵĴ���(����: ����), ��������.

��·ͼ���ļ� "BLDC-V10-ʵ���·.pdf".

�����ź���P3.2�����������ź�, ���5~20ms, ������1.000~1.610ms.

1.160ms��ʼ����, 1.610msΪ����ٶ�, �ֱ���Ϊ2us.

����������Ǽ򵥿���, ���û�д��� ��0��ʱ30���л� �������.

���ڹ�0��ⲿ����RC�˲�, ���Ըı����ֵ���Դ�Լ�Ķ�Ӧ�������ʱ��ʱ30�ȵ�ʱ��.

�����߿��������Ƶ�·�ͳ���.

******************************************/

#define MAIN_Fosc		24000000L	//������ʱ��

#include "STC15Fxxxx.H"

//CMPCR1
#define	CMPEN	0x80	//1: ����Ƚ���, 0: ��ֹ,�رձȽ�����Դ
#define	CMPIF	0x40	//�Ƚ����жϱ�־, ���������ػ��½����ж�, �����0
#define	PIE		0x20	//1: �ȽϽ����0��1, �����������ж�
#define	NIE		0x10	//1: �ȽϽ����1��0, �����½����ж�
#define	PIS		0x08	//����������ѡ��, 0: ѡ���ⲿP5.5��������,           1: ��ADCIS[2:0]��ѡ���ADC�������������.
#define	NIS		0x04	//���븺����ѡ��, 0: ѡ���ڲ�BandGap��ѹBGv��������, 1: ѡ���ⲿP5.4������.
#define	CMPOE	0x02	//1: ����ȽϽ�������P1.2, 0: ��ֹ.
#define	CMPRES	0x01	//�ȽϽ��, 1: CMP+��ƽ����CMP-,  0: CMP+��ƽ����CMP-,  ֻ��

//CMPCR2
#define	INVCMPO	0x80	//1: �Ƚ������ȡ��,  0: ��ȡ��
#define	DISFLT	0x40	//1: �ر�0.1uF�˲�,   0: ����
#define	LCDTY	0x00	//0~63, �ȽϽ���仯��ʱ������

sbit SWK = P3^3; //�ⲿ����
sbit LED = P5^5; //LED


sbit PWM2_L = P3^4;
sbit PWM1_L = P3^5;
sbit PWM0_L = P3^6;


u8	Step;
u8	PWM_Value; // ����PWMռ�ձȵ�ֵ
u16	RxPulseWide; //
bit	B_RxOk;
bit	B_RUN;
u8	PWW_Set;
u8	Rx_cnt;
u8	TimeOut;	//��ת��ʱ

#define DISABLE_CMP_INT CMPCR1 &= ~0X40		// �رձȽ����ж�
#define ENABLE_CMP_INT  CMPCR1 |= 0X40		// �򿪱Ƚ����ж�

/*************************/

void	Delay_n_ms(u8 dly)
{
	u16	j;
	do
	{
		j = MAIN_Fosc / 13000;	//��ʱ1ms, �������ڴ˽���������
		while(--j)	;
	}while(--dly);
}


void delay_us(u8 us)
{
	do
	{
		NOP(20);	//@24MHz
	}
	while(--us);
}
 void StepXL(void) // �������к���
{
 switch(Step)
  {
	case 0:  //AB
		CCAP1H = PWM_Value;CCAP2H=0;CCAP0H=0;//��B�� ����
		PWM0_L=1;PWM1_L =0;PWM2_L=0;//��A��ĸ�
		ADC_CONTR = 0XED;	CMPCR1 = 0xAC;// ѡ��P1.5��ΪADC���� ��c���ѹ 	�������ж�
		break;
	case 1:  //AC
		CCAP2H = PWM_Value;CCAP0H=0;CCAP1H=0;//��C�� ����
		PWM0_L=1;PWM1_L =0;PWM2_L=0;//��A��ĸ�
		ADC_CONTR = 0XEC;	CMPCR1 = 0x9C;// ѡ��P1.4��ΪADC���� ��B���ѹ	�½����ж�
		break;
	case 2:  //BC
		CCAP2H = PWM_Value;CCAP0H=0;CCAP1H=0;//��C�� ����
		PWM0_L=0;PWM1_L =1;PWM2_L=0;//��B��ĸ�
		ADC_CONTR = 0XEB;	CMPCR1 = 0xAC;// ѡ��P1.3��ΪADC���� ��a���ѹ	�������ж�
		break;
	case 3:  //BA
		CCAP0H = PWM_Value;CCAP1H=0;CCAP2H=0;//��A�� ����
		PWM0_L=0;PWM1_L =1;PWM2_L=0;//��B��ĸ�
		ADC_CONTR = 0XED;	CMPCR1 = 0x9C;// ѡ��P1.5��ΪADC���� ��c���ѹ  �½����ж�
		break;
	case 4:  //CA
		CCAP0H = PWM_Value;CCAP1H=0;CCAP2H=0;//��A�� ����
		PWM0_L=0;PWM1_L =0;PWM2_L=1;//��C��ĸ�
		ADC_CONTR = 0XEC;	CMPCR1 = 0xAC;// ѡ��P1.4��ΪADC���� ��B���ѹ	�������ж�
		break;
	case 5:  //CB
		CCAP1H = PWM_Value;CCAP2H=0;CCAP0H=0;//��B�� ����
		PWM0_L=0;PWM1_L =0;PWM2_L=1;//��C��ĸ�
		ADC_CONTR = 0XEB;	CMPCR1 = 0x9C;// ѡ��P1.3��ΪADC���� ��a���ѹ	�½����ж�
		break;


	default:
		break;
  }	
}

#define CCP_S0 0x10                 //P_SW1.4
#define CCP_S1 0x20                 //P_SW1.5
void PWM_Init(void)
{
	PWM0_L = 0;
	PWM1_L = 0;
	PWM2_L = 0;
	
	P3M0=0x70;P3M1=0x00;
	P5M0=0x00;P5M1=0x00;

   
//	CMOD = 1 << 1; //ѡ��ϵͳʱ��/2Ϊʱ��Դ����PWMƵ��=24M/2/256=46.9K
//	CMOD = 5 << 1; //ѡ��ϵͳʱ��/4Ϊʱ��Դ����PWMƵ��=24M/4/256=23.4K
	CMOD = 6 << 1; //ѡ��ϵͳʱ��/6Ϊʱ��Դ����PWMƵ��=24M/6/256=15.6K(Ч����)

	CL=0;			// PCA����������
	CH=0;

	
	PCA_PWM0 = 0X00;
	CCAP0H=0;    // ��ʼ��ռ�ձ�Ϊ0% H��ֵװ�ص�L��
	CCAP0L=0;
	CCAPM0=0x42;	// ����ΪPWMģʽ
	
	PCA_PWM1 = 0X00;
	CCAP1H=0;    // ��ʼ��ռ�ձ�Ϊ0%
	CCAP1L=0;
	CCAPM1=0x42;	// ����ΪPWMģʽ
	
	PCA_PWM2 = 0X00;
	CCAP2H=0;    // ��ʼ��ռ�ձ�Ϊ0%
	CCAP2L=0;
	CCAPM2=0x42;	// ����ΪPWMģʽ
	
	CR = 1;
}

void ADC_Init(void)
{
	P1M0=0x00;P1M1=0x1C;
	P1ASF = 0X38; // ��ͨP1.3 P1.4 P1.5��AD�����
}
//ADC�ж�
void CMP_INT(void) interrupt 21
{
	CMPCR1 &= ~0X40; // ���������жϱ�־λ
	if(Step<5)	Step++;	 //����
	else		Step = 0;
	StepXL();
	TimeOut = 15;	//10ms��ʱ
}

void CMP_Init(void)
{
	CMPCR1 = 0X8C;	// 1000 1100 �򿪱Ƚ�����P5.4��Ϊ�Ƚ����ķ�������ˣ�ADC������Ϊ������� 
	CMPCR2 = 60;	// 60��ʱ���˲�
	P5n_pure_input(0x10);
}

u8 StartMotor(void)	  //�����������
{
	u16 timer,i;
	DISABLE_CMP_INT; // �رȽ����ж�
	PWM_Value = 70;	// ��ʼռ�ձ�
	Step = 1;StepXL();	// ��ʼλ��
	Delay_n_ms(8);		//��������ʱ�䣨����̫�ߣ�
	PWM_Value = 50;	// ��ʼռ�ձ�
	Delay_n_ms(20);	//��������ʱ�䣨����̫�ߣ�
	PWM_Value = PWM_Value;// 
	timer = 50;   //
//	return(1);
	while(1)
	{
		for(i=0; i<timer; i++)	delay_us(50);
		timer--;
		if(timer < 35)
        {
            PWM0_L=0;PWM1_L =0;PWM2_L=0;//��A��ĸ�
            CCAP2H=0;CCAP0H=0;CCAP1H=0;//��C�� ����
            return(1);//����ѭ��
        }  	
		if( Step < 5)	Step++;
		else			Step = 0;
		StepXL();
	}
}



/**********************************************/
void main(void)
{
	u16 kk;
    bit ready_bz=1;
	
	PWM_Init();
	ADC_Init();
	CMP_Init();
	LED = 0; //����LED

 ////////////////////////////////
 //������3��  ��1��2��3��
	Delay_n_ms(250);	
    PWM_Value = 30;	//������С	10-100
	Step = 0;
	StepXL();			// ��ʼλ��
	Delay_n_ms(10);

	for(kk=1500; kk>0; kk--)
	{Step = 1,StepXL(),delay_us(10);			// ��ʼλ��;  //
	 Step = 3,StepXL(),delay_us(10);}
	Delay_n_ms(250);	
	for(kk=1500; kk>0; kk--)
	{Step = 1,StepXL(),delay_us(15);			// ��ʼλ��;  //
	 Step = 3,StepXL(),delay_us(15);}
	Delay_n_ms(250);	
	for(kk=1500; kk>0; kk--)
	{Step = 1,StepXL(),delay_us(20);			// ��ʼλ��;  //
	 Step = 3,StepXL(),delay_us(20);}

 //////////////////////////////////////


	PWM_Value = 0;
	RxPulseWide = 1000;
	PWW_Set = 0;
	Rx_cnt  = 0;
	TimeOut = 0;

	EA  = 1; // �����ж�
	LED = 1; //�ر�LED
	
	while (1)
	{
	Delay_n_ms(1);	//��ʱ1ms, �������ڴ˽���������

	//
	if(SWK==0)	//���δ����, ���������
	{
	 LED=0;//LED
	 StartMotor();	// �������
//	 CMPCR1 &= ~0X40;// ���������жϱ�־λ
	 ENABLE_CMP_INT; // �򿪱Ƚ����ж�
	 TimeOut = 0;
	 B_RUN = 1;
	 while(SWK==0)  //������תʹ��һ�³���
		{
	     LED=1;//LED
		 PWM_Value=150;
		}
	}
	else
	{
	 PWM_Value = 0;
	 B_RUN = 0;
	 CCAP0H=0;	CCAP1H=0;	CCAP2H=0;  // ռ�ձ�Ϊ0
	 PWM0_L=0;	PWM1_L=0;	PWM2_L=0;  // ���� ���׸�λ
	 DISABLE_CMP_INT; // �رȽ����ж�
	}
             
	
	}
}



