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
#include "utilities/idt/idt.h"


#ifdef settings_video

// default colore dei caratteri del terminale (in futuro potrebbe cambiare il colore in base alle situazioni)
char actual_color_terminal = VERDE_CHIARO;
volatile u16 terminal_row    = 0;  // tiene traccia a quale riga del monitor sto scrivendo (max value VGA_HEIGHT)
volatile u16 terminal_col    = 0;  // tiene traccia della colonna del monitor da dove sto scrivendo (max value VGA_WIDTH)
u16* video_mem               = 0;
u8 panic_init = 0;

static uchar* panic_face = (uchar*) "\n\
\t\t\tOh no! Critical error!\n\
         ________________________________\n\
        (                                (\n\
      :(                                  ):(\n\
    :(                                      ):(\n\
  :(            XXXX         XXXX             ):(\n\
:(              XXXX         XXXX              ):(\n\
:(                                              ):(\n\
:(                                              ):(\n\
:(                                              ):(\n\
  :(            -----------------             ):(\n\
    :(                                      ):(\n\
      :(                                 ):(\n\
        :(_______________________________(\n\
        \n\
";

#undef settings_video
#endif

#define VGA_WIDTH   80
#define VGA_HEIGHT  100
#define NUM_SPACE_TAB 4

#ifdef prototype_fun_print

u16 set_char_terminal(char, char);
void terminal_put_char(int, int, char, char);
void terminal_writechar(char, char);
void print(const uchar*);
void panic(const uchar*, struct regs_t*);
void update_orologio_display();
void terminal_initialize();

void enable_cursor(u8 start_cursor, u8 end_cursor);
void disable_cursor_cursor(u8 x, u8 y);

#endif

#ifndef prototype_fun_print

extern void terminal_initialize(u8);
extern void terminal_writechar(uchar, char);
extern void print(const uchar*);
extern void panic(const uchar*, struct regs_t*);
extern void try_the_setup(uchar);
extern void gestisci_char_to_write(uchar);
extern void update_cursor_on_x_y_pos(u16, u16);

#ifndef settings_video

extern u8 flag_x_colour_shell;
extern char actual_color_terminal;
extern volatile u16 terminal_row;
extern volatile u16 terminal_col;

#endif

#endif

#endif
