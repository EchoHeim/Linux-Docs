/*============================================================================
#
# Author: fan 
# Last modified: 2015-06-23 14:19
# Filename: stdin.c
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

int main(void)
{
	int ret;
	char buf[10] = {'\0'};

	ret = fread(buf, 1, sizeof(buf)-1, stdin);
	buf[ret] = '\0';
	printf("buf = %s\tret = %d\n", buf, ret);



	return 0;
}

