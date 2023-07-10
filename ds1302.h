#ifndef _DS1302_H_
#define _DS1302_H_
#include<reg52.h>
#define uchar unsigned char
#define uint unsigned int

sbit clk = P1^0;	  //ds1302ʱ���߶���
sbit io =  P1^1;	  //������
sbit rst = P1^2;	  //��λ��
extern uchar miao,fen,shi,ri,yue,week,nian;


/*************дһ�����ݵ���Ӧ�ĵ�ַ��***************/
void write_ds1302(uchar add,uchar dat);

/*************�����ݱ��浽ds1302 RAM��**0-31*************/
void write_ds1302ram(uchar add,uchar dat);

/*************�����ݴ�ds1302 RAM������**0-31*************/
uchar read_ds1302ram(uchar add);

/*************�Ӷ�Ӧ�ĵ�ַ��һ�����ݳ���***************/
uchar read_ds1302(uchar add);

/*************��ʼ��ds1302ʱ��***************/
void init_ds1302();

/*************��Ҫ��ʱ�� ������ ��������***************/
void read_time();

/*************��Ҫд��ʱ�� ������ ��д��ds1302��***************/
void write_time();

/**********************����ds1302ʱ�亯��**********************/
void set_ds1302time(uchar num,uchar *shi,uchar dat);	 //��ʱ






/******************
	ds1302 �ڲ�RAM   RAM0  1100 000R/W   1�� 0д
					 RAM1  1100 001R/W  
					       ....... 
					 RAM30 1111 110R/W   
********************/
						//��  ��   ʱ   ��   ��  ��   ���� 	
uchar code write_add[]={0x80,0x82,0x84,0x86,0x88,0x8c,0x8a};   //д��ַ
uchar code read_add[] ={0x81,0x83,0x85,0x87,0x89,0x8d,0x8b};   //����ַ
uchar code init_ds[]  ={0x58,0x29,0x07,0x05,0x10,0x14,0x1};   
uchar miao,fen,shi,ri,yue,week,nian;
uchar i;


/*************дһ�����ݵ���Ӧ�ĵ�ַ��***************/
void write_ds1302(uchar add,uchar dat)
{		
	rst = 1;			 //�Ѹ�λ���ø�
	for(i=0;i<8;i++)
	{				     //��λ��ǰ

		io = add & 0x01;    	
		add >>= 1;		 //�ѵ�ַ����һλ
		clk = 1;		 //ʱ�����ø�	 
		clk = 0;		 //ʱ�����õͿ�ʼд����
	}									 
	for(i=0;i<8;i++)
	{

		io = dat & 0x01;
		dat >>= 1;		 //����������һλ	
		clk = 1;		 //ʱ�����ø�
		clk = 0;		 //ʱ�����õͿ�ʼд����
	}
	rst = 0;			 //��λ�ߺϵ�
}

/*************�Ӷ�Ӧ�ĵ�ַ��һ�����ݳ���***************/
uchar read_ds1302(uchar add)
{
	uchar value,i;
	rst = 1;			 //�Ѹ�λ���ø�
	for(i=0;i<8;i++)
	{				     //��λ��ǰ
		clk = 0;		 //ʱ�����õͿ�ʼд����
		io = add & 0x01;    	
		add >>= 1;		 //�ѵ�ַ����һλ
		clk = 1;		 //ʱ�����ø�
	}		
	for(i=0;i<8;i++)
	{
		clk = 1;		 //ʱ�����ø�
		clk = 0;		 //ʱ�����õͿ�ʼ������
		value >>= 1;
		if(io == 1)
			value |= 0x80;
	}
	rst = 0;			 //��λ�ߺϵ�
	clk = 0;
	io = 0;
	return value;		 //���ض�����������
}



/*************��Ҫ��ʱ�� ������ ��������***************/
void read_time()
{
	miao = read_ds1302(read_add[0]);	//����
	fen  = read_ds1302(read_add[1]);	//����
	shi  = read_ds1302(read_add[2]);	//��ʱ
	ri   = read_ds1302(read_add[3]);	//����
	yue  = read_ds1302(read_add[4]);	//����
	nian = read_ds1302(read_add[5]);	//����
	week = read_ds1302(read_add[6]);	//������
}

/*************��Ҫд��ʱ�� ������ ��д��ds1302��***************/
void write_time()
{
	write_ds1302(0x8e,0x00);			//��д����

	write_ds1302(write_add[0],0x80);	

	write_ds1302(write_add[0],miao);	//д��
	write_ds1302(write_add[1],fen);		//д��
	write_ds1302(write_add[2],shi);		//дʱ
	write_ds1302(write_add[3],ri);		//д��
	write_ds1302(write_add[4],yue);		//д��
	write_ds1302(write_add[5],nian);	//д����
	write_ds1302(write_add[6],week);	//д��
	write_ds1302(0x8e,0x80);			//�ر�д����
}

/*************�����ݱ��浽ds1302 RAM��**0-31*************/
void write_ds1302ram(uchar add,uchar dat)
{
	add <<= 1;     //��ַ�Ǵӵڶ�λ��ʼ��
	add &= 0xfe;   //�����λ����  ��д������
	add |= 0xc0;   //��ַ�����λΪ 1  
	write_ds1302(0x8e,0x00);
	write_ds1302(add,dat);	
	write_ds1302(0x8e,0x80);
}

/*******************************************
�������ƣ�set_ds1302time
��    �ܣ��޸�ʱ�亯������Ϊ��16��ֹ���ܼ򵥵ļӼӼ���
��    ����num --�ӻ��߼�   0--��   1--��
          *shi--������Ҫ�ı��ʱ�������������  ��ס������Ǳ�����ַ  �ڱ���ǰ��&����
          dat --Ϊ����ʱ��������ֵ   ����0x24  ���ӵ�0x24�����0
����ֵ  ����
*******************************************/
void set_ds1302time(uchar num,uchar *shi,uchar dat)	 //��ʱ
{
  	if(num == 1)
    {
    	*shi+=0x01;
		if((*shi & 0x0f) >= 0x0a)
			*shi = (*shi & 0xf0) + 0x10;
		if(*shi >= dat)
			*shi = 0;
    }
    else
    {
		if(*shi == 0x00)
			*shi = dat;
		if((*shi & 0x0f) == 0x00)
			*shi = (*shi | 0x0a) - 0x10;
		*shi -=0x01 ; 
    }  
}

/*************�����ݴ�ds1302 RAM������**0-31*************/
uchar read_ds1302ram(uchar add)
{
	add <<= 1;     //��ַ�Ǵӵڶ�λ��ʼ��
	add |= 0x01;   //�����λ��1  �Ƕ�����
	add |= 0xc0;   //��ַ�����λΪ 1  
	return(read_ds1302(add));	
}


/*************��ʼ��ds1302ʱ��***************/
void init_ds1302()
{
	uchar i;
	rst = 0;	//��һ�ζ�д����ʱҪ��IOƷ�õ�
	clk = 0;
	io = 0;
	i = read_ds1302ram(30);   
	if(i != 3)
	{	
		i = 3;
		write_ds1302ram(30,i);			 //4050   4100		 3080

		write_ds1302(0x8e,0x00);	            //��д����
		for(i=0;i<7;i++)
			write_ds1302(write_add[i],init_ds[i]);	//�����λֵ0 ����ds1302����
		write_ds1302(0x8e,0x80);	//��д����
	}

	read_time();		  //��ʱ��
	if(miao >= 0x60)
	{
		write_ds1302(0x8e,0x00);	            //��д����
			write_ds1302(write_add[0],0x01);	//�����λֵ0 ����ds1302����
		write_ds1302(0x8e,0x80);	//��д����
		
	}

}


#endif