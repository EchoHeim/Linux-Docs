#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <sys/types.h>

void fun()
{
	printf("father get signal\n");
}
int main()
{
	int pid = fork();
	if(pid>0)
	{
		signal(2,fun);
		printf("I am father!!! my pid is %d\n",getpid());
		while(1);
	}
	if(pid==0)
	{
		printf("I am child!!! my pid is %d,my ppid is %d\n",getpid(),getppid());
		sleep(1);
		kill(getppid(),2);
		while(1);
	}
	return 0;
}
