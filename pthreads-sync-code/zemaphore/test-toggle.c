#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <string.h>
#include <errno.h>
#include <signal.h>
#include <wait.h>
#include <pthread.h>
#include "zemaphore.h"

#define NUM_THREADS 3
#define NUM_ITER 10

zem_t s1;
zem_t s2;
zem_t s3;
int curr_done=0;

void *justprint(void *data)
{
  int thread_id = *((int *)data);

  

  for(int i=0; i < NUM_ITER; i++)
    {
      if(i==0 && thread_id==0)
        {
          printf("This is thread %d\n", thread_id);
          zem_up(&s1);
          curr_done=1;
          continue;
        }
      if(thread_id==1)
        {
          zem_down(&s1);
           printf("This is thread %d\n", thread_id);
          zem_up(&s2);
        }
        if(thread_id==2)
        {
          zem_down(&s2);
           printf("This is thread %d\n", thread_id);
          zem_up(&s3);
        }
        if(thread_id==0)
        {
          zem_down(&s3);
           printf("This is thread %d\n", thread_id);
          zem_up(&s1);
        }
      // printf("This is thread %d\n", thread_id);
    }
  return 0;
}

int main(int argc, char *argv[])
{

  pthread_t mythreads[NUM_THREADS];
  int mythread_id[NUM_THREADS];

  zem_init(&s1,0);
  zem_init(&s2,0);
  zem_init(&s3,0);
  
  for(int i =0; i < NUM_THREADS; i++)
    {
      mythread_id[i] = i;
      pthread_create(&mythreads[i], NULL, justprint, (void *)&mythread_id[i]);
    }
  
  for(int i =0; i < NUM_THREADS; i++)
    {
      pthread_join(mythreads[i], NULL);
    }
  
  return 0;
}
