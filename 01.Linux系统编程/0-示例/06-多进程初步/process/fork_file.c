#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>

int main(void)
{
  char szBuf[32] = {'\0'};
  int fd = open("./xx.txt", O_RDONLY);

  if(fork() > 0)  //�����̵���fork�ķ���ֵ���ӽ��̵�PID 
  {
    close(fd);
    return 0;
  }

  sleep(3); 
  read(fd, szBuf, sizeof(szBuf)-1);
  printf("\nstring:%s\n",szBuf);
  close(fd);

  return 0;
}

