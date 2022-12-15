#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>
#include <stdlib.h>
int main()
{
	pid_t pc,pr;
	pc=fork();
	if(pc==0)
	{
		printf("This is child process with pid of %d\n",getpid());
		sleep(10);
		exit(0);
	}
	else if(pc>0)
	{
		pr=wait(NULL);//如果不需要返回值,可以NULL,如果需要传递一个指针
		printf("pid:%d,I catched a child process with pid of %d\n", pr,getpid());
		return 0;
	}
	exit(0);
}
