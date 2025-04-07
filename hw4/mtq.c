#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#include "deq.h"
#include "mtq.h"
#include "error.h"
#include "mole.h"

typedef struct
{
    pthread_mutex_t mutexlock;
    // Will add condition variables later
    // pthread_cond_t condition;
    Deq *deq;
    // Keep track of the multihreaded queue a different way
    int size;
    int max;
    int zeroflag;
} *MtqRep;

// Functions need to create
// Init

// DOCUMENTATION
extern Mtq mtq_new(int max)
{
    // Create the multithreaded queue
    MtqRep rep = (MtqRep)malloc(sizeof *rep);
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

    // Initialize the max size of the mtq
    // Zero means limit will be never hit (handled later)
    if (rep->max == 0)
    {
        // Mark zero flag
        rep->zeroflag = 1;
    }
    rep->max = max;

    // Return the deq
    return rep;
}

// Destroy

// DOCUMENTATION
extern void mtq_del(Mtq mtq)
{
    // Tear apart the multithreaded queue
    MtqRep rep = (MtqRep)mtq;

    // NEED TO DO MORE

    // Free the deq
    // deq_del(rep->deq);

    // Free the mtq
    free(mtq);
}

// Get

// DOCUMENTATION
extern Mole mtq_head_get(Mtq mtq)
{
    // Grab the Mole at the head of the queue

    // Get the representation of the multithreaded queue
    MtqRep rep = (MtqRep)mtq;

    // Lock the mutex
    pthread_mutex_lock(&rep->mutexlock);

    // Needs something in the mtq
    while (rep->size != 0)
    {
        // Just Spin?
        // Add condition variable here
    }

    // Something is in the mtq!
    // ? I think this is accessing it properly
    Mole mole = deq_head_get(rep->deq);

    // Unlock and add signaling (W.I.P)
    pthread_mutex_unlock(&rep->mutexlock);

    // Return the acquired mole
    return mole;
}

// Put

// DOCUMENTATION
extern void mtq_tail_put(Mtq mtq, Mole mole)
{
    // Put the Mole at the tail of the queue

    // Get the representation of the multithreaded queue
    MtqRep rep = (MtqRep)mtq;

    // Lock the mutex
    pthread_mutex_lock(&rep->mutexlock);

    // Has it hit the limit?
    while (!(rep->zeroflag) || rep->size > rep->max)
    {
        // Just Spin?
        // Add condition variable here
    }

    // Able to put something on the mtq
    deq_tail_put(rep->deq, mole);

    // Adjust size
    rep->size = rep->size + 1;

    // Unlock and add signaling (W.I.P)
    pthread_mutex_unlock(&rep->mutexlock);

    // Successful operation!
    return;
}

// Print for debug?
