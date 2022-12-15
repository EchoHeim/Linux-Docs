#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/stat.h>

int main()
{
	unlink("1.fifo");
	int file1=mkfifo("1.fifo",0655);
	if (file1==-1)
	{
		printf("create fail!\n");
	}
	else
	{
		printf("create success!\n");
	}
	exit(0);
}
