/*============================================================================
#
# Author: fan 
# Last modified: 2015-06-23 15:10
# Filename: fget.c
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
	char c;

	while((c = fgetc(stdin)) != '\n')
		fputc(c,stdout);


	return 0;
}

