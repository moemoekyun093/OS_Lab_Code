#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define NUM_THREADS 10
int curr_held=0;
pthread_mutex_t lock; // Declare a mutex
pthread_cond_t *mycond;
int arr[NUM_THREADS];
int done =0;


void *thread_function(void *arg) {

        int f=(int)arg;
        while(1)
        {
        pthread_mutex_lock(&lock);
        if(curr_held==0 && f==0)
        {
            printf("I am thread %d\n",f);
            arr[f+1]=1;
            pthread_cond_signal(&mycond[f+1]);
            curr_held=1;
            pthread_mutex_unlock(&lock);
            continue;
        }
        
            while(arr[f] != 1)
                {
                    int d=pthread_cond_wait(&mycond[f],&lock);
                    // printf("I am woken up %d\n",d);
                }
            arr[f]=0;
        
        printf("I am thread %d\n",f);
            // printf("%d\n",arr[f+1]);
            arr[(f+1)%NUM_THREADS]=1;
            pthread_cond_signal(&mycond[(f+1)%NUM_THREADS]);
            // printf("wake up status%d\n",c);
        
        pthread_mutex_unlock(&lock);
        }
    
    pthread_exit(NULL);
}

int main() {
    pthread_t threads[NUM_THREADS];
    int rc;
    long t;
    mycond=malloc(sizeof(pthread_cond_t)*NUM_THREADS);

    for(int i=0;i<NUM_THREADS;i++)
    {
        arr[i]=0;
    }
    
    for (t = 0; t < NUM_THREADS; t++) {
        // printf("Creating thread %ld\n", t);
        rc = pthread_create(&threads[t], NULL, thread_function, (void *)t);
        if (rc) {
            printf("ERROR: return code from pthread_create() is %d\n", rc);
            exit(-1);
        }
    }

    // Wait for all threads to finish
    for (t = 0; t < NUM_THREADS; t++) {
        pthread_join(threads[t], NULL);
    }
    // pthread_mutex_lock(&lock);
    //     while(done == 0)
    //         pthread_cond_wait(&mycond,&lock);
    // pthread_mutex_unlock(&lock);

    printf("All threads have completed.\n");
    // printf("%d",c);
    pthread_exit(NULL);
}
