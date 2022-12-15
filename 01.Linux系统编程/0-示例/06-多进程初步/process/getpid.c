#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>

int main(void)
{

  printf("pid=%d\nppid=%d\nuid=%d\neuid=%d\ngid=%d\negid=%d\n",
  	      getpid(),getppid(),getuid(),geteuid(),getgid(),getegid());

  return 0;
}
