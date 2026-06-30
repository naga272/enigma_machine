#include "utilities/video/kprintf.h"
#include "utilities/memory/heap/malloc.h"
#include <stdarg.h>


MODULE_LICENSE("GPL-3.0");
MODULE_AUTHOR("naga272");
MODULE_DESCRIPTION("stampa a schermo di stringhe formattate");


// void terminal_writechar(uchar, char);


void putchar(char c) {
    terminal_writechar((uchar) c, actual_color_terminal);
}


O3 char* int_to_bin(i32 num, char* c)
{
    if (num == 0) {
        c[0] = '0';
        return c;
    }

    i32 temp = num;
    size_t bits = 0;

    while (temp) {
        bits++;
        temp >>= 1;
    }

    c[bits] = '\0';

    while (num) {
        bits--;
        c[bits] = (num & 1) ? '1' : '0';
        num >>= 1;
    }

    return c;
}


O3 ainline void gestisci_segnaposto(char segnaposto, va_list* args_list, i32* len)
{
    switch (segnaposto) {
        case 's': {
            // caso stampa stringa
            char* str = va_arg(*args_list, char*);
            
            if (!str)
                str = "(null)";

            i32 j;
            for (j = 0; str[j] != '\0'; j++) {
                putchar(str[j]);
                (*len)++;
            }
            return;
        }
        case 'i': {
            // caso stampa integer
            i32 integer = va_arg(*args_list, i32);
            if (integer == 0) {
                print((uchar*) "0");
                return;
            }
            print_num_hex_no_pad(integer);
            return;
        }
        case 'c': {
            // caso carattere
            i32 c = va_arg(*args_list, i32);
            putchar((char) c);
            return;
        }
        case 'p': {
            // caso bisogna stampare ptr
            // il mio kernel e' a 32 bit,
            // mi e' sufficiente usare il tipo i32
            size_t ptr_addr = (size_t) va_arg(*args_list, i32);
            print_hex(ptr_addr);
            return;
        }
        case 'b': {
            char c[11];

            i32 number = va_arg(*args_list, i32);
            int_to_bin(number, c);
            print((uchar*) c);

            kfree(c);
        }
        default:
            return;
    }
}


O3 i32 kprintf(const char* fmt, ...)
{
    i32 len = 0;
    va_list args_list;
    va_start(args_list, fmt);

    for (i32 i = 0; fmt[i] != '\0'; i++) {

        if (fmt[i] == '%') {
            i++;
            gestisci_segnaposto(fmt[i], &args_list, &len);
        } else {
            putchar(fmt[i]);
            len++;
        }
    }

    va_end(args_list);
    return len;
}
