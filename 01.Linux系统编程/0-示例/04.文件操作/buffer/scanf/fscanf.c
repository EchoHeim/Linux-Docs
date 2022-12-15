/*============================================================================
#
# Author: fan 
# Last modified: 2015-06-23 14:39
# Filename: fscanf.c
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
	char buf[10] = {'\0'};
	int i;
	FILE * fp;

	fp = fopen("a.txt", "r+b");
	if(NULL == fp)
	{
		perror("fopen");	
		return -1;
	}

	//实际上从a.txt文件里面读
	fscanf(fp, "%d%s", &i, buf);

	printf("i = %d, buf = %s\n", i, buf);
	
	fclose(fp);
	fp = NULL;

	return 0;
}

