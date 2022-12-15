
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
			配置串口的基本参数
			该程序在Tiny4412测试通过！
UART0 					UART2	       UART3      发送数据正常
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

	/*配置串口的校验位*/
    switch( nEvent )
    {
    case 'O':                     //奇校验
        newtio.c_cflag |= PARENB;
        newtio.c_cflag |= PARODD;
        newtio.c_iflag |= (INPCK | ISTRIP);
        break;
    case 'E':                     //偶校验
        newtio.c_iflag |= (INPCK | ISTRIP);
        newtio.c_cflag |= PARENB;
        newtio.c_cflag &= ~PARODD;
        break;
    case 'N':                    //无校验
        newtio.c_cflag &= ~PARENB;
        break;
    }

	/*配置串口的波特率*/
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
    default: /*默认设置波特率为9600*/
        cfsetispeed(&newtio, B9600);
        cfsetospeed(&newtio, B9600);
        break;
    }

	/*配置停止位*/
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
        perror("串口配置失败!\n");
        return -1;
    }
    printf("串口配置成功!\n");
    return 0;
}

/*--------------------------------------------------------
				打开串口设备端口
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
            perror("串口打开错误!\n");
            return(-1);
        }
        else
        {
            printf("打开串口 %s 成功!!\n",dev[comport]);
        }
    }

    else
    {
    	perror("串口选择错误!\n");
        return(-1);
    }

	/*设置设备文件的属性为0 */
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
        printf("设备类型获取成功!\n");
    }

    printf("fd-open 打开的文件描述符=%d\n",fd);
    return fd;
}

