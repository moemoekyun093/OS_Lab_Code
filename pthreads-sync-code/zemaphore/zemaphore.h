#include <pthread.h>

typedef struct zemaphore {
    int counter;
    pthread_mutex_t lock;
    pthread_cond_t mycond;

} zem_t;

void zem_init(zem_t *, int);
void zem_up(zem_t *);
void zem_down(zem_t *);
