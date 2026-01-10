#ifndef STDLIB_H
#define STDLIB_H

#include <stddef.h>

extern void* memset(void *ptr, int, size_t);

#ifdef WATER_MARK_ALG
extern void* malloc(size_t num_bytes);
extern void* calloc(size_t num_bytes);
#endif

void* memset(void *ptr, int, size_t);

#endif