#include "Include.h" 


int main(void)
{ 
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//����ϵͳ�ж����ȼ�����2
	delay_init(168);  //��ʼ����ʱ����
	uart_init(115200);//��ʼ�����ڲ�����Ϊ115200
  USART2_Init(115200);
	LED_Init();
	UW_Init();
	TIM1_Int_Init(65535,168-1);	//168Mhz����Ƶ��,�������㳬��������ʱ��

	TIM4_Int_Init(9999,84-1);	//100Hz
  
   while(1) 
	{
	  TIM_Run_Limit();
  }
}
