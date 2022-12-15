#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <signal.h>
void handler(int sig)
{
	if(sig ==SIGUSR1)
	{
		printf("get SIGUSR1\n");
	}

	if(SIGKILL == sig)
	{
		printf("get SIGKILL\n");
	}


	if(SIGABRT == sig)
	{
		printf("get SIGABRT\n");	
	}
	
	if(SIGINT == sig)
	{
		printf("get SIGINT\n");
	}
}

int main(void)
{
	signal(SIGUSR1, handler);
	signal(SIGKILL, handler);
	signal(SIGABRT, handler);
	signal(SIGINT, handler);
	int i = 0;
	while(1)
	{
		printf("i = %d\n", i++);
		sleep(1);
		if(0 == i%3)
		{
			kill(getpid(), SIGUSR1);	
			//raise(10);
		}

		if( 0 == i%4)
			kill(getpid(),SIGABRT);
	}
	
	return 0;	
}
