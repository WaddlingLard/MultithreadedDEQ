#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>

#include "lawn.h"
#include "mole.h"

// Adding a deq to use
#include "deq.h"

static Mole produce(Lawn l) { return mole_new(l, 0, 0); }
static void consume(Mole m) { mole_whack(m); }

int main()
{
  Deq jobs = deq_new();
  srandom(time(0));
  const int n = 10;
  Lawn lawn = lawn_new(0, 0);
  for (int i = 1; i <= n; i++)
  {
    // Put the Mole at the front of the deq
    deq_head_put(jobs, produce(lawn));

    // Consume the Mole by pulling it off the deq though LIFO fashion
    consume(deq_tail_get(jobs));
  }
  lawn_free(lawn);
  deq_del(jobs, 0);
}
