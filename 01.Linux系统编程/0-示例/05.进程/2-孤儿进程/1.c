#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
/*
父进程退出，子进程while死在那里，终端执行 ps -ef命令
发现子进程被init祖先进程接收
*/
int main()
{
	int pid = fork();
	if(pid<0)
	{
		printf("create fork err!!!\n");
		return -1;
	}
	if(pid==0)
	{
		printf("child is going !!! %d\n",getpid());
		while(1);
	}
	if(pid>0)
	{
		printf("father is going!!!\n");
		exit(0);
	}
	return 0;
}
