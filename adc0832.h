#include<reg52.h> 
#include<intrins.h>

#ifndef __ADC0832_H__
#define __ADC0832_H__
/*****************************************
ʹ��˵��:
ֱ�ӵ���get_ad_data();�˺��������ǽ���ȡʮ��
ADֵ�����ʮ�ε�ƽ��ֵ

ˮλ���㣺
				Ad_dat=(float)((Ad_dat-2)/2.4);  //����ˮλ
				ADC_Value = (Ad_dat);	
				
				

****************************************/
#define ENABLE 1
#define DISABLE 0

#define TWO_CHANLE DISABLE


#if TWO_CHANLE == ENABLE

static unsigned int  A_D();
unsigned char get_ad_data(void);
#else

unsigned char adc0832(unsigned char CH);

#endif



#endif