/*============================================================================
#
# Author: fan 
# Last modified: 2015-04-07 10:20
# Filename: pause.c
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

void handler(int sig)
{
	switch(sig)
	{
		case SIGUSR1:
			printf("get SIGUSR1 signal\n");

		break;

		case SIGALRM:
			printf("get SIGALRM signal\n");
		break;
			
		case SIGINT:

			printf("get SIGINT signal\n");
			break;

		default:
			printf("wrong siganl\n");
	}
}
int main(void)
{

	signal(SIGALRM, handler);
	signal(SIGUSR1, handler);
	signal(SIGINT, handler);
	printf("程序挂起\n");
	pause(); //调用该函数当前进程就会挂起
	printf("程序恢复\n");
	return 0;
}

