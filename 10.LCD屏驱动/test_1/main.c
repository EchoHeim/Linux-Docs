#include "includes.h"

int main(int argc,char **argv)
{
	unsigned char ch = '1';
	char chs[32];				   //16*16=256����
	unsigned char s[] = "����";   //Ҫ��ʾ�ĺ���

	Lcd_init (); 				   //��ʼ��֡�����豸

	lcd_clear(WHITE);
	show_bmp(100,100,"3.bmp");  
	show_point(400,240,0xf80000);

	show_string(100,400,0x12345678,0x0000ff,s);
	Lcd_close();						//�ر�֡�����豸
	
	return 0;
}

