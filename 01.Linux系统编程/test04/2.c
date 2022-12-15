#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include <sys/wait.h>
int main()
{
	char buf[100];
	unlink("1.fifo");
	int fl=mkfifo("1.fifo",0666);
	if(fl==-1)
	{
		printf("create failed!\n");
		exit(0);
	}
	else
	{
		int pid=fork();
		if(pid>0)
		{
			int fd=open("1.fifo",O_RDONLY);
			read(fd,buf,sizeof(buf));
			printf("str=%s\n",buf);
			printf("father will exit!!!\n");
			wait(NULL);
			close(fd);
		}
		if(pid==0)
		{
			int fd=open("1.fifo",O_WRONLY);
			if(fd==-1)
			{
				printf("open failed!\n");
				exit(0);
			}
			else
				printf("open succeed!\n");
			if(write(fd,"hello world!",13)==-1)
				printf("write failed!\n");
			else
				printf("write succeed!\n");
			close(fd);
			exit(0);
		}
	}
	exit(0);
}
