#ifndef __USART2_H
#define __USART2_H
#include "sys.h"

void USART2_Init(u32 bound);
void UART2_Send_Byte(u8 Byte);
void UART2_Send_Data(u8 *buf,u8 len);
#endif
