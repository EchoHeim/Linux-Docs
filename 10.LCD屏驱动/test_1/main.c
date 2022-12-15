#include "includes.h"

int main(int argc,char **argv)
{
	unsigned char ch = '1';
	char chs[32];				   //16*16=256个点
	unsigned char s[] = "我们";   //要显示的汉字

	Lcd_init (); 				   //初始化帧缓冲设备

	lcd_clear(WHITE);
	show_bmp(100,100,"3.bmp");  
	show_point(400,240,0xf80000);

	show_string(100,400,0x12345678,0x0000ff,s);
	Lcd_close();						//关闭帧缓冲设备
	
	return 0;
}

