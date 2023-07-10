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


//���Ŷ���
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

//��������
uchar menu = 0;//�˵�
uchar  w_shi=0x08,w_fen=0x39,w_miao=0x00,t_miao=0x10;
uchar  hk_shi=0x08,hk_fen=0x09,hk_miao=0x50;
uchar  hg_shi=0x23,hg_fen=0x59,hg_miao=0x59;
uchar  ck_shi=0x08,ck_fen=0x30,ck_miao=0x28;
uchar  cg_shi=0x23,cg_fen=0x59,cg_miao=0x59;
uint temp;//�¶�
uint temp_h = 3100, temp_l = 2000;//�¶�������
uint Turbi, Turbi_h = 60;
uchar o2=5, o2_h = 7;        
uchar n=0;
uchar i;
uint t;
uchar w;
	uchar code dis1[]="ʱ��";
	uchar code dis2[]="�¶�";
	uchar code dis3[]="��";
	uchar code dis4[]=".:%";
	uchar code dis5[]="  ����";
	uchar code dis6[]="  ����";
	uchar  dis7[]="�¶��޶ȵ���";
	uchar  dis8[]="����";
	uchar  dis9[]="����";
	uchar  dis10[]="ʵʱ";
	uchar  dis11[]="ιʳ";
	uchar  dis12[]="ʱ";
	uchar  dis13[]="��";
	uchar  code dis14[]="ˮ��ʱ�����";
	uchar  code dis15[]="����ʱ�����";
	uchar  code dis16[]="��";
	uchar  code dis17[]="��";
	uchar  code dis18[]="��";
	uchar  code dis19[]="ʱ�����";
	uchar  code dis20[]="mg/L";

//��������
//��ʾ����  ÿ���˵��Ľṹ
void Dis_menu();
//��ʾ ����
void Dis_Dat();
//��ȡ����
void Get_Dat();
//��ʾ���ú�ı����ֵ
void Dis_Set_Dat();
//����ɨ��
void Key_Scan();
//���ݴ�������ֵ�����ⲿ�豸
void Proc_alart();
//����ʱ
void Peoc_Time_Alarm();



	void main()
{
//	 wela=0;
//   dula=0;
	 wei=0;
   chou=0;
	 chong=0;
		    delay_1ms(100);//�ȴ�ϵͳ�ȶ�
	      init_ds1302();
			  delay_1ms(10);
				lcd_init();//Һ����ʼ��
				write_cmd(0x01); //���LCD����ʾ����
				delay_1ms(20);	
      	Dis_menu();//��ʾ�˵��ṹ
		while(1)
				{           				
			  Get_Dat();//��ȡ����	
				Dis_Dat();//��ʾ��̬����
        Key_Scan();//����ɨ��		            					
			  Dis_Set_Dat();//��ʾ���ú�ı����ֵ
		    Peoc_Time_Alarm();//����ʱ				
				Proc_alart();//���ݴ�������ֵ�����ⲿ�豸
				}
}



//��ʾ����  ÿ���˵��Ľṹ
void Dis_menu()
{
	
write_cmd(0x01); //���LCD����ʾ����	

delay_1ms(10); //��ʱ

lcd_init();  //��ʼ��LCD
	
  //����menu ����Ӧ��ʾ�����˵��Ľṹ
				if(menu == 0)
{			
lcd_pos(0,1); //������ʾλ��Ϊ��һ�еĵ�2���ַ�
i = 0;
while(dis1[i]!='\0')
{
write_dat(dis1[i]); //��ʾ�ַ�
i++;
}
lcd_pos(1,1); //������ʾλ��Ϊ�ڶ��еĵ�2���ַ�
i = 0;
while(dis2[i]!='\0')
{
write_dat(dis2[i]); //��ʾ�ַ�
i++;
}
i = 0;
while(dis3[i]!='\0')
{
write_dat(dis3[i]); //��ʾ�ַ�
i++;
}
lcd_pos(2,0);
i = 0;
while(dis5[i]!='\0')
{
write_dat(dis5[i]);  //��ʾ�ַ�
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
					write_cmd(0x01); //���LCD����ʾ����	
					delay_1ms(10); //��ʱ

					lcd_pos(0,1); //������ʾλ��Ϊ��1�еĵ�2���ַ�
					i = 0;
					while(dis7[i]!='\0')
					{
					write_dat(dis7[i]); //��ʾ�ַ�
					i++;
					}
					//�¶�������ʾ
					lcd_pos(1,1); //������ʾλ��Ϊ��2�еĵ�2���ַ�
					i = 0;
					while(dis8[i]!='\0')
					{
					write_dat(dis8[i]); //��ʾ�ַ�
					i++;
					}
					i = 0;
					while(dis3[i]!='\0')
					{
					write_dat(dis3[i]); //��ʾ�ַ�
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


					write_cmd(0x01); //���LCD����ʾ����	

					delay_1ms(10); //��ʱ


					lcd_pos(0,1); //������ʾλ��Ϊ��1�еĵ�2���ַ�
					i = 0;
					while(dis7[i]!='\0')
					{
					write_dat(dis7[i]); //��ʾ�ַ�
					i++;
					}

				
					//�¶�������ʾ
					lcd_pos(2,1); //������ʾλ��Ϊ��3�еĵ�2���ַ�
					i = 0;
					while(dis9[i]!='\0')
					{
					write_dat(dis9[i]); //��ʾ�ַ�
					i++;
					}

					i = 0;
					while(dis3[i]!='\0')
					{
					write_dat(dis3[i]); //��ʾ�ַ�
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
							
						
//ʵʱ ιʳ ʱ����			
if(menu>=3 && menu<=8)
			{
	{
	lcd_pos(0,2);
	i = 0;
while(dis19[i]!='\0')
{
write_dat(dis19[i]); //��ʾ�ַ�
i ++;
}			
	
	lcd_pos(2,0);
	i = 0;
while(dis10[i]!='\0')
{
write_dat(dis10[i]); //��ʾ�ַ�
i ++;
}			

	lcd_pos(3,0);
	i = 0;
while(dis11[i]!='\0')
{
write_dat(dis11[i]); //��ʾ�ַ�
i ++;
}	

	lcd_pos(1,3);
	i = 0;
while(dis12[i]!='\0')
{
write_dat(dis12[i]); //��ʾ�ַ�
i ++;
}			

	lcd_pos(1,5);
	i = 0;
while(dis13[i]!='\0')
{
write_dat(dis13[i]); //��ʾ�ַ�
i ++;
}	

	lcd_pos(1,7);
	i = 0;
while(dis18[i]!='\0')
{
write_dat(dis18[i]); //��ʾ�ַ�
i ++;
}	

}
	}	


//ˮ��ʱ�����
	if(menu>=9 && menu<=14)
	{
	lcd_pos(0,1);
	i = 0;
while(dis14[i]!='\0')
{
write_dat(dis14[i]); //��ʾ�ַ�
i ++;
}			
	
	lcd_pos(2,0);
	i = 0;
while(dis16[i]!='\0')
{
write_dat(dis16[i]); //��ʾ�ַ�
i ++;
}			

	lcd_pos(3,0);
	i = 0;
while(dis17[i]!='\0')
{
write_dat(dis17[i]); //��ʾ�ַ�
i ++;
}	

	lcd_pos(1,3);
	i = 0;
while(dis12[i]!='\0')
{
write_dat(dis12[i]); //��ʾ�ַ�
i ++;
}			

	lcd_pos(1,5);
	i = 0;
while(dis13[i]!='\0')
{
write_dat(dis13[i]); //��ʾ�ַ�
i ++;
}

	lcd_pos(1,7);
	i = 0;
while(dis18[i]!='\0')
{
write_dat(dis18[i]); //��ʾ�ַ�
i ++;
}
}

	
//����ʱ�����
if(menu>=15 && menu<=20)
{
lcd_pos(0,1);
	i = 0;
while(dis15[i]!='\0')
{
write_dat(dis15[i]); //��ʾ�ַ�
i ++;
}			
	
	lcd_pos(2,0);
	i = 0;
while(dis16[i]!='\0')
{
write_dat(dis16[i]); //��ʾ�ַ�
i ++;
}			

	lcd_pos(3,0);
	i = 0;
while(dis17[i]!='\0')
{
write_dat(dis17[i]); //��ʾ�ַ�
i ++;
}	

	lcd_pos(1,3);
	i = 0;
while(dis12[i]!='\0')
{
write_dat(dis12[i]); //��ʾ�ַ�
i ++;
}			

	lcd_pos(1,5);
	i = 0;
while(dis13[i]!='\0')
{
write_dat(dis13[i]); //��ʾ�ַ�
i ++;
}	
	
		lcd_pos(1,7);
	i = 0;
while(dis18[i]!='\0')
{
write_dat(dis18[i]); //��ʾ�ַ�
i ++;
}	
	

}			
		
}



//��ȡ����
void Get_Dat()
{
if (menu == 0)
   {	
    temp = Get_temp();//��ȡ�¶�    		
		read_time();//��ȡʱ��        
   // o2 = (255 - adc0832(0)) / 2.55; //��ȡ����Ũ�� ת��Ϊ�ٷֱ�		 
    Turbi = (255 - adc0832(1)) / 2.55; //��ȡ���Ƕ� ת��Ϊ�ٷֱ�    		
   
   }
}

//��ʾ��̬����
void Dis_Dat()	
{

	 if(menu == 0)
			{			

				
//ʱ����ʾ
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
				
//�¶���ʾ	
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
						
//�Ƕ���ʾ				
		    lcd_pos(2,3);	
        write_dat(dis4[1]);				
		    write_dat((Turbi / 100 % 10 )+ 0x30);
        write_dat((Turbi / 10 % 10) + 0x30);
        write_dat((Turbi % 10) + 0x30);	
        write_dat(dis4[2]);		
				
//������ʾ			
		    lcd_pos(3,3);	
        write_dat(dis4[1]);				
		    write_dat((o2 / 100 % 10 )+ 0x30);
        write_dat((o2 / 10 % 10) + 0x30);
        write_dat((o2 % 10) + 0x30);	
        //write_dat(dis4[2]);			
			
			}
}




	void Key_Scan()  //����ɨ��
 {
			
		if(!key1)  //������²˵���
		delay_1ms(10);
		if(!key1)  
				{
					menu++;
					if(menu > menu_max)  //�ж��Ƿ񵽴����˵���
					{						
						menu = 0;
					}					
					Dis_menu();			//��ʾ�˵��ṹ
					while(!key1);
				}			
				
			
		//������
    if(!key2)       //��⵽����Ϊ�͵�ƽ
    {               
    delay_1ms(10); //����
    if(!key2)   //�ٴ�ȷ�ϰ����Ƿ�Ϊ�͵�ƽ
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
            while(!key2); //�жϰ����Ƿ��ɿ�						
        }
    }

	
    if(!key3)       //��⵽����Ϊ�͵�ƽ
    {               
    delay_1ms(10); //����
    if(!key3)   //�ٴ�ȷ�ϰ����Ƿ�Ϊ�͵�ƽ
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
            while(!key3); //�жϰ����Ƿ��ɿ�
        }
    }
		
		
if(!key4)       //��⵽����Ϊ�͵�ƽ
    {               
    delay_1ms(10); //����
    if(!key4)   //�ٴ�ȷ�ϰ����Ƿ�Ϊ�͵�ƽ
        {
				
				menu=0;
				write_cmd(0x01); //���LCD����ʾ����
				delay_1ms(20);	
      	Dis_menu();//��ʾ�˵��ṹ
				
				while(!key4); //�жϰ����Ƿ��ɿ�
				}		
}
}


//��ʾ���ú�ı����ֵ
void Dis_Set_Dat()
{			
 //����menu ָ��ҳ����ʾ��Ӧ������
    switch(menu)
		{
		  case 0:
		  break;
//�¶�����			
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
//�¶�����
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
//ʵʱʱ�����
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
//ιʳʱ��
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
//��ˮ��ʱ��
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
			
//��ˮ��ʱ��
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

//������ʱ��
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
			
//������ʱ��
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




//����ʱ
void Peoc_Time_Alarm()
{  
	//��ǰʱ���붼�����趨��ʱʱ��ʱ ��ιʳ����ʱ��ֵ 10�� ��ʼιʳ

//  if(shi == w_shi && fen == w_fen && miao ==t_miao)

		wei = 0;
		
	if(shi == w_shi && fen == w_fen && miao ==w_miao)
	
{  
  wei = 1;
	if(miao<t_miao)
	{
		for(n=0;n<100;n++)
	{
		bujin();//�������ιʳ6��
	}
	}
}
}


//���ݴ�������ֵ�����ⲿ�豸
void Proc_alart()
{   
  
	//�����豸
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



//��ˮ�豸
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




//�����豸
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



	




