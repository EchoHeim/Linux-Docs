#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>

int main(void)
{
	unsigned char key_val=0;
	int fd=open("/dev/key_drv",O_RDWR);
	if(fd<0)
		printf("error!\n");
	while(1)
	{
		read(fd,&key_val,1);
		if(key_val)
			printf("key_val = %d\n",key_val);
		key_val=0;
	}
	return 0;	
}
