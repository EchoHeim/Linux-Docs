#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(void)
{
	int i = 1;
	while(i)
	{
		printf("time:%d\n", i++);
		sleep(1);
		if(i == 10)
			abort();
	}
	return 0;
}
