#ifndef MALLOC_H
#define MALLOC_H

#include <stddef.h>

extern void kfree(void* ptr);
void kfree(void* ptr);

extern void* kmalloc(size_t size);
extern void* kcalloc(size_t size);
extern void* krealloc(void* old_ptr, size_t old_size, size_t new_size);

void* kmalloc(size_t size);
void* kcalloc(size_t size);
void* krealloc(void* old_ptr, size_t old_size, size_t new_size);

#endif
