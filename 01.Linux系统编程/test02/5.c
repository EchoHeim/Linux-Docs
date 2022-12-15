#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
//可以右击文件看文件属性改变了，文件创建的时候默认属性为644 大小为0
//使用chmod命令可以改变属性，使用这个函数可以改变大小
int main()
{
	 int fd = open("a.txt", O_WRONLY);
	 ftruncate(fd,1000);
	 close(fd);
	 return 0;
}
