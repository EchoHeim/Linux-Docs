#include <stdio.h>
#include <pthread.h>
//子线程处理函数
void *p_main(void *arg)                      
{
    printf("当前是在子线程\n");
    sleep(3);
    printf("子线程睡眠3秒后\n");
}
int main(void)
{
    pthread_t id;
    int ret;

    //创建一个线程(创建的子线程ID、线程属性、线程执行函数、参数)
    ret = pthread_create(&id, NULL, p_main, NULL);
    if(ret)                                       
    {
        perror("线程创建失败\n");
        return -1;
    }
    sleep(1);
	//取消掉正在运行的子线程
    pthread_cancel(id);
	printf("主线程取消掉了子线程\n");
    return 0;
}

