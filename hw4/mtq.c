/**
 * A multithreaded queue with several thread safe operations.
 *
 * @author Brian Wu
 * @version 1.0
 */

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

/**
 * Makes a new Multithreaded queue
 * @param max: the maximum amount of elements that can be in a queue at a given time
 * @return Mtq: New multithreaded queue
 */
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
    if (max == 0)
    {
        // Mark zero flag
        rep->zeroflag = 1;
    }
    else
    {
        rep->zeroflag = 0;
    }
    rep->max = max;

    // Return the deq
    return rep;
}

/**
 * Deletes the multithreaded queue
 * @param Mtq: Multithreaded queue
 */
extern void mtq_del(Mtq mtq)
{
    // Tear apart the multithreaded queue
    MtqRep rep = (MtqRep)mtq;

    pthread_cond_destroy(&rep->condition);
    pthread_mutex_destroy(&rep->readlock);
    pthread_mutex_destroy(&rep->writelock);

    // Free the deq
    deq_del(rep->deq, 0);

    // Free the mtq
    free(mtq);
}

/**
 * Get the Mole at the head of the multithreaded queue
 * @param Mtq: Multithreaded queue
 * @return Mole: the mole that has been in the queue for the longest
 */
extern Mole mtq_head_get(Mtq mtq)
{

    // Grab the Mole at the head of the queue

    // Get the representation of the multithreaded queue
    MtqRep rep = (MtqRep)mtq;

    // Lock the mutex
    pthread_mutex_lock(&rep->readlock);

    // Needs something in the mtq
    // ! logic is wrong
    while (rep->size == 0)
    {
        // Just Spin?
        // Add condition variable here
        pthread_cond_wait(&rep->condition, &rep->readlock);
    }

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

/**
 * Put an element at the end of the mtq via the tail (for queue purposes)
 * @param Mtq: Multithread queue
 * @param Mole: Mole element
 */
extern void mtq_tail_put(Mtq mtq, Mole mole)
{

    // Put the Mole at the tail of the queue

    // Get the representation of the multithreaded queue
    MtqRep rep = (MtqRep)mtq;

    // Lock the mutex
    pthread_mutex_lock(&rep->writelock);

    // Has it hit the limit?
    while (!(rep->zeroflag) && rep->size > rep->max)
    {
        // Add condition variable here
        pthread_cond_wait(&rep->condition, &rep->writelock);
    }

    // Able to put something on the mtq
    deq_tail_put(rep->deq, mole);

    // Adjust size
    rep->size = rep->size + 1;

    // Unlock and add signaling
    pthread_mutex_unlock(&rep->writelock);
    pthread_cond_signal(&rep->condition);

    // Successful operation!
    return;
}
