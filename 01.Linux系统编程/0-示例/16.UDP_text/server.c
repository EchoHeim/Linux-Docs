#include <stdio.h>
#include <unistd.h>
#include <sys/socket.h>
#include <string.h>
#include <netinet/in.h>

#define PORT 3333  //本服务器的端口号

int main(void)
{
    int sock_fd,ret;
    char buffer[1024] = {};						//缓冲区				
    struct sockaddr_in server_addr,client_addr;
    int len = sizeof(struct sockaddr_in);		//计算空间大小
	/*int socket(int family,int type,int protocol)//socket函数原型
	int family协议族
		(1)AF_INET  IPv4协议  PF_INET = AF_INET
		(2)AF_INET6 IPv6协议
		(3)AF_LOCAL UNIX协议
	int type套接字类型
		(1)SOCK_STREAM  字节流套接字socket(针对TCP/IP协议)
		(2)SOCK_DGRAM   数据报套接字(针对UDP协议)
		(3)SOCK_RAW     原始套接字
	protocol 必须为 0(原始套接字除外)
	返回值:	成功: 返回非负套接字描述符
			出错: 1
	*/	
	/* 服务器端开始建立sock_fd描述符 */
    sock_fd = socket(AF_INET,SOCK_DGRAM,0);//使用UDP协议 使用IPv4
    if(sock_fd == -1)
    {
        perror("socket");
        return -1;
    }
    server_addr.sin_family = AF_INET;				//本机协议族
    server_addr.sin_port   = htons(PORT);			//本机端口号
    server_addr.sin_addr.s_addr = inet_addr("192.168.0.101");//本机的IP地址
	/* 捆绑sockfd描述符到IP地址 */ 
    ret = bind(sock_fd,(struct sockaddr *)&server_addr,len);//绑定
    if(ret == -1)
    {
        perror("bind");
        return -1;
    }
	while(1)
    {   /*接收客户端发送过来的数据*/
    	
		//recvfrom(int s, void *buf, size_t len, int flags,struct sockaddr *from, socklen_t *fromlen);
        recvfrom(sock_fd,buffer,sizeof(buffer),0,(struct sockaddr *)&client_addr,&len);
        printf("%s : %s\n",inet_ntoa(client_addr.sin_addr),buffer);

        /*sendto(sock_fd,"hello client",13,0,(struct sockaddr *)&client_addr,len);*/
		//sendto(int s, const void *buf, size_t len, int flags, const struct sockaddr *to, socklen_t tolen);
		/*发送数据到客户端*/
        sendto(sock_fd,"copy",5,0,(struct sockaddr *)&client_addr,len);
        memset(buffer,0,sizeof(buffer));
    }
    close(sock_fd);
    return 0;
}







