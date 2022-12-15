#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>

int main(void)
{
 pid_t pid,rec;

 pid = fork();

 if(pid == 0)   //����һ�����̣��ӽ��̴�ӡһ�仰Ȼ���˳�
 {
  printf("child process pid = %d\n", getpid());
  sleep(2);
  exit(1);
 }
 else
 {
  int n;
  rec = waitpid(pid,&n,0);
  printf("father process:the wait process pid = %d rec = %d\n",pid, rec);
  printf("n = %d\n",n);
  sleep(10);
 }
 return 0;
}
