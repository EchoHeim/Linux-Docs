#include <stdio.h>
#include <stdlib.h>
#include <string.h>
# include <sys/types.h>
# include <sys/ipc.h>
#include <sys/wait.h>

struct msgbuf
{
	long mtype;
	char str[4];
};
int main()
{
	int key,msg;
	struct msgbuf data;
	int fd = fork();
	if(fd>0)
	{
		wait(NULL);
		key = ftok(".",1);
		msg = msgget(key, IPC_CREAT);
		memset(&data,0,sizeof(data));
		msgrcv(msg,&data,sizeof(data),1,0);
		printf("%s\n",data.str);
		msgctl(msg,IPC_RMID,NULL);
	}
	if(fd==0)
	{
		key = ftok(".",1);
		msg = msgget(key, IPC_CREAT);
		memset(&data,0,sizeof(data));
		data.mtype = 1;
		strcpy(data.str,"hel");
		msgsnd(msg,&data,sizeof(data),0);
		exit(0);
	}
	return 0;
}
