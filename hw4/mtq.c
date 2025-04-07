#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#include "deq.h"
#include "mtq.h"
#include "error.h"

typedef struct
{
    pthread_mutex_t mutexlock;
    // Will add condition variables later
    // pthread_cond_t condition;
    Deq *deq;
    // Keep track of the multihreaded queue a different way
    int size;
} *Mtq;

// Functions need to create
// Init

// DOCUMENTATION
extern Mtq newMtq()
{
    // Create the multithreaded queue
    Mtq rep = (Mtq)malloc(sizeof *rep);
    if (!rep)
    {
        // Memory failure
        ERROR("ERROR: Malloc failed!");
    }

    // Initialize the mutex lock
    pthread_mutex_init(&rep->mutexlock, 0);

    // Add deq and starting size
    rep->deq = deq_new();
    if (!rep->deq)
    {
        // Deq instantiation failure
        ERROR("ERROR: Creating deq failed!");
    }
    rep->size = 0;

    // Return the deq
    return rep;
}

// Destroy
// DOCUMENTATION
extern void delMtq()
{
}

// Get
// Put
// Print for debug?
