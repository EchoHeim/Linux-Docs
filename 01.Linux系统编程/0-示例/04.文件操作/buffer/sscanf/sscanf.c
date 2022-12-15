/*============================================================================
#
# Author: fan 
# Last modified: 2015-06-23 14:47
# Filename: sscanf.c
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
	char src[] = "32 abcdefghijklmn";
	char buf[10] = {'\0'};
	int i;
	
	//从src字符串里面读取内容
	//把32赋值给i, 把后面的字符串赋值给buf
	sscanf(src, "%d%s", &i, buf);

	printf("i = %d, buf = %s\n", i, buf);


	return 0;
}

