/*============================================================================
#
# Author: fan 
# Last modified: 2015-06-26 10:07
# Filename: intterrupt.c
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
void int_handler(int num)
{
	//printf("catch siganl %d\n", num);	
	printf("你真的希望退出吗?, 真的(Y)|假的(N)");
	if(getchar() == 'y' || getchar() == 'Y')
	{
		exit(0);	
	}
	
}


int main(void)
{
	int i = 0;
	signal(SIGINT, int_handler);


	while(1)
	{
		
		printf("times %d\n", i++);
		sleep(1);
	}


	return 0;
}

