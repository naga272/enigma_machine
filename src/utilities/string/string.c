#include "utilities/string/string.h"


MODULE_LICENSE("GPL-3.0");
MODULE_AUTHOR("naga272");
MODULE_DESCRIPTION("permette la gestione elementare di stringhe e caratteri");


O3 void *memmove(void *dest, const void *src, u32 n)
{
    uchar *d = dest;
    const uchar *s = src;

    if (d < s) {
        for (u32 i = 0; i < n; i++)
            d[i] = s[i];
    } else {
        for (u32 i = n; i > 0; i--)
            d[i - 1] = s[i - 1];
    }

    return dest;
}


O3 i32 tonumericdigit(char c)
{
    return c - 48;
}


i8 isdigit(char c)
{
    return c >= 48 && c <= 57;
}


O3 char tolower(char c)
{
    return (c >= 65 && c <= 90)? c + 32 : c;
}


O3 uchar* strcat(uchar* ptr1, size_t size_ptr1, uchar* ptr2)
{
    // mov ptr1, ptr2
    for (size_t i = 0; i < size_ptr1; i++)
        ptr1[i] = ptr2[i];

    return ptr1;
}


O3 i32 istrncmp(const char* s1, const char* s2, u32 n)
{
    // ignora differenze tra maiuscole e minuscole
    uchar u1, u2;
    while (n-- > 0) {
        u1 = (uchar) *s1++;
        u2 = (uchar) *s2++;

        if (u1 != u2 && tolower(u1) != tolower(u2))
            return u1 - u2;

        if (u1 == '\0')
            return 0;
    }

    return 0;
}


i32 strncmp(const char* str1, const char* str2, i32 n)
{
    uchar u1, u2;

    while (n-- > 0) {
        u1 = (uchar)*str1++;
        u2 = (uchar)*str2++;

        if (u1 != u2)
            return u1 - u2;
    
        if (u1 == '\0')
            return 0;
    }

    return 0;
}


u8 strcmp(const uchar* a, const uchar* b)
{
    // per i miei scopi non mi serve sapere se una stringa e maggiore dell'altra etc...
    // voglio sapere solo se sono uguali (1) oppure no (0)

    while (*a && *b) {
        if (*a != *b)
            return 0;
        a++;
        b++;
    }

    // se entrambi hanno finito anche i char, allora restituisce 1
    return (*a == '\0' && *b == '\0');
}


O3 char* itoa(i32 value, char* buf)
{
    // int to array (inverso di atoi)
    char* p = buf;
    i32 sign = value;

    if (value == 0) {
        *p++ = '0';
        *p = 0;
        return buf;
    }

    if (value < 0)
        value = -value;

    while (value) {
        *p++ = '0' + (value % 10);
        value /= 10;
    }

    if (sign < 0)
        *p++ = '-';

    *p = 0;

    // reverse (last to first)
    for (char* q = buf, *r = p - 1; q < r; q++, r--) {
        char tmp = *q;
        *q = *r;
        *r = tmp;
    }

    return buf;
}


O3 i32 strnlen_terminator(const char* str, u32 max, char terminator)
{
    i32 idx = 0;
    for (idx = 0; idx < max; idx++)
        if (str[idx] == '\0' || str[idx] == terminator)
            break;
    
    return idx;
}


O3 size_t strnlen(const char* string, size_t max_size)
{
    size_t idx = 0;

    while (string[idx] != '\0' && idx < max_size)
        idx++;

    return idx;
}


O3 size_t strlen(const char* string)
{
    size_t idx = 0;

    while (string[idx] != '\0')
        idx++;

    return idx;
}


O3 i32 memcmp(void* s1, void* s2, i32 count)
{
    char* c1 = s1;
    char* c2 = s2;

    while(count-- > 0) {
        if (*c1++ != *c2++)
            return c1[-1] < c2[-1] ? -1 : 1;
    }

    return 0;
}


O3 char* strcpy(char* dest, const char* src)
{
    char* dest_base = dest;
    while (*src != 0) {
        *dest = *src;
        dest++;
        src++;
    }

    *dest = 0;
    return dest_base;
}


O3 void* memcpy(void* dest, void* src, i32 len)
{
    char *d = dest;
    char *s = src;

    while (len--)
        *d++ = *s++;

    return dest;
}


O3 char* strdup(char* str)
{
    size_t idx = strlen(str);
    char* ptr = kcalloc(idx);

    if (!ptr)
        return ptr;

    return (char*) memcpy(ptr, str, idx);
}


u8 starts_with(char* str, char* prefix)
{
    while(*prefix) {
        if (*str != *prefix)
            return 0;

        str++;
        prefix++;
    }

    return 1;
}


size_t common_prefix(char* a, char* b)
{
    size_t i = 0;

    while (a[i] && b[i] && a[i] == b[i])
        i++;

    return i;
}
