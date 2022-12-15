/*============================================================================
#
# Author: fan 
# Last modified: 2015-03-31 22:43
# Filename: aa.c
# Description: 
#	从src文件读内容,然后写到dst文件
#	非缓冲IO
===========================================================================*/
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <error.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>

#define SRCFILE "src.txt"
#define DSTFILE "dst.txt"

int main(void)
{
	int s_fd, d_fd;
	int len;
	char buffer[1024];

	//open失败返回-1
	s_fd = open(SRCFILE, O_RDONLY);
	if(0 > s_fd)
	{
		perror("cannot open file src.");
		return -1;
	}

	//mode是八进制有前缀0
	d_fd = open(DSTFILE, O_CREAT|O_WRONLY, 0666);
	if(0 > d_fd)
	{
		perror("can not open file dst.");
		close(s_fd);
		return -1;
	}


	//read成功返回所读的字节数,错误返回-1
	//write成功返回所写的字节数,错误返回-1
	while(0 < (len = read(s_fd, buffer, sizeof(buffer))))
	{
		if(write(d_fd, buffer, len) < 0) 
		{
			perror("can not write file dst.");
			break;
		}
	}

	close(s_fd);
	close(d_fd);

	return 0;
}
