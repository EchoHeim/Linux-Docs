#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>

int main(void)
{
 pid_t pid,rec;

 pid = fork();

 if(pid == 0)   //创建一个进程，子进程打印一句话然后退出
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
