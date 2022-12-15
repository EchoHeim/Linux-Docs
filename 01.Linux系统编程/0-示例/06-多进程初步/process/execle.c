#include <unistd.h>
#include <stdio.h>

int main(void)
{
 char *arrEnv[] = {"PATH=/bin:/usr/bin", "TERM=console", NULL};  //指定环境变量
 
 printf("aaaa\n");
 execle("/bin/ls", "ls", "-l", NULL,arrEnv);
 printf("bbbb\n");
 printf("bbbb\n");
 return 0;
}

