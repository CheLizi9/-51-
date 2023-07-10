#include "adc0832.h"


#if TWO_CHANLE == ENABLE

sbit ADC0832_CS=P1^6;	//ADC0832  控制IO口	  使能口
sbit ADC0832_CLK=P1^5;	//时钟IO口
sbit ADC0832_DIO=P1^3;	//数据输入输出IO口 

static unsigned int  A_D()	    //ADC0832   读值程序
{
	unsigned char i;
	unsigned char dat;					 
	ADC0832_CS=1;   //一个转换周期开始
	ADC0832_CLK=0;  //为第一个脉冲作准备
	ADC0832_CS=0;  //CS置0，片选有效	
	ADC0832_DIO=1;    //DIO置1，规定的起始信号  
	ADC0832_CLK=1;   //第一个脉冲
	ADC0832_CLK=0;   //第一个脉冲的下降沿，此前DIO必须是高电平
	ADC0832_DIO=1;   //DIO置1， 通道选择信号  
	ADC0832_CLK=1;   //第二个脉冲，第2、3个脉冲下沉之前，DI必须跟别输入两位数据用于选择通道，这里选通道RH0 
	ADC0832_CLK=0;   //第二个脉冲下降沿 
	ADC0832_DIO=0;   //DI置0，选择通道0
	ADC0832_CLK=1;    //第三个脉冲
	ADC0832_CLK=0;    //第三个脉冲下降沿 
	ADC0832_DIO=1;    //第三个脉冲下沉之后，输入端DIO失去作用，应置1
	ADC0832_CLK=1;    //第四个脉冲
	for(i=0;i<8;i++)  //高位在前
	{
		ADC0832_CLK=1;         //第四个脉冲
		ADC0832_CLK=0; 
		dat<<=1;       //将下面储存的低位数据向右移
		dat|=(unsigned char)ADC0832_DIO; 	 //将输出数据DIO通过或运算储存在dat最低位 
	}	  		        
	ADC0832_CS=1;          //片选无效 
	return dat;	 //将读书的数据返回     
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

sbit CS=P1^5;	//ADC0832  控制IO口	  使能口
sbit Clk=P1^6;	//时钟IO口
sbit DATI=P1^7;	//数据输入输出IO口 
sbit DATO = P1^7;
unsigned int dat = 0x00;      //AD值

/****************************************************************************
函数功能:AD转换子程序
入口参数:CH   0 or 1
出口参数:dat
****************************************************************************/
unsigned char adc0832(unsigned char CH)
{
      unsigned char i,test,adval;
     adval = 0x00;
     test = 0x00;
     Clk = 0;       //初始化
     DATI = 1;
    _nop_();
    CS = 0;
    _nop_();
    Clk = 1;
   _nop_();


   if ( CH == 0x00 )      //通道选择
   {
       Clk = 0;
       DATI = 1;      //通道0的第一位
       _nop_();
      Clk = 1;
        _nop_();
        Clk = 0;
      DATI = 0;      //通道0的第二位
      _nop_();
      Clk = 1;
      _nop_();
    } 
    else
    {
       Clk = 0;
    DATI = 1;      //通道1的第一位
      _nop_();
      Clk = 1;
      _nop_();
      Clk = 0;
      DATI = 1;      //通道1的第二位
    _nop_();
     Clk = 1;
     _nop_();
   }

      Clk = 0;
      DATI = 1;
    for( i = 0;i < 8;i++ )      //读取前8位的值
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
      for (i = 0; i < 8; i++)      //读取后8位的值
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
      if(adval == test) //比较前8位与后8位的值，如果不相同舍去。若一直出现显示为零，请将该行去掉
       dat = test;
       nop_();
       CS = 1;        //释放ADC0832
       DATO = 1;
       Clk = 1;
       return dat;
}

#endif



