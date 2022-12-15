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
//argv[0]:./mkbl2   argv[1]:../led.bin  argv[2]:bl2.bin  argv[3]:14336
//./mkbl2 ../led.bin bl2.bin 14336 

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

	BufLen = atoi(argv[3]);  //"14336" -->14336
	Buf = (char *)malloc(BufLen);
	memset(Buf, 0x00, BufLen);

	fp = fopen(argv[1], "rb");//"../led.bin"
	if( fp == NULL)
	{
		printf("source file open error\n");
		free(Buf);
		return -1;
	}

	fseek(fp, 0L, SEEK_END); //移动文件指针到最后
	fileLen = ftell(fp);     //读取当文件指针，得到是文件长度
	fseek(fp, 0L, SEEK_SET); //移动文件指针到开头

	if ( fileLen >  (BufLen-4))//这里是随便写一个数，判断不要大于14K代码
	{
		printf("Usage: unsupported size,size more than 14K \n");
		free(Buf);
		fclose(fp);
		return -1;
	}

	nbytes = fread(Buf, 1, BufLen, fp);//读1次，长度BufLen，存放在Buf中
     
	fclose(fp);                        //关闭文件

        //循环累加前面14K-4字节
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
	nbytes	= fwrite( a, 1, BufLen, fp);

	if ( nbytes != BufLen )
	{
		printf("destination file write error\n");
		free(Buf);
		fclose(fp);
		return -1;
	}

	free(Buf);
	fclose(fp);

	return 0;
}
