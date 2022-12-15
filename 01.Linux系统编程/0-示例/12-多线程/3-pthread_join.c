#include <stdio.h>
#include <pthread.h>

void *p_main(void *arg)
{
    printf("当前是在子线程\n");
    sleep(3);
    printf("子线程3秒延时后\n");
}

int main(void)
{
    pthread_t id;
    int ret;

    //创建子线程
    ret = pthread_create(&id, NULL, p_main, NULL);
    if(ret)
    {
        perror("子线程创建失败");
        return -1;
    }
    sleep(1);
	
    //等待子线程结束
    pthread_join(id,NULL);
    printf("全部结束\n");

    return 0;
}
