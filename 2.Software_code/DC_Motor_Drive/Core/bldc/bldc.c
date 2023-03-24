#include "bldc.h"


bldc_define bldc;

//code u8 HalltoSetup[8]={7,5,3,4,1,0,2,7};
//code u8 BemfCode[6] = {4,6,2,3,1,5};


/*******************************************************************************
  * @brief  换相程序
  * @param  无
  * @retval 无
  */
void StepXL(void) 
{
	/* 速度计算单元 */
	bldc.SpeedT[bldc.SpeedTindex++] = GetSpeedTime();
	if(bldc.SpeedTindex>5) bldc.SpeedTindex=0;
	chip.Speedtime1 = BytetoWord(TH0, TL0);
	 
	/* 换相 */
	if(bldc.dEnPhase==false) return;  // 关闭了换相
	if(bldc.dDirLas == dCCW)
	{
		switch(bldc.dphase)
		{
		case 0:  // AB
			_AHpwm;
			_BL1;
	
			bldc.adBuf[currbufchang] = Getad(currchang);
			ADC_CONTR = 5;      //选择P1.5作为ADC输入 即c相电压
			CMPCR1    = 0x9C;   //bit7=1 允许比较器, bit4=1 比较结果由1变0, 产生下降沿中断 (不能响应下降沿中断?)
			break;
	
		case 1:  // AC
			_AHpwm;
			_CL1;
	
			bldc.adBuf[volbufchang] = Getad(volchang);
			ADC_CONTR = 4;      //选择P1.4作为ADC输入 即B相电压
			CMPCR1    = 0xAC;   //上升沿中断
			break;
	
		case 2:  // BC
			_BHpwm;
			_CL1;
	
			bldc.adBuf[ntcbufchang] = Getad(ntcchang);
			ADC_CONTR = 3;      //选择P1.3作为ADC输入 即a相电压
			CMPCR1    = 0x9C;   //下降沿中断
			break;
	
		case 3:  // BA
			_BHpwm;
			_AL1;
	
			bldc.adBuf[currbufchang] = Getad(currchang);
			ADC_CONTR = 5;      //选择P1.5作为ADC输入 即c相电压 
			CMPCR1    = 0xAC;   //上升沿中断
			break;
	
		case 4: // CA
			_CHpwm;
			_AL1;
	
			bldc.adBuf[volbufchang] = Getad(volchang);
			ADC_CONTR = 4;      //选择P1.4作为ADC输入 即B相电压
			CMPCR1    = 0x9C;   //下降沿中断
			break;
	
		case 5: // CB
			_CHpwm;
			_BL1;
		
			bldc.adBuf[ntcbufchang] = Getad(ntcchang);
			ADC_CONTR = 3;      // 选择P1.3作为ADC输入 即a相电压
			CMPCR1    = 0xAC;   //上升沿中断
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
			ADC_CONTR = 4;      //选择P1.4作为ADC输入 即B相电压
			CMPCR1    = 0xAC;   //上
			break;

		case 1:  // BA
			_BHpwm;
			_AL1;
	
			bldc.adBuf[currbufchang] = Getad(currchang);
			ADC_CONTR = 5;      //选择P1.5作为ADC输入 即c相电压 
			CMPCR1    = 0x9C;   //下
			break;

		case 2:  // BC
			_BHpwm;
			_CL1;
	
			bldc.adBuf[ntcbufchang] = Getad(ntcchang);
			ADC_CONTR = 3;      //选择P1.3作为ADC输入 即a相电压
			CMPCR1    = 0xAC;   //上
			break;

		case 3:  // AC
			_AHpwm;
			_CL1;
	
			bldc.adBuf[volbufchang] = Getad(volchang);
			ADC_CONTR = 4;      //选择P1.4作为ADC输入 即B相电压
			CMPCR1    = 0x9C;   //下
			break;

		case 4:  // AB
			_AHpwm;
			_BL1;
	
			bldc.adBuf[currbufchang] = Getad(currchang);
			ADC_CONTR = 5;      //选择P1.5作为ADC输入 即c相电压
			CMPCR1    = 0xAC;   //上
			break;
	
		case 5: // CB
			_CHpwm;
			_BL1;
		
			bldc.adBuf[ntcbufchang] = Getad(ntcchang);
			ADC_CONTR = 3;      // 选择P1.3作为ADC输入 即a相电压
			CMPCR1    = 0x9C;   // 下
			break;
	
		default:
			break;
		}	
	}
}



/*******************************************************************************
  * @brief  MOS导通
  * @param  无
  * @retval 无
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
  * @brief  MOS自检程序
  * @param  无
  * @retval 无
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
  * @brief  电机启动
  * @param  无
  * @retval 无
  */
u8 StartMotor(void)
{
	u16 timer=300,i;
	u16 tempad = 0;
	
	CLEAR_CMP_INT;
	EA = 0;	            						// 启动之前，不进入比较中断				
	bldc.dpwm = __dspeedPwm(5.0);				// 5%占空比
	bldc.dphase = 0;							// 定位
	bldc.dEnPhase  = true;						// 允许换相
	Settime(tSpeedTime);
	StepXL();								    // 初始位置
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
			while(!GetDelayTime(50));   // 50us延时
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
		bldc.dpwm = __dspeedPwm(10.0);			// 10%占空比
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
  * @brief  速度计算
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
        if((bldc.SpeedT[GsIndex] >= 0xFFFF) || bldc.dEnPhase == false)     // 发生溢出,=0说明停转了
        {
            time1 = __dSleepKp; 
            break;
        }

        time1 += bldc.SpeedT[GsIndex];
        GsIndex = (GsIndex==0) ? 5:(GsIndex-1);
    }  
    if(time1 < 540) time1 = 540;                                                // 速度太快，不处理
    // 低通滤波
    bldc.dSpeedOut = LowPass((u16)(__dSleepKp / time1), bldc.dSpeedOut, RcCutoff(1000.0, 100.0));
}



/*******************************************************************************
  * @brief  电机运行状态
  * @param  无
  * @retval 无
  */
 void BldcRun(void)
 {
 	switch(bldc.dRunMode)
	{
    //---------------------------------------------------------
	case eCheckMOS:	  // MOS自检
		if(MosCheck())
			bldc.dRunMode = eStopState;	 // 请求进入停止状态
		else
			bldc.dRunMode = eFault;		 // 请求进入故障状态	 
		break;

	//---------------------------------------------------------
	case eStopState:  // 停止运行
		switch(bldc.dState)
		{
		case eCheckMOS:
			bldc.dState = eStopState;  // 电机成功进入停止状态
			break;

		case eStartState:
		case eRunState:
		case eEabsState: 				// 在运行或者刹车的状态下请求进入停止状态
			_ABCL0;
			_ABCH0;
			bldc.dpwm = 0;
			bldc.dState = eStopState;	// 给PWM关闭并输出关闭后，成功进入停止状态
			break;
		}
		break;

	//---------------------------------------------------------
	case eStartState: // 启动电机
		switch(bldc.dState)
		{
	   	case eEabsState:					// 只有在切换方向的情况下才有重新启动
		case eStopState:					// 只有在停止状态下才允许请求启动
			bldc.dDirLas  = bldc.dDir;      // 给定方向
			if(StartMotor())
			{  /* 启动成功 */
				bldc.dSpeedLas = 1;			// 给定最小的启动占空比
				bldc.dRunMode = eRunState;
				bldc.dState   = eStartState; // 启动成功进入，正常运行模式
			}
			else
			{  /* 启动失败 */
				bldc.dRunMode = eStopState;	 // 失败退出到停止模式
				bldc.dState   = eStartState;
				bldc.dEnPhase = false;	//	禁止换相
				// 给系统包故障，启动失败
				user.errled.errindex = StartErr;
			}
			break;
 
		default:
			break;
		}
		break;

	//---------------------------------------------------------
	case eRunState:	  // 电机运行
		switch(bldc.dState)
		{
		case eStartState:
			bldc.dState   = eRunState;
			break;

		default:
			if(bldc.dSpeed>100) bldc.dSpeed=100;	      // 限制速度
			bldc.dSpeedLas = slope(bldc.dSpeed, bldc.dSpeedLas, _slop(100), _slop(10)); 
			if(bldc.dSpeedLas > 0)
			{ 
				bldc.dpwm =  __dspeedPwm(bldc.dSpeedLas); // 更新速度

				// 堵占检测
				if(++bldc.dsPhaseTimeOut > dPlugUpTime)
				{
					bldc.dRunMode = eFault;
					bldc.dEnPhase = false;        // 禁止换相
				}

				// 切换方向
				if(bldc.dDirLas != bldc.dDir)
				{
					bldc.dDirFlag = true;		  // 标记本次刹车是为换向准备的
					bldc.dRunMode = eEabsState;	  // 系统指定切换方向，先停车，再换向
				}
			}
			else
			{
				CLEAR_CMP;
				bldc.dRunMode  = eStopState;	
				bldc.dSpeedLas = 0;
				bldc.dpwm      = 0;
				bldc.dEnPhase  = false;	 //	禁止换相
			}
			break;
		}
		break;

	//---------------------------------------------------------
	case eEabsState:  // 刹车
		switch(bldc.dState)
		{
		case eRunState:
			_ABCH0;
			_ABCL1;
			if(bldc.dDirFlag==false)
				bldc.dpwm = 0;
			bldc.dEnPhase  = false;	// 禁止换相
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
					bldc.dRunMode = eStartState;  // 换向之后从新启动
				}
				else
					bldc.dRunMode = eStopState;
			}
			break;
		}
		break;

	//---------------------------------------------------------
	case eFault:	  // 故障
		switch(bldc.dState)
		{
		case eCheckMOS:
			break;

		case eRunState:
			user.errled.errindex = Stall;
			_ABCL0;
			_ABCH0;
			bldc.dpwm = 0;
			bldc.dEnPhase = false;	// 禁止换相
			bldc.dState   = eFault;	// 给PWM关闭并输出关闭后，成功进入停止状态
			break;
		}
		break;
	}

	// 在没有换相使能的情况下检测电流
	if(bldc.dEnPhase == false)
	{
		bldc.adBuf[currbufchang] = Getad(currchang);
		bldc.adBuf[volbufchang]  = Getad(volchang);
		bldc.adBuf[ntcbufchang]  = Getad(ntcchang);
	}
 }