#include "config.h"
#include "kernel.h"
#include "idt/idt.h"
#include "stdlib/stdlib.h"
#include "video/video.h"


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


O3 void init_shell() 
{
    terminal_initialize(BG_BIANCO_C_NERO);
    print((uchar*) start_msg);
}


O3 void kernel_main()
{
    idt_init();
    enable_interrupts();
    init_shell();

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
    
}
