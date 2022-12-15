#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int main(int argc,char*argv[])
{
	int fd;
	printf("main is call!!!\n");
	fd = open("/dev/led2",O_RDWR);
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
