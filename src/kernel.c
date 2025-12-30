#include "config.h"
#include "kernel.h"
#include "utilities/idt/idt.h"
#include "utilities/stdlib/stdlib.h"
#include "utilities/video/video.h"
#include "utilities/idt/body_int/slave/rtc_orologio.h"
#include "utilities/idt/body_int/master/input_keyboard.h"


uchar start_msg[] = "\
=============================================================\n\
|Welcome to my EnigmaOs!                                    |\n\
|author: naga272                                            |\n\
|Set a colour for your shell:                               |\n\
|  -digita 1 per un background blue and colore testo white  |\n\
|  -digita 2 per un background bianco and colore testo nero |\n\
|  -digita 3 per un background nero and colore testo bianco |\n\
|  -digita 4 per un background nero and colore testo verde  |\n\
=============================================================\n\
>>> inserisci qui il numero: ";


// struct che contiene .sec, .min, .ore
struct tempo_t t;

// formattazione orario in prima riga
uchar time_formatted[9];

// usato in modo provvisorio per aggiornare il timer (finche non capisco il problema
// in IRQ#8)
u8 first_rendering = 1;


O3 void init_shell()
{
    terminal_initialize(BG_BIANCO_C_NERO);
    print((uchar*) start_msg);
}


O3 static inline void render_time()
{
    if (!t.rtc_dirty && !first_rendering)
        return;

    if (tmp_char_container)
        return;

    rtc_get_time(&t);
    // t = (struct tempo_t*) get_tempo();

    u8 tmp_terminal_col = terminal_col;
    u8 tmp_terminal_row = terminal_row;

    terminal_col = VGA_WIDTH - 9;
    terminal_row = 0;

    time_formatted[0] = '0' + (t.ore / 10);
    time_formatted[1] = '0' + (t.ore % 10);
    time_formatted[2] = ':';
    
    time_formatted[3] = '0' + (t.min / 10);
    time_formatted[4] = '0' + (t.min % 10);
    time_formatted[5] = ':';
    
    time_formatted[6] = '0' + (t.sec / 10);
    time_formatted[7] = '0' + (t.sec % 10);
    time_formatted[8] = '\0';

    print((uchar*) time_formatted);

    terminal_row = tmp_terminal_row;
    terminal_col = tmp_terminal_col;

    update_cursor_on_x_y_pos(terminal_row, terminal_col);

    set_rtc_dirty(&t, 0);
    first_rendering = 0;
}


O3 static inline void main()
{
    if (FASE_SETUP) {
        try_the_setup(tmp_char_container);
        return;
    }
    
    gestisci_char_to_write(tmp_char_container);
    tmp_char_container = 0;

    render_time();

    /*
    === DIVISIONE PER ZERO TRIGGERA LA Blue Screen of the dead ===
    */

    
    asm volatile (
        "xor %%edx, %%edx\n"
        "mov $1, %%eax\n"
        "div %%edx\n"
        :
        :
        : "eax", "edx"
    );
    
    asm volatile("hlt");
}


O3 void kernel_main()
{
    disable_interrupts();
    idt_init();
    enable_interrupts();
    init_shell();

    asm volatile("sti");

    while (1)
        main();
}
