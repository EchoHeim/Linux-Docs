#include <stdio.h>
#include <pthread.h>
//���̴߳�����
void *p_main(void *arg)                      
{
    printf("��ǰ�������߳�\n");
    sleep(3);
    printf("���߳�˯��3���\n");
}
int main(void)
{
    pthread_t id;
    int ret;

    //����һ���߳�(���������߳�ID���߳����ԡ��߳�ִ�к���������)
    ret = pthread_create(&id, NULL, p_main, NULL);
    if(ret)                                       
    {
        perror("�̴߳���ʧ��\n");
        return -1;
    }
    sleep(1);
	//ȡ�����������е����߳�
    pthread_cancel(id);
	printf("���߳�ȡ���������߳�\n");
    return 0;
}

