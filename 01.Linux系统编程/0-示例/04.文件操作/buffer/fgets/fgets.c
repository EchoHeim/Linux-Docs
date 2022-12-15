/*============================================================================
#
# Author: fan 
# Last modified: 2015-06-23 15:22
# Filename: fgets.c
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
	FILE * fp;
	char buf[16] = {'\0'};

	fp = fopen("a.txt", "r+b");

	if(NULL == fp)
	{
		perror("fopen");	
		return -1;
	}
	//printf("开始读文件");
	puts("开始读文件"); //puts自动在后面添加换�?	while(1)
	{
		if(NULL == fgets(buf, sizeof(buf), fp))
			break;

		printf("%s", buf);
	}

	fclose(fp);
	fp = NULL;
	return 0;
}

