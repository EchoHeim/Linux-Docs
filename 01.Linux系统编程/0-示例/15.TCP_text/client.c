#include <stdio.h>
#include <string.h>
#include <sys/types.h>        
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
int main()
{
	int sd;
	struct sockaddr_in seraddr;
	int len;
	int ret;
	char s[1024];//保存发送信息
	char buff[1024];//保存接收信息
	int data_len = 0;
	//1.创建套接字描述符
	sd = socket(AF_INET,SOCK_STREAM,0);
	if(sd<0)
		return -1;

	//2.描述服务器信息。
	seraddr.sin_family = AF_INET;
	seraddr.sin_port = htons(8888);//
	seraddr.sin_addr.s_addr = inet_addr("192.168.0.101");  //in_addr_t inet_addr(const char *straddr);/

	len = sizeof(struct sockaddr_in);
	//3.连接服务器
	//int connect(int sockfd, struct sockaddr *serv_addr, int addrlen)
	ret = connect(sd,(const struct sockaddr *)&seraddr,len);
	if(ret < 0)
	{
		return -1;
	}
	printf("connect to server ok!\n");
	//连接服务器成功之后，与服务器进行对话。
	while(1)
	{
		gets(s);
		send(sd,s,strlen(s)+1,0);//将从终端中读取字符串发送给服务
		if(strcmp("byebye",s)==0)
			break;
		data_len = recv(sd,buff,sizeof(buff),0);//读取服务器返回的内容
		printf("%s\n",buff);
	}
	//关闭套接字。
	close(sd);
}







