#ifndef __Location_h_H
#define __Location_h_H
#include "sys.h"
#include "Include.h" 

float findmax_min(float *time);
void OutPutDate_3_axis(u8 state);
void Calculate_xPoint_XYZ(void);
void OutPutDate_4_axis(void);
void* LocationGet(Dis_InitTypeDef Dis);
#endif
