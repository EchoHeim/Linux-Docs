#include <stdio.h>
#include <pthread.h>
#include <fcntl.h>
#include <string.h>

#define MAX 5
int fd;

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

void *p_main(void * arg)
{
    int count = 0;
    int i;
    char buf[128] = {};
       while (count < MAX)
        {
	     	pthread_mutex_lock(&mutex);
            snprintf(buf, sizeof(buf), "child pid %lu count = %5d\n", pthread_self(), count++);
            for (i = 0; i < strlen(buf); i++)
            {
                write(fd, &buf[i], 1);
                usleep(10);
            }
	    	pthread_mutex_unlock(&mutex);
	    	usleep(10);
        }
        pthread_exit(0);
}

int main(void)
{
    pthread_t id;
    int ret;
    int count = 0;
    int i;
    char buf[128];

	//打开文件
    fd = open("txt",O_RDWR|O_CREAT,0666);

    //创建线程
    ret = pthread_create(&id,NULL,p_main,NULL);
    if(ret<0){ perror("线程创建失败\n");  return 0; }

    while (count < MAX)
    {
	    pthread_mutex_lock(&mutex);
        snprintf(buf, sizeof(buf), "parent pid %lu count = %5d\n", pthread_self(), count++);
        for (i = 0; i < strlen(buf); i++)
        {
            write(fd, &buf[i], 1);
            usleep(10);
        }
		pthread_mutex_unlock(&mutex);
		usleep(10);
    }
    pthread_join(id,NULL);
    return 0;
}
