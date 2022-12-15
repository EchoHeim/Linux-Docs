#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>

int main(void)
{
	int pid_wait;
	int status;
	int pid = fork();
	if(pid == 0)
	{
		printf("in child:%d\n", getpid());
		sleep(2);
		exit(12);
	}
	else
	{	
		pid_wait = wait(&status); //阻塞函数,直到有子进程退出它才会返回
		
		//判断是否是正常退出,即是否main函数自然返回,或者调用exit和_exit
		if(WIFEXITED(status)) 
			//如果是正常退出,就打印子进程的返回值
			printf("pid:%d, yes wait value is %d\n",pid_wait, WEXITSTATUS(status));
		else if(WIFSIGNALED(status))
			printf("no wait value is %d\n ", WIFSIGNALED(status));	
	}
	return 0;
}
