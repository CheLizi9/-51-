/**********************************************
ע�����

ÿ����ַ���ֻ�ܴ洢8�ֽڣ����ֵ����255������Ҫ��ֵ��

ʹ�÷�����

data_high = Tem_H/100;
data_low = Tem_H%100;

Sector_Erase(0x2000);                                       // ������Ƭ���ڲ�EEPROM������
EEPROM_Write(0x2000, data_high);
EEPROM_Write(0x2001, data_low);

data_high = Tem_L/100;
data_low = Tem_L%100;
EEPROM_Write(0x2002, data_high);
EEPROM_Write(0x2003, data_low);

--------------------------------

data_high = EEPROM_Read(0x2000);                     // ��EEPROM�ж�ȡ����ֵ
data_low = EEPROM_Read(0x2001);

Tem_H = (data_high*100)+data_low;


data_high = EEPROM_Read(0x2002);                     // ��EEPROM�ж�ȡ����ֵ
data_low = EEPROM_Read(0x2003);

Tem_L = (data_high*100)+data_low;      



//��ȡ���籣�������
void Read_e2()
{
	uchar Check = 0;
	Check = EEPROM_Read(0x2000);                     // ��EEPROM�ж�ȡ����ֵ
	if(Check == 18)
	{
		C_shi 	= EEPROM_Read(0x2001);
		C_fen 	= EEPROM_Read(0x2002);
		C_miao 	= EEPROM_Read(0x2003);
		Tem_H 	= EEPROM_Read(0x2004);
		Tem_L 	= EEPROM_Read(0x2005);
		Hum_H 	= EEPROM_Read(0x2006);
		Hum_L	 	= EEPROM_Read(0x2007);
		if(C_shi > 0x60 || C_fen > 0x60 || C_miao > 0x60 || Tem_H > 99 || Tem_L > 99 || Hum_H > 99 || Hum_L > 99)
		{
			C_shi 	= 0x07;
			C_fen 	= 0x32;
			C_miao 	= 0x35;
			Tem_H 	= 35;
			Tem_L 	= 10;
			Hum_H 	= 70;
			Hum_L	 	= 20;
		}
	}
}
//�����ݱ�����оƬ��
void Write_e2()
{
	Sector_Erase(0x2000);                                       // ������Ƭ���ڲ�EEPROM������
	EEPROM_Write(0x2000, 18);
	EEPROM_Write(0x2001, C_shi);
	EEPROM_Write(0x2002, C_fen);
	EEPROM_Write(0x2003, C_miao);
	EEPROM_Write(0x2004, Tem_H);
	EEPROM_Write(0x2005, Tem_L);
	EEPROM_Write(0x2006, Hum_H);
	EEPROM_Write(0x2007, Hum_L);
}


**********************************************/
#ifndef _EEPROM_ISP_H
#define _EEPROM_ISP_H

#include <REG52.H>
#include<intrins.h>

sfr ISP_DATA  = 0xe2;                   // ���ݼĴ���
sfr ISP_ADDRH = 0xe3;                   // ��ַ�Ĵ����߰�λ
sfr ISP_ADDRL = 0xe4;                   // ��ַ�Ĵ����Ͱ�λ
sfr ISP_CMD   = 0xe5;                   // ����Ĵ���
sfr ISP_TRIG  = 0xe6;                   // ������Ĵ���
sfr ISP_CONTR = 0xe7;                   // ����Ĵ���



static void ISP_Disable();
unsigned char EEPROM_Read(unsigned int add);
void EEPROM_Write(unsigned int add, unsigned char ch);
void Sector_Erase(unsigned int add);



#endif