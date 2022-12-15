#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

int main()
{
	int pid1,pid2;
//	int a,b;
	pid1 = fork();
	if(pid1==0)
	{
		printf("child1 is going!\tpid = %d,father pid = %d\n",getpid(),getppid());
		return 0;
	}
	pid2 = fork();
	if(pid2==0)
	{
		printf("child2 is going!\tpid = %d,father pid = %d\n",getpid(),getppid());
		return 0;
	}
	waitpid(pid1,NULL,0);
	waitpid(pid2,NULL,0);
	return 0;
}
