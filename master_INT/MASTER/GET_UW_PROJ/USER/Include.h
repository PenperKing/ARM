#ifndef __Include_h
#define __Include_h
#include "sys.h"
#include "delay.h"
#include "led.h"
#include "usart.h"	
#include "timer.h"
#include "UW.h" 
#include "key.h"
#include "USART2.h" 

#define NOW_WD 32
#define Voice_SPEED (331.45+0.61*NOW_WD)  

typedef struct _Coordinate
{
	float x;
	float y;
	float z;
}Coord_InitTypeDef;

typedef struct _Distance
{
	float A;
	float B;
	float C;
	float D;
}Dis_InitTypeDef;

//根据三个点三个坐标求出X,NEW .best THAN HEAD
typedef struct _Point_Dat
{
    float x;
    float y;
    float z;
    float Distance;
}Point_Dat_Define;




#define AB 94.5
#define AD 96.0

void* LocationGet(Dis_InitTypeDef Dis);
void TIM_Run_Limit(void);
void OutPutDate_4_axis(void);	
unsigned char get_check_sum(unsigned char *pack, unsigned short pack_len);
float findmax_min(float *time);
void define_state(u8 state);
void OutPutDate_3_axis(u8 state);
void Calculate_xPoint_XYZ(void);
#endif
