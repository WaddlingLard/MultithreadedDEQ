#ifndef MTQ_H
#define MTQ_H

#include "mole.h"

typedef void *Mtq;

extern Mtq mtq_new();
extern void mtq_tail_put(Mtq mtq, Mole mole);
extern Mole mtq_head_get(Mtq mtq);
extern void mtq_del(Mtq mtq);

#endif