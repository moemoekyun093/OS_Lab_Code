// C program to implement one side of FIFO
// This side writes first, then reads
#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

int main()
{
	int returnValue=mkfifo("abcd",0666);
	printf("The mkfifo() call returned %d\n", returnValue);
	int fd=open("FIFOpipe",O_WRONLY);
	write(fd,"hello",6);
	// close(fd);
	// fd=open("FIFOpipe",O_WRONLY);
	write(fd,"hello",6);


	return 0;
}
