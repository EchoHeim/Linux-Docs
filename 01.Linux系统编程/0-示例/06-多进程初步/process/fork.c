#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main(void)
{
  pid_t pid;      
  printf("hello world1\n");
  pid = fork();    
  if(pid == -1)     
  {
    printf("fork is error!!\n");   
    exit(1);                       
  } 
  else if(pid == 0)    
  {
    printf("the return value is %d\n
	        in child process!!\n
			my PID is %d\n",
			                   pid,getpid());
  }
  else                
  {                    
    printf("the return value is %d\n
	        in the father process!!\n
			my PID is %d\n",
			                   pid,getpid());
  }
  printf("Hello World2\n\n");   
}










