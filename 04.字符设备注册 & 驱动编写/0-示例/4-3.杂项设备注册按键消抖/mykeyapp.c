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
	while(1)
	{
		read(fd,&str,1);
		if(str>0)
		{
			printf("key %d is pass\n",str);
		}	
	}	
	close(fd);
	return 0;
}
