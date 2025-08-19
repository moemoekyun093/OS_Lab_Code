#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t condition = PTHREAD_COND_INITIALIZER;
int child_done = 0;

void* child_thread(void* arg) {
    // Do some work
    printf("Child thread is doing some work...\n");
    
    // Simulating work by sleeping for 3 seconds
    // sleep(1);
    
    // Notify parent that child is done
    pthread_mutex_lock(&mutex);
    child_done = 1;
    pthread_cond_signal(&condition);
    printf("hehe\n");
    pthread_mutex_unlock(&mutex);
    
    pthread_exit(NULL);
}

void* parent_thread(void* arg) {
    // Parent waits for child to finish
    // pthread_mutex_lock(&mutex);
    pthread_cond_wait(&condition, &mutex);
    printf("Parent has entered\n");
    // pthread_yield(NULL);
    
        pthread_cond_wait(&condition, &mutex); // at end of wait_cond I'm assuming it will release the lock again
    
    // pthread_mutex_unlock(&mutex);
    
    printf("Parent: Child has finished its work.\n");
    
    pthread_exit(NULL);
}

int main() {
    pthread_t parent, child;
    
    // Create parent thread
    pthread_create(&parent, NULL, parent_thread, NULL);
    
    // Create child thread
    pthread_create(&child, NULL, child_thread, NULL);
    
    // Join parent thread
    pthread_join(child, NULL);
    pthread_join(parent, NULL);
    
    // Join child thread
    
    
    return 0;
}
