/*============================================================================
#
# Author: fan 
# Last modified: 2015-06-26 10:33
# Filename: child.c
# Description: 
#
#
#
#
===========================================================================*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>

void child_handler(int signal)
{
	pid_t pid;
	int status;

	pid = wait(&status);

	printf("child:%d exit\n", pid);
}

int main(void)
{

	int count = 10;
	signal(SIGCHLD, child_handler); //注册信号

	pid_t pid;
	
	while(count--)
	{
		pid = fork();
		sleep(1);
		if(0 > pid)
		{
			perror("fork");	
			return -1;
		}
		else if(0 == pid)
		{
			printf("my pid:%d\n", getpid());	
			return 0;
		}
		else
		{
			sleep(1);
			continue;
		}

	}
	return 0;
}

