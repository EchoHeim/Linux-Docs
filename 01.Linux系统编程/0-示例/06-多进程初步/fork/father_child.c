#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int main(void)
{
	int pid = fork();
	/*
		fork:创建子进程失败返回-1;
			 成功:父进程返回大于0的数,即子进程的pid
			 	  子进程返回0
	*/
	if(0 > pid)
	{
		printf("创建子进程失败\n");	
	}
	else if( 0 == pid)
	{
		printf("child process, pid:%d, ppid:%d\n", getpid(), getppid());	
	}
	else
	{
		printf("father process, pid:%d, child id:%d\n", getpid(), pid);	
	}
	return 0;
}

