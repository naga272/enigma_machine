#include "utilities/video/kprintf.h"
#include <stdarg.h>

// void terminal_writechar(uchar, char);


void putchar(char c) {
    terminal_writechar((uchar) c, actual_color_terminal);
}


O3 i32 kprintf(const char* fmt, ...)
{
    i32 len = 0;
    va_list args_list;
    va_start(args_list, fmt);

    for (i32 i = 0; fmt[i] != '\0'; i++) {

        if (fmt[i] == '%') {
            i++;

            if (fmt[i] == 's') {
                // case argument char*
                char* str = va_arg(args_list, char*);
                i32 j;
                for (j = 0; str[j] != '\0'; j++) {
                    putchar(str[j]);
                    len++;
                }

            } else if (fmt[i] == 'i') {

                // case argument integer
                i32 integer = va_arg(args_list, i32);
                print_hex(integer);

            }

        } else {
            putchar(fmt[i]);
            len++;
        }
    }

    va_end(args_list);
    return len;
}
