#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int num = 100;
int main()
{
	int pid = fork();
	if(pid > 0)
	{
//		wait(NULL);
		sleep(10);
		printf("father\tnum = %d\n",num);
	}
	if(pid == 0)
	{
		num = 90;
		printf("child\tnum = %d\n",getpid());
		while(1);
	}
//	exit(0);
}
