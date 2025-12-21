#include "stdlib/stdlib.h"


// start heap memory
#define BASE_PTR_HEAP (void*) 0x100000
static void* current_address_top = BASE_PTR_HEAP;


void* memset(void *ptr, int c, size_t n)
{
    char *p = (char *) ptr;
    for (size_t i = 0; i < n; i++)
        p[i] = (char)c;

    return ptr;
}


static inline void* allocWaterMark(size_t num_bytes)
{
    /*
    *   Allocazione heap con metodo WaterMark
    **/
    void* base_alloc = current_address_top;
    current_address_top += num_bytes;
    return base_alloc;
}


void* malloc(size_t num_bytes)
{
    return allocWaterMark(num_bytes);
}


void* calloc(size_t num_bytes)
{
    void* base_addr = malloc(num_bytes);
    memset(base_addr, 0, num_bytes);
    return base_addr;
}
