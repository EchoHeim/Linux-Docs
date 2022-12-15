#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/types.h>
#include <errno.h>
#include <unistd.h>
#include <string.h>
int main(void)
{

	int fda, fdb,fdaa, fdbb;
	char buffer[128]= {0};
	int len = 0;
	fda = open("a.txt", O_RDONLY);
	fdb = open("b.txt", O_RDONLY);
	fdbb = dup(fdb); //这里fdbb和fdb值是一样。
	fdaa = dup2(fda, fdb);//这里fdb、fda、fdaa的值都是一样(fdb首先关闭原来的描述符，然后被赋值fda)
	printf("fda:%d\nfdb:%d\nfdaa:%d\nfdbb:%d\n", fda, fdb, fdaa, fdbb);
	read(fdb, buffer, sizeof(buffer)-1);
	printf("buffer:%s\n", buffer);
	memset(buffer, '\0', 12);
	lseek(fda, 0L, SEEK_SET);
	len = read(fda, buffer, sizeof(buffer)-1);
	if(0 > len)
		perror("read fda");
	puts(buffer);
	close(fda);
	close(fdb);
	close(fdaa);
	close(fdbb);
	return 0;
}
