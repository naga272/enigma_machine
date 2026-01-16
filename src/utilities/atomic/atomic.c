#include "utilities/atomic/atomic.h"


/* ha rotto le palle la concorrenza */


void atomic_inc(atomic_t *x)
{
    // "+m"(x->v) significa che x->v e' un address in ram
    asm volatile(
        "lock incl %0"
        : "+m"(x->counter)
        :
        : "memory"
    );
}


void atomic_set(atomic_t *x, i32 val)
{
    asm volatile(
        "movl %1, %0"
        : "=m" (x->counter)
        : "r" (val)
        : "memory"
    );
}


void atomic_dec(atomic_t *x)
{
    asm volatile(
        "lock decl %0"
        : "+m" (x->counter)
        :
        : "memory"
    );
}


void atomic_add(atomic_t *x, i32 val)
{
    asm volatile(
        "lock addl %1, %0"
        : "+m"(x->counter)
        : "r"(val)
        : "memory"
    );
}


void atomic_sub(atomic_t *x, i32 val)
{
    asm volatile(
        "lock subl %1, %0"
        : "+m"(x->counter)
        : "r"(val)
        : "memory"
    );
}


i32 atomic_read(const atomic_t *x)
{
    i32 val;
    asm volatile(
        "movl %1, %0"
        : "=r"(val)
        : "m"(x->counter)
        : "memory"
    );
    return val;
}
