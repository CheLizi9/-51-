#ifndef __DS18B20_H__
#define __DS18B20_H__


#include <reg52.h>

//DS18B20 IO设置
sbit DS18B20_DQ = P2^2;

#ifndef uchar
#define uchar unsigned char
#endif

#ifndef uint 
#define uint unsigned int
#endif

//函数或者变量声明
extern void DS18B20_Delay( unsigned int n );
extern void DS18B20_Write_Byte( unsigned char dat);
extern uchar DS18B20_Read_Byte( );
extern bit DS18B20_Init();
extern uint Get_temp(void);

extern unsigned char flag_temper;

#endif
