#include "config.h"
#include "kernel.h"
#include "idt/idt.h"
#include "stdlib/stdlib.h"
#include "video/video.h"


extern uchar bff_cmd_line[SIZE_COMMAND_SHELL];

uchar start_msg[] = "\
=============================================================\n\
|Welcome to my EnigmaOs!                                    |\n\
|author: naga272                                            |\n\
|Set a colour for your shell:                               |\n\
|  -digita 1 per un background blue and colore testo white  |\n\
|  -digita 2 per un background bianco and colore testo nero |\n\
|  -digita 3 per un background nero and colore testo bianco |\n\
=============================================================\n\
>>> number: ";


void init_shell() 
{
    print((uchar*) start_msg);
}


void kernel_main()
{
    terminal_initialize(BG_BIANCO_C_NERO);
    init_shell();
    idt_init();
    enable_interrupts();
    memset((void*) bff_cmd_line, 0, SIZE_COMMAND_SHELL);
}
