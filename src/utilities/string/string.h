#ifndef STRING_H
#define STRING_H

#include <stddef.h>
#include "config.h"

extern char* itoa(int value, char* buf);
extern u8 strcmp(const uchar* ptr1, const uchar* ptr2);
extern uchar* strcat(uchar* ptr1, size_t size_ptr1, uchar* ptr2);

char* itoa(int value, char* buf);
u8 strcmp(const uchar* a, const uchar* b);
uchar* strcat(uchar* ptr1, size_t size_ptr1, uchar* ptr2);


#endif