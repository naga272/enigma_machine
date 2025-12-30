#include "utilities/string/string.h"

unsigned char* strcat(unsigned char* ptr1, size_t size_ptr1, unsigned char* ptr2)
{
    for (size_t i = 0; i < size_ptr1; i++)
        ptr1[i] = ptr2[i];
    
    return ptr1;
}


char* itoa(int value, char* buf)
{
    char* p = buf;
    int sign = value;

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

    // reverse
    for (char* q = buf, *r = p - 1; q < r; q++, r--) {
        char tmp = *q;
        *q = *r;
        *r = tmp;
    }

    return buf;
}
