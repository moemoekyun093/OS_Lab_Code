/**
 * Simple program demonstrating shared memory in POSIX systems.
 *
 * This is the consumer process
 *
 * Figure 3.18
 *
 * @author Gagne, Galvin, Silberschatz
 * Operating System Concepts - Ninth Edition
 * Copyright John Wiley & Sons - 2013
 */

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/shm.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <unistd.h>
#include <string.h>

int main()
{
	const char *name = "OS";
	const int SIZE = 4096;

	int shm_fd;
	void *ptr;
	int i;

	/* open the shared memory segment */
	shm_fd = shm_open(name, O_RDWR, 0666);
	if (shm_fd == -1) {
		printf("shared memory failed\n");
		exit(-1);
	}

	/* now map the shared memory segment in the address space of the process */
	ptr = mmap(0,SIZE, PROT_READ|PROT_WRITE, MAP_SHARED, shm_fd, 0);
	if (ptr == MAP_FAILED) {
		printf("Map failed\n");
		exit(-1);
	}

	/* now read from the shared memory region */
	const char* w1= "freeeee";
	 const char* w2= "OSisFUN";
	 void* ptr1=ptr;
	 int c;
	 int d=0;
	mkfifo("efg",0666);
	int fd1;
	int fd2;
	fd1=open("abc",O_RDONLY);
	fd2=open("efg",O_WRONLY);
	 for(int i=0;i<1000;i++)
	 {	
		
		
		read(fd1,&c,sizeof(c));
		printf("%s  %d\n", (char *)(ptr+c),c/8);
		sprintf(ptr+c,"%s",w1);

		d=c;
		write(fd2,&d,sizeof(d));
		usleep(100000);
	 }

	 close(fd1);
	 close(fd2);
	

	/* remove the shared memory segment */
	if (shm_unlink(name) == -1) {
		printf("Error removing %s\n",name);
		exit(-1);
	}

	
	// int fd1=open("FIFOpipe",O_RDONLY);
	// char a[6];
	// read(fd1,a,6);
	// printf("%s",a);
	return 0;
}
