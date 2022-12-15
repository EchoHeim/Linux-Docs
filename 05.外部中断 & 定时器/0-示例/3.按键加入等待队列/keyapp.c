#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <string.h>
int main()
{
	unsigned char key;
	int fd = open("/dev/key",O_RDWR);
	if(fd<0)
	{
		printf("open fail!!!\n");
		return -1;
	}
	read(fd,&key,1);
	printf("key = %d\n",key);
	close(fd);
	return 0;
}
