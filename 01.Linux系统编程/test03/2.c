#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <signal.h>
#include <fcntl.h>

int main()
{
	char str[20]={'\0'};
//	printf("%daaaa\n",getpid());
	int fp=open("bb.txt",O_RDWR|O_CREAT,0755);
	int n=fork();
	if(n==0)
	{
		sleep(3);
		write(fp,"hello world!",13);
		lseek(fp,0,SEEK_SET);
		read(fp,str,13);
		printf("read: %s\n",str);
		close (fp);
//		printf("hello world! n = %d ,m = %d\n",n,m);
		exit(0);
	}
	else
	{
		write(fp,"abc linux!",10);
		close(fp);
//		printf("hello world!%d  %d    n = %d ,m = %d\n",getpid(),getppid(),n,m);
//		return 0;
		exit(0);
	}
}
