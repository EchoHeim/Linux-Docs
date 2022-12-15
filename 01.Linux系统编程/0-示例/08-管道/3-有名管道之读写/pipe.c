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
	int num = mkfifo("./1.fifo",0666);
	if(num <0)
	{
		printf("create fail!!!\n");
		exit(0);
	}
	fd = open("./1.fifo",O_WRONLY);
	if(fd <0)
	{
		printf("open fail!!!\n");
		exit(0);
	}
	write(fd,"hello",6);
	close(fd);
	return 0;
}
