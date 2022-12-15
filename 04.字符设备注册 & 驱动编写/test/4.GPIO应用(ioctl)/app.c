#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>

int main(void)
{
	unsigned char key_val=0,beep_val=0;
	int fd_led = open("/dev/hello_led",O_RDWR);
	int fd_beep = open("/dev/hello_beep",O_RDWR);
	int fd_key = open("/dev/hello_key",O_RDWR);
	if((fd_led<0)||(fd_beep<0)||(fd_key<0))
	{
		printf("error!\n");
		return -1;
	}	
	while(1)
	{
		read(fd_key,&key_val,1);
		switch(key_val)
		{
			case 1:beep_val=1;write(fd_beep,&beep_val,1);break;
			case 2:ioctl(fd_led,11,1);ioctl(fd_led,12,1);ioctl(fd_led,13,1);ioctl(fd_led,14,1);break;
			case 3:ioctl(fd_led,11,0);ioctl(fd_led,12,0);ioctl(fd_led,13,0);ioctl(fd_led,14,0);break;
			case 4:beep_val=0;write(fd_beep,&beep_val,1);break;
		}
	}
	return 0;	
}
