#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
/*
fork函数创建子进程函数，在子进程中运行返回0
在父进程中运行返回子进程的PID。
*/
int main()
{
	int pid = fork();
	if(pid==0)
	{
		printf("child fork is create!\nchild pid = %d\n",getpid());
		exit(0);
	}
	else if(pid>0)
	{
		printf("father is going!\nfather pid = %d\n",getpid());
		exit(0);
	}
	else if(pid<0)
	{
		printf("create fork err!!!\n");
		exit(0);
	}
	exit(0);
}
