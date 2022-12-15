#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
int main()
{
	int key,shnum;
	char *p;
	int fd = fork();
	if(fd>0)
	{
		wait(NULL);
		key=ftok(".",1);	
		shnum = shmget(key,20,IPC_CREAT);
		p = (char *)shmat(shnum,NULL,0);
		printf("%s\n",p);
		shmdt(p);
		shmctl(shnum,IPC_RMID,NULL);
	}
	if(fd==0)
	{
		key = ftok(".",1);
		shnum = shmget(key,20,IPC_CREAT);
		p = (char *)shmat(shnum,NULL,0);
		memcpy(p,"hellowirld",11);
		shmdt(p);
		exit(0);
	}
	return 0;
}
