#ifndef STDLIB_H
#define STDLIB_H

#include <stddef.h>

extern void* memset(void *ptr, int, size_t);
extern void* malloc(size_t num_bytes);
extern void* calloc(size_t num_bytes);


void* memset(void *ptr, int, size_t);

#endif