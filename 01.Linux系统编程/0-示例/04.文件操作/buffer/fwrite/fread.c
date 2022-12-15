#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <strings.h>
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

	bzero(stu, sizeof(stu));
	if(2 != argc)
	{
		printf("Invalid usgae\n");	
		return -1;
	}
	
	fp = fopen(argv[1], "r+b");
	if(NULL == fp)
	{
		perror("fopen");	
		return -2;
	}

	ret = fread(stu, sizeof(struct student), 10, fp);
	if(10 != ret)
	{
		printf("ret = %d\n", ret);	
	}

	for(i = 0; i < 10; i++)
	{
		printf("stu[%d]:name = %s, num = %d\n", i, stu[i].name, stu[i].num);
	}


	fclose(fp);
	fp = NULL;

	return 0;	
}
