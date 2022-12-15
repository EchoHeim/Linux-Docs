#include <stdio.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>

#define PORT 3333 //���صĶ˿ں�
/*�ͻ���*/
int main(void)
{
    int sock_fd,ret;
    char buf[1024] = {};					//������
    struct sockaddr_in server_addr;
    int len = sizeof(struct sockaddr_in);	//��С�ļ���
	/*����socket�׽���������*/
    sock_fd = socket(AF_INET,SOCK_DGRAM,0);	//ʹ��UDPЭ��
    if(sock_fd == -1)
    {
        perror("socket");
        return -1;
    }
    server_addr.sin_family = AF_INET;//������
    server_addr.sin_port   = htons(PORT);
    server_addr.sin_addr.s_addr = inet_addr("192.168.0.101");
    
   while(1)
   {
        ret = sendto(sock_fd,"hello",6,0,(struct sockaddr *)&server_addr,len);
        printf("ret = %d\n",ret);
        ret = recvfrom(sock_fd,buf,sizeof(buf),0,(struct sockaddr *)&server_addr,&len);
        if(0 == strcmp(buf,"copy"))
            printf("%s : %s\n",inet_ntoa(server_addr.sin_addr),buf);
        else
            printf("recv error\n");
        sleep(3);
    }
    close(sock_fd);
    return 0;
}






