#include <stdio.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>

#define PORT 3333 //本地的端口号
/*客户端*/
int main(void)
{
    int sock_fd,ret;
    char buf[1024] = {};					//缓冲区
    struct sockaddr_in server_addr;
    int len = sizeof(struct sockaddr_in);	//大小的计算
	/*建立socket套接字描述符*/
    sock_fd = socket(AF_INET,SOCK_DGRAM,0);	//使用UDP协议
    if(sock_fd == -1)
    {
        perror("socket");
        return -1;
    }
    server_addr.sin_family = AF_INET;//服务器
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






