#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

//孤儿进程
int main(void)
{
	int pid = fork();
	if(pid>0)
	{
		sleep(2);
//		exit(0);
	}
	else //子进程
	{
		//由于父进程先退出,那么该进程就成了孤儿进程
		while(1)
		{
			sleep(1);
			//2s之后ppid变为init进程,即1
			printf("pid:%d\t ppid:%d\n", getpid(), getppid());
		}
	}
}

