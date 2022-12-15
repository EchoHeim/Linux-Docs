#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
void fun()
{
	printf("I am fun!!!\n");
}
void bye(void) 
{
	fun();
    printf("goodbye!!!\n");
}
int main(void)
{
	int i,a;
	i = atexit(bye);
	a = atexit(fun);
	if (i != 0) 
	{
		fprintf(stderr, "cannot set exit function\n");
		return -1;
	}
	return 0;
}
