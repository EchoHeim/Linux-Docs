#include "includes.h"

void delay(unsigned long t)
{
	int i,j;
	for (i = 0; i < 999; ++i)
	{
		for (j = 0; j < t; ++j);
	}
}

int main(int argc,char **argv)
{
	char ch[2];		
	int x=0,y=0;
	FILE *fd = NULL;
	fd = fopen("/test.txt","r");
	if(fd == NULL)
	{
		printf("打开失败！\n");
		return -1;
	}

	Lcd_init (); 				   //初始化帧缓冲设备
	lcd_clear(0xdddddd);
	while(!(feof(fd)))
	{
		fread(ch,2,1,fd);
		if(ch[0]<128)
		{
			if(ch[0]=='\t')
			{
				show_string(x,y,0x0,0xdddddd," ");
				show_string(x+8,y,0x0,0xdddddd," ");
				show_string(x+16,y,0x0,0xdddddd," ");
				show_string(x+24,y,0x0,0xdddddd," ");
				x+=32;
			}
			else if((ch[0]=='\r')||(ch[0]=='\n'))
			{
				x = 0;
				y+=8;
				if(y>463)
					y=0;
			}
			else
			{
				show_string(x,y,0x0,0xdddddd,ch);
				x+=8;
			}
			fseek(fd,-1,SEEK_CUR);
		}
		else
		{
			show_string(x,y,0x0,0xdddddd,ch);
			x+=16;
		}
		if(x>784)
		{
			x=0;
			y+=16;
		}
		if(y>450)
		{
			sleep(1);
			lcd_clear(0xdddddd);	
			y=0;
		}
	}
	
	Lcd_close();						//关闭帧缓冲设备
	
	return 0;
}

