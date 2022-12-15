#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>
int main()
{
	int fds[2];
	char str[20];
	pipe(fds);
	int pid = fork();
	if(pid>0)
	{
		read(fds[0],str,6);
		printf("str=%s\n",str);
		exit(0);
	}
	if(pid==0)
	{
		sleep(10);
		write(fds[1],"hello",6);
		exit(0);
	}
	return 0;
}
