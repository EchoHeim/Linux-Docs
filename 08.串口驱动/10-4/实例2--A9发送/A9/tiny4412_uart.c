#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <errno.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <termios.h>
#include <stdlib.h>     


/*---------------------------------------------------------------
			���ô��ڵĻ�������
			�ó�����Tiny4412����ͨ����
UART0 					UART2	       UART3      ������������
-----------------------------------------------------------------*/
int set_opt(int fd,int nSpeed, int nBits, char nEvent, int nStop)
{
    struct termios newtio,oldtio;
    if  ( tcgetattr( fd,&oldtio)  !=  0)
    {
        perror("SetupSerial 1");
        return -1;
    }
    bzero( &newtio, sizeof( newtio ) );
    newtio.c_cflag  |=  CLOCAL | CREAD;
    newtio.c_cflag &= ~CSIZE;

    switch( nBits )
    {
    case 7:
        newtio.c_cflag |= CS7;
        break;
    case 8:
        newtio.c_cflag |= CS8;
        break;
    }

	/*���ô��ڵ�У��λ*/
    switch( nEvent )
    {
    case 'O':                     //��У��
        newtio.c_cflag |= PARENB;
        newtio.c_cflag |= PARODD;
        newtio.c_iflag |= (INPCK | ISTRIP);
        break;
    case 'E':                     //żУ��
        newtio.c_iflag |= (INPCK | ISTRIP);
        newtio.c_cflag |= PARENB;
        newtio.c_cflag &= ~PARODD;
        break;
    case 'N':                    //��У��
        newtio.c_cflag &= ~PARENB;
        break;
    }

	/*���ô��ڵĲ�����*/
    switch( nSpeed )
    {
    case 2400:
        cfsetispeed(&newtio, B2400);
        cfsetospeed(&newtio, B2400);
        break;
    case 4800:
        cfsetispeed(&newtio, B4800);
        cfsetospeed(&newtio, B4800);
        break;
    case 9600:
        cfsetispeed(&newtio, B9600);
        cfsetospeed(&newtio, B9600);
        break;
    case 115200:
        cfsetispeed(&newtio, B115200);
        cfsetospeed(&newtio, B115200);
        break;
    default: /*Ĭ�����ò�����Ϊ9600*/
        cfsetispeed(&newtio, B9600);
        cfsetospeed(&newtio, B9600);
        break;
    }

	/*����ֹͣλ*/
    if( nStop == 1 )
    {
        newtio.c_cflag &=  ~CSTOPB;
    }
    else if ( nStop == 2 )
    {
        newtio.c_cflag |=  CSTOPB;
    }
    newtio.c_cc[VTIME]  = 0;
    newtio.c_cc[VMIN] = 0;
    tcflush(fd,TCIFLUSH);
    if((tcsetattr(fd,TCSANOW,&newtio))!=0)
    {
        perror("��������ʧ��!\n");
        return -1;
    }
    printf("�������óɹ�!\n");
    return 0;
}

/*--------------------------------------------------------
				�򿪴����豸�˿�
----------------------------------------------------------*/
int open_port(int comport)
{
    int fd;
    const char *dev[]= {"/dev/ttySAC0","/dev/ttySAC1","/dev/ttySAC2","/dev/ttySAC3"};
    long  vdisable;
    if ( comport >= 0 && comport < 4)
    {
        fd = open( dev[comport], O_RDWR|O_NOCTTY|O_NDELAY);
        if (-1 == fd)
        {
            perror("���ڴ򿪴���!\n");
            return(-1);
        }
        else
        {
            printf("�򿪴��� %s �ɹ�!!\n",dev[comport]);
        }
    }

    else
    {
    	perror("����ѡ�����!\n");
        return(-1);
    }

	/*�����豸�ļ�������Ϊ0 */
    if(fcntl(fd, F_SETFL, 0)<0)
    {
        printf("fcntl failed!\n");
    }
    else
    {
        printf("fcntl=%d\n",fcntl(fd, F_SETFL,0));
    }

    if(isatty(STDIN_FILENO)==0)
    {
        printf("standard input is not a terminal device\n");
    }
    else
    {
        printf("�豸���ͻ�ȡ�ɹ�!\n");
    }

    printf("fd-open �򿪵��ļ�������=%d\n",fd);
    return fd;
}


/*

*/
int main(int argc,char *args[])
{
    int fd;
    int nread=0,i = 0;
    int port;
		perror("���θ�ʽ��./app 0-3");
    if(argc == 2) 
		{
        port = atoi(args[1]);   /*��������ַ���תΪ����*/
        if(port <0 || port > 3) /*�жϴ��ڵķ�Χ*/
        {
            perror("��Ч���ںţ�0~3");
            exit(-1);
        }

        if((fd=open_port(port))<0) /*�ж�open���ص��ļ�������*/
        {
            perror("open_port���ڶ˿ڴ򿪴���\n");
            exit(-1);
        }
    }
    else /*���û�д��Σ�Ĭ�ϴ򿪴���0*/
    {
        if((fd=open_port(0))<0) /*�ж�open���ص��ļ�������*/
        {
            perror("open_port error");
            exit(-1);
        }
    }

    if((i=set_opt(fd,9600,8,'N',1))<0)/*���ô��ڵĻ�������*/
    {
        perror("set_opt error");
        return;
    }
    printf("fd=%d\n",fd);

    
/*
�öŰ��߽������������Ĵ���IO������ת����ģ����ߴ����߽������Ϳ���ֱ�ӷ������ݣ�
*/
 		char buff[10]; 
    while (1) 
    {
      //nread=read(fd,buff,4);
      write(fd,"hello",6);
		sleep(2);
    }
    close(fd);
    return;
}

