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
	printf("open ok!!!\n");
	while(1);
	close(fd);
	return 0;
}
