#include <stdio.h>
#include <string.h>
int main()
{
	char str[20]={'\n'};
	FILE *fp=fopen("2.txt","w+");
	if(fp==NULL)
	{
		printf("open err!!!\n");
		return -1;
	}
	gets(str);
	while(strlen(str)!=0)
	{
		fputs(str,fp);
		fputc('\n',fp);
		gets(str);
	}
	fseek(fp,0,SEEK_SET);
	while(fgets(str,20,fp)!=NULL)
	{
		printf("str=%s",str);
	}
	fclose(fp);
	return 0;
}
