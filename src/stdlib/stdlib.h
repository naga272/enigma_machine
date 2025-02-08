#ifndef STDLIB_H
#define STDLIB_H

#include <stddef.h>

void* memset(void *ptr, int, size_t);



void* malloc(size_t);   // allocazione dinamica della memoria
void* calloc(size_t);   // allocazione dinamica della memoria ma con tutti gli elementi inizializzati a 0



#endif