
#include "reg52.h"

//对系统默认数据类型进行重定义 
typedef unsigned char u8;
typedef unsigned int u16;

//定义ULN2003控制步进电机管脚
sbit IN1_A = P1^4;
sbit IN2_B = P2^7;
sbit IN3_C = P2^6;
sbit IN4_D = P2^1;

//定义独立按键控制脚
sbit KEY1=P3^1;
sbit KEY2=P3^0;
sbit KEY3=P3^2;
sbit KEY4=P3^3;

//使用宏定义独立按键按下的键值
#define KEY1_PRESS 1
#define KEY2_PRESS 2
#define KEY3_PRESS 3
#define KEY4_PRESS 4
#define KEY_UNPRESS 0

//定义步进电机速度，值越小，速度越快；最小不能小于 1
#define STEPMOTOR_MAXSPEED 1
#define STEPMOTOR_MINSPEED 5

/*
函 数 名 : delay_10us
函数功能 : 延时函数，ten_us=1 时，大约延时 10us
输 入 : ten_us
输 出 : 无
*/
void delay_10us(u16 ten_us)
{
	while(ten_us--);
}

/*
函 数 名 : delay_ms
函数功能 : ms 延时函数，ms=1 时，大约延时 1ms
输 入 : ten_us
输 出 : 无
*/
void delay_ms(u16 ms)
{
	u16 i,j;
	for (i=ms;i>0;i--)
	{
		for (j=110;j>0;j--);
	}
}

/*
函 数 名 : key_scan
函数功能 : 检测独立按键是否按下，按下则返回对应键值
输 入 : mode=0：单次扫描按键
		mode=1：连续扫描按键
输 出 : KEY1_PRESS：K1 按下
		KEY2_PRESS：K2 按下
		KEY3_PRESS：K3 按下
		KEY4_PRESS：K4 按下
		KEY_UNPRESS：未有按键按下
*/
u8 key_scan(u8 mode)
{
	static u8 key = 1;

	if (mode) key = 1;//连续扫描按键
	//任意按键按下
	if (key == 1 && (KEY1==0||KEY2==0||KEY3==0||KEY4==0))
	{
		delay_10us(1000); //消抖
		key = 0;

		if (KEY1 == 0)
		{
			return 	KEY1_PRESS;
		}
		else if (KEY2 == 0)
		{
			return 	KEY2_PRESS;	
		}
		else if (KEY3 == 0)
		{
			return 	KEY3_PRESS;	
		}
		else if (KEY4 == 0)
		{
			return 	KEY4_PRESS;	
		}
	}
	//无按键按下
	else if (KEY1==1&&KEY2==1&&KEY3==1&&KEY4==1)
	{
		key = 1;
	}
	return KEY_UNPRESS;
}

/*
函 数 名 : step_motor_28BYJ48_send_pulse
函数功能 : 输出一个数据给 ULN2003 从而实现向步进电机发送一个脉冲
输 入 : step：指定步进序号，可选值 0~7	
		dir：方向选择,1：顺时针,0：逆时针
输 出 : 无
*/
void step_motor_28BYJ48_send_pulse(u8 step,u8 dir)
{
	u8 temp = step;

	//如果为逆时针旋转
	if (dir == 0)
	{
		temp = 7 - step; //调换节拍信号,将8个节拍反向输出
	}

	//8 个节拍控制：A->AB->B->BC->C->CD->D->DA
	switch (temp)
		
	{
		case 0: IN1_A=1;IN2_B=0;IN3_C=0;IN4_D=0;break;
		case 1: IN1_A=1;IN2_B=1;IN3_C=0;IN4_D=0;break;
		case 2: IN1_A=0;IN2_B=1;IN3_C=0;IN4_D=0;break;
		case 3: IN1_A=0;IN2_B=1;IN3_C=1;IN4_D=0;break;
		case 4: IN1_A=0;IN2_B=0;IN3_C=1;IN4_D=0;break;
		case 5: IN1_A=0;IN2_B=0;IN3_C=1;IN4_D=1;break;
		case 6: IN1_A=0;IN2_B=0;IN3_C=0;IN4_D=1;break;
		case 7: IN1_A=1;IN2_B=0;IN3_C=0;IN4_D=1;break;
	}
}

/*
函 数 名 : main
函数功能 : 主函数
输 入 : 无
输 出 : 无
*/
uchar m=0;


void bujin ()
{	

	u8 key = 0;
	u8 dir = 0; //默认逆时针方向
	u8 speed = STEPMOTOR_MAXSPEED; //默认最大速度旋转
	u8 step = 0;	
  m=0;	
		for (m=0; m < 60; m++)
		{
		step_motor_28BYJ48_send_pulse(step++,dir);
		if (step == 8) step = 0;
		delay_ms(speed); //延时1ms
				
	  }
	}
	

	

//			key = key_scan(0);	//单次扫描
//		if (key == KEY1_PRESS)//换向
//		{
//			dir = !dir;
//		}
//		else if (key == KEY2_PRESS)//加速
//		{
//			if(speed > STEPMOTOR_MAXSPEED)
//				speed -= 1;
//		}
//		else if (key == KEY3_PRESS)//减速
//		{
//			if (speed < STEPMOTOR_MINSPEED)
//				speed += 1;
//		}