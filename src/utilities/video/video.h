#ifndef VIDEO_H
#define VIDEO_H

/*

---------------------> asse x
| C(actual_video_row; actual_video_col)
|    
|
|
v asse y

C = posizione cursore
*/

#include "config.h"
#include <stddef.h>
#include <stdint.h>


#ifdef settings_video

// default colore dei caratteri del terminale (in futuro potrebbe cambiare il colore in base alle situazioni)
char actual_color_terminal = VERDE_CHIARO; 
u16* video_mem      = 0;
u16 terminal_row    = 0;  // tiene traccia a quale riga del monitor sto scrivendo (max value VGA_HEIGHT)
u16 terminal_col    = 0;  // tiene traccia della colonna del monitor da dove sto scrivendo (max value VGA_WIDTH)

#undef settings_video
#endif

#define VGA_WIDTH   80
#define VGA_HEIGHT  100
#define NUM_SPACE_TAB 4

#ifdef prototype_fun_print

uint16_t set_char_terminal(char, char);
void terminal_put_char(int, int, char, char);
void terminal_writechar(char, char);
void print(const uchar*);
void printk(const uchar*);
void terminal_initialize();
void panic(const uchar*);


void enable_cursor(u8 start_cursor, u8 end_cursor);
void disable_cursor_cursor(u8 x, u8 y);

#endif


#endif
