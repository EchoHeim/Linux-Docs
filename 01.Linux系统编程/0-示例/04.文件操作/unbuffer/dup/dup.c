#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <error.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>

int main(void)
{

	char buffer[1024] = {0};
	char src[] = "hello linux";
	int fda = open("a.txt", O_RDWR); //创建成功系统返回一个文件描述符
	int fdb = dup(fda);//复制文件描述符,文件描述符的引用数+1
	//int fdb =fda; //这样做是错误的,只要关闭一个文件描述符,另外一个就不可以使用了
	read(fda, buffer, sizeof(buffer)-1); //读内容
	puts(buffer); //显示
	close(fda); //关闭文件描述符


	if(write(fdb,  src, strlen(src)) <0)
	{
		perror("fdb write");
		return -2;
	}
	
	lseek(fdb, 0, SEEK_SET); //重新定位到文件首

	read(fdb, buffer, sizeof(buffer) -1);//再读出来

	puts(buffer);//再显示
	close(fdb);
	return 0;
}
