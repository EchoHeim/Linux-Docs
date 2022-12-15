#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>


void  handler(int sig)
{
	if(SIGALRM == sig)
	{
		printf("get sigalarm signal.\n");	
	}
}

int main(void)
{

	signal(SIGALRM, handler);
	
	printf("my pid:%d\n", getpid());
	alarm(5); //5s之后发送sigalam信号
	printf("b4 pase()\n");
	//pause(); //pause信号容易受到干扰,收到什么信号都会被唤醒


	//在使用sleep的时候,尽量不要用alarm函数
	//sleep内部实现就是pause和alarm
	sleep(20);
	//alarm(20);
	//pause();

	printf("after pause();\n");



	return 0;
}

