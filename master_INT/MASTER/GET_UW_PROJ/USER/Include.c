#include "Include.h" 
#include "arm_math.h" 

extern u32 ms_count[3];
extern u8 Get_UW_flag[3];
extern u32 ms;
extern u8 state;
extern u8 Seq[4];
extern float distance[4];
extern float time[4];
float time_back[4]={0};
extern unsigned char SI_Send[10];
double test=0;

int Dis_UART_OUT[3];

float Length_a=AB/2;
float Length_b=AD/2;
float XA2,XB2,XC2,XD2,Length_a2,Length_b2;


const Point_Dat_Define ABCD[4]={47.25,48.0,0,177.03,//A
	                             -47.25,48.0,0,197.56, //B
	                             -47.25,-48.0,0,186.26,//C
	                              47.25,-48.0,0,174.99 //D
                                };
Point_Dat_Define ABC[3];//A       21.54   -11.21 162.65	
																
void define_state(u8 state)
{
	  switch (state)
		{
			case 0x0f:OutPutDate_4_axis();break;
			case 0x07:
			case 0x0B:
			case 0x0D:
			case 0x0E:OutPutDate_3_axis(state);break;
			default :break;
		}
}
void OutPutDate_3_axis(u8 state)
{
	if(state==0x0E)//缺A
	{
		ABC[0]=ABCD[1];
		ABC[1]=ABCD[2];
		ABC[2]=ABCD[3];
		ABC[1].Distance=(time[1]/1000-15)*Voice_SPEED/10+10;
		ABC[2].Distance=(time[2]/1000-15)*Voice_SPEED/10+10;
		ABC[3].Distance=(time[3]/1000-15)*Voice_SPEED/10+10;
		Calculate_xPoint_XYZ();
	}
	if(state==0x0D)//缺B
	{
		ABC[0]=ABCD[0];
		ABC[1]=ABCD[2];
		ABC[2]=ABCD[3];
		ABC[1].Distance=(time[0]/1000-15)*Voice_SPEED/10+10;
		ABC[2].Distance=(time[2]/1000-15)*Voice_SPEED/10+10;
		ABC[3].Distance=(time[3]/1000-15)*Voice_SPEED/10+10;
		Calculate_xPoint_XYZ();
	}
		if(state==0x0B)//缺C
	{
		ABC[0]=ABCD[0];
		ABC[1]=ABCD[1];
		ABC[2]=ABCD[3];
		ABC[1].Distance=(time[0]/1000-15)*Voice_SPEED/10+10;
		ABC[2].Distance=(time[1]/1000-15)*Voice_SPEED/10+10;
		ABC[3].Distance=(time[3]/1000-15)*Voice_SPEED/10+10;
		Calculate_xPoint_XYZ();
	}
		if(state==0x07)//缺D
	{
		ABC[0]=ABCD[0];
		ABC[1]=ABCD[1];
		ABC[2]=ABCD[2];
		ABC[1].Distance=(time[0]/1000-15)*Voice_SPEED/10+10;
		ABC[2].Distance=(time[1]/1000-15)*Voice_SPEED/10+10;
		ABC[3].Distance=(time[2]/1000-15)*Voice_SPEED/10+10;
		Calculate_xPoint_XYZ();
	}
}
//3us
void* LocationGet(Dis_InitTypeDef Dis)
{
   Coord_InitTypeDef Coord;
   void *ret=&Coord;
	 float z1,z2;
   XA2=Dis.A*Dis.A;
   XB2=Dis.B*Dis.B;
   XC2=Dis.C*Dis.C;
   XD2=Dis.D*Dis.D;
   Length_a2=Length_a*Length_a;
   Length_b2=Length_b*Length_b;
   Coord.x=(XC2-XD2+XB2-XA2)/8/Length_a;
   Coord.y=(XD2-XA2+XC2-XB2)/8/Length_b;
	 arm_sqrt_f32((XA2+XB2-Length_a2-Length_b2-2*Coord.x*Coord.x-2*Coord.y*Coord.y)/2,&z1);
	 arm_sqrt_f32((XC2+XD2-Length_a2+Length_b2-2*Coord.x*Coord.x-2*Coord.y*Coord.y)/2,&z2);
   Coord.z=(z1+z2)/2;
	return ret;
}


//四个距离计算坐标
void OutPutDate_4_axis(void)
{
	state=0;
	u8 i=0;
	Coord_InitTypeDef* Now_Location;
  Dis_InitTypeDef Now_Dis;
	
	time[0]=time[0]/1000-15;
	time[1]=time[1]/1000-15;
	time[2]=time[2]/1000-15;
	time[3]=time[3]/1000-15;
  
//NOW_Dis储存四个点距离
	
//	float max_min=findmax_min(time);
//	
//	if(max_min<1.5)
//	{
//		for(i=0;i<4;i++)
//		 time_back[i]=time[i];
//	}
//	else 
//	{
//		for(i=0;i<4;i++)
//		 time[i]=time_back[i];
//	}	
	Now_Dis.A=time[0]*Voice_SPEED/10+10;
	Now_Dis.B=time[1]*Voice_SPEED/10+10;
	Now_Dis.C=time[2]*Voice_SPEED/10+10;
	Now_Dis.D=time[3]*Voice_SPEED/10+10;
	
	//printf("AX=%0.2f,BX=%0.2f,CX=%0.2f,DX=%0.2f\n",Now_Dis.A,Now_Dis.B,Now_Dis.C,Now_Dis.D);
	
	Now_Location=(Coord_InitTypeDef*)LocationGet(Now_Dis);
	//此处加printf为啥结构体指针释放？？？？？？
	Dis_UART_OUT[0]=(int)(Now_Location->x*100+0.5);
	Dis_UART_OUT[1]=(int)(Now_Location->y*100+0.5);
	Dis_UART_OUT[2]=(int)(Now_Location->z*100+0.5);
  
	//printf("%0.2f,",Dis_UART_OUT[0]/100.0,Dis_UART_OUT[1]/100.0,Dis_UART_OUT[2]/100.0);
	printf("%0.2f %0.2f %0.2f %0.2f %0.2f %0.2f %0.2f ",Now_Dis.A,Now_Dis.B,Now_Dis.C,Now_Dis.D,\
	Dis_UART_OUT[0]/100.0,Dis_UART_OUT[1]/100.0,Dis_UART_OUT[2]/100.0);
	SI_Send[8]=0;
	if(Dis_UART_OUT[0]<0)SI_Send[8]|=0x01,Dis_UART_OUT[0]=-Dis_UART_OUT[0];
	else SI_Send[8]&=~0x01;
	if(Dis_UART_OUT[1]<0)SI_Send[8]|=0x02,Dis_UART_OUT[1]=-Dis_UART_OUT[1];
	else SI_Send[8]&=~0x02;
	if(Dis_UART_OUT[2]<0)SI_Send[8]|=0x04,Dis_UART_OUT[2]=-Dis_UART_OUT[2];
	else SI_Send[8]&=~0x04;
  SI_Send[2]=Dis_UART_OUT[0]/256;
	SI_Send[3]=Dis_UART_OUT[0]%256;
	
	SI_Send[4]=Dis_UART_OUT[1]/256;
	SI_Send[5]=Dis_UART_OUT[1]%256;
	
	SI_Send[6]=Dis_UART_OUT[2]/256;
	SI_Send[7]=Dis_UART_OUT[2]%256;

}
//声速 c=331.45+0.61t，当前温度
//超声波波动1cm

void TIM_Run_Limit(void)
{
	 if((TIM_GetCounter(TIM1)+ms_count[0]*65536)/1000>5000)
		 {
			 ms_count[0]=0;
			 Get_UW_flag[0]=0;
		 }
}

float findmax_min(float *time)
{
	float max_value,min_value;
	u32 max_num,min_num;
	arm_max_f32(time,4,&max_value,&max_num);
	arm_min_f32(time,4,&min_value,&min_num);
	
	return max_value-min_value;
}


											
//3us
void Calculate_xPoint_XYZ(void)
{
    int i=0;
    float Cal_X;
    float Cal_Y;
    float Cal_Z;

    float Cal_a=ABC[0].x-ABC[1].x;
    float Cal_b=ABC[0].y-ABC[1].y;
    float Cal_c=ABC[0].x-ABC[2].x;
    float Cal_d=ABC[0].y-ABC[2].y;
    float Cal_m=0.5*(ABC[1].Distance*ABC[1].Distance-ABC[0].Distance*ABC[0].Distance+ABC[0].x*ABC[0].x+\
    ABC[0].y*ABC[0].y-ABC[1].x*ABC[1].x-ABC[1].y*ABC[1].y);
    float Cal_n=0.5*(ABC[2].Distance*ABC[2].Distance-ABC[0].Distance*ABC[0].Distance+ABC[0].x*ABC[0].x+\
    ABC[0].y*ABC[0].y-ABC[2].x*ABC[2].x-ABC[2].y*ABC[2].y);

    Cal_X=(Cal_b*Cal_n-Cal_d*Cal_m)/(Cal_b*Cal_c-Cal_a*Cal_d);
    Cal_Y=(Cal_a*Cal_n-Cal_c*Cal_m)/(Cal_d*Cal_d-Cal_b*Cal_c);
    arm_sqrt_f32(ABC[1].Distance*ABC[1].Distance-(ABC[0].x-Cal_X)*(ABC[0].x-Cal_X)\
               -(ABC[0].y-Cal_Y)*(ABC[0].y-Cal_Y),&Cal_Z);
		
		
	
	Dis_UART_OUT[0]=(int)(Cal_X*100+0.5);
	Dis_UART_OUT[1]=(int)(Cal_Y*100+0.5);
	Dis_UART_OUT[2]=(int)(Cal_Z*100+0.5);
  
	//printf("%0.2f,",Dis_UART_OUT[0]/100.0,Dis_UART_OUT[1]/100.0,Dis_UART_OUT[2]/100.0);

	SI_Send[8]=0;
	if(Dis_UART_OUT[0]<0)SI_Send[8]|=0x01,Dis_UART_OUT[0]=-Dis_UART_OUT[0];
	else SI_Send[8]&=~0x01;
	if(Dis_UART_OUT[1]<0)SI_Send[8]|=0x02,Dis_UART_OUT[1]=-Dis_UART_OUT[1];
	else SI_Send[8]&=~0x02;
	if(Dis_UART_OUT[2]<0)SI_Send[8]|=0x04,Dis_UART_OUT[2]=-Dis_UART_OUT[2];
	else SI_Send[8]&=~0x04;
  SI_Send[2]=Dis_UART_OUT[0]/256;
	SI_Send[3]=Dis_UART_OUT[0]%256;
	
	SI_Send[4]=Dis_UART_OUT[1]/256;
	SI_Send[5]=Dis_UART_OUT[1]%256;
	
	SI_Send[6]=Dis_UART_OUT[2]/256;
	SI_Send[7]=Dis_UART_OUT[2]%256;
   // printf("%0.2f,%0.2f,%0.2f\n",Cal_X,Cal_Y,Cal_Z);
}
