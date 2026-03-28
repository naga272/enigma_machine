#ifndef STRING_H
#define STRING_H

#include <stddef.h>
#include "config.h"

extern char* itoa(int value, char* buf);
extern u8 strcmp(const uchar* ptr1, const uchar* ptr2);
extern uchar* strcat(uchar* ptr1, size_t size_ptr1, uchar* ptr2);
extern size_t strnlen(const char* string, size_t max_size);
extern size_t strlen(const char* string);
extern i32 tonumericdigit(char c);
extern i8 isdigit(char c);
extern i32 memcmp(void* addr, void* tocmp, size_t len);

char* itoa(int value, char* buf);
u8 strcmp(const uchar* a, const uchar* b);
uchar* strcat(uchar* ptr1, size_t size_ptr1, uchar* ptr2);
size_t strnlen(const char* string, size_t max_size);
size_t strlen(const char* string);
i32 tonumericdigit(char c);
i8 isdigit(char c);
i32 memcmp(void* addr, void* tocmp, size_t len);

#endif