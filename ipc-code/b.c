// C program to implement one side of FIFO
// This side reads first, then reads
#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

int main()
{
	int fd1=open("FIFOpipe",O_RDONLY);
	char a[6];
	read(fd1,a,6);
	printf("%s",a);
	fflush(stdout);

	sleep(5);
	read(fd1,a,6);
	printf("%s",a);
	return 0;
}
