
#include <stdio.h>
#include <string.h>
#include <sys/types.h>       
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
int main()
{
/***********/
	int sd,cli_sd;//保存创建的套接字描述符,cli_sd：保存客户端套接字
	int len; 
	int ret;
	int cli_port;
	char *cli_ip = NULL;
	struct sockaddr_in my_addr;//存放套接字要绑定的具体的ip和端口信息
	struct sockaddr_in cli_addr;//连接的客户端的信息
	char buffer[1024];//保存接收信息
	int data_len;//保存信息大小
/***********/
	//1.建立一个套接字
	/*int socket(int family, int type, int protocol) 
	*三个参数：
	*family:表示协议簇
	*type:表示套接字类型
	*protocol:通常是0，
	*返回创建成功的套接字,失败返回-1;
	*/
	sd = socket(AF_INET,SOCK_STREAM,0);
	if(sd<0)
	{
		perror("socket");
		return -1;
	}
	//2.bind套接字到端口
	//int bind(int sockfd, struct sockaddr *my_addr, int addrlen)
	/*
	* sockfd:是我们上面创建的描述符，
	* my_addr：使用它来描述出来具体的ip和端口信息。
	* addlen:是第二个参数的字节大小。
	*/

	len = sizeof(struct sockaddr);
//这个结构描述的ip和端口数据会在网络上进行传输，要求赋值时使用的都是网络字节序。
//int inet_aton(const char *straddr,struct in_addr *addrptr);
	//192.168.0.101
	my_addr.sin_family = AF_INET;
	my_addr.sin_port = htons(8888);//htons()、ntohs()、htonl()和ntohl()。
	ret = inet_aton("192.168.0.101",&my_addr.sin_addr);
	if(ret < 0)
	{
		printf("inet_aton error\n");
		return ret;
	}
	//当这个端口已经被绑定过了，会出错，
	//ip地址必须是本机ip.如果不是也会出错。
	ret = bind(sd,(struct sockaddr *)&my_addr,len);
	if(ret < 0)
	{
		perror("bind");
		return -1;
	}

	//3.listen 设置能够接受的最大的请求数。
	ret = listen(sd,5);
	if(ret < 0)
	{
		return -1;
	}

	//4.accept 等待有客户端连接并接受请求。
	//int accept(int sockfd, struct sockaddr *addr, socklen_t *addrlen)
	/*
	* sd:服务器的sd
	* addr：用来保存请求的客户端的地址信息
	* addrlen: 是保存addr的大小。
	* accept:返回值是用来和客户端进行通信的套接字。
	*/
	cli_sd = accept(sd,(struct sockaddr *)&cli_addr,&len);
	if(cli_sd < 0)
	{
		perror("accept");
		return -1;
	}
	//打印出客户端的信息：char * inet_ntoa(struct in_addr inaddr);
	cli_ip = inet_ntoa(cli_addr.sin_addr);
	cli_port = ntohs(cli_addr.sin_port);//要转化成主机字节序
	printf ("client %s:%d is connected!\n",cli_ip,cli_port);
	//5.进行收发网络的处理。
	//收的函数  recv  recvfrom read.
	//发送的函数send sendto write
	while(1)
	{
		
		//int recv(int sockfd, void *buf,int len, unsigned int flags)
		/*
		* sockfd:客户端套接字
		* len：要读取的数据的大小。
		* data_len如果小于0表示出错
		*/
		data_len = recv(cli_sd,buffer,sizeof(buffer),0);
		printf("%d: %s\n",data_len,buffer);
		if(strcmp(buffer,"byebye")==0)
			break;
		gets(buffer);
		/*strcat(buffer,": data for server\n");*/
		//在客户端发送的数据之后加上一个尾巴。
		//int send(int sockfd, const void *msg, int len, int flags)
		send(cli_sd,buffer,strlen(buffer)+1,0);
	}
	//6.程序结束时，关闭套接字
	close(cli_sd);//先关闭客户端
	close(sd);
}

