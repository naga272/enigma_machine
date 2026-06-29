#ifndef STRING_H
#define STRING_H

#include <stddef.h>
#include "config.h"
#include "utilities/memory/heap/malloc.h"

extern char* itoa(i32 value, char* buf);
extern u8 strcmp(const uchar* ptr1, const uchar* ptr2);
extern uchar* strcat(uchar* ptr1, size_t size_ptr1, uchar* ptr2);
extern size_t strnlen(const char* string, size_t max_size);
extern size_t strlen(const char* string);
extern i32 tonumericdigit(char c);
extern i8 isdigit(char c);
extern i32 memcmp(void* s1, void* s2, i32 count);
extern char* strcpy(char* dest, const char* src);
extern i32 strncmp(const char* str1, const char* str2, i32 n);
extern i32 strnlen_terminator(const char* str, u32 max, char terminator);
extern void* memcpy(void* dest, void* src, i32 len);
extern i32 istrncmp(const char* s1, const char* s2, u32 n);
extern char* strdup(char*);
extern void* memmove(void *dest, const void *src, u32 n);
extern u8 starts_with(char* str, char* prefix);
extern size_t common_prefix(char* a, char* b);

u8 starts_with(char* str, char* prefix);
size_t common_prefix(char* a, char* b);

// richiesto dal compilatore usando il flag O3 per certe funzioni
void* memmove(void *dest, const void *src, u32 n);

char* strdup(char*);
char* itoa(i32 value, char* buf);
u8 strcmp(const uchar* a, const uchar* b);
uchar* strcat(uchar* ptr1, size_t size_ptr1, uchar* ptr2);
size_t strnlen(const char* string, size_t max_size);
size_t strlen(const char* string);
i32 tonumericdigit(char c);
i8 isdigit(char c);
i32 memcmp(void* s1, void* s2, i32 count);
char* strcpy(char* dest, const char* src);
i32 strncmp(const char* str1, const char* str2, i32 n);
i32 strnlen_terminator(const char* str, u32 max, char terminator);
void* memcpy(void* dest, void* src, i32 len);
i32 istrncmp(const char* s1, const char* s2, u32 n);

#endif