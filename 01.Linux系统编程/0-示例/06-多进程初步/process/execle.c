#include <unistd.h>
#include <stdio.h>

int main(void)
{
 char *arrEnv[] = {"PATH=/bin:/usr/bin", "TERM=console", NULL};  //ָ����������
 
 printf("aaaa\n");
 execle("/bin/ls", "ls", "-l", NULL,arrEnv);
 printf("bbbb\n");
 printf("bbbb\n");
 return 0;
}

