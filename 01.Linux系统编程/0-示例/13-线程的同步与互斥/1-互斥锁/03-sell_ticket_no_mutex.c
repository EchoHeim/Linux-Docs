#include <stdio.h>
#include <pthread.h>
int ticketcount = 20;	//火车票，公共资源（全局）
void* salewinds1(void* args)
{
    while(ticketcount > 0)
    {
        printf("窗口1正在售票，当前有%d张票\n",ticketcount);
        sleep(3);
        ticketcount --;
        printf("窗口1售票完，当前剩余%d张票\n",ticketcount);
    }
}
void* salewinds2(void* args)
{
    while(ticketcount > 0)
    {
        printf("窗口2正在售票，当前有%d张票\n",ticketcount);
        sleep(3);
        ticketcount --;
        printf("窗口2售票完，当前剩余%d张票\n",ticketcount);
    }
}
int main()
{
    pthread_t pthid1 = 0;
    pthread_t pthid2 = 0;

	//创建窗口1
    pthread_create(&pthid1,NULL,salewinds1,NULL);

	//创建窗口2
    pthread_create(&pthid2,NULL,salewinds2,NULL);

	//等待子线程退出
    pthread_join(pthid1,NULL);
    pthread_join(pthid2,NULL);
    return 0;
}

