#ifndef _SAFETY_H
#define _SAFETY_H

#include "main.h"

typedef struct
{
	uint16_t CurrAd;
	uint16_t OverCurrTime;

	uint16_t PowerAd;
	uint16_t PowerBuf[10];
	uint16_t  PowerIndex;
	uint16_t OverPowerTime;
	uint16_t UnderPowerTime;

}safety_define;
extern safety_define safety;

extern void CurrIRms(void);
extern void PowerSet(void);

#endif