#include"lcd12864.h"

/*��ʱ����*/

void delay_1ms(uint x)

{

uint i,j;

for(j=0;j<x;j++)

for(i=0;i<110;i++);

}


/*******************************************************************************
* �� �� ��         : LCD_Busy
* ��������		   : ���LCD�Ƿ�æ
* ��    ��         : ��
* ��    ��         : 1��0��1��ʾ��æ��0��ʾæ��
*******************************************************************************/
//uchar LCD_Busy(void)
//{
//	uchar i = 0;

//	LCD_RS = 0;   	//ѡ������
//	LCD_RW = 1;	//ѡ���ȡ
//	LCD_EN = 1;
//	delay_1ms(1);
//	while((LCD_data & 0x80) == 0x80)	//����ȡ����ֵ
//	{
//		i++;
//		if(i > 100)
//		{
//			LCD_EN = 0;
//			return 0;	   //�����ȴ�ʱ�䷵��0��ʾʧ��
//		}
//	}
//	LCD_EN = 0;
//	return 1;
//}




/*д�����LCD12864����RS=L��RW=L��EN=�����壬D0-D7=ָ���롣*/

void write_cmd(uchar cmd)

{
//uchar i;
//	i = 0;
//	while( LCD_Busy() == 0)
//	{
//		delay_1ms(1);
//		i++;
//		if( i>100)
//		{
//			return;	   //�����ȴ��˳�
//		}	
//	}
LCD_RS = 0;//ѡ������

LCD_RW = 0; //ѡ��д��

LCD_EN = 0;//��ʼ��ʹ�ܶ�

P0 = cmd;//��������

delay_1ms(5);

LCD_EN = 1;//дʱ��

delay_1ms(5);

LCD_EN = 0;

}

/*д�����ݵ�LCD12864����RS=H��RW=L��EN=�����壬D0-D7=ָ���롣*/

void write_dat(uchar dat)

{
//uchar i;
//	i = 0;
//	while( LCD_Busy() == 0)
//	{
//		delay_1ms(1);
//		i++;
//		if( i>100)
//		{
//			return;	   //�����ȴ��˳�
//		}	
//	}
LCD_RS = 1;//ѡ������

LCD_RW = 0;//ѡ��д��

LCD_EN = 0; //��ʼ��ʹ�ܶ�

P0 = dat;//��������

delay_1ms(5);

LCD_EN = 1;//дʱ��

delay_1ms(5);

LCD_EN = 0;

}



/*LCD��ʼ���趨*/

void lcd_init()

{

LCD_PSB = 1; //���з�ʽ

write_cmd(0x30); //����ָ�����

delay_1ms(5);

write_cmd(0x0C); //��ʾ�����ع��

delay_1ms(5);

write_cmd(0x01); //���LCD����ʾ����

delay_1ms(5);

}

/*�趨��ʾλ��*/

void lcd_pos(uchar X,uchar Y)

{

uchar pos;

if(X==0)

{X=0x80;}

else if(X==1)

{X=0x90;}

else if(X==2)

{X=0x88;}

else if(X==3)

{X=0x98;}

pos = X+Y;

write_cmd(pos);

}


