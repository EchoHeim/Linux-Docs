#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <linux/input.h>

// /dev/input/event??

int main(int argc, char *argv[])
{
	int fd, ret;
	struct input_event e;

	fd = open(argv[1], O_RDWR);

	if(fd == -1)
	{
		perror(argv[1]);
		return -1;
	}

	while(1)
	{
		ret = read(fd, &e, sizeof(struct input_event));
		
		if( -1 == ret )
		continue;

		if(e.type == EV_KEY)
		{
			if(e.value)
			printf("%d Down.\n", e.code);
			
			else
			printf("%d Up.\n", e.code);
		}

		else if(e.type == EV_SYN)
		{
			printf("sync event\n");
		}
	}
}








