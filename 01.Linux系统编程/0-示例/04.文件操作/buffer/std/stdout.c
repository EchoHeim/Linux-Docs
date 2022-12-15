/*============================================================================
#
# Author: fan 
# Last modified: 2015-06-23 14:24
# Filename: stdout.c
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
	char buf[] = "Linux program!\n";

	ret = fwrite(buf, 1, sizeof(buf), stdout);

	printf("ret = %d\n", ret);

	return 0;
}

