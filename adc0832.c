#include "adc0832.h"


#if TWO_CHANLE == ENABLE

sbit ADC0832_CS=P1^6;	//ADC0832  ����IO��	  ʹ�ܿ�
sbit ADC0832_CLK=P1^5;	//ʱ��IO��
sbit ADC0832_DIO=P1^3;	//�����������IO�� 

static unsigned int  A_D()	    //ADC0832   ��ֵ����
{
	unsigned char i;
	unsigned char dat;					 
	ADC0832_CS=1;   //һ��ת�����ڿ�ʼ
	ADC0832_CLK=0;  //Ϊ��һ��������׼��
	ADC0832_CS=0;  //CS��0��Ƭѡ��Ч	
	ADC0832_DIO=1;    //DIO��1���涨����ʼ�ź�  
	ADC0832_CLK=1;   //��һ������
	ADC0832_CLK=0;   //��һ��������½��أ���ǰDIO�����Ǹߵ�ƽ
	ADC0832_DIO=1;   //DIO��1�� ͨ��ѡ���ź�  
	ADC0832_CLK=1;   //�ڶ������壬��2��3�������³�֮ǰ��DI�������������λ��������ѡ��ͨ��������ѡͨ��RH0 
	ADC0832_CLK=0;   //�ڶ��������½��� 
	ADC0832_DIO=0;   //DI��0��ѡ��ͨ��0
	ADC0832_CLK=1;    //����������
	ADC0832_CLK=0;    //�����������½��� 
	ADC0832_DIO=1;    //�����������³�֮�������DIOʧȥ���ã�Ӧ��1
	ADC0832_CLK=1;    //���ĸ�����
	for(i=0;i<8;i++)  //��λ��ǰ
	{
		ADC0832_CLK=1;         //���ĸ�����
		ADC0832_CLK=0; 
		dat<<=1;       //�����洢��ĵ�λ����������
		dat|=(unsigned char)ADC0832_DIO; 	 //���������DIOͨ�������㴢����dat���λ 
	}	  		        
	ADC0832_CS=1;          //Ƭѡ��Ч 
	return dat;	 //����������ݷ���     
}

unsigned char get_ad_data(void)
{
	unsigned char i = 0,sum = 0,RH = 0;
	float Ad_dat=0;
	while(i <10)
	{
		i++;
		sum +=A_D();  //Get the sum of values ten times
	}
	Ad_dat=(unsigned char)(sum/10);	 //Calculate the average
	if(Ad_dat>2)
	{
		Ad_dat=(float)((Ad_dat-2)/2.4);  //Calculate the water level
		RH=(unsigned char)(Ad_dat);	
	}
	else
		RH=0;

	return RH;		
}


#else

sbit CS=P1^5;	//ADC0832  ����IO��	  ʹ�ܿ�
sbit Clk=P1^6;	//ʱ��IO��
sbit DATI=P1^7;	//�����������IO�� 
sbit DATO = P1^7;
unsigned int dat = 0x00;      //ADֵ

/****************************************************************************
��������:ADת���ӳ���
��ڲ���:CH   0 or 1
���ڲ���:dat
****************************************************************************/
unsigned char adc0832(unsigned char CH)
{
      unsigned char i,test,adval;
     adval = 0x00;
     test = 0x00;
     Clk = 0;       //��ʼ��
     DATI = 1;
    _nop_();
    CS = 0;
    _nop_();
    Clk = 1;
   _nop_();


   if ( CH == 0x00 )      //ͨ��ѡ��
   {
       Clk = 0;
       DATI = 1;      //ͨ��0�ĵ�һλ
       _nop_();
      Clk = 1;
        _nop_();
        Clk = 0;
      DATI = 0;      //ͨ��0�ĵڶ�λ
      _nop_();
      Clk = 1;
      _nop_();
    } 
    else
    {
       Clk = 0;
    DATI = 1;      //ͨ��1�ĵ�һλ
      _nop_();
      Clk = 1;
      _nop_();
      Clk = 0;
      DATI = 1;      //ͨ��1�ĵڶ�λ
    _nop_();
     Clk = 1;
     _nop_();
   }

      Clk = 0;
      DATI = 1;
    for( i = 0;i < 8;i++ )      //��ȡǰ8λ��ֵ
    {
       _nop_();
       adval <<= 1;
       Clk = 1;
       _nop_();
       Clk = 0;
       if (DATO)
          adval |= 0x01;
      else
          adval |= 0x00;
    }
      for (i = 0; i < 8; i++)      //��ȡ��8λ��ֵ
      {
           test >>= 1;
           if (DATO)
              test |= 0x80;
           else 
              test |= 0x00;
          _nop_();
          Clk = 1;
          _nop_();
          Clk = 0;
      }
      if(adval == test) //�Ƚ�ǰ8λ���8λ��ֵ���������ͬ��ȥ����һֱ������ʾΪ�㣬�뽫����ȥ��
       dat = test;
       nop_();
       CS = 1;        //�ͷ�ADC0832
       DATO = 1;
       Clk = 1;
       return dat;
}

#endif



