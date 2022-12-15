#include <stdio.h>
#include <pthread.h>
#include <sys/syscall.h>
#include <signal.h>

//信号处理函数
void report(int sig)                            
{
    printf("接收到的信号是 = %d\n,发送信号的线程ID = %lu\n",sig,pthread_self());
}

//子线程1处理函数
void * p_main1(void *arg)                    
{
    signal(SIGUSR1,report);                       //注册信号
    
    printf("子线程1的ID = %d,子线程1的进程ID =%d \n",pthread_self(),getpid());
    while(1)sleep(1);                                    
}

//子线程2处理函数 
void *p_main2(void *arg)                    
{
    signal(SIGUSR1,report);                      //注册信号
    
    printf("子线程2的ID = %lu,子线程2的进程ID =%d \n",pthread_self(),getpid());
    while(1)sleep(1);
}
int main(void)
{
    pthread_t id1, id2;  
    int ret;
	
	//创建子线程1
    ret = pthread_create(&id1, NULL, p_main1, NULL);
    if(ret)  										
    {
        perror("子线程1创建失败\n");
        return -1;
    }  
	
	//创建子线程2
    ret = pthread_create(&id2, NULL, p_main2, NULL);
    if(ret)                     //子线程2创建失败
    {
        perror("子线程2创建失败\n");
        return -1;
    }
	
    printf("主线程的ID = %d,进程ID =%d \n",pthread_self(),getpid());
    sleep(1);                  //延时1秒，等该所有子线程就位
	
    pthread_kill(id1,SIGUSR1); //给子线程1发信号SIGUSR1
    sleep(1);
	
    pthread_kill(id2,SIGUSR1); //给子线程2发信号SIGUSR1    
 
    pthread_join(id1,NULL);    //等待子线程结束(子线程是死循环，所以挂在这里)
    pthread_join(id2,NULL);
    return 0;
}
