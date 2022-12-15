/*============================================================================
#
# Author: fan 
# Last modified: 2015-06-26 10:29
# Filename: defalut.c
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
	int i = 0;
	signal(SIGINT, SIG_IGN); //忽略ctrl+c信号

	//..............做了很多的事情


	signal(SIGINT, SIG_DFL); //恢复成默认处理函数

	while(1)
	{
		printf("times : %d\n", i++);	
		sleep(1);
	}

	return 0;
}

