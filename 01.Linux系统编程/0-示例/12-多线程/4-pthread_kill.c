#include <stdio.h>
#include <pthread.h>
#include <sys/syscall.h>
#include <signal.h>

//�źŴ�����
void report(int sig)                            
{
    printf("���յ����ź��� = %d\n,�����źŵ��߳�ID = %lu\n",sig,pthread_self());
}

//���߳�1������
void * p_main1(void *arg)                    
{
    signal(SIGUSR1,report);                       //ע���ź�
    
    printf("���߳�1��ID = %d,���߳�1�Ľ���ID =%d \n",pthread_self(),getpid());
    while(1)sleep(1);                                    
}

//���߳�2������ 
void *p_main2(void *arg)                    
{
    signal(SIGUSR1,report);                      //ע���ź�
    
    printf("���߳�2��ID = %lu,���߳�2�Ľ���ID =%d \n",pthread_self(),getpid());
    while(1)sleep(1);
}
int main(void)
{
    pthread_t id1, id2;  
    int ret;
	
	//�������߳�1
    ret = pthread_create(&id1, NULL, p_main1, NULL);
    if(ret)  										
    {
        perror("���߳�1����ʧ��\n");
        return -1;
    }  
	
	//�������߳�2
    ret = pthread_create(&id2, NULL, p_main2, NULL);
    if(ret)                     //���߳�2����ʧ��
    {
        perror("���߳�2����ʧ��\n");
        return -1;
    }
	
    printf("���̵߳�ID = %d,����ID =%d \n",pthread_self(),getpid());
    sleep(1);                  //��ʱ1�룬�ȸ��������߳̾�λ
	
    pthread_kill(id1,SIGUSR1); //�����߳�1���ź�SIGUSR1
    sleep(1);
	
    pthread_kill(id2,SIGUSR1); //�����߳�2���ź�SIGUSR1    
 
    pthread_join(id1,NULL);    //�ȴ����߳̽���(���߳�����ѭ�������Թ�������)
    pthread_join(id2,NULL);
    return 0;
}
