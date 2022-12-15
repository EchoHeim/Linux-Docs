#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include <sys/wait.h>
void fun ()
{
	printf("i am fun!\n");
}

int main()
{
	signal(SIGALRM,fun);
	alarm(5);
//	fun();
	while(1);
	return 0;
}
