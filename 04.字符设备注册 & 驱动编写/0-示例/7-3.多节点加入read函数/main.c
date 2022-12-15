#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int main(int argc,char*argv[])
{
	int fd;
	unsigned char buff;
	printf("main is call!!!\n");
	fd = open("/dev/led2",O_RDWR);
	read(fd,&buff,1);
	if(buff==1)
		printf("led is on!!!\n");
	else
	printf("led is off!!!\n");
	if(fd<0)
	{	
		printf("open err\n");
		return -1;
	}
	printf("open ok\n");
	sleep(5);	
	close(fd);	
	return 0;
}
