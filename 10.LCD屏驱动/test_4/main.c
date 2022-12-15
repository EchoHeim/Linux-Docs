#include "includes.h"
#include <signal.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <errno.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <termios.h>
#include <stdlib.h>    
char time_flag_t;

int main(int argc,char *args[])
{	
//	int *pf,*pc,*pd;
	 int fd;
    int nread=0,i = 0;
    int port;
		perror("传参格式：./app 0-3");
    if(argc == 2) 
		{
        port = atoi(args[1]);   /*将传入的字符串转为整数*/
        if(port <0 || port > 3) /*判断串口的范围*/
        {
            perror("无效串口号：0~3");
            exit(-1);
        }

        if((fd=open_port(port))<0) /*判断open返回的文件描述符*/
        {
            perror("open_port串口端口打开错误\n");
            exit(-1);
        }
    }
    else /*如果没有传参，默认打开串口0*/
    {
        if((fd=open_port(0))<0) /*判断open返回的文件描述符*/
        {
            perror("open_port error");
            exit(-1);
        }
    }

    if((i=set_opt(fd,9600,8,'N',1))<0)/*配置串口的基本参数*/
    {
        perror("set_opt error");
        return;
    }
    printf("fd=%d\n",fd);

		char buff[50]; 
 		int aa = 0;
 		
 		
	struct input_event ev_key;
	int fds;
    fds = open(EVENT_NAME, 0);  
    if (fds < 0)
    {
        perror("open device key!");
        exit(1);
    }

	Lcd_init (); 				   //初始化帧缓冲设备
	show_bmp(0,0,"1.bmp");

	int pid1 = fork();
	int pid2 = fork();
	
	if(pid1 > 0)
	{
		while(1)
		{
			nread=read(fd,buff,50);
			sleep(1);
			if(nread>0)
			{
				for( aa = 0;aa<5;aa ++)
				{
					printf("%d   ",buff[aa]);
				}
				show_string(400,20,0x12345678,0xcccccc,"光照等级:",32,0);
				show_num(550,20,0x12345678,0xcccccc,buff[0],1,32,0x01);
				
				show_string(400,55,0x12345678,0xcccccc,"火灾报警:",32,0);
				if(buff[1] == 1)
					show_string(550,55,0x12345678,0xcccccc,"危险:",32,1);
				else if(buff[1] == 0)
					show_string(550,55,0x12345678,0xcccccc,"安全:",32,1);
					
				if(buff[2] == 1)
					show_string(600,20,0x12345678,0xcccccc,"有人",32,1);
				else if(buff[2] == 0)
					show_string(600,20,0x12345678,0xcccccc,"无人",32,1);
					
				show_string(400,90,0x12345678,0xcccccc,"温度:",32,0);
				show_num(550,90,0x12345678,0xcccccc,buff[3],2,32,0x11);
				show_string(400,125,0x12345678,0xcccccc,"湿度:",32,0);
				show_num(550,125,0x12345678,0xcccccc,buff[4],2,32,0x11);
				memset(buff,0,50);
				nread=0;	 
			}
		}
	}
	if(pid2 == 0)
	{
		while (1)
		{
			read(fds, &ev_key, sizeof(struct input_event));
			if (EV_ABS == ev_key.type)
			{
				Change_pic(700,20,700,20,24,16,pic);
				show_string(700,20,0x12345678,0xcccccc,"X =",16,0);
				Change_pic(700,40,700,40,24,16,pic);
				show_string(700,40,0x12345678,0xcccccc,"Y =",16,0);
				if(ev_key.code == ABS_X)
				{
					Change_pic(732,20,732,20,24,16,pic);
					show_num(732,20,0x12345678,0xcccccc,ev_key.value,3,16,0x00);
				}
				else if(ev_key.code == ABS_Y)
				{
					Change_pic(732,40,732,40,24,16,pic);
					show_num(732,40,0x12345678,0xcccccc,ev_key.value,3,16,0x00);
				}
			}
		}
		exit(0);
	}
	if(pid1 == 0)
	{	
		int fds, retval;
		struct rtc_time rtc_tm;
		
		fds = open ("/dev/rtc0", O_RDONLY);
		if (fds == -1) 
		{
			perror("/dev/rtc");
			exit(1);
		}

		retval = ioctl(fds, RTC_RD_TIME, &rtc_tm);
		if (retval == -1) 
		{
			perror("ioctl");
			exit(1);
		}
		rtc_tm.tm_year = set_time[0] - 1900;
		rtc_tm.tm_mon = set_time[1] - 1;
		rtc_tm.tm_mday = set_time[2];
		rtc_tm.tm_hour = set_time[3];
		rtc_tm.tm_min = set_time[4];
		rtc_tm.tm_sec = set_time[5];
//		retval = ioctl(fds, RTC_SET_TIME, &rtc_tm);

		show_string(25,120,0x12345678,0xcccccc,"星期",24,0);
		show_string(116,20,0x12345678,0xcccccc,"-  -",48,0);
		show_string(92,70,0x12345678,0xcccccc,":  :",48,0);
		while(1)
		{
			retval = ioctl(fds, RTC_RD_TIME, &rtc_tm);
			if (time_flag_t != rtc_tm.tm_sec)
			{			
				Change_pic(20,20,20,20,96,48,pic);
				show_num(20,20,0x12345678,0xcccccc,rtc_tm.tm_year + 1900,4,48,0x10);
				Change_pic(140,20,140,20,48,48,pic);
				show_num(140,20,0x12345678,0xcccccc,rtc_tm.tm_mon + 1,2,48,0x10);
				Change_pic(212,20,212,20,48,48,pic);
				show_num(212,20,0x12345678,0xcccccc,rtc_tm.tm_mday, 2,48,0x10);
				
				Change_pic(44,70,44,70,48,48,pic);
				show_num(44,70,0x12345678,0xcccccc,rtc_tm.tm_hour, 2,48,0x10);
				Change_pic(116,70,116,70,48,48,pic);
				show_num(116,70,0x12345678,0xcccccc,rtc_tm.tm_min, 2,48,0x10);
				Change_pic(188,70,188,70,48,48,pic);
				show_num(188,70,0x12345678,0xcccccc,rtc_tm.tm_sec, 2,48,0x10);

				Change_pic(73,120,73,120,24,24,pic);
				switch(RTC_Get_Week(rtc_tm.tm_year+1900,rtc_tm.tm_mon+1,rtc_tm.tm_mday))		//星期显示;
				{
					case 0:show_string(73,120,0x12345678,0xcccccc,"日",24,0);break;
					case 1:show_string(73,120,0x12345678,0xcccccc,"一",24,0);break;
					case 2:show_string(73,120,0x12345678,0xcccccc,"二",24,0);break;
					case 3:show_string(73,120,0x12345678,0xcccccc,"三",24,0);break;
					case 4:show_string(73,120,0x12345678,0xcccccc,"四",24,0);break;
					case 5:show_string(73,120,0x12345678,0xcccccc,"五",24,0);break;
					case 6:show_string(73,120,0x12345678,0xcccccc,"六",24,0);break;
				}
				time_flag_t = rtc_tm.tm_sec;
			}
		}
	}
	return 0;
}

