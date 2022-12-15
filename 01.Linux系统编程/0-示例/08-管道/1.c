#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include <sys/wait.h>
int main()
{
	int fds[2],pid;
	char str[10];
	pipe(fds);
	pid = fork();
	if(pid==0)
	{
		write(fds[1],"hello",6);
		exit(0);
	}
	if(pid>0)
	{
		wait(NULL);
		read(fds[0],str,6);
	}
	printf("str = %s\n",str);
	close(fds[0]);
	close(fds[1]);
	return 0;
}
