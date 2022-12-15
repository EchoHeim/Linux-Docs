#include <stdio.h>
#include <pthread.h>
#include<semaphore.h>
sem_t sem;
void *fun1(void *num)
{
	sem_wait(&sem);
	printf("I am fun1\n");
	sleep(5);
	sem_post(&sem);
}
void *fun2(void *num)
{
	sem_wait(&sem);
	printf("I am fun2\n");
	sleep(5);
	sem_post(&sem);
}
int main()
{
	pthread_t id1,id2;
	sem_init(&sem,0,1);
	pthread_create(&id1,NULL,fun1,NULL);
	pthread_create(&id2,NULL,fun2,NULL);
	pthread_join(id1,NULL);
	pthread_join(id2,NULL);
	return 0;
}





