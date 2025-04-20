#include "stdlib/stdlib.h"

void* current_address = (void*) (0x1000000);


void* memset(void *ptr, int c, size_t n)
{
    char *ptr_t = (char*) ptr;

    for (size_t i = 0; i < n; i++) {
        ptr_t[i] = (char) c;  
    } 

    return ptr;
}
