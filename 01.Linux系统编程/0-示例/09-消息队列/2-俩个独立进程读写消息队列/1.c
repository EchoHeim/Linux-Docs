#include <stdio.h>
#include <stdlib.h>
#include <string.h>
# include <sys/types.h>
# include <sys/ipc.h>
struct msgbuf
{
	long mtype;
	char str[4];
};
int main()
{
	struct msgbuf data;
	int key=ftok(".",1);
	int msg = msgget(key,IPC_CREAT);
	if(msg<0)
	{
		printf("create fail!!!\n");
		return -1;
	}
	memset(&data,0,sizeof(data));
	data.mtype = 1;
	strcpy(data.str,"abc");
	msgsnd(msg,&data,sizeof(data),0);
	return 0;
}
