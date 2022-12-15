#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>

int main(void)
{
	char ch;
	int fd=open("/dev/hello_dri",O_RDWR);
	if(fd<0)
		printf("error!\n");
	while(1)
	{
		read(fd,ch,1);
	}
	return 0;	
}
