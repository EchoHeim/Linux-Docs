#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
/*
原子操作函数是解决多进程操作时，多个进程同时操作一个文件时出错。
就是原子操作函数进行读写的时候不会改变内部文件指针
例如：
执行pread(fd,str1,12,0);的意思就是执行以下来个代码：
read(fd,str,12);  
lseek(fd,0,0);
*/
int main()
{
	int fd;
	char str1[20]={'\n'};
	char str[10]={"123456798"};
	fd = open("1.txt",O_RDWR|O_CREAT,0755);
	if(fd<0)
	{
		printf("open fail!!!\n");
		return -1;
	}
	pwrite(fd,str,strlen(str),0);
	//lseek(fd,0,0);
	pread(fd,str1,12,0);
	printf("%s\n",str1);
	close(fd);
	return 0;
}
