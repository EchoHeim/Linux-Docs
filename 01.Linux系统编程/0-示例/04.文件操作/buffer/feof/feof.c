
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int main(void)
{
	FILE * fp;
	char buf[128] = {'\0'};
	int ret;
	long pos;
	fp = fopen("a.txt", "rb");

	if(NULL == fp)
	{
		perror("fopen");	
		return -1;
	}
	//到达文件结尾还会再多执行一次,可以这样认为feof实际是判断的上一次读写的情况
	while(!feof(fp))
	{
		fgets(buf, sizeof(buf), fp);
		pos = ftell(fp);
		printf("pos:%ld buf= %s", pos, buf);
	}


	fclose(fp);
	return 0;
}

