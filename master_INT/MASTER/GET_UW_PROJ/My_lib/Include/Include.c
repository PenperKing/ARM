#include "Include.h" 
#include "arm_math.h" 

extern u32 ms_count[3];
extern u8 Get_UW_flag[4];
extern unsigned char SI_Send[10];
extern u32 ms;
extern u8 state;
extern u8 Seq[4];


double test=0;

															
void define_state(u8 state)
{
	  if(state==0x0f)  //15us
			  OutPutDate_4_axis();  
	 // else             //14us
   //	  OutPutDate_3_axis(state);
		//需要对ms_count加以限制才能使用上一行语句
}

void TIM_Run_Limit(void)
{
	 if((TIM_GetCounter(TIM1)+ms_count[0]*65536)/1000/168>5000)
		 {
			 ms_count[0]=0;
			 Get_UW_flag[0]=0;
			 Get_UW_flag[1]=0;
			 Get_UW_flag[2]=0;
			 Get_UW_flag[3]=0;
		 }
}



void SI4432_Send(void)
{
	Get_UW_flag[0]=1;
	Get_UW_flag[1]=1;
	Get_UW_flag[2]=1;
	Get_UW_flag[3]=1;
	ms_count[0]=0;
	UART2_Send_Data(SI_Send,10);
	TIM_SetCounter(TIM1, 0);
}
