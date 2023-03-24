#include "bldc.h"


bldc_define bldc;

//code u8 HalltoSetup[8]={7,5,3,4,1,0,2,7};
//code u8 BemfCode[6] = {4,6,2,3,1,5};


/*******************************************************************************
  * @brief  �������
  * @param  ��
  * @retval ��
  */
void StepXL(void) 
{
	/* �ٶȼ��㵥Ԫ */
	bldc.SpeedT[bldc.SpeedTindex++] = GetSpeedTime();
	if(bldc.SpeedTindex>5) bldc.SpeedTindex=0;
	chip.Speedtime1 = BytetoWord(TH0, TL0);
	 
	/* ���� */
	if(bldc.dEnPhase==false) return;  // �ر��˻���
	if(bldc.dDirLas == dCCW)
	{
		switch(bldc.dphase)
		{
		case 0:  // AB
			_AHpwm;
			_BL1;
	
			bldc.adBuf[currbufchang] = Getad(currchang);
			ADC_CONTR = 5;      //ѡ��P1.5��ΪADC���� ��c���ѹ
			CMPCR1    = 0x9C;   //bit7=1 ����Ƚ���, bit4=1 �ȽϽ����1��0, �����½����ж� (������Ӧ�½����ж�?)
			break;
	
		case 1:  // AC
			_AHpwm;
			_CL1;
	
			bldc.adBuf[volbufchang] = Getad(volchang);
			ADC_CONTR = 4;      //ѡ��P1.4��ΪADC���� ��B���ѹ
			CMPCR1    = 0xAC;   //�������ж�
			break;
	
		case 2:  // BC
			_BHpwm;
			_CL1;
	
			bldc.adBuf[ntcbufchang] = Getad(ntcchang);
			ADC_CONTR = 3;      //ѡ��P1.3��ΪADC���� ��a���ѹ
			CMPCR1    = 0x9C;   //�½����ж�
			break;
	
		case 3:  // BA
			_BHpwm;
			_AL1;
	
			bldc.adBuf[currbufchang] = Getad(currchang);
			ADC_CONTR = 5;      //ѡ��P1.5��ΪADC���� ��c���ѹ 
			CMPCR1    = 0xAC;   //�������ж�
			break;
	
		case 4: // CA
			_CHpwm;
			_AL1;
	
			bldc.adBuf[volbufchang] = Getad(volchang);
			ADC_CONTR = 4;      //ѡ��P1.4��ΪADC���� ��B���ѹ
			CMPCR1    = 0x9C;   //�½����ж�
			break;
	
		case 5: // CB
			_CHpwm;
			_BL1;
		
			bldc.adBuf[ntcbufchang] = Getad(ntcchang);
			ADC_CONTR = 3;      // ѡ��P1.3��ΪADC���� ��a���ѹ
			CMPCR1    = 0xAC;   //�������ж�
			break;
	
		default:
			break;
		}
	}
	else if(bldc.dDirLas == dCW)
	{
		switch(bldc.dphase)
		{
		case 0: // CA
			_CHpwm;
			_AL1;
	
			bldc.adBuf[volbufchang] = Getad(volchang);
			ADC_CONTR = 4;      //ѡ��P1.4��ΪADC���� ��B���ѹ
			CMPCR1    = 0xAC;   //��
			break;

		case 1:  // BA
			_BHpwm;
			_AL1;
	
			bldc.adBuf[currbufchang] = Getad(currchang);
			ADC_CONTR = 5;      //ѡ��P1.5��ΪADC���� ��c���ѹ 
			CMPCR1    = 0x9C;   //��
			break;

		case 2:  // BC
			_BHpwm;
			_CL1;
	
			bldc.adBuf[ntcbufchang] = Getad(ntcchang);
			ADC_CONTR = 3;      //ѡ��P1.3��ΪADC���� ��a���ѹ
			CMPCR1    = 0xAC;   //��
			break;

		case 3:  // AC
			_AHpwm;
			_CL1;
	
			bldc.adBuf[volbufchang] = Getad(volchang);
			ADC_CONTR = 4;      //ѡ��P1.4��ΪADC���� ��B���ѹ
			CMPCR1    = 0x9C;   //��
			break;

		case 4:  // AB
			_AHpwm;
			_BL1;
	
			bldc.adBuf[currbufchang] = Getad(currchang);
			ADC_CONTR = 5;      //ѡ��P1.5��ΪADC���� ��c���ѹ
			CMPCR1    = 0xAC;   //��
			break;
	
		case 5: // CB
			_CHpwm;
			_BL1;
		
			bldc.adBuf[ntcbufchang] = Getad(ntcchang);
			ADC_CONTR = 3;      // ѡ��P1.3��ΪADC���� ��a���ѹ
			CMPCR1    = 0x9C;   // ��
			break;
	
		default:
			break;
		}	
	}
}



/*******************************************************************************
  * @brief  MOS��ͨ
  * @param  ��
  * @retval ��
  */
void MOSCON(phase)
{
	switch(phase)
	{
	case 0:_AH1;break;
	case 1:_AL1;break;
	case 2:_BH1;break;
	case 3:_BL1;break;
	case 4:_CH1;break;
	case 5:_CL1;break;
	}
}

/*******************************************************************************
  * @brief  MOS�Լ����
  * @param  ��
  * @retval ��
  */
u8 MosCheck(void)
{
	u8 i;
	_ABCL0;
	_ABCH0;
    for(i=0; i<6; i++)
    {
        MOSCON(i);
        if(Getad(currchang)>=__CurrAD(1.0))
        {
            bldc.dState = AmosH + i;
            return false;
        }
		_ABCL0;
		_ABCH0;
    }
    bldc.dState = eCheckMOS;
    return true;
}


/*******************************************************************************
  * @brief  �������
  * @param  ��
  * @retval ��
  */
u8 StartMotor(void)
{
	u16 timer=300,i;
	u16 tempad = 0;
	
	CLEAR_CMP_INT;
	EA = 0;	            						// ����֮ǰ��������Ƚ��ж�				
	bldc.dpwm = __dspeedPwm(5.0);				// 5%ռ�ձ�
	bldc.dphase = 0;							// ��λ
	bldc.dEnPhase  = true;						// ������
	Settime(tSpeedTime);
	StepXL();								    // ��ʼλ��
	if(bldc.adBuf[currbufchang] > __CurrAD(1.0))
	{ 
		Uart1_SendByte(0x01);
		EA = 1;
		return 0;
	}

	Settime(tDelayTime);
	while(!GetDelayTime(3000));

	while(1)
	{
		for(i=0; i<timer; i++)
		{	
			Settime(tDelayTime);
			while(!GetDelayTime(50));   // 50us��ʱ
		}
		timer -= timer / 15 + 1;
		if(timer < 25)	
		{
			CLEAR_CMP_INT;
			ENABLE_CMP_INT;
			Uart1_SendByte(0x03);
			EA = 1;
			return 1;
		}
		bldc.dpwm = __dspeedPwm(10.0);			// 10%ռ�ձ�
		if(++bldc.dphase > 5) bldc.dphase = 0;
		StepXL();
		if(bldc.adBuf[currbufchang] > __CurrAD(2.0)) 
		{
			if(++tempad > 5)
			{
				Uart1_SendByte(0x02);
				EA = 1;
				return 0;
			}
		}
		else
		{
			if(tempad>0) tempad--;
		}
	}
}


/*******************************************************************************
  * @brief  �ٶȼ���
  * @param  None
  * @retval None 
  */
void speedCal(void)
{
    u32 time1=0;
    u8  GsIndex = bldc.SpeedTindex;
	u8  i=0; 

    for(i=0; i<3; i++) 
    {
        if((bldc.SpeedT[GsIndex] >= 0xFFFF) || bldc.dEnPhase == false)     // �������,=0˵��ͣת��
        {
            time1 = __dSleepKp; 
            break;
        }

        time1 += bldc.SpeedT[GsIndex];
        GsIndex = (GsIndex==0) ? 5:(GsIndex-1);
    }  
    if(time1 < 540) time1 = 540;                                                // �ٶ�̫�죬������
    // ��ͨ�˲�
    bldc.dSpeedOut = LowPass((u16)(__dSleepKp / time1), bldc.dSpeedOut, RcCutoff(1000.0, 100.0));
}



/*******************************************************************************
  * @brief  �������״̬
  * @param  ��
  * @retval ��
  */
 void BldcRun(void)
 {
 	switch(bldc.dRunMode)
	{
    //---------------------------------------------------------
	case eCheckMOS:	  // MOS�Լ�
		if(MosCheck())
			bldc.dRunMode = eStopState;	 // �������ֹͣ״̬
		else
			bldc.dRunMode = eFault;		 // ����������״̬	 
		break;

	//---------------------------------------------------------
	case eStopState:  // ֹͣ����
		switch(bldc.dState)
		{
		case eCheckMOS:
			bldc.dState = eStopState;  // ����ɹ�����ֹͣ״̬
			break;

		case eStartState:
		case eRunState:
		case eEabsState: 				// �����л���ɲ����״̬���������ֹͣ״̬
			_ABCL0;
			_ABCH0;
			bldc.dpwm = 0;
			bldc.dState = eStopState;	// ��PWM�رղ�����رպ󣬳ɹ�����ֹͣ״̬
			break;
		}
		break;

	//---------------------------------------------------------
	case eStartState: // �������
		switch(bldc.dState)
		{
	   	case eEabsState:					// ֻ�����л����������²�����������
		case eStopState:					// ֻ����ֹͣ״̬�²�������������
			bldc.dDirLas  = bldc.dDir;      // ��������
			if(StartMotor())
			{  /* �����ɹ� */
				bldc.dSpeedLas = 1;			// ������С������ռ�ձ�
				bldc.dRunMode = eRunState;
				bldc.dState   = eStartState; // �����ɹ����룬��������ģʽ
			}
			else
			{  /* ����ʧ�� */
				bldc.dRunMode = eStopState;	 // ʧ���˳���ֹͣģʽ
				bldc.dState   = eStartState;
				bldc.dEnPhase = false;	//	��ֹ����
				// ��ϵͳ�����ϣ�����ʧ��
				user.errled.errindex = StartErr;
			}
			break;
 
		default:
			break;
		}
		break;

	//---------------------------------------------------------
	case eRunState:	  // �������
		switch(bldc.dState)
		{
		case eStartState:
			bldc.dState   = eRunState;
			break;

		default:
			if(bldc.dSpeed>100) bldc.dSpeed=100;	      // �����ٶ�
			bldc.dSpeedLas = slope(bldc.dSpeed, bldc.dSpeedLas, _slop(100), _slop(10)); 
			if(bldc.dSpeedLas > 0)
			{ 
				bldc.dpwm =  __dspeedPwm(bldc.dSpeedLas); // �����ٶ�

				// ��ռ���
				if(++bldc.dsPhaseTimeOut > dPlugUpTime)
				{
					bldc.dRunMode = eFault;
					bldc.dEnPhase = false;        // ��ֹ����
				}

				// �л�����
				if(bldc.dDirLas != bldc.dDir)
				{
					bldc.dDirFlag = true;		  // ��Ǳ���ɲ����Ϊ����׼����
					bldc.dRunMode = eEabsState;	  // ϵͳָ���л�������ͣ�����ٻ���
				}
			}
			else
			{
				CLEAR_CMP;
				bldc.dRunMode  = eStopState;	
				bldc.dSpeedLas = 0;
				bldc.dpwm      = 0;
				bldc.dEnPhase  = false;	 //	��ֹ����
			}
			break;
		}
		break;

	//---------------------------------------------------------
	case eEabsState:  // ɲ��
		switch(bldc.dState)
		{
		case eRunState:
			_ABCH0;
			_ABCL1;
			if(bldc.dDirFlag==false)
				bldc.dpwm = 0;
			bldc.dEnPhase  = false;	// ��ֹ����
			bldc.dState = eEabsState;
			break;

		case eEabsState:
			if(++bldc.dBkinTime > dBrakdTime)
			{
				bldc.dBkinTime = 0;
				_ABCL0;
				if(bldc.dDirFlag==true)
				{
					bldc.dDirFlag = false;
					bldc.dRunMode = eStartState;  // ����֮���������
				}
				else
					bldc.dRunMode = eStopState;
			}
			break;
		}
		break;

	//---------------------------------------------------------
	case eFault:	  // ����
		switch(bldc.dState)
		{
		case eCheckMOS:
			break;

		case eRunState:
			user.errled.errindex = Stall;
			_ABCL0;
			_ABCH0;
			bldc.dpwm = 0;
			bldc.dEnPhase = false;	// ��ֹ����
			bldc.dState   = eFault;	// ��PWM�رղ�����رպ󣬳ɹ�����ֹͣ״̬
			break;
		}
		break;
	}

	// ��û�л���ʹ�ܵ�����¼�����
	if(bldc.dEnPhase == false)
	{
		bldc.adBuf[currbufchang] = Getad(currchang);
		bldc.adBuf[volbufchang]  = Getad(volchang);
		bldc.adBuf[ntcbufchang]  = Getad(ntcchang);
	}
 }