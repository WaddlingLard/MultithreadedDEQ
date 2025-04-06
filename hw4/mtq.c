#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#include "deq.h"

typedef struct
{
    pthread_mutex_t mutexlock;
    // Will add condition variables later
    // pthread_cond_t condition;
    Deq *deq;
} *Mtq;
