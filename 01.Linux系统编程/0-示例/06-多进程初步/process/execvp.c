#include <unistd.h>
#include <stdio.h>

int main(void)
{
 char *str[] = {"ls", "-l", NULL};
 
 printf("aaaa\n");
 execvp("ls", str);  //���Ӿ���·��
 printf("bbbb\n");
 printf("bbbb\n");
 return 0;
}

