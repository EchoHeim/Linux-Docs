#include <stdio.h>
#include <pthread.h>
int ticketcount = 20;
pthread_mutex_t lock;
void* salewinds1(void* args)
{
    while(1)
    {
        //因为要访问全局的共享变量，所以就要加锁
        pthread_mutex_lock(&lock); 
        if(ticketcount > 0)  //如果有票
        {
			printf("窗口1正在售票，当前有%d张票\n",ticketcount);
			sleep(3);
			ticketcount --;
			printf("窗口1售票完，当前剩余%d张票\n",ticketcount);
        }
        else                //如果没票
        {
            pthread_mutex_unlock(&lock); //没票就解锁
            pthread_exit(NULL);          //退出子线程
        }
        pthread_mutex_unlock(&lock);     //如果有票，卖完票要解锁
        sleep(1);   	//要放到锁的外面，让另一个有时间锁
    }
}
void* salewinds2(void* args)
{
    while(1)
    {
        pthread_mutex_lock(&lock);   //加锁
        if(ticketcount>0)            //如果有票
        {
			printf("窗口2正在售票，当前有%d张票\n",ticketcount);
			sleep(3);
			ticketcount --;
			printf("窗口2售票完，当前剩余%d张票\n",ticketcount);
        }
        else                //如果没票
        {
            pthread_mutex_unlock(&lock); //没票就解锁
            pthread_exit(NULL);          //退出子线程
        }
        pthread_mutex_unlock(&lock);     //如果有票，卖完票要解锁
        sleep(1);   	//要放到锁的外面，让另一个有时间锁
    }

}
int main()
{
    pthread_t pthid1 = 0;
    pthread_t pthid2 = 0;

	//初始化锁
    pthread_mutex_init(&lock,NULL);  

	//创建窗口1
    pthread_create(&pthid1,NULL,salewinds1,NULL); 

	//创建窗口2
    pthread_create(&pthid2,NULL,salewinds2,NULL);

	//等待子线程退出
    pthread_join(pthid1,NULL);
    pthread_join(pthid2,NULL);

	//销毁锁
    pthread_mutex_destroy(&lock);     
    return 0;
}

