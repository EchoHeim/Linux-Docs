#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
int main()
{
	unsigned char str;
	int fd = open("/dev/mykey",O_RDWR);
	if(fd<0)
	{
		printf("open fail!!!\n");
	}
	printf("open ok!!!\n");
	while(1)
	{
		read(fd,&str,1);
		sleep(1);
	}	
	close(fd);
	return 0;
}
