#include "utilities/video/kprintf.h"
#include "utilities/memory/heap/malloc.h"
#include "utilities/string/string.h"
#include <stdarg.h>


// void terminal_writechar(uchar, char);
volatile i8 lvl_info_support = 4;


volatile uchar kprintd_color[4] = {
    ROSSO,
    GIALLO,
    VERDE,
    BIANCO
};


void putchar(char c)
{
    terminal_writechar((uchar) c, actual_color_terminal);
}


O3 char* int_to_bin(i32 num, char* c)
{
    /* 
    * dato @num intero inserisco quel numero in formato binario
    * all'interno dell'array puntato da @c
    * */
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


O3 static inline ainline void gestisci_segnaposto(char segnaposto, va_list* args_list, i32* len)
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


O3 i32 kprintd(char* fmt)
{
    /*
    * kernel print debug
    * i primi char devono essere formattati in questo modo:
    * "<n>resto del messaggio"
    * La funzione va a prendere n (numero intero) per scegliere il colore da usare
    * per stampare i char a schermo (vedi config.h).
    * In caso di mal formattazione della stringa viene stampato a schermo un allert.
    * Se n possiede un valore uguale o inferio di lvl_info_support il messaggio
    * viene considerato e stampato, altrimento viene ignorato
    */
    if ((fmt[0] != '<' && fmt[2] != '>') || !isdigit(fmt[1]))
        return kprintd(KWARN "\nkprintd bad formatted\n");

    u8 level_log = fmt[1] - 48;

    if (level_log < 0 && level_log > 4)
        return kprintd(KWARN "kprintd bad formatted (number error)\n");

    if (level_log > lvl_info_support)
        return 0;

    uchar tmp_col_term = actual_color_terminal;

    actual_color_terminal = kprintd_color[level_log];

    // push (rdi + 3),
    // rdi quando esce tiene sempre offset base di fmt
    print((uchar*) (fmt + 3));

    // ripristino
    actual_color_terminal = tmp_col_term;

    return 0;
}
