#include <stdio.h>
#include <unistd.h>
#include <signal.h>
void fun()
{
	printf("I am fun!!!\n");
}
int main()
{
	int ret;
	char str[4]={"12"};
	int fds[2];
	signal(SIGPIPE,fun);
	pipe(fds);
	close(fds[0]);
	write(fds[1],str,2);
	while(1);
	return 0;
}
