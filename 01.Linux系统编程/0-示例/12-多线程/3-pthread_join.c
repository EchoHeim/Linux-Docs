#include <stdio.h>
#include <pthread.h>

void *p_main(void *arg)
{
    printf("��ǰ�������߳�\n");
    sleep(3);
    printf("���߳�3����ʱ��\n");
}

int main(void)
{
    pthread_t id;
    int ret;

    //�������߳�
    ret = pthread_create(&id, NULL, p_main, NULL);
    if(ret)
    {
        perror("���̴߳���ʧ��");
        return -1;
    }
    sleep(1);
	
    //�ȴ����߳̽���
    pthread_join(id,NULL);
    printf("ȫ������\n");

    return 0;
}
