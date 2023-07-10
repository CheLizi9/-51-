#ifndef __LCD12864_H
#define __LCD12864_H

#include<reg52.h>

#include<intrins.h>  /*��ຯ����*/

#include<stdlib.h>  /*�����⣬�ɲ�*/

#define uchar unsigned char /*�궨��-8λ���ַ��ͱ���*/

#define uint unsigned int /*�궨��-16λ�����ͱ���*/

/*�˿ڶ���*/

#define LCD_data P0  //LCD12864������  ��ȡ����ֵ

sbit LCD_RS = P3^5;  //����\ָ�� ѡ��

sbit LCD_RW = P3^6;  //��\д ѡ��

sbit LCD_EN = P3^4;  //��\дʹ��

sbit LCD_PSB = P3^7;  //���д������� ѡ��

//sbit wela    =P2^6;
//sbit dula    =P2^7;

//�������������

void delay_1ms(uint x);//�ӳٺ���
//uchar LCD_Busy(void);//���LCD�Ƿ�æ
void write_cmd(uchar cmd);//д����
void write_dat(uchar dat);//д����
void lcd_init();//lcd��ʼ��
void lcd_pos(uchar X,uchar Y);//��ʾ����

#endif












