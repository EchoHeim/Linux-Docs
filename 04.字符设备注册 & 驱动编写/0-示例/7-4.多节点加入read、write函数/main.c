#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int main(int argc,char*argv[])
{
	int fd;
	unsigned char buff=1;
	unsigned char c_buff=0;
	fd = open("/dev/led2",O_RDWR);
	while(1)
	{
		write(fd,&c_buff,1);
		sleep(1);
		write(fd,&buff,1);
		sleep(1);
	}
	close(fd);	
	return 0;
}
