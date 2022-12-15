/*============================================================================
#
# Author: fan 
# Last modified: 2015-06-23 16:21
# Filename: read.c
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
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
int main(void)
{
	int fd;
	int ret;
	char buf[32] = {'\0'};
	fd = open("a.txt", O_RDWR|O_CREAT);

	if(0 >= fd)
	{
		perror("open");	
		return -1;
	}


	while(1)
	{
			
		ret = read(fd, buf, sizeof(buf)-1);
		if(0 >= ret)
		{
			perror("read");	
			break;
		}

		buf[ret] = '\0';
		printf("%s", buf);
	}

	close(fd);
	return 0;
}

