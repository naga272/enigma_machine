#ifndef VIDEO_H
#define VIDEO_H

/*

---------------------> asse x
|[C][P][P][P][P][P][P]
|[P][P][P][P][P][P][P]
|[P][P][P][P][P][P][P]
|[P][P][P][P][P][P][P]
v asse y

P = Celle schermo
C = posizione cursore

la posizione di C è data da terminal_row e terminal_col
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


static uchar giorni_settimana[8][4] = {
    /* A quanto pare l'rtc ha un suo modo di tenere la conta dei giorni:
        sunday = 1
        monday = 2
        tuesday = 3
        wednesday = 4
        etc ...
    */
    "",
    "SUN",
    "MON",
    "TUE",
    "WED",
    "THU",
    "FRI",
    "SAT",
};


// struct che contiene .sec, .min, .ore, .giorno, mese, anno
struct tempo_t t;
/*
formattazione orario in prima riga
"ddd:MM:yyyy hh:mm:ss"
*/
uchar time_formatted[22];
// usato in modo provvisorio per aggiornare il timer (finche non capisco il problema
// in IRQ#8)


#undef settings_video
#endif

#define VGA_WIDTH   80
#define VGA_HEIGHT  100
#define NUM_SPACE_TAB 4

u16 set_char_terminal(uchar, char);
void terminal_put_char(int, int, uchar, char);
void terminal_writechar(uchar, char);
void print(const uchar*);
void panic(const uchar*, struct regs_t*);
void update_orologio_display();
void terminal_initialize(u8);

void enable_cursor(u8 start_cursor, u8 end_cursor);
void disable_cursor_cursor(u8 x, u8 y);
void render_time();


extern void terminal_initialize(u8);
extern void terminal_writechar(uchar, char);
extern void print(const uchar*);
extern void panic(const uchar*, struct regs_t*);
extern void try_the_setup(uchar);
extern void gestisci_char_to_write(uchar);
extern void update_cursor_on_x_y_pos(u16, u16);
extern void render_time();

extern u8 flag_x_colour_shell;
extern char actual_color_terminal;
extern volatile u16 terminal_row;
extern volatile u16 terminal_col;

#endif
