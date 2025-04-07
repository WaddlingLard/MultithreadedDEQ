#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#include "deq.h"
#include "mtq.h"
#include "error.h"
#include "mole.h"

typedef struct
{
    pthread_mutex_t readlock, writelock;
    // Will add condition variables later
    pthread_cond_t condition;
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

    // Initialize the mutex locks and condition
    pthread_mutex_init(&rep->readlock, NULL);
    pthread_mutex_init(&rep->writelock, NULL);
    pthread_cond_init(&rep->condition, NULL);

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
    fprintf(stdout, "Grabbing a mole from the mtq!\n");
    // Grab the Mole at the head of the queue

    // Get the representation of the multithreaded queue
    MtqRep rep = (MtqRep)mtq;

    // Lock the mutex
    pthread_mutex_lock(&rep->readlock);

    fprintf(stdout, "Hand in cookie jar to get!\n");

    // Needs something in the mtq
    // ! logic is wrong
    while (rep->size == 0)
    {
        // Just Spin?
        // Add condition variable here
        fprintf(stdout, "Nothing is in the mtq!\n");
        // fprintf(stdout, "Size: %d, Max: %d\n", rep->size, rep->max);
        pthread_cond_wait(&rep->condition, &rep->readlock);
        fprintf(stdout, "Waiting complete!\n");
    }

    fprintf(stdout, "Size: %d, Max: %d\n", rep->size, rep->max);

    fprintf(stdout, "Grabbing item in cookie jar!\n");

    // Something is in the mtq!
    // ? I think this is accessing it properly
    Mole mole = deq_head_get(rep->deq);

    // Adjust size
    rep->size = rep->size - 1;

    // Unlock and add signaling (W.I.P)
    pthread_mutex_unlock(&rep->readlock);
    pthread_cond_signal(&rep->condition);

    // Return the acquired mole
    return mole;
}

// Put

// DOCUMENTATION
extern void mtq_tail_put(Mtq mtq, Mole mole)
{

    fprintf(stdout, "Starting to add a Mole!\n");
    // Put the Mole at the tail of the queue

    // Get the representation of the multithreaded queue
    MtqRep rep = (MtqRep)mtq;

    // Lock the mutex
    pthread_mutex_lock(&rep->writelock);

    fprintf(stdout, "Hand in cookie jar (PUTTING)!\n");

    // Has it hit the limit?
    // ! logic error
    while (!(rep->zeroflag) || rep->size > rep->max)
    {
        // Just Spin?
        // Add condition variable here
        fprintf(stdout, "Cannot add! Statement 1: %d, 2: %d\n", !(rep->zeroflag), rep->size < rep->max);
        pthread_cond_wait(&rep->condition, &rep->writelock);
    }

    fprintf(stdout, "About to add, current size: %d, max: %d\n", rep->size, rep->max);

    // Able to put something on the mtq
    deq_tail_put(rep->deq, mole);

    // Adjust size
    rep->size = rep->size + 1;

    // Unlock and add signaling (W.I.P)
    pthread_mutex_unlock(&rep->writelock);
    pthread_cond_signal(&rep->condition);

    // Successful operation!
    return;
}

// Print for debug?
