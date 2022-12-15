#include <stdio.h>
#include <pthread.h>
pthread_mutex_t lock;
pthread_cond_t cond;
void *fun1(void *p)
{
	pthread_mutex_lock(&lock); 
	printf("I am fun1 text1\n");
	pthread_cond_wait(&cond,&lock);
	printf("I am fun1 text2\n");
	pthread_mutex_unlock(&lock);
}
void *fun2(void *p)
{
	pthread_mutex_lock(&lock); 
	printf("I am fun2 text1\n");
	sleep(5);
	pthread_cond_signal(&cond);
	pthread_mutex_unlock(&lock);
	printf("I am fun2 text2\n");
}
int main()
{
	pthread_t pthid1 = 0;
	pthread_t pthid2 = 0;
	pthread_mutex_init(&lock,NULL);  
	pthread_cond_init(&cond,NULL);
	pthread_create(&pthid1,NULL,fun1,NULL); 
	pthread_create(&pthid2,NULL,fun2,NULL);
	pthread_join(pthid1,NULL);
	pthread_join(pthid2,NULL);
	pthread_mutex_destroy(&lock);     
	return 0;
}
