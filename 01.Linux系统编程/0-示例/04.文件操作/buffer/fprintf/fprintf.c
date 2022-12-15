/*============================================================================
#
# Author: fan 
# Last modified: 2015-06-23 14:51
# Filename: fprintf.c
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
	char buf[] = "Linux program!";

	//也可以输出到文件里,fopen打开一个文件,传给fprintf第一个参数
	//这里是输出到标准输出
	fprintf(stdout, "str:%s:%d\n", buf, 10);


	return 0;
}

