#include "eeprom_isp.h"



/*********************************************************/
//       ��Ƭ���ڲ�EEPROM��ʹ��
/*********************************************************/

static void ISP_Disable()
{
    ISP_CONTR = 0;
    ISP_ADDRH = 0;
    ISP_ADDRL = 0;
}

/*********************************************************/
// �ӵ�Ƭ���ڲ�EEPROM��һ���ֽڣ���0x2000��ַ��ʼ
/*********************************************************/
unsigned char EEPROM_Read(unsigned int add)
{
    ISP_DATA  = 0x00;
    ISP_CONTR = 0x83;
    ISP_CMD   = 0x01;
    ISP_ADDRH = (unsigned char)(add >> 8);
    ISP_ADDRL = (unsigned char)(add & 0xff);
    // ��STC89C51ϵ����˵��ÿ��Ҫд��0x46����д��0xB9,ISP/IAP�Ż���Ч
    ISP_TRIG  = 0x46;
    ISP_TRIG  = 0xB9;
    _nop_();
    ISP_Disable();
    return (ISP_DATA);
}


/*********************************************************/
// ����Ƭ���ڲ�EEPROMдһ���ֽڣ���0x2000��ַ��ʼ
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
// ������Ƭ���ڲ�EEPROM��һ������
// д8�����������һ���ĵ�ַ���������������д��ǰҪ�Ȳ���
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
