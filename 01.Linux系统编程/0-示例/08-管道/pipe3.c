#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <stdlib.h>
int main()
{
	int fds[2];
	char str[10];
	pipe(fds);
	int pid = fork();
	if(pid>0)
	{
		fgets(str,5,stdin);
		write(fds[1],str,5);
	}
	if(pid==0)
	{
		sleep(2);
		printf("child is going!!\n");
		read(fds[0],str,5);
		printf("str = %s\n",str);	
		exit(0);
	}
	wait(NULL);
	close(fds[0]);
	close(fds[1]);
	return 0;
}
