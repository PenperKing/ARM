#ifndef __UW_H
#define __UW_H
#include "sys.h"



#define UW_GAIN(n) GPIO_Write(GPIOG,n)

//LED�˿ڶ���
#define INH_1 PDout(5)
#define INH_2 PDout(6)
#define INH_3 PDout(7)
void UW_Init(void);//��ʼ��	
void EXTIX_Init(void);
void jinzhi_transmit_10_16(u8 *date,u8 len);

#endif
