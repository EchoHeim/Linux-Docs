#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <errno.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <termios.h>
#include <stdlib.h>    

int main(void)
{
	unsigned char val=0,usart_val=0;
	unsigned char a='1',b='2',c='3',d='4',e='5';
	int fd=open("/dev/myusart2",O_RDWR);
	int fd1=open("/dev/mykeydrv",O_RDWR);
	int fd2=open("/dev/myled",O_RDWR);
	if(fd<0)
	{
		printf("usart open failed!!!\n");
		return -1;
	}
	if(fd1<0)
	{
		printf("key open failed!!!\n");
		return -1;
	}
	if(fd2<0)
	{
		printf("led open failed!!!\n");
		return -1;
	}
	printf("open succeed!!!\n");
	while(1)
	{
		int pid=fork();
		if(pid>0)
		{
			while(1)
			{
				read(fd1,&val,1);//读取按键值
				switch(val)
				{
					case 1:write(fd,&a,1);break;
					case 2:write(fd,&b,1);break;
					case 3:write(fd,&c,1);break;
					case 4:write(fd,&d,1);break;
					default:write(fd,&e,1);break;
				}
			}
			wait(NULL);
			exit(0);
		}
		if(pid==0)
		{
			while(1)
			{
				read(fd,&usart_val,1);//读取串口值
				switch(usart_val)
				{
					case '1':{ioctl(fd2,1,1);sleep(2);ioctl(fd2,1,0);}break;
					case '2':{ioctl(fd2,3,1);sleep(2);ioctl(fd2,3,0);}break;
					case '3':{ioctl(fd2,4,1);sleep(2);ioctl(fd2,4,0);}break;
					case '4':{ioctl(fd2,5,1);sleep(2);ioctl(fd2,5,0);}break;
					default:{ioctl(fd2,1,0);ioctl(fd2,3,0);ioctl(fd2,4,0);
								ioctl(fd2,5,0);	}break;
				}
			}
		}
		exit(0);
	}
	return 0;
}







