#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>

#include "lawn.h"
#include "mole.h"

// Adding a deq to use
#include "deq.h"
#include "error.h"

// Used for multithreading
#include <pthread.h>

// static Mole produce(Lawn l) { return mole_new(l, 0, 0); }
// static void consume(Mole m) { mole_whack(m); }

// ADD DOCUMENTATION
static void *produce(void *a)
{
  void **arg = a;
  if (!arg[0] || !arg[1])
  {
    // Variables are not properly set when passing to produce
    ERROR("Struct is not assembled properly");
  }
  Deq q = (Deq)arg[0];
  Lawn l = (Lawn)arg[1];
  deq_tail_put(q, mole_new(l, 0, 0));
  return 0;
}

// ADD DOCUMENTATION
static void *consume(void *a)
{
  if (!a)
  {
    ERROR("Invalid passing of deq");
  }
  Deq q = (Deq)a;
  mole_whack(deq_head_get(q));
  return 0;
}

// DOCUMENTATION
void multicreateproduce(int n, pthread_t **producers, void *mp)
{
  for (int i = 0; i < n; i++)
  {
    // MT variant to produce
    pthread_create(producers[i], 0, produce, mp);
  }
}

// DOCUMENTATION
void multicreateconsume(int n, pthread_t **consumers, void *deq)
{
  for (int i = 0; i < n; i++)
  {
    // MT variant to consume
    pthread_create(consumers[i], 0, consume, deq);
  }
}

// DOCUMENTATION
void multijoinproduce(int n, pthread_t **producers)
{
  // Join the threads back together
  for (int i = 0; i < n; i++)
  {
    // Wait for produce thread to finish
    pthread_join(*producers[i], 0);
  }
}

// DOCUMENTATION
void multijoinconsume(int n, pthread_t **consumers)
{
  // Join the consume threads back together
  for (int i = 0; i < n; i++)
  {
    // Wait for consume thread to finish
    pthread_join(*consumers[i], 0);
  }
}

int main()
{
  // Used for the produce function
  struct Moleproduce
  {
    void *deq;
    void *lawn;
  } typedef Moleproduce;

  Deq jobs = deq_new();
  srandom(time(0));
  const int n = 10;
  pthread_t producetids[n];
  pthread_t consumetids[n];
  Lawn lawn = lawn_new(0, 0);
  // for (int i = 1; i <= n; i++)

  // Create struct to send to produce function
  Moleproduce mp;
  mp.deq = jobs;
  mp.deq = lawn;

  // Execute multithreaded operations
  multicreateproduce(n, (pthread_t **)producetids, (void *)&mp);
  multicreateconsume(n, (pthread_t **)consumetids, jobs);

  multijoinproduce(n, (pthread_t **)producetids);
  multijoinconsume(n, (pthread_t **)consumetids);

  lawn_free(lawn);
  deq_del(jobs, 0);
}
