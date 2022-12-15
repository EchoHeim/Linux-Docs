#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include <string.h>
#define SOURCEFILE "src.txt"
#define DESTFILE	"dest.txt"


int usage(char * file)
{
	printf("Invalid arguments.\n");
	printf("usage:%s file1 file\n", file);

	return 0;	
}

int main(int argc ,char ** argv)
{
	int s_fd, d_fd;
	char buffer[1024];
	int len = 0;

	char src[128] = {'\0'};
	char dst[128] = {'\0'};
	
	if(3 != argc)
	{
		usage(argv[0]);	
		return -1;
	}


	//src = argv[1];
	//dst = argv[2];
	strcpy(src, argv[1]);
	strcpy(dst, argv[2]);


	memset(buffer, sizeof(buffer), 0);
	//s_fd = open(SOURCEFILE, O_RDONLY);
	//d_fd = open(DESTFILE, O_WRONLY| O_CREAT);

	s_fd = open(src, O_RDONLY);
	d_fd = open(dst, O_WRONLY| O_CREAT);
	if(0 > s_fd || 0> d_fd)
	{
		perror("cannot open file.");
		return -1;
	}

	while((len = read(s_fd, buffer, sizeof(buffer)-1)) > 0)
	{
		if(write(d_fd, buffer, len) < 0)
		{
			perror("can not write file.");
			return -1;
		
		}
		
	}

	close(s_fd);
	close(d_fd);

	return 0;
}
