#include <unistd.h>
#include <stdio.h>

int main(void)
{
 printf("aaaa\n");
 execlp("ls", "ls", "-l", NULL);  //execlp �� execl ������:����Ҫ·����ע��:����Ҫ��NULL��β
 printf("bbbb\n");
 printf("bbbb\n");

 return 0;
}
