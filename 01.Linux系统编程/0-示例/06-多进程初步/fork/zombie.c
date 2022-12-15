#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
int main(void)
{
	int pid = fork();
	if(0 > pid)
	{
		puts("can not create child process.");
	}
	else if(0 == pid)
	{
		exit(10);
	}
	else
	{
		sleep(10);
	}
	return 0;
}
