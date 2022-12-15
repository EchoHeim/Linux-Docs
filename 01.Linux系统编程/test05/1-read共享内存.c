#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>

int main()
{
	key_t key=2;
//	key_t key=ftok("a.dat",1);
	int shmid=shmget(key,1024,IPC_CREAT);
	
	printf("key = %d shmid = %d\n",key,shmid);

	char *p = (char *)shmat(shmid,NULL,0);
	printf("receive data:%s\n",p);
	shmctl(shmid,IPC_RMID,0);
	return 0;
}
