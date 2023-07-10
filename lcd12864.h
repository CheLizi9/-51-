#ifndef __LCD12864_H
#define __LCD12864_H

#include<reg52.h>

#include<intrins.h>  /*汇编函数库*/

#include<stdlib.h>  /*函数库，可查*/

#define uchar unsigned char /*宏定义-8位的字符型变量*/

#define uint unsigned int /*宏定义-16位的整型变量*/

/*端口定义*/

#define LCD_data P0  //LCD12864数据线  读取到的值

sbit LCD_RS = P3^5;  //数据\指令 选择

sbit LCD_RW = P3^6;  //读\写 选择

sbit LCD_EN = P3^4;  //读\写使能

sbit LCD_PSB = P3^7;  //并行串行数据 选择

//sbit wela    =P2^6;
//sbit dula    =P2^7;

//函数或变量声明

void delay_1ms(uint x);//延迟函数
//uchar LCD_Busy(void);//检测LCD是否忙
void write_cmd(uchar cmd);//写命令
void write_dat(uchar dat);//写数据
void lcd_init();//lcd初始化
void lcd_pos(uchar X,uchar Y);//显示坐标

#endif












