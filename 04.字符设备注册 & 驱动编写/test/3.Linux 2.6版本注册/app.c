#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>

/*
 	led流水灯程序；
	Linux2.6版本注册设备节点，要分别打开对应的节点文件；
*/
int main(void)
{
	unsigned char led_val=1;		
	int fd1,fd2,fd3,fd4;	
	while(1)
	{
		fd1=open("/dev/led1",O_RDWR);
		if(fd1<0)
		{
			printf("error!\n");
			return -1;
		}
		led_val=1;
		write(fd1,&led_val,1);
		sleep(1);
		led_val=0;
		write(fd1,&led_val,1);
		close(fd1);

		fd2=open("/dev/led2",O_RDWR);
		if(fd2<0)
		{
			printf("error!\n");
			return -1;
		}
		led_val=1;
		write(fd2,&led_val,1);
		sleep(1);
		led_val=0;
		write(fd2,&led_val,1);
		close(fd2);

		fd3=open("/dev/led3",O_RDWR);
		if(fd3<0)
		{
			printf("error!\n");
			return -1;
		}
		led_val=1;
		write(fd3,&led_val,1);
		sleep(1);
		led_val=0;
		write(fd3,&led_val,1);
		close(fd3);

		fd4=open("/dev/led4",O_RDWR);
		if(fd4<0)
		{
			printf("error!\n");
			return -1;
		}
		led_val=1;
		write(fd4,&led_val,1);
		sleep(1);
		led_val=0;
		write(fd4,&led_val,1);
		close(fd4);
	}
	return 0;	
}
