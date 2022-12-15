#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int main(void)
{
	printf("hello world");//printf行缓冲区,遇到换行符才会刷新缓冲区
	_exit(0);
}

