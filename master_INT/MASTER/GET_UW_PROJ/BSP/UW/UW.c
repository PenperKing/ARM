#include "UW.h" 
#include "can.h"
#include "delay.h"
#include <stdio.h>
#include "Include.h"
//����GPIOG��GPIOF���÷�����ͻ
//������GPIOF,�޷�����GPIOG
float time[4]={0};
extern u32 ms_count[3];
extern u8 Get_UW_flag[4];
u8 CanBuf[3][3]={0};
u8 state=0;
u8 Seq[4]={1};
float distance[4]={0};

float Dis_test=0;
void UW_Init(void)
{    	 
  GPIO_InitTypeDef  GPIO_InitStructure;

  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOG, ENABLE);

 
  GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_All;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;//��ͨ���ģʽ
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;//�������
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;//100MHz
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;//����
  GPIO_Init(GPIOG, &GPIO_InitStructure);//��ʼ��
	
	  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);

 
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4|GPIO_Pin_5|GPIO_Pin_6|GPIO_Pin_7;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;//��ͨ���ģʽ
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;//�������
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;//100MHz
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;//����
  GPIO_Init(GPIOD, &GPIO_InitStructure);//��ʼ��
	GPIO_ResetBits(GPIOD, GPIO_Pin_4|GPIO_Pin_5|GPIO_Pin_6|GPIO_Pin_7);
	
	UW_GAIN(0x5555);
	
	//UW_GAINԽ�󣬽�������Խ��
	EXTIX_Init();
}

	   
//�ⲿ�жϳ�ʼ������
void EXTIX_Init(void)
{
	NVIC_InitTypeDef   NVIC_InitStructure;
	EXTI_InitTypeDef   EXTI_InitStructure;
  GPIO_InitTypeDef  GPIO_InitStructure;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE);//ʹ��SYSCFGʱ��
	
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE, ENABLE);//ʹ��GPIOA,GPIOEʱ��
 
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2|GPIO_Pin_3|GPIO_Pin_4|GPIO_Pin_5; 
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;//��ͨ����ģʽ
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;//100M
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;//����
  GPIO_Init(GPIOE, &GPIO_InitStructure);
	
	SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOE, EXTI_PinSource2);
	SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOE, EXTI_PinSource3);
	SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOE, EXTI_PinSource4);
	SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOE, EXTI_PinSource5);

	
	/* ����EXTI_Line2,3,4 */
	EXTI_InitStructure.EXTI_Line = EXTI_Line2| EXTI_Line3 | EXTI_Line4 | EXTI_Line5;
  EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;//�ж��¼�
  EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling; //�½��ش���
  EXTI_InitStructure.EXTI_LineCmd = ENABLE;//�ж���ʹ��
  EXTI_Init(&EXTI_InitStructure);//����
 
	NVIC_InitStructure.NVIC_IRQChannel = EXTI2_IRQn;//�ⲿ�ж�2
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x02;//��ռ���ȼ�3
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x03;//�����ȼ�2
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;//ʹ���ⲿ�ж�ͨ��
  NVIC_Init(&NVIC_InitStructure);//����
	
	
	NVIC_InitStructure.NVIC_IRQChannel = EXTI3_IRQn;//�ⲿ�ж�3
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x02;//��ռ���ȼ�2
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x03;//�����ȼ�2
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;//ʹ���ⲿ�ж�ͨ��
  NVIC_Init(&NVIC_InitStructure);//����
	
	
	NVIC_InitStructure.NVIC_IRQChannel = EXTI4_IRQn;//�ⲿ�ж�4
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x02;//��ռ���ȼ�1
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x03;//�����ȼ�2
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;//ʹ���ⲿ�ж�ͨ��
  NVIC_Init(&NVIC_InitStructure);//����
	
	NVIC_InitStructure.NVIC_IRQChannel = EXTI9_5_IRQn;//�ⲿ�ж�5
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x02;//��ռ���ȼ�1
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x03;//�����ȼ�2
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;//ʹ���ⲿ�ж�ͨ��
  NVIC_Init(&NVIC_InitStructure);//����
	   
}




//�ⲿ�ж�2�������
void EXTI2_IRQHandler(void)
{
	if(EXTI_GetITStatus(EXTI_Line2) != RESET&&Get_UW_flag[0])
  {
	 
			 time[0]=TIM_GetCounter(TIM1)+ms_count[0]*65536;
				Get_UW_flag[0]=0;
				state|=0x01;
				define_state(state);
	//			time[0]=TIM_GetCounter(TIM1)+ms_count[0]*65536;
	//			Get_UW_flag[0]=0;
	//			time[0]=time[0]/1000-15;
	//     Dis_test=time[0]*Voice_SPEED/10+10;
	//			
	//			printf("%f,",Dis_test);
	}
	 EXTI_ClearITPendingBit(EXTI_Line2);//���LINE2�ϵ��жϱ�־λ 
} 
//�ⲿ�ж�3�������
void EXTI3_IRQHandler(void)
{
	if(EXTI_GetITStatus(EXTI_Line3) != RESET&&Get_UW_flag[1])
  {
			 time[1]=TIM_GetCounter(TIM1)+ms_count[0]*65536;
				Get_UW_flag[1]=0;
				state|=0x02;
				define_state(state);
	}
	EXTI_ClearITPendingBit(EXTI_Line3);  //���LINE3�ϵ��жϱ�־λ  
}
//�ⲿ�ж�4�������
void EXTI4_IRQHandler(void)
{
	if(EXTI_GetITStatus(EXTI_Line4) != RESET&&Get_UW_flag[2])
  {
		 time[2]=TIM_GetCounter(TIM1)+ms_count[0]*65536;
			Get_UW_flag[2]=0;
			state|=0x04;
			define_state(state);
	}		
	EXTI_ClearITPendingBit(EXTI_Line4);//���LINE4�ϵ��жϱ�־λ
}

//�ⲿ�ж�1�������
void EXTI9_5_IRQHandler(void)
{
	if(EXTI_GetITStatus(EXTI_Line5) != RESET&&Get_UW_flag[3])
  {
		 time[3]=TIM_GetCounter(TIM1)+ms_count[0]*65536;
			Get_UW_flag[3]=0;
			state|=0x08;
		  define_state(state);
	}
		EXTI_ClearITPendingBit(EXTI_Line5);//���LINE2�ϵ��жϱ�־λ 
}

void jinzhi_transmit_10_16(u8 *date,u8 len)
{
  for(int i=0;i<len;i++)
   date[i]=(date[i]/10)*16+date[i]%10;
}

