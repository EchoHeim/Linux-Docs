#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
int get_sem(int sem,int num)
{
	struct sembuf s;
	s.sem_num = 0;
	s.sem_op = -1;
	s.sem_flg = 0;
	return semop(sem,&s,1);
}
int put_sem(int sem,int num)
{
	struct sembuf s;
	s.sem_num = 0;
	s.sem_op = 1;
	s.sem_flg = 0;
	return semop(sem,&s,1);
}
int main()
{
	int key = ftok(".",1);
	int sem = semget(key,1,IPC_CREAT);
	semctl(sem,0,SETVAL,4);
	int ret = semctl(sem,0,GETVAL);
	printf("%d\n",ret);
	if(fork()>0)
	{

	}
	else
	{

	}
	return 0;
}
