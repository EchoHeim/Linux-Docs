#include <stdio.h>

int my_fputs(char *p,FILE *fp);
int main()
{
	char ch;
	FILE *fp=fopen("2.txt","w+");
	if(fp==NULL)
	{
		printf("open err!!!\n");
		return -1;
	}
	ch=getchar();
	while(ch!='#')
	{
		fputc(ch,fp);
		ch=getchar();
	}
	rewind(fp);
	while(feof(fp)==0)
	{
		ch=fgetc(fp);
		printf("%c",ch);
	}
	fclose(fp);
	return 0;
}
int my_fputs(char *p,FILE *fp)
{
	while(*p!='\0')
	{
		fputc(*p,fp);
		p++;
	}
	return 0;
}
