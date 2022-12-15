/*============================================================================
#
# Author: fan 
# Last modified: 2015-06-23 17:24
# Filename: feof.c
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
	char buf[128] = {'\0'};
	int ret;
	long pos;
	fp = fopen("a.txt", "rb");

	if(NULL == fp)
	{
		perror("fopen");	
		return -1;
	}
	//针对于feof最后会多执行一次,
	//所以正确的做法是先做后判断
	fgets(buf, sizeof(buf), fp);
	while(!feof(fp))
	{
		pos = ftell(fp);
		printf("pos:%ld buf= %s", pos, buf);
		fgets(buf, sizeof(buf), fp);
	}
	//这样先做后判断后,就不会在多执行一次

	fclose(fp);
	return 0;
}

