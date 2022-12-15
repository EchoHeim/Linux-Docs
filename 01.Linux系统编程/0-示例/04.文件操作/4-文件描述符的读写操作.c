#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int main()
{
	char str[20];
	int fd = open("2.txt",O_RDWR|O_CREAT,0655);
	if(fd<0)
	{
		printf("open fail!!!\n");
		return -1;
	}
	write(fd,"helloworld",11);
	lseek(fd,0,SEEK_SET);
	read(fd,str,11);
	printf("str = %s\n",str);
	close(fd);
	return 0;
}
