#include "safety.h"

safety_define safety;

/*******************************************************************************
  * @brief  ƽ����������
  * @param  ��
  * @retval ��
  */
void CurrIRms(void)
{
	safety.CurrAd = LowPass(bldc.adBuf[currbufchang], safety.CurrAd, RcCutoff(1000.0, 20.0));
	if(safety.CurrAd > __CurrAD(3.0))
	{
		if(++safety.OverCurrTime > dOverIRmsTime)
		{
			safety.OverCurrTime = dOverIRmsTime;
			user.errled.errindex = Flow3A;	
		}
	}
	else
	{
		if(safety.OverCurrTime > 0) safety.OverCurrTime--;	
	}
}


/*******************************************************************************
  * @brief  ��ѹ����
  * @param  ��
  * @retval ��
  */
void PowerSet(void)
{
	safety.PowerAd = LowPass(bldc.adBuf[volbufchang], safety.PowerAd, RcCutoff(1000.0, 20.0));
	safety.PowerBuf[safety.PowerIndex++] = safety.PowerAd;
	if(safety.PowerIndex >= 10)
	{
		u16 tmpPowerAd = meanFilter(safety.PowerBuf, 10);

		if(tmpPowerAd > __Power(25.0))
		{
			if(++safety.OverPowerTime > dOverPowerTime)
			{
				safety.OverPowerTime = dOverPowerTime;
				user.errled.errindex = OverPowe;
			}
		}
		else
		{
			if(safety.OverPowerTime > 0) safety.OverPowerTime--;
		}


	   	if(tmpPowerAd < __Power(7.0))
		{
			if(++safety.UnderPowerTime > dUnderPowerTime)
			{
				safety.UnderPowerTime = dUnderPowerTime;
				user.errled.errindex = UnderPowe;
			}
		}
		else
		{
			if(safety.UnderPowerTime > 0) safety.UnderPowerTime--;
		}

	} 
}