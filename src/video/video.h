#ifndef VIDEO_H
#define VIDEO_H

/*

---------------------> asse x
|. P(actual_video_row; actual_video_col)
|    
|
|
v asse y

*/

#include "config.h"
#include <stddef.h>
#include <stdint.h>


/* STANDARD COLOR */
#define NERO            0
#define BLU             1
#define VERDE           2
#define CIANO           3
#define ROSSO           4
#define VIOLA           5
#define MARRONE         6
#define GRIGIO          7
#define GRIGIO_SCURO    8
#define BLU_CHIARO      9
#define VERDE_CHIARO    10
#define CIANO_CHIARO    11
#define ROSSO_CHIARO    12
#define VIOLA_CHIARO    13
#define GIALLO          14
#define BIANCO          15

/* SET BACKBGROUND CON COLORE TESTO*/
#define BG_BLU_C_WHITE      (BLU << 4)      | BIANCO
#define BG_BIANCO_C_NERO    (BIANCO << 4)   | NERO


#ifdef settings_video

// default colore dei caratteri del terminale (in futuro potrebbe cambiare il colore in base alle situazioni)
char actual_color_terminal = VERDE_CHIARO; 
u16* video_mem      = 0;
u16 terminal_row    = 0;  // tiene traccia a quale riga del monitor sto scrivendo (max value VGA_HEIGHT)
u16 terminal_col    = 0;  // tiene traccia della colonna del monitor da dove sto scrivendo (max value VGA_WIDTH)

#endif

#define VGA_WIDTH   80
#define VGA_HEIGHT  100

#ifdef prototype_fun_print

uint16_t set_char_terminal(char c, char colour);
void terminal_put_char(int x, int y, char c, char colour);
void terminal_writechar(char c, char colour);
void print(const unsigned char* string);
void terminal_initialize();

#endif

#endif