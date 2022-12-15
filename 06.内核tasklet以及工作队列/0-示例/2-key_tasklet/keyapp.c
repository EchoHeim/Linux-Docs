#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <poll.h>
int main()
{
	unsigned char key;
	struct pollfd fds[1];
	int fd = open("/dev/key",O_RDWR);
	if(fd<0)
	{
		printf("open fail!!!\n");
		return -1;
	}
	fds[0].fd = fd;
	fds[0].events = POLLIN;
	if(poll(fds,1,5000))
	{
		read(fd,&key,1);
		printf("key = %d\n",key);
	}
	else
		printf("bye bye!!!\n");
	close(fd);
	return 0;
}
