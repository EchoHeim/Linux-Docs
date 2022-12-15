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
	int pid = fork();
	if(pid)
	{
		signal(3,fun);
		while(1)
		{
			printf("father!\n");
			sleep(1);
		}
	}
	else
	{
		sleep(3);
		kill(getppid(),3);
	}
	exit(0);
}
