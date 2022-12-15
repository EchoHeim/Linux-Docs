#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
/*
子进程先退出，父进程没有清理子进程资源，在父进程没有退出
的15秒内执行 ps -aux 查看到子进程变为僵尸进程。父进程退出前会把
子进程资源清理掉。
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
		exit(0);
	}
	if(pid>0)
	{
		printf("father is going!!!\n");
		sleep(15);
		//while(1);
	}
	return 0;
}
