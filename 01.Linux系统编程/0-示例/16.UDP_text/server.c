#include <stdio.h>
#include <unistd.h>
#include <sys/socket.h>
#include <string.h>
#include <netinet/in.h>

#define PORT 3333  //���������Ķ˿ں�

int main(void)
{
    int sock_fd,ret;
    char buffer[1024] = {};						//������				
    struct sockaddr_in server_addr,client_addr;
    int len = sizeof(struct sockaddr_in);		//����ռ��С
	/*int socket(int family,int type,int protocol)//socket����ԭ��
	int familyЭ����
		(1)AF_INET  IPv4Э��  PF_INET = AF_INET
		(2)AF_INET6 IPv6Э��
		(3)AF_LOCAL UNIXЭ��
	int type�׽�������
		(1)SOCK_STREAM  �ֽ����׽���socket(���TCP/IPЭ��)
		(2)SOCK_DGRAM   ���ݱ��׽���(���UDPЭ��)
		(3)SOCK_RAW     ԭʼ�׽���
	protocol ����Ϊ 0(ԭʼ�׽��ֳ���)
	����ֵ:	�ɹ�: ���طǸ��׽���������
			����: 1
	*/	
	/* �������˿�ʼ����sock_fd������ */
    sock_fd = socket(AF_INET,SOCK_DGRAM,0);//ʹ��UDPЭ�� ʹ��IPv4
    if(sock_fd == -1)
    {
        perror("socket");
        return -1;
    }
    server_addr.sin_family = AF_INET;				//����Э����
    server_addr.sin_port   = htons(PORT);			//�����˿ں�
    server_addr.sin_addr.s_addr = inet_addr("192.168.0.101");//������IP��ַ
	/* ����sockfd��������IP��ַ */ 
    ret = bind(sock_fd,(struct sockaddr *)&server_addr,len);//��
    if(ret == -1)
    {
        perror("bind");
        return -1;
    }
	while(1)
    {   /*���տͻ��˷��͹���������*/
    	
		//recvfrom(int s, void *buf, size_t len, int flags,struct sockaddr *from, socklen_t *fromlen);
        recvfrom(sock_fd,buffer,sizeof(buffer),0,(struct sockaddr *)&client_addr,&len);
        printf("%s : %s\n",inet_ntoa(client_addr.sin_addr),buffer);

        /*sendto(sock_fd,"hello client",13,0,(struct sockaddr *)&client_addr,len);*/
		//sendto(int s, const void *buf, size_t len, int flags, const struct sockaddr *to, socklen_t tolen);
		/*�������ݵ��ͻ���*/
        sendto(sock_fd,"copy",5,0,(struct sockaddr *)&client_addr,len);
        memset(buffer,0,sizeof(buffer));
    }
    close(sock_fd);
    return 0;
}







