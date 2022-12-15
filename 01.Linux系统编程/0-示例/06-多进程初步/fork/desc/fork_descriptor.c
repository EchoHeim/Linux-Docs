#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(void)
{
	pid_t pid;
	int fd;
	int i=1;
	char *ch1="hello";
	char *ch2="world";
	char *ch3="IN";
	if((fd=open("test.txt",O_RDWR|O_CREAT,0644))==-1)
	{
		perror("parent open");
		exit(1);
	}
	if(write(fd,ch1,strlen(ch1))==-1)
	{	 
		perror("parent write");
		exit(1);
	}
	if((pid=fork())==-1)
	{
		perror("fork");
		exit(1);
	}
	else if(pid==0)
	{
		i=2; //复制了一份,	
		printf("in child\n");
		printf("i=%d\n",i);
		if(write(fd,ch2,strlen(ch2))==-1)//fd也复制了一份
			perror("child write");

		close(fd);
		return 0;
	}
	else
	{
		sleep(1);
		printf("in parent\n");
		printf("i=%d\n",i);
		if(write(fd,ch3,strlen(ch3))==-1)
			perror("parent,write");
		wait(NULL); 	//等待子进程结束;
		close(fd);
		return 0;
	}
	return 0;
}
