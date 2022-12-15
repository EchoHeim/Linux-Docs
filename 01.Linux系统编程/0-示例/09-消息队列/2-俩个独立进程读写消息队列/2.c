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
	msgrcv(msg,&data,sizeof(data),1,0);
	printf("%s\n",data.str);
	msgctl(msg,IPC_RMID,NULL);
	return 0;
}
