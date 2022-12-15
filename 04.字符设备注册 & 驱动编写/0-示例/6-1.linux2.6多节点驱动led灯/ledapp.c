#include <stdio.h>
#include <stdlib.h>
#include <error.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
int main()
{
	int fd = open("dev/led2",O_RDWR);
	if(fd<0)
	{
		perror("open:");
		return -1;
	}
	printf("open success!!!\n");
	sleep(2);
	close(fd);
	return 0;
}
