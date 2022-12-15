#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

//向文件里写入和读出数据；

int main()
{
	char str[12],ch[1];
	int fd=open("3.txt",O_RDWR|O_CREAT,0655);
	if(fd<0)
	{
		printf("open err!\n");
		return -1;
	}
	lseek(fd,0,SEEK_END);
	gets(str);
	write(fd,str,strlen(str)+1);
	lseek(fd,0,SEEK_SET);
	while(read(fd,ch,1)>0)
	{
		printf("%c",ch[0]);	
	}
	close(fd);
	return 0;
}
