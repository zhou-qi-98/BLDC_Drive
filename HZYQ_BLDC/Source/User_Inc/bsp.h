#ifndef __BSP_H__
#define __BSP_H__

#include "gpio.h"
#include "var.h"
#include "typedef.h"

int PID_Function(uint16_t desir_speed, uint16_t measure_speed);

void PID_Init(void);


#endif

