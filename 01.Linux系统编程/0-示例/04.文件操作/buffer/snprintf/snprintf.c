/*============================================================================
#
# Author: fan 
# Last modified: 2015-06-23 14:56
# Filename: snprintf.c
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
	char src[] = "Linux C program!";
	char buf[40] = {'\0'};
	//格式化字符串函数,n可以指定大小
	snprintf(buf, sizeof(buf)-1, "src:%s--len:%d", src, (int)strlen(src));

	printf("%s\n", buf);


	return 0;
}

