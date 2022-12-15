#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <poll.h>

int main(void)
{
	unsigned int key_val=0,return_val;
	int fd_key = open("/dev/hello_key",O_RDWR);
	struct pollfd fds;
	fds.fd = fd_key;
	fds.events = POLLIN;
	if(fd_key<0)
	{
		printf("error!\n");
		return -1;
	}
 	return_val = poll(&fds,1,5000);
	if(return_val)
	{
		read(fd_key,&key_val,1);
		switch(key_val)
		{
			case 1:printf("key1 is OK!\n");break;
			case 2:printf("key2 is OK!\n");break;
			case 3:printf("key3 is OK!\n");break;
			case 4:printf("key4 is OK!\n");break;
		}
	}
	return 0;
}
