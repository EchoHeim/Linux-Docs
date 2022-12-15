#include "includes.h"

int main(int argc,char **argv)
{
	int count,fd;
	struct input_event ev_key;
	
	fd = open("/dev/input/event0", 0);//根据实际情况 有可能不是event1
	if (fd < 0)
	{
		perror("open device key!");
		exit(1);
	}

	Lcd_init (); 				   //初始化帧缓冲设备
	show_bmp(0,0,"1.bmp");
	while (1)
	{
		count = read(fd, &ev_key, sizeof(struct input_event));

		if (EV_ABS == ev_key.type)
		{
			Change_pic(92,20,92,20,40,16,pic);
			show_string(92,20,0x12345678,0xcccccc," X = ",0);
			Change_pic(92,40,92,40,40,16,pic);
			show_string(92,40,0x12345678,0xcccccc," Y = ",0);
			if(ev_key.code== ABS_X)
			{
				Change_pic(132,20,132,20,24,16,pic);
				show_num(132,20,0x12345678,0xcccccc,ev_key.value,3,0);
			}
			else if(ev_key.code== ABS_Y)
			{
				Change_pic(132,40,132,40,24,16,pic);
				show_num(132,40,0x12345678,0xcccccc,ev_key.value,3,0);
			}
		}
	}
	
	close(fd);	
	Lcd_close();						//关闭帧缓冲设备
	
	return 0;
}

