#include<reg52.h> 
#include<intrins.h>

#ifndef __ADC0832_H__
#define __ADC0832_H__
/*****************************************
使用说明:
直接调用get_ad_data();此函数功能是将获取十次
AD值运算出十次的平均值

水位计算：
				Ad_dat=(float)((Ad_dat-2)/2.4);  //计算水位
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