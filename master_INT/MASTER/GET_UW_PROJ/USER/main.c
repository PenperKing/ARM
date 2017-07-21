#include "Include.h" 


int main(void)
{ 
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//设置系统中断优先级分组2
	delay_init(168);  //初始化延时函数
	uart_init(115200);//初始化串口波特率为115200
  USART2_Init(115200);
	LED_Init();
	UW_Init();
	TIM1_Int_Init(65535,168-1);	//168Mhz计数频率,用来计算超声波传输时间

	TIM4_Int_Init(9999,84-1);	//100Hz
  
   while(1) 
	{
	  TIM_Run_Limit();
  }
}
