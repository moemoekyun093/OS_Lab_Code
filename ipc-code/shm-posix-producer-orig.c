/**
 * Simple program demonstrating shared memory in POSIX systems.
 *
 * This is the producer process that writes to the shared memory region.
 *
 * Figure 3.17
 *
 * @author Silberschatz, Galvin, and Gagne
 * Operating System Concepts  - Ninth Edition
 * Copyright John Wiley & Sons - 2013
 */

#include <stddef.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <sys/shm.h>
#include <sys/stat.h>
#include <sys/mman.h>

int main()
{
	const int SIZE = 4096;
	const char *name = "OS";
	const char *message0= "Studying ";
	const char *message1= "Operating Systems ";
	const char *message2= "Is Fun!";

	int shm_fd;
	void *ptr;

	// /* create the shared memory segment */
	shm_fd = shm_open(name, O_CREAT | O_RDWR, 0666);

	// /* configure the size of the shared memory segment */
	ftruncate(shm_fd,SIZE);

	// /* now map the shared memory segment in the address space of the process */
	ptr = mmap(0,SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, shm_fd, 0);
	if (ptr == MAP_FAILED) {
		printf("Map failed\n");
		return -1;
	}
	// ptr=fdopen(shm_fd,"w");
	// fprintf(ptr,"hehe");
	/**
	 * Now write to the shared memory region.
 	 *
	 * Note we must increment the value of ptr after each write.
	 */
	 
	 const char* w1= "freeeee";
	 const char* w2= "OSisFUN";
	 int c=0;
	 int d;
	 void* ptr1=ptr;
	//  printf("%d",SIZE/(strlen(w1)+1));
	for(int i=0;i<SIZE/(strlen(w1)+1);i++)
	 {	
		sprintf(ptr,"%s",w1);
		ptr += strlen(w1)+1;
		
	 }
	 ptr=ptr1;
	mkfifo("abc",0666);
	int fd1;
	int fd2;
	fd1=open("abc",O_WRONLY);
	fd2=open("efg",O_RDONLY);
	
	 for(int i=0;i<1000;i++)
	 {	
		
		if(i>511)
		{
			read(fd2,&d,sizeof(d));
			printf("%d\n",d);
			sprintf(ptr+d,"%s",w2);
		}
		else {
			sprintf(ptr+c,"%s",w2);
		}
		
		
		write(fd1,&c,sizeof(c));
		c+=strlen(w2)+1;
		c%=4096;



		
		

		
	 }
	 close(fd1);
	 close(fd2);



	// sprintf(ptr,"%s",message1);
	// ptr += strlen(message1);
	// sprintf(ptr,"%s",message2);
	// ptr += strlen(message2);

	// printf("S_IRWXU = %d\n", O_WRONLY);

    // int returnValue;

    // //should return 0, if we are running this program
    // //for the first time.
    // returnValue = mkfifo("FIFOpipe", 0666);

    // printf("The mkfifo() call returned %d\n", returnValue);
	// int fd=open("FIFOpipe",O_WRONLY|O_NONBLOCK);
	// write(fd,"hello",6);
    return 0;
}
