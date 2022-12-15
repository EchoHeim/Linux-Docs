#include <stdio.h>
#include <errno.h>
#include <stdlib.h>

int main(int argc, char ** argv)
{
	int ret;
	FILE * fp;
	char buf[128] = {'\0'};
	if(2 != argc)
	{
		printf("Invalid usage!\n");	
		return -1;
		
	}

	fp = fopen(argv[1], "rb");
	
	if(NULL == fp)
	{
		perror("fopen");	
		return -2;
	}


	while(1)
	{
		ret = fread(buf, 1, sizeof(buf)-1, fp);
		if(1 >= ret)
		{
			break;
		}
		buf[ret] = '\0'; //在读的字节数后追加\0
		printf("buf=%s\n", buf);
		
	}
	

	fclose(fp);
	fp = NULL;

	return 0;	
}
