#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>

int main()
{
	int fd;
	char str[10]={"\0"};
	fd = open("./1.fifo",O_RDONLY);
	if(fd <0)
	{
		printf("open fail!!!\n");
		exit(0);
	}
	read(fd,str,5);
	printf("str = %s\n",str);
	close(fd);
	return 0;
}
