#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>

int main(int argc,char **argv)
{
	int fd;
	int i;
	int led_val;

	if(argc != 2)
	{
		printf("Usage : 1、%s   2、/dev/led\n",argv[0]);
		return -1;
	}
	fd = open(argv[1],O_RDWR);
	
	if(fd<= 0)
	{
		printf("open error!!\n");
		return -1;
	}

	 led_val = 0;
	 write(fd,&led_val, 1);
	 close(fd);

	return 0;
}
