#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int main(int argc,char *arr[])
{
	char ch[1];
	int fd=open(arr[1],O_RDWR,0755);
	if(fd<0)
	{
		printf("open err!\n");
		return -1;
	}
	lseek(fd,0,SEEK_SET);
	int fd2=open(arr[2],O_RDWR|O_CREAT,0655);
	while(read(fd,ch,1)>0)
	{
		write(fd2,ch,1);
	}
	close(fd);
	close(fd2);
	return 0;
}
