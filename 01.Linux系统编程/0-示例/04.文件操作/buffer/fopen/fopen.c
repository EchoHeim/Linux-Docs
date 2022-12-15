#include <stdio.h>
#include <errno.h>
//main函数的3种形式
//int main(void)
//int main(int argc, char ** argv, char ** env)
//argc代表的是参数的个数,包括本身; 
//argv代表的是每一个参数
//env代表的是环境变量
int main(int argc, char ** argv)
{
	FILE * fp;

	if(2 != argc)
	{
		printf("Invaild usage\n");	
		return -1;
	}
	
	fp = fopen(argv[1], "w+b");
	
	if(NULL == fp)
	{
		//perror("fopen");	
		printf("errno=%d\n", errno);
		return -2;
	}

	printf("fopen successfully!\n");


	fclose(fp);
	fp = NULL; //防止野指针生成
	return 0;	
}
