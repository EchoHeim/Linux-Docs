#include <unistd.h>
#include <stdio.h>

int main(void)
{
 char *str[] = {"ls", "-l", NULL}; //����һ��argv����
 
 printf("aaaa\n");
 execv("/bin/ls", str);
 printf("bbbb\n");
 printf("bbbb\n");
 return 0;
}

