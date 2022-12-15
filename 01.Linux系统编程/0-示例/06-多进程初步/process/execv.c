#include <unistd.h>
#include <stdio.h>

int main(void)
{
 char *str[] = {"ls", "-l", NULL}; //定义一个argv数组
 
 printf("aaaa\n");
 execv("/bin/ls", str);
 printf("bbbb\n");
 printf("bbbb\n");
 return 0;
}

