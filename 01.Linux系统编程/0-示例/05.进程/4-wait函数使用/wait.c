#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
/*
	程序执行后发现程序死在那里，原因是wait函数会等待指定
	进程退出然后做清理工作，子进程不退出程序自然在那里等待。
*/
int main()
{
	int status;
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
		wait(&status);
		printf("father is end!!!\n");
		exit(0);
	}
	return 0;
}
