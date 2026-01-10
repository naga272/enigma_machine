#ifndef MALLOC_H
#define MALLOC_H

extern void kfree(void*);
void kfree(void*);

extern void* kmalloc(size_t);
extern void* kcalloc(size_t);

void* kmalloc(size_t);
void* kcalloc(size_t);

#endif
