#include <stdio.h>
#include <pthread.h>
#include <sys/syscall.h>
#include <string.h>

char buffer[128];

void *  p_main(void *arg)                //子线程处理函数
{
    int a;  
	
    printf("子线程ID=%d\n",pthread_self()); //打印子线程的ID    
    //printf("主线程ID=%d\n",pthread_self()); //打印主线程的ID
    printf("本进程ID=%d\n",getpid());       //打印本进程的进程ID号
    printf("buffer=%s\n",buffer);           //输出 buffer里的内容
    sleep(1);                                      
    pthread_exit(0);                        //结束子线程 
}
int main(void)
{
    pthread_t id;  
	int ret;

	//创建子线程
    ret = pthread_create(&id, NULL, p_main, NULL);  
    if(ret)
    {
        perror("子线程创建失败\n");
        return -1;
    }  
    printf("子线程ID=%d\n",id);             //打印子线程的ID
    printf("主线程ID=%d\n",pthread_self()); //打印主线程的ID
    printf("本进程ID=%d\n",getpid());       //打印本进程的进程ID号
    memcpy(buffer,"hello",6);               //内存拷贝到buffer 
    pthread_join(id,NULL);                  //等待子线程结束 
    
    
    return 0;
}

