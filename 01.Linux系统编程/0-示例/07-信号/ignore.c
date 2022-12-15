/*============================================================================
#
# Author: fan 
# Last modified: 2015-06-26 10:26
# Filename: ignore.c
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


int main(void)
{
	signal(SIGINT, SIG_IGN); //ctrl + c信号
	signal(SIGSEGV, SIG_IGN); //段错误信号

	int i = 0;

	while(1)
	{
		printf("times : %d\n", i++);	
		sleep(1);	
	}


	return 0;
}

