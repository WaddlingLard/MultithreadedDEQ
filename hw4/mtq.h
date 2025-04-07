#ifndef MTQ_H
#define MTQ_H

typedef void *Mtq;

extern Mtq newMtq();
extern void putMtq();
extern Data getMtq();
extern void delMtq();

#endif