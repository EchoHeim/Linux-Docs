#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

int main(void)
{
	FILE *fp = NULL;
	char str[128] = "This is a test string...";
	fp = fopen("a.dat", "w+");

	if(NULL == fp)
	{
		printf("can not open file.\n");
		return -1;
	}

	fwrite(str, strlen(str), 1, fp);
	puts("strat to sleep.");
	sleep(3);
	fclose(fp);
	puts("file has been closed.");

	sleep(3);
	exit(0);
}
