//--app-key.c

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <linux/input.h>

int main(int argc, char **argv)
{
	int count, i;
	int fd;
	struct input_event ev_key;
	fd = open("/dev/input/event1", 0);//根据实际情况 有可能不是event1
	if (fd < 0)
	{
		perror("open device key!");
		exit(1);
	}

	while (1)
	{

		count = read(fd, &ev_key, sizeof(struct input_event));

		if (EV_ABS == ev_key.type)
		{
            
			printf("type:%d,code:%s,value:%d\n", ev_key.type, 
                (ev_key.code== ABS_X) ? "ABS_X" :"ABS_Y", 
                ev_key.value);
		}

		if (EV_SYN == ev_key.type)
			printf("syn event\n");

	}
	close(fd);
	return 0;
}

