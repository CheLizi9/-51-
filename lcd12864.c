#include"lcd12864.h"

/*延时函数*/

void delay_1ms(uint x)

{

uint i,j;

for(j=0;j<x;j++)

for(i=0;i<110;i++);

}


/*******************************************************************************
* 函 数 名         : LCD_Busy
* 函数功能		   : 检测LCD是否忙
* 输    入         : 无
* 输    出         : 1或0（1表示不忙，0表示忙）
*******************************************************************************/
//uchar LCD_Busy(void)
//{
//	uchar i = 0;

//	LCD_RS = 0;   	//选择命令
//	LCD_RW = 1;	//选择读取
//	LCD_EN = 1;
//	delay_1ms(1);
//	while((LCD_data & 0x80) == 0x80)	//检测读取到的值
//	{
//		i++;
//		if(i > 100)
//		{
//			LCD_EN = 0;
//			return 0;	   //超过等待时间返回0表示失败
//		}
//	}
//	LCD_EN = 0;
//	return 1;
//}




/*写入命令到LCD12864，令RS=L，RW=L，EN=高脉冲，D0-D7=指令码。*/

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
//			return;	   //超过等待退出
//		}	
//	}
LCD_RS = 0;//选择命令

LCD_RW = 0; //选择写入

LCD_EN = 0;//初始化使能端

P0 = cmd;//放置数据

delay_1ms(5);

LCD_EN = 1;//写时序

delay_1ms(5);

LCD_EN = 0;

}

/*写入数据到LCD12864，令RS=H，RW=L，EN=高脉冲，D0-D7=指令码。*/

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
//			return;	   //超过等待退出
//		}	
//	}
LCD_RS = 1;//选择数据

LCD_RW = 0;//选择写入

LCD_EN = 0; //初始化使能端

P0 = dat;//放置数据

delay_1ms(5);

LCD_EN = 1;//写时序

delay_1ms(5);

LCD_EN = 0;

}



/*LCD初始化设定*/

void lcd_init()

{

LCD_PSB = 1; //并行方式

write_cmd(0x30); //基本指令操作

delay_1ms(5);

write_cmd(0x0C); //显示开，关光标

delay_1ms(5);

write_cmd(0x01); //清除LCD的显示内容

delay_1ms(5);

}

/*设定显示位置*/

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


