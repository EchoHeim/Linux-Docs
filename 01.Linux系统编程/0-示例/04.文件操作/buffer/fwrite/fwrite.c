#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>

struct student{
	char name[32];
	int num;
};


int main(int argc, char ** argv)
{
	FILE * fp;
	int ret;
	int i;
	struct student stu[10];

	if(2 != argc)
	{
		printf("Invalid usgae\n");	
		return -1;
	}
	
	fp = fopen(argv[1], "wb");
	if(NULL == fp)
	{
		perror("fopen");	
		return -2;
	}

	for(i = 0; i < 10; i++)
	{
		strcpy(stu[i].name, "aaaaa");
		stu[i].num = i;
	}

	ret = fwrite(stu, sizeof(struct student), 10, fp);
	if(10 != ret)
	{
		printf("ret = %d\n", ret);	
	}

	fclose(fp);
	fp = NULL;

	return 0;	
}
