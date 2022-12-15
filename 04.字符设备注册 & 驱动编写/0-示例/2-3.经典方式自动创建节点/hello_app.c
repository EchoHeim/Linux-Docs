#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/ioctl.h>
#define DEV_NAME "/dev/ZSK_1"
int main()
{
    int fd,ret;
    
    fd  = open(DEV_NAME,O_RDWR);
    if(fd < 0)
    {
        printf("open fail\n");
        exit(0);
    }
    close(fd);
    return 0;
}
