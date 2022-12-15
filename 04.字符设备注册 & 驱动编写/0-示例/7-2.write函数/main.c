#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
int main(int argc,char*argv[])
{
	int fd;
	unsigned char led_dat=0;
	printf("main is call!!!\n");
	fd = open("/dev/LED",O_RDWR);
	if(fd<0)
	{	
		printf("open err\n");
		return -1;
	}
	printf("open ok\n");
	sleep(2);	
	write(fd,&led_dat,1);
	sleep(2);	
	led_dat = 1;
	write(fd,&led_dat,1);
	sleep(2);	
	close(fd);	
	return 0;
}
