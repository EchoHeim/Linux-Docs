#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int main()
{
	char *p;
	char *str;
	int key = ftok(".",13);//建立键值
	int shnum=shmget(key,12,IPC_CREAT);//通过键值创建共享内存
	p = (char *)shmat(shnum,NULL,0);//将共享内存映射到进程空间
	memcpy(p,"helloworld",11);//写数据
	shmdt(p);
	shnum=shmget(key,12,IPC_CREAT);
	str= (char *)shmat(shnum,NULL,0);
	printf("%s\n",str);
	shmdt(p);
	shmctl(shnum,IPC_RMID,NULL);
	return 0;
}
