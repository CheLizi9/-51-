#include "eeprom_isp.h"



/*********************************************************/
//       单片机内部EEPROM不使能
/*********************************************************/

static void ISP_Disable()
{
    ISP_CONTR = 0;
    ISP_ADDRH = 0;
    ISP_ADDRL = 0;
}

/*********************************************************/
// 从单片机内部EEPROM读一个字节，从0x2000地址开始
/*********************************************************/
unsigned char EEPROM_Read(unsigned int add)
{
    ISP_DATA  = 0x00;
    ISP_CONTR = 0x83;
    ISP_CMD   = 0x01;
    ISP_ADDRH = (unsigned char)(add >> 8);
    ISP_ADDRL = (unsigned char)(add & 0xff);
    // 对STC89C51系列来说，每次要写入0x46，再写入0xB9,ISP/IAP才会生效
    ISP_TRIG  = 0x46;
    ISP_TRIG  = 0xB9;
    _nop_();
    ISP_Disable();
    return (ISP_DATA);
}


/*********************************************************/
// 往单片机内部EEPROM写一个字节，从0x2000地址开始
/*********************************************************/
void EEPROM_Write(unsigned int add, unsigned char ch)
{
    ISP_CONTR = 0x83;
    ISP_CMD   = 0x02;
    ISP_ADDRH = (unsigned char)(add >> 8);
    ISP_ADDRL = (unsigned char)(add & 0xff);
    ISP_DATA  = ch;
    ISP_TRIG  = 0x46;
    ISP_TRIG  = 0xB9;
    _nop_();
    ISP_Disable();
}


/*********************************************************/
// 擦除单片机内部EEPROM的一个扇区
// 写8个扇区中随便一个的地址，便擦除该扇区，写入前要先擦除
/*********************************************************/
void Sector_Erase(unsigned int add)
{
    ISP_CONTR = 0x83;
    ISP_CMD   = 0x03;
    ISP_ADDRH = (unsigned char)(add >> 8);
    ISP_ADDRL = (unsigned char)(add & 0xff);
    ISP_TRIG  = 0x46;
    ISP_TRIG  = 0xB9;
    _nop_();
    ISP_Disable();
}
