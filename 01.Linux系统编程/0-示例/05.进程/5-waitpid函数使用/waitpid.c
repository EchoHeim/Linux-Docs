#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main()
{
	int status;
	int pid = fork();
	if(pid<0)
	{
		printf("create fork err!!!\n");
		return -1;
	}
	if(pid==0)
	{
		printf("child is going !!! %d\n",getpid());
		sleep(10);
	}
	if(pid>0)
	{
		printf("father is going!!!\n");
		waitpid(pid,&status,0);
		printf("father is end!!!\n");
		exit(0);
	}
	return 0;
}
