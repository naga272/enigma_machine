#ifndef ATOMIC_H
#define ATOMIC_H


#include "config.h"


typedef struct {
    i32 counter;
} atomic_t;


extern void atomic_set(atomic_t*, i32);
extern void atomic_add(atomic_t*, i32);
extern void atomic_sub(atomic_t*, i32);

extern void atomic_inc(atomic_t*);
extern void atomic_dec(atomic_t*);
extern i32 atomic_read(const atomic_t*);


void atomic_set(atomic_t*, i32);
void atomic_add(atomic_t*, i32);
void atomic_sub(atomic_t*, i32);
void atomic_inc(atomic_t*);
void atomic_dec(atomic_t*);
i32 atomic_read(const atomic_t*);

#endif
