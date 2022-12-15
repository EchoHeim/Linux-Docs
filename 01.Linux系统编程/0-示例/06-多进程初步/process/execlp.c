#include <unistd.h>
#include <stdio.h>

int main(void)
{
 printf("aaaa\n");
 execlp("ls", "ls", "-l", NULL);  //execlp 与 execl 的区别:不需要路径，注意:参数要以NULL结尾
 printf("bbbb\n");
 printf("bbbb\n");

 return 0;
}
