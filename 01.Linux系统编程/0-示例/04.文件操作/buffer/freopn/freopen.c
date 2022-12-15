/*============================================================================
#
# Author: fan 
# Last modified: 2015-06-23 14:27
# Filename: freopen.c
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

#define reFile "a.txt"

int main(void)
{
	FILE * fp;
	int ret;
	char buf[10] = {'\0'};


	//关联stdin到a.txt,那么后续从stdin读文件,就是从a.txt里面读
	fp = freopen(reFile, "r+b", stdin);

	if(NULL == fp)
	{
		perror("freopen");	
		return -1;
	}

	//实际上是从a.txt里面读文件
	ret = fread(buf, 1, sizeof(buf)-1, stdin);

	printf("buf = %s\tret = %d\n", buf, ret);

	fclose(fp);
	return 0;
}

