#include "utilities/io/io.h"
#include "utilities/video/video.h"
#include "utilities/idt/body_int/master/pit.h"
#include "utilities/idt/idt.h"


// usato in int20h_handler
u8 num_color = 0;


O3 void do_pit(uchar *msg_error, struct regs_t* status_reg)
{
    /*
    *   Funzione chiamata da int20_handler() in pic.c
    *   nel caso in cui e' stata triggherata una eccezione
    *   dalla cpu.
    *   A ogni chiamata si occupa di cambiare il colore delle scritte
    *   nella funzione panic()
    * **/

    if (num_color > 15)
        num_color = 1;

    switch (num_color) {
        // ho saltato un colore perche' il colore delle scritte sono uguali al colore del bg
        case 1:
            actual_color_terminal = BG_GC_C_GC(BLU, NERO);
            break;
        case 2:
            actual_color_terminal = BG_GC_C_GC(BLU, VERDE);
            break;
        case 3:
            actual_color_terminal = BG_GC_C_GC(BLU, CIANO);
            break;
        case 4:
            actual_color_terminal = BG_GC_C_GC(BLU, ROSSO);
            break;
        case 5:
            actual_color_terminal = BG_GC_C_GC(BLU, VIOLA);
            break;
        case 6:
            actual_color_terminal = BG_GC_C_GC(BLU, MARRONE);
            break;
        case 7:
            actual_color_terminal = BG_GC_C_GC(BLU, GRIGIO);
            break;
        case 8:
            actual_color_terminal = BG_GC_C_GC(BLU, GRIGIO_SCURO);
            break;
        case 9:
            actual_color_terminal = BG_GC_C_GC(BLU, BLU_CHIARO);
            break;
        case 10:
            actual_color_terminal = BG_GC_C_GC(BLU, VERDE_CHIARO);
            break;
        case 11:
            actual_color_terminal = BG_GC_C_GC(BLU, CIANO_CHIARO);
            break;
        case 12:
            actual_color_terminal = BG_GC_C_GC(BLU, ROSSO_CHIARO);
            break;
        case 13:
            actual_color_terminal = BG_GC_C_GC(BLU, VIOLA_CHIARO);
            break;
        case 14:
            actual_color_terminal = BG_GC_C_GC(BLU, GIALLO);
            break;
        case 15:
            actual_color_terminal = BG_GC_C_GC(BLU, BIANCO);
            break;
    }

    panic(msg_error, status_reg);
    num_color++;
}


O3 void init_hardware_pit()
{
    /*
    *   Imposta il timer.
    *   Vado a dire sostanzialmente a ogni quanto deve fare una determinata
    *   azione.
    * **/

    outb(0x43, 0x36);
    outb(0x40, PIT_DIV & 0xFF);         // low
    outb(0x40, (PIT_DIV >> 8) & 0xff);  // high
}
