#include <stdio.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <pthread.h>

#define MAX     5
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER; //��̬����������

//������
void handler(int fd, char *name)
{
    int count = 0, i;
    char buf[1024];

    while (count < MAX)
    {
        pthread_mutex_lock(&mutex);                //����
        snprintf(buf, sizeof(buf), "%s ���߳�ID�� %8x count = %5d\n", name, pthread_self(), count++);
        for (i = 0; i < strlen(buf); i++)
        {
            write(fd, &buf[i], 1);
            usleep(10);
        }	
        pthread_mutex_unlock(&mutex);              //����
		usleep(10);
    }
}
void *do_work(void *data)
{
    //���̵߳��ô�����
    handler(*(int *)data, "child");
	
    return NULL;
}
int main(int argc, char *argv[])
{
    int fd;
    pthread_t id;
	//��һ�� �ı�(O_TRUNC����ļ����ڣ�������ֻд/��д��ʽ�򿪣�������ļ�ȫ������(�����䳤�Ƚض�Ϊ0))  
    fd = open("txt", O_RDWR | O_CREAT | O_TRUNC);
         if (fd == -1)    perror("�ı���ʧ��");
	//�������߳�
    if (pthread_create(&id, NULL, do_work, (void *)&fd)) 
        perror("�������߳�ʧ��");

	//���̵߳��ô�����
    handler(fd, "parent");

	//�ȴ����߳̽��� 
    pthread_join(id, NULL);                              
    return 0;
}
