#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <poll.h>
#include <signal.h>
#include <unistd.h>
#include <fcntl.h>
int fd;
void sig_fun(int signum)
{
	static unsigned char val = 0;
	read(fd,&val,1);
	printf("val =  %d\n",val);
}
int main()
{
	int Oflags;
	fd = open("/dev/key",O_RDWR);
	if(fd<0)
	{
		printf("open fail!!!\n");
		return -1;
	}
	signal(SIGIO,sig_fun);
	fcntl(fd,F_SETOWN,getpid());
	Oflags = fcntl(fd,F_GETFL);
	fcntl(fd,F_SETFL,Oflags|FASYNC);
	while(1)
	{
		printf("fasync\n");
		sleep(3);
	}
	printf("bye bye!!!\n");
	close(fd);
	return 0;
}
