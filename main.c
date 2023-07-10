#include "reg52.h"
#include <stdio.h>
#include "all_define.h"
#include "lcd12864.h"
#include "ds18b20.h"
#include "adc0832.h"
#include "all_define.h"
#include "ds1302.h"
#include "bujin.h"

#define menu_max			20


//引脚定义
sbit key1 = P3 ^ 0;
sbit key2 = P3 ^ 1;
sbit key3 = P3 ^ 2;
sbit key4 = P3 ^ 3;
sbit beep = P2 ^ 3;        
sbit hot  = P2 ^ 0;
sbit wei  = P2 ^ 1;
sbit chou  = P2 ^ 4;
sbit chong  = P1 ^ 3;
bit Flag_Get_data = 0;

//变量定义
uchar menu = 0;//菜单
uchar  w_shi=0x08,w_fen=0x39,w_miao=0x00,t_miao=0x10;
uchar  hk_shi=0x08,hk_fen=0x09,hk_miao=0x50;
uchar  hg_shi=0x23,hg_fen=0x59,hg_miao=0x59;
uchar  ck_shi=0x08,ck_fen=0x30,ck_miao=0x28;
uchar  cg_shi=0x23,cg_fen=0x59,cg_miao=0x59;
uint temp;//温度
uint temp_h = 3100, temp_l = 2000;//温度上下限
uint Turbi, Turbi_h = 60;
uchar o2=5, o2_h = 7;        
uchar n=0;
uchar i;
uint t;
uchar w;
	uchar code dis1[]="时间";
	uchar code dis2[]="温度";
	uchar code dis3[]="℃";
	uchar code dis4[]=".:%";
	uchar code dis5[]="  浑浊";
	uchar code dis6[]="  氧气";
	uchar  dis7[]="温度限度调节";
	uchar  dis8[]="上限";
	uchar  dis9[]="下限";
	uchar  dis10[]="实时";
	uchar  dis11[]="喂食";
	uchar  dis12[]="时";
	uchar  dis13[]="分";
	uchar  code dis14[]="水泵时间调节";
	uchar  code dis15[]="氧泵时间调节";
	uchar  code dis16[]="开";
	uchar  code dis17[]="关";
	uchar  code dis18[]="秒";
	uchar  code dis19[]="时间调节";
	uchar  code dis20[]="mg/L";

//函数声明
//显示界面  每个菜单的结构
void Dis_menu();
//显示 数据
void Dis_Dat();
//获取数据
void Get_Dat();
//显示设置后改变的数值
void Dis_Set_Dat();
//按键扫描
void Key_Scan();
//根据传感器数值处理外部设备
void Proc_alart();
//处理定时
void Peoc_Time_Alarm();



	void main()
{
//	 wela=0;
//   dula=0;
	 wei=0;
   chou=0;
	 chong=0;
		    delay_1ms(100);//等待系统稳定
	      init_ds1302();
			  delay_1ms(10);
				lcd_init();//液晶初始化
				write_cmd(0x01); //清除LCD的显示内容
				delay_1ms(20);	
      	Dis_menu();//显示菜单结构
		while(1)
				{           				
			  Get_Dat();//获取数据	
				Dis_Dat();//显示动态数据
        Key_Scan();//按键扫描		            					
			  Dis_Set_Dat();//显示设置后改变的数值
		    Peoc_Time_Alarm();//处理定时				
				Proc_alart();//根据传感器数值处理外部设备
				}
}



//显示界面  每个菜单的结构
void Dis_menu()
{
	
write_cmd(0x01); //清除LCD的显示内容	

delay_1ms(10); //延时

lcd_init();  //初始化LCD
	
  //根据menu 来对应显示整个菜单的结构
				if(menu == 0)
{			
lcd_pos(0,1); //设置显示位置为第一行的第2个字符
i = 0;
while(dis1[i]!='\0')
{
write_dat(dis1[i]); //显示字符
i++;
}
lcd_pos(1,1); //设置显示位置为第二行的第2个字符
i = 0;
while(dis2[i]!='\0')
{
write_dat(dis2[i]); //显示字符
i++;
}
i = 0;
while(dis3[i]!='\0')
{
write_dat(dis3[i]); //显示字符
i++;
}
lcd_pos(2,0);
i = 0;
while(dis5[i]!='\0')
{
write_dat(dis5[i]);  //显示字符
i++;
}
 lcd_pos(3,0);
	i=0;		
	while(dis6[i]!='\0')
		{
			write_dat(dis6[i]);
			i++;
		}			
 lcd_pos(3,5);
	i=0;		
	while(dis20[i]!='\0')
		{
			write_dat(dis20[i]);
			i++;
		}		
    }	
				if(menu == 1)
							{
					write_cmd(0x01); //清除LCD的显示内容	
					delay_1ms(10); //延时

					lcd_pos(0,1); //设置显示位置为第1行的第2个字符
					i = 0;
					while(dis7[i]!='\0')
					{
					write_dat(dis7[i]); //显示字符
					i++;
					}
					//温度上限显示
					lcd_pos(1,1); //设置显示位置为第2行的第2个字符
					i = 0;
					while(dis8[i]!='\0')
					{
					write_dat(dis8[i]); //显示字符
					i++;
					}
					i = 0;
					while(dis3[i]!='\0')
					{
					write_dat(dis3[i]); //显示字符
					i++;
					}
						 
			lcd_pos(1,3);
							write_dat(dis4[1]);

							write_dat((temp_h/1000)+0x30);
							write_dat(temp_h%1000/100+0x30);
							write_dat(dis4[0]);
							write_dat(temp_h%100/10+0x30);
							write_dat(temp_h%10+0x30);
							i=0;	
							
					
					}
	
			if(menu == 2)
							{


					write_cmd(0x01); //清除LCD的显示内容	

					delay_1ms(10); //延时


					lcd_pos(0,1); //设置显示位置为第1行的第2个字符
					i = 0;
					while(dis7[i]!='\0')
					{
					write_dat(dis7[i]); //显示字符
					i++;
					}

				
					//温度下限显示
					lcd_pos(2,1); //设置显示位置为第3行的第2个字符
					i = 0;
					while(dis9[i]!='\0')
					{
					write_dat(dis9[i]); //显示字符
					i++;
					}

					i = 0;
					while(dis3[i]!='\0')
					{
					write_dat(dis3[i]); //显示字符
					i++;
					}		
	            lcd_pos(2,3);
							write_dat(dis4[1]);
							write_dat((temp_l/1000)+0x30);
							write_dat(temp_l%1000/100+0x30);
							write_dat(dis4[0]);
							write_dat(temp_l%100/10+0x30);
							write_dat(temp_l%10+0x30);
							i=0;						
					}
							
						
//实时 喂食 时调节			
if(menu>=3 && menu<=8)
			{
	{
	lcd_pos(0,2);
	i = 0;
while(dis19[i]!='\0')
{
write_dat(dis19[i]); //显示字符
i ++;
}			
	
	lcd_pos(2,0);
	i = 0;
while(dis10[i]!='\0')
{
write_dat(dis10[i]); //显示字符
i ++;
}			

	lcd_pos(3,0);
	i = 0;
while(dis11[i]!='\0')
{
write_dat(dis11[i]); //显示字符
i ++;
}	

	lcd_pos(1,3);
	i = 0;
while(dis12[i]!='\0')
{
write_dat(dis12[i]); //显示字符
i ++;
}			

	lcd_pos(1,5);
	i = 0;
while(dis13[i]!='\0')
{
write_dat(dis13[i]); //显示字符
i ++;
}	

	lcd_pos(1,7);
	i = 0;
while(dis18[i]!='\0')
{
write_dat(dis18[i]); //显示字符
i ++;
}	

}
	}	


//水泵时间调节
	if(menu>=9 && menu<=14)
	{
	lcd_pos(0,1);
	i = 0;
while(dis14[i]!='\0')
{
write_dat(dis14[i]); //显示字符
i ++;
}			
	
	lcd_pos(2,0);
	i = 0;
while(dis16[i]!='\0')
{
write_dat(dis16[i]); //显示字符
i ++;
}			

	lcd_pos(3,0);
	i = 0;
while(dis17[i]!='\0')
{
write_dat(dis17[i]); //显示字符
i ++;
}	

	lcd_pos(1,3);
	i = 0;
while(dis12[i]!='\0')
{
write_dat(dis12[i]); //显示字符
i ++;
}			

	lcd_pos(1,5);
	i = 0;
while(dis13[i]!='\0')
{
write_dat(dis13[i]); //显示字符
i ++;
}

	lcd_pos(1,7);
	i = 0;
while(dis18[i]!='\0')
{
write_dat(dis18[i]); //显示字符
i ++;
}
}

	
//氧泵时间调节
if(menu>=15 && menu<=20)
{
lcd_pos(0,1);
	i = 0;
while(dis15[i]!='\0')
{
write_dat(dis15[i]); //显示字符
i ++;
}			
	
	lcd_pos(2,0);
	i = 0;
while(dis16[i]!='\0')
{
write_dat(dis16[i]); //显示字符
i ++;
}			

	lcd_pos(3,0);
	i = 0;
while(dis17[i]!='\0')
{
write_dat(dis17[i]); //显示字符
i ++;
}	

	lcd_pos(1,3);
	i = 0;
while(dis12[i]!='\0')
{
write_dat(dis12[i]); //显示字符
i ++;
}			

	lcd_pos(1,5);
	i = 0;
while(dis13[i]!='\0')
{
write_dat(dis13[i]); //显示字符
i ++;
}	
	
		lcd_pos(1,7);
	i = 0;
while(dis18[i]!='\0')
{
write_dat(dis18[i]); //显示字符
i ++;
}	
	

}			
		
}



//获取数据
void Get_Dat()
{
if (menu == 0)
   {	
    temp = Get_temp();//获取温度    		
		read_time();//获取时间        
   // o2 = (255 - adc0832(0)) / 2.55; //获取氧气浓度 转换为百分比		 
    Turbi = (255 - adc0832(1)) / 2.55; //获取浑浊度 转换为百分比    		
   
   }
}

//显示动态数据
void Dis_Dat()	
{

	 if(menu == 0)
			{			

				
//时间显示
				lcd_pos(0,3);
				write_dat(dis4[1]);			
				write_dat(shi/16%16+0x30);	
				write_dat(shi%16+0x30);
				write_dat(dis4[1]);
				write_dat(fen/16%16+0x30);	
				write_dat(fen%16+0x30);
				write_dat(dis4[1]);
				write_dat(miao/16%16+0x30);	
				write_dat(miao%16+0x30);
				
//温度显示	
			lcd_pos(1,3);
			write_dat(dis4[1]);
			write_dat((temp/1000)+0x30);
			write_dat(temp%1000/100+0x30);
			write_dat(dis4[0]);
			write_dat(temp%100/10+0x30);
			write_dat(temp%10+0x30);				
			i=0;		
			while(dis3[i]!='\0')
				{
					write_dat(dis3[i]);
					i++;					
				}	
						
//浊度显示				
		    lcd_pos(2,3);	
        write_dat(dis4[1]);				
		    write_dat((Turbi / 100 % 10 )+ 0x30);
        write_dat((Turbi / 10 % 10) + 0x30);
        write_dat((Turbi % 10) + 0x30);	
        write_dat(dis4[2]);		
				
//氧气显示			
		    lcd_pos(3,3);	
        write_dat(dis4[1]);				
		    write_dat((o2 / 100 % 10 )+ 0x30);
        write_dat((o2 / 10 % 10) + 0x30);
        write_dat((o2 % 10) + 0x30);	
        //write_dat(dis4[2]);			
			
			}
}




	void Key_Scan()  //按键扫描
 {
			
		if(!key1)  //如果按下菜单键
		delay_1ms(10);
		if(!key1)  
				{
					menu++;
					if(menu > menu_max)  //判断是否到达最大菜单数
					{						
						menu = 0;
					}					
					Dis_menu();			//显示菜单结构
					while(!key1);
				}			
				
			
		//按键加
    if(!key2)       //检测到按键为低电平
    {               
    delay_1ms(10); //消抖
    if(!key2)   //再次确认按键是否为低电平
        {

            switch(menu)
            {
            case 0: break;
            case 1: temp_h=temp_h+100; break;
            case 2: temp_l=temp_l+100; break;
						case 3: set_ds1302time(1,&shi,0x24);	break;
						case 4:	set_ds1302time(1,&fen,0x60);	break;	
						case 5: set_ds1302time(1,&miao,0x60);	break;
							
						case 6: set_ds1302time(1,&w_shi,0x24);	break;
						case 7:	set_ds1302time(1,&w_fen,0x60);	break;	
						case 8: set_ds1302time(1,&w_miao,0x60);	break;	

						case 9: set_ds1302time(1,&hk_shi,0x24);	break;
						case 10:	set_ds1302time(1,&hk_fen,0x60);	break;	
						case 11: set_ds1302time(1,&hk_miao,0x60);	break;

						case 12: set_ds1302time(1,&hg_shi,0x24);	break;
						case 13:	set_ds1302time(1,&hg_fen,0x60);	break;	
						case 14: set_ds1302time(1,&hg_miao,0x60);	break;

						case 15: set_ds1302time(1,&ck_shi,0x24);	break;
						case 16:	set_ds1302time(1,&ck_fen,0x60);	break;	
						case 17: set_ds1302time(1,&ck_miao,0x60);	break;

						case 18: set_ds1302time(1,&cg_shi,0x24);	break;
						case 19:	set_ds1302time(1,&cg_fen,0x60);	break;	
						case 20: set_ds1302time(1,&cg_miao,0x60);	break;
            default:
              break;
            }	
            write_time();						
            Dis_Set_Dat();
            while(!key2); //判断按键是否松开						
        }
    }

	
    if(!key3)       //检测到按键为低电平
    {               
    delay_1ms(10); //消抖
    if(!key3)   //再次确认按键是否为低电平
        {
            switch(menu)
            {
            case 0: break;
            case 1: temp_h=temp_h-100; break;
            case 2: temp_l=temp_l-                     100; break;
						case 3: set_ds1302time(0,&shi,0x24);	break;
						case 4:	set_ds1302time(0,&fen,0x60);	break;	
						case 5: set_ds1302time(0,&miao,0x60);	break;
							
						case 6: set_ds1302time(0,&w_shi,0x24);	break;
						case 7:	set_ds1302time(0,&w_fen,0x60);	break;	
						case 8: set_ds1302time(0,&w_miao,0x60);	break;	

						case 9:  set_ds1302time(0,&hk_shi,0x24);	break;
						case 10: set_ds1302time(0,&hk_fen,0x60);	break;	
						case 11: set_ds1302time(0,&hk_miao,0x60);	break;

						case 12: set_ds1302time(0,&hg_shi,0x24);	break;
						case 13: set_ds1302time(0,&hg_fen,0x60);	break;	
						case 14: set_ds1302time(0,&hg_miao,0x60);	break;

						case 15: set_ds1302time(0,&ck_shi,0x24);	break;
						case 16: set_ds1302time(0,&ck_fen,0x60);	break;	
						case 17: set_ds1302time(0,&ck_miao,0x60);	break;

						case 18: set_ds1302time(0,&cg_shi,0x24);	break;
						case 19: set_ds1302time(0,&cg_fen,0x60);	break;	
						case 20: set_ds1302time(0,&cg_miao,0x60);	break;
            default:
              break;
            }
						write_time();
            Dis_Set_Dat();
            while(!key3); //判断按键是否松开
        }
    }
		
		
if(!key4)       //检测到按键为低电平
    {               
    delay_1ms(10); //消抖
    if(!key4)   //再次确认按键是否为低电平
        {
				
				menu=0;
				write_cmd(0x01); //清除LCD的显示内容
				delay_1ms(20);	
      	Dis_menu();//显示菜单结构
				
				while(!key4); //判断按键是否松开
				}		
}
}


//显示设置后改变的数值
void Dis_Set_Dat()
{			
 //根据menu 指定页面显示对应的数据
    switch(menu)
		{
		  case 0:
		  break;
//温度上限			
			case 1:
			lcd_pos(1,3);
							write_dat(dis4[1]);
							write_dat((temp_h/1000)+0x30);
							write_dat(temp_h%1000/100+0x30);
							write_dat(dis4[0]);
							write_dat(temp_h%100/10+0x30);
							write_dat(temp_h%10+0x30);
							i=0;		
			break;
//温度下限
			case 2:
			lcd_pos(2,3);
							write_dat(dis4[1]);
							write_dat((temp_l/1000)+0x30);
							write_dat(temp_l%1000/100+0x30);
							write_dat(dis4[0]);
							write_dat(temp_l%100/10+0x30);
							write_dat(temp_l%10+0x30);
							i=0;					
		  break;				
//实时时间调节
			case 3:
			lcd_pos(2,3);	
		write_dat(shi/16%16+0x30);	
		write_dat(shi%16+0x30);
			break;	
	    case 4:
			lcd_pos(2,5);	
		write_dat(fen/16%16+0x30);	
		write_dat(fen%16+0x30);
			break;
			case 5:
			lcd_pos(2,7);	
	  write_dat(miao/16%16+0x30);	
		write_dat(miao%16+0x30);
			break;	
//喂食时间
			case 6:
			lcd_pos(3,3);	
		write_dat(w_shi/16%16+0x30);	
		write_dat(w_shi%16+0x30);;
			break;	
	    case 7:
			lcd_pos(3,5);	
		write_dat(w_fen/16%16+0x30);	
		write_dat(w_fen%16+0x30);
			break;
			case 8:
		  lcd_pos(3,7);	
		write_dat(w_miao/16%16+0x30);	
		write_dat(w_miao%16+0x30);
		  break;
//换水开时间
		  case 9:
		   lcd_pos(2,3);    
					write_dat(hk_shi /16%16+0x30);
			    write_dat(hk_shi %16+0x30);
			break;
			case 10:
			lcd_pos(2,5);
					write_dat(hk_fen /16%16+0x30);
			    write_dat(hk_fen %16+0x30);
      break;
			case 11:
			lcd_pos(2,7);
					write_dat(hk_miao /16%16+0x30);
			    write_dat(hk_miao %16+0x30);
      break;
			
//换水关时间
			case 12:
			lcd_pos(3,3);
					write_dat(hg_shi /16%16+0x30);
			    write_dat(hg_shi %16+0x30);
			break;
			case 13:
			lcd_pos(3,5);
					write_dat(hg_fen /16%16+0x30);
			    write_dat(hg_fen %16+0x30);
			break;
			case 14:
			lcd_pos(3,7);
					write_dat(hg_miao /16%16+0x30);
			    write_dat(hg_miao %16+0x30);
			break;

//充氧开时间
			case 15:
		   lcd_pos(2,3);    
					write_dat(ck_shi /16%16+0x30);
			    write_dat(ck_shi %16+0x30);
			break;
			case 16:
			lcd_pos(2,5);
					write_dat(ck_fen /16%16+0x30);
			    write_dat(ck_fen %16+0x30);
      break;
			case 17:
			lcd_pos(2,7);
					write_dat(ck_miao /16%16+0x30);
			    write_dat(ck_miao %16+0x30);
      break;
			
//充氧关时间
			case 18:
			lcd_pos(3,3);
					write_dat(cg_shi /16%16+0x30);
			    write_dat(cg_shi %16+0x30);
			break;
			case 19:
			lcd_pos(3,5);
					write_dat(cg_fen /16%16+0x30);
			    write_dat(cg_fen %16+0x30);
			break;		
			case 20:
			lcd_pos(3,7);
					write_dat(cg_miao /16%16+0x30);
			    write_dat(cg_miao %16+0x30);
			break;												
		 }
					
}




//处理定时
void Peoc_Time_Alarm()
{  
	//当前时分秒都等于设定定时时间时 给喂食倒计时赋值 10秒 开始喂食

//  if(shi == w_shi && fen == w_fen && miao ==t_miao)

		wei = 0;
		
	if(shi == w_shi && fen == w_fen && miao ==w_miao)
	
{  
  wei = 1;
	if(miao<t_miao)
	{
		for(n=0;n<100;n++)
	{
		bujin();//步进电机喂食6秒
	}
	}
}
}


//根据传感器数值处理外部设备
void Proc_alart()
{   
  
	//加温设备
if(temp<temp_h)
{	
	hot=1;
}
	else
hot=0;	

if(temp<temp_l-100 || temp>temp_h+100)
	beep=0;
else
	beep=1;



//换水设备
if(Turbi<Turbi_h)
	chou=0;
if(Turbi>Turbi_h)
{	
if(shi == hk_shi && fen == hk_fen && miao == hk_miao)
{
  chou=1;
}

if(shi == hg_shi && fen == hg_fen && miao == hg_miao)
{
  chou=0;
}
}	




//充氧设备
if(o2>o2_h)
	chong=0;
if(o2<o2_h)
{

if(shi == ck_shi && fen == ck_fen && miao == ck_miao)
{
  chong=1;
}

if(shi == cg_shi && fen == cg_fen && miao == cg_miao)
{
  chong=0;
}

}
}



	




