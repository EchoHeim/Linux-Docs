#include <stdio.h>
#include <unistd.h>
int main()
{
	char str2[10]={'\0'};
	char str[6]={"1234"};
	int fds[2];
	pipe(fds);
	write(fds[1],str,4);
	read(fds[0],str2,5);
	printf("%s\n",str2);
	return 0;
}
