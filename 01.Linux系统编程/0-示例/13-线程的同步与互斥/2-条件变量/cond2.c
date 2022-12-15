#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
pthread_mutex_t mutex;//定义了一个互斥锁变量
pthread_cond_t cond;//定义了一个条件变量
void * child1(void *arg)
{
	printf("线程 1 开始运行！ \n");
	printf("线程 1 上锁了 : %d\n", pthread_mutex_lock(&mutex));
	printf("线程 1 开始等待条件被激活\n");
	pthread_cond_wait(&cond,&mutex); //等待父线程发送信号
	printf("条件满足后，停止阻塞！ \n");
	pthread_mutex_unlock(&mutex);
	return 0;
}
int main(void)
{
	pthread_t tid1;
	printf("测试条件变量！ \n");
	pthread_mutex_init(&mutex,NULL);
	pthread_cond_init(&cond,NULL);
	pthread_create(&tid1,NULL,child1,NULL);
	sleep(5); //6
	pthread_cond_signal(&cond);//让条件满足，即激活条件
	sleep(3);
	pthread_cond_destroy(&cond);//注销条件变量
	pthread_mutex_destroy(&mutex);//注销互斥锁变量
	return 0;
}
