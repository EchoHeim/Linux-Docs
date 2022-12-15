#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <error.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>

//空洞文件
//在mmap需要用到空洞文件
#define FILENAME "whence.txt"

int main(void)
{
	int fd;
	long len = 4096;
	char str[] = "I am here.";

	fd = open(FILENAME, O_CREAT|O_WRONLY, 0666);
	if(0 > fd)
	{
		perror("can not create file or open file.");
		return -1;
	}
	printf("fd = %d\nSTDIN_FILENO=%d\n", fd, STDIN_FILENO);
	printf("STDOUT_FILENO = %d\n", STDOUT_FILENO);
	printf("STDERR_FILENO = %d\n", STDERR_FILENO);
	
	lseek(fd, len ,SEEK_SET);  //从开始开始读

	if(write(fd, str, strlen(str)) < 0)
	{
		perror("can not write file.");
		return -1;
	}

	
	

	return 0;
}
