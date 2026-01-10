#include "utilities/string/string.h"


O3 uchar* strcat(uchar* ptr1, size_t size_ptr1, uchar* ptr2)
{
    // mov ptr1, ptr2
    for (size_t i = 0; i < size_ptr1; i++)
        ptr1[i] = ptr2[i];

    return ptr1;
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


O3 char* itoa(int value, char* buf)
{
    // int to array (inverso di atoi)
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

    // reverse (last to first)
    for (char* q = buf, *r = p - 1; q < r; q++, r--) {
        char tmp = *q;
        *q = *r;
        *r = tmp;
    }

    return buf;
}
