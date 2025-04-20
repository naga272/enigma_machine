#include "string/string.h"

unsigned char* strcat(unsigned char* ptr1, size_t size_ptr1, unsigned char* ptr2)
{
    for (size_t i = 0; i < size_ptr1; i++)
        ptr1[i] = ptr2[i];
    
    return ptr1;
}