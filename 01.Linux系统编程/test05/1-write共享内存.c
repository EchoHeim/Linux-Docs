#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>

int main()
{
	key_t key=2;
//	key_t key=ftok(".",1);
	int shmid=shmget(key,1024,IPC_CREAT);
	
	printf("key = %d shmid = %d\n",key,shmid);

	char *p = (char *)shmat(shmid,NULL,0);
	memset(p,0,1024);
	memcpy(p,"Hello!",1024);
	shmdt(p);
	exit(0);
}
