#include <stdio.h>
#include <unistd.h>

int main(void)
{
	int i = 0;
	char buf[128] = {'\0'};
	printf("please input:");
//	scanf("%s",buf);	//这里会挂起
	scanf("%[^\n]",buf);
	printf("you input:%s\n",buf);

	while(1)
	{
		printf("%d times.\n", ++i);	
		sleep(1);
	}
	return 0;
}
