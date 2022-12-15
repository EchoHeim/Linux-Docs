#include <stdio.h>
#include <pthread.h>
#include <sys/syscall.h>
#include <string.h>

char buffer[128];

void *  p_main(void *arg)                //���̴߳�����
{
    int a;  
	
    printf("���߳�ID=%d\n",pthread_self()); //��ӡ���̵߳�ID    
    //printf("���߳�ID=%d\n",pthread_self()); //��ӡ���̵߳�ID
    printf("������ID=%d\n",getpid());       //��ӡ�����̵Ľ���ID��
    printf("buffer=%s\n",buffer);           //��� buffer�������
    sleep(1);                                      
    pthread_exit(0);                        //�������߳� 
}
int main(void)
{
    pthread_t id;  
	int ret;

	//�������߳�
    ret = pthread_create(&id, NULL, p_main, NULL);  
    if(ret)
    {
        perror("���̴߳���ʧ��\n");
        return -1;
    }  
    printf("���߳�ID=%d\n",id);             //��ӡ���̵߳�ID
    printf("���߳�ID=%d\n",pthread_self()); //��ӡ���̵߳�ID
    printf("������ID=%d\n",getpid());       //��ӡ�����̵Ľ���ID��
    memcpy(buffer,"hello",6);               //�ڴ濽����buffer 
    pthread_join(id,NULL);                  //�ȴ����߳̽��� 
    
    
    return 0;
}

