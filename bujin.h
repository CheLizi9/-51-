
#include "reg52.h"

//��ϵͳĬ���������ͽ����ض��� 
typedef unsigned char u8;
typedef unsigned int u16;

//����ULN2003���Ʋ�������ܽ�
sbit IN1_A = P1^4;
sbit IN2_B = P2^7;
sbit IN3_C = P2^6;
sbit IN4_D = P2^1;

//��������������ƽ�
sbit KEY1=P3^1;
sbit KEY2=P3^0;
sbit KEY3=P3^2;
sbit KEY4=P3^3;

//ʹ�ú궨������������µļ�ֵ
#define KEY1_PRESS 1
#define KEY2_PRESS 2
#define KEY3_PRESS 3
#define KEY4_PRESS 4
#define KEY_UNPRESS 0

//���岽������ٶȣ�ֵԽС���ٶ�Խ�죻��С����С�� 1
#define STEPMOTOR_MAXSPEED 1
#define STEPMOTOR_MINSPEED 5

/*
�� �� �� : delay_10us
�������� : ��ʱ������ten_us=1 ʱ����Լ��ʱ 10us
�� �� : ten_us
�� �� : ��
*/
void delay_10us(u16 ten_us)
{
	while(ten_us--);
}

/*
�� �� �� : delay_ms
�������� : ms ��ʱ������ms=1 ʱ����Լ��ʱ 1ms
�� �� : ten_us
�� �� : ��
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
�� �� �� : key_scan
�������� : �����������Ƿ��£������򷵻ض�Ӧ��ֵ
�� �� : mode=0������ɨ�谴��
		mode=1������ɨ�谴��
�� �� : KEY1_PRESS��K1 ����
		KEY2_PRESS��K2 ����
		KEY3_PRESS��K3 ����
		KEY4_PRESS��K4 ����
		KEY_UNPRESS��δ�а�������
*/
u8 key_scan(u8 mode)
{
	static u8 key = 1;

	if (mode) key = 1;//����ɨ�谴��
	//���ⰴ������
	if (key == 1 && (KEY1==0||KEY2==0||KEY3==0||KEY4==0))
	{
		delay_10us(1000); //����
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
	//�ް�������
	else if (KEY1==1&&KEY2==1&&KEY3==1&&KEY4==1)
	{
		key = 1;
	}
	return KEY_UNPRESS;
}

/*
�� �� �� : step_motor_28BYJ48_send_pulse
�������� : ���һ�����ݸ� ULN2003 �Ӷ�ʵ���򲽽��������һ������
�� �� : step��ָ��������ţ���ѡֵ 0~7	
		dir������ѡ��,1��˳ʱ��,0����ʱ��
�� �� : ��
*/
void step_motor_28BYJ48_send_pulse(u8 step,u8 dir)
{
	u8 temp = step;

	//���Ϊ��ʱ����ת
	if (dir == 0)
	{
		temp = 7 - step; //���������ź�,��8�����ķ������
	}

	//8 �����Ŀ��ƣ�A->AB->B->BC->C->CD->D->DA
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
�� �� �� : main
�������� : ������
�� �� : ��
�� �� : ��
*/
uchar m=0;


void bujin ()
{	

	u8 key = 0;
	u8 dir = 0; //Ĭ����ʱ�뷽��
	u8 speed = STEPMOTOR_MAXSPEED; //Ĭ������ٶ���ת
	u8 step = 0;	
  m=0;	
		for (m=0; m < 60; m++)
		{
		step_motor_28BYJ48_send_pulse(step++,dir);
		if (step == 8) step = 0;
		delay_ms(speed); //��ʱ1ms
				
	  }
	}
	

	

//			key = key_scan(0);	//����ɨ��
//		if (key == KEY1_PRESS)//����
//		{
//			dir = !dir;
//		}
//		else if (key == KEY2_PRESS)//����
//		{
//			if(speed > STEPMOTOR_MAXSPEED)
//				speed -= 1;
//		}
//		else if (key == KEY3_PRESS)//����
//		{
//			if (speed < STEPMOTOR_MINSPEED)
//				speed += 1;
//		}