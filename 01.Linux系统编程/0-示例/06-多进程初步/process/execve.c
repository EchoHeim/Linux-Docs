#include <unistd.h>
#include <stdio.h>

int main(void)
{
  char *str[] = {"ls", "-l", NULL};
  char *arrEnv[] = {"PATH=/bin:/usr/bin", "TERM=console", NULL};

  printf("aaaa\n");

  execve("/bin/ls", str, arrEnv);
  printf("bbbb\n");
  printf("bbbb\n");
  return 0;
}

