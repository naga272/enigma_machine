#ifndef INPUT_KEYBOARD_H
#define INPUT_KEYBOARD_H

#include "utilities/enigma/enigma.h"
#include "utilities/stdlib/stdlib.h"
#include "utilities/enigma/keyboard.h"

#ifndef FASE_SETUP
#define FASE_SETUP (flag_x_colour_shell == 0)
#endif

extern uchar core_enigma(uchar container);

// from video/video.c - video.h
extern size_t actual_color_terminal;
extern void print(const uchar*);
extern void printk(const uchar*);
extern void terminal_writechar(const uchar, int);
extern void terminal_initialize(int);
extern void panic(const uchar*);


/* lock serve ha bloccare il numero di messaggi per errore durante la fase di setup */
u8 lock = 0;

// usato per dire se la fase di setup e' finita (try_answer foo)
u8 flag_x_colour_shell = 0;

/*
*   Usati per memorizzare i caratteri da criptare
*/
uchar bff_cmd_line[SIZE_COMMAND_SHELL];
size_t idx_buffer = 0;

#endif