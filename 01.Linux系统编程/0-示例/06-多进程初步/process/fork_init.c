#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(void)
{
  pid_t pid = fork();

  if( pid == 0)   //�ӽ���
  {
   printf("this is child process\n");
   while(1);
  }

  else   //�������˳� �ӽ��̳�Ϊ�¶�����
  {
   printf("father process will exit after 2 sec\n");
   sleep(2);
   printf("father process exit\n");
   exit(0);
 }

 return 0;
}
