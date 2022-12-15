#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
int main(int argc,char*argv[])
{
	int fd;
	unsigned char buf;
	unsigned char data=1;
	printf("main is call!!!\n");
	fd = open("/dev/LED",O_RDWR);
	if(fd<0)
	{	
		printf("open err\n");
		return -1;
	}
	fd=read(fd,&buf,1);
	printf("buf = %d\n",buf);
	if(buf==0)
	{
		data=1;
		write(fd,&data,1);
	}
	else
	{
		data=0;
		write(fd,&data,1);
	}
	sleep(3);
	close(fd);	
	return 0;
}
