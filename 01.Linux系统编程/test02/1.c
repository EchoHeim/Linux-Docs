#include <stdio.h>
void my_puts(char *p,FILE *pa)
{
	while(*p!='\0')
	{
		fputc(*p,pa);
		p++;
	}
}

void my_putc(FILE *fp)	//从终端输入字符,以%结束;
{
	char ch;
	ch=getchar();
	while(ch!='%')
	{
		fputc(ch,fp);
		ch=getchar();
	}
}

int main()
{
	char ch;
	FILE *fp=fopen("1.txt","w+");
	if(fp==NULL)
	{
		printf("open err!\n");
		return -1;
	}
	my_puts("qwertyui",fp);
//	my_putc(fp);
	fclose(fp);
	return 0;	
}
