#include <unistd.h>                                  #include <unistd.h>
#include <stdio.h>                                   #include <stdio.h>
                                                     
int main(void)                                       int main(void)
{                                                    {
 pid_t pid;                                           pid_t pid;      
 printf("aaaa\n");                                    printf("aaaa\n");   
                                                                       
 pid = fork();                                        pid = fork();
                                                      
 if(pid==0)                                           if(pid==0)
   execl("/bin/ls", "ls", "-l", NULL);                  execl("/bin/ls", "ls", "-l", NULL);
                                                     
 if(pid > 0)                                          if(pid > 0)
 {                                                    {
  printf("bbbb\n");                                    printf("bbbb\n");
  printf("bbbb\n");                                    printf("bbbb\n");
 }                                                    }
 printf("hello\n");                                   printf("hello\n");
 return 0;                                            return 0;
}                                                    }

