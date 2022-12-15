#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
/*
vfork函数创建的子进程和父进程共同占用父进程资源，
这样导致创建子进程后，子进程运行独占资源导致父进程
阻塞。编译程序可以看到现象。
只有子进程退出或者调用exec函数族父进程才可以继续执行。
*/
int main()
{
	int pid = vfork();
	if(pid<0)
	{
		printf("create fork err!!!\n");
		return -1;
	}
	if(pid==0)
	{
		printf("child fork is create !!!\n");
		printf("child pid = %d\n",getpid());
		while(1);
	}
	if(pid>0)
	{
		printf("father is going!!!\n");
		printf("father pid = %d\n",getpid());
	}
	return 0;
}
