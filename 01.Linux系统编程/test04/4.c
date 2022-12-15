#include <unistd.h>
#include <stdio.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include <sys/wait.h>

void fun()
{
	printf("I am fun!\n");
}

int main()
{
//	signal(SIGINT,fun);			//自定义处理，调用fun函数；
//	signal(SIGINT,SIG_IGN);		//忽略处理；
	signal(SIGINT,SIG_DFL);		//默认处理；
	while(1)
	{
		printf("main\n");
		sleep(1);
	}
	exit(0);
}
