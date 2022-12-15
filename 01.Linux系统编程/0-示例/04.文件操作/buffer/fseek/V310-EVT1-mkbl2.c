/*
 * Copyright (c) 2010 Samsung Electronics Co., Ltd.
 *              http://www.samsung.com/
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main (int argc, char *argv[])
{
	FILE		*fp;
	unsigned char	src;
	char		*Buf, *a;
	int		BufLen;
	int		nbytes, fileLen;
	unsigned int	checksum = 0;
	int		i;

	if (argc != 4)
	{
		printf("Usage: mkbl1 <source file> <destination file> <size> \n");
		return -1;
	}

	BufLen = atoi(argv[3]);
	Buf = (char *)malloc(BufLen);
	memset(Buf, 0x00, BufLen);

	fp = fopen(argv[1], "rb");
	if( fp == NULL)
	{
		printf("source file open error\n");
		free(Buf);
		return -1;
	}

	fseek(fp, 0L, SEEK_END); //定位的文件末尾
	fileLen = ftell(fp);//返回当前文件指针的位置,由于当前文件指针在末尾,则可以知道文件的大小
	fseek(fp, 0L, SEEK_SET);//重新定位的文件的开头

	if ( BufLen > fileLen )
	{
		printf("Usage: unsupported size\n");
		free(Buf);
		fclose(fp);
		return -1;
	}

	//每次读一个字节,读bufLen个字节
	nbytes = fread(Buf, 1, BufLen, fp);

	if ( nbytes != BufLen )
	{
		printf("source file read error\n");
		free(Buf);
		fclose(fp);
		return -1;
	}

	fclose(fp);

	//checksum验证
	for(i = 0;i < (14 * 1024) - 4;i++)
	{
		checksum += (unsigned char)(Buf[i]);
	}
	*(unsigned int*)(Buf+i) = checksum;

	fp = fopen(argv[2], "wb");
	if (fp == NULL)
	{
		printf("destination file open error\n");
		free(Buf);
		return -1;
	}

	a	= Buf;
	//重新写文件
	nbytes	= fwrite( a, 1, BufLen, fp);

	if ( nbytes != BufLen )
	{
		printf("destination file write error\n");
		free(Buf);
		fclose(fp);
		return -1;
	}

	//释放缓冲区
	free(Buf);
	//使用完了,记得关闭文件
	fclose(fp);

	return 0;
}
