#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int main(void)
{
	fork();
	fork();
	fork();
	fork();

	printf("fork process\n");

	return 0;
}

