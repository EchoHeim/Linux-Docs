#include <stdio.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <pthread.h>

#define MAX     5
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER; //静态创建互斥锁

//处理函数
void handler(int fd, char *name)
{
    int count = 0, i;
    char buf[1024];

    while (count < MAX)
    {
        pthread_mutex_lock(&mutex);                //加锁
        snprintf(buf, sizeof(buf), "%s 的线程ID是 %8x count = %5d\n", name, pthread_self(), count++);
        for (i = 0; i < strlen(buf); i++)
        {
            write(fd, &buf[i], 1);
            usleep(10);
        }	
        pthread_mutex_unlock(&mutex);              //解锁
		usleep(10);
    }
}
void *do_work(void *data)
{
    //子线程调用处理函数
    handler(*(int *)data, "child");
	
    return NULL;
}
int main(int argc, char *argv[])
{
    int fd;
    pthread_t id;
	//打开一个 文本(O_TRUNC如果文件存在，并且以只写/读写方式打开，则清空文件全部内容(即将其长度截短为0))  
    fd = open("txt", O_RDWR | O_CREAT | O_TRUNC);
         if (fd == -1)    perror("文本打开失败");
	//创建子线程
    if (pthread_create(&id, NULL, do_work, (void *)&fd)) 
        perror("创建子线程失败");

	//主线程调用处理函数
    handler(fd, "parent");

	//等待子线程结束 
    pthread_join(id, NULL);                              
    return 0;
}
