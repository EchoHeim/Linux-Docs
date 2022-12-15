#include <stdio.h>
#include <pthread.h>

void clean1(void *arg)
{
    printf("in clean1: %d\n", (int)arg);
}

void clean2(void *arg)
{
    printf("in clean2: %d\n", (int)arg);
}

void clean3(void *arg)
{
    printf("in clean3: %d\n", (int)arg);
}

void *p_main(void *arg)
{
    int i;

    pthread_cleanup_push(clean1, (void *)1111);
    pthread_cleanup_push(clean2, (void *)2222);
    pthread_cleanup_push(clean3, (void *)3333);//����ջ���Ĳ�����������

    for(i = 0; i < 3; i++)
    {
        printf("%d in p_main: i = %d\n",*(int *)arg, i);
        usleep(500 * 1000);
    }
	
    //���˳�ǰû��ִ��POP��������֮ǰע���PUSH������ȫ��ִ��
    pthread_exit(0);  
    
    pthread_cleanup_pop(1);//1ִ��֮ǰע��ĺ��� 0������
    pthread_cleanup_pop(0);
    pthread_cleanup_pop(1);
    pthread_exit(0);
}

int main(void)
{
    int ret,num=1234;
    pthread_t id;

    //�����߳�
    ret = pthread_create(&id, NULL, p_main, (void *)&num);
    if(ret)
    {
        perror("�����߳�ʧ��");
        return -1;
    }
	
	//���߳��������ȴ����߳�ִ�����˳��ټ����������
    pthread_join(id, NULL); 
    return 0;
}


