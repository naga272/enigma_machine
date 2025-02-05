#ifndef VIDEO_H
#define VIDEO_H

#include <stddef.h>
#include <stdint.h>



/*

---------------------> asse x
|. P(actual_video_row; actual_video_col)
|    
|
|
v asse y

*/

uint16_t* video_mem_address = (uint16_t*) (0x00000);
size_t actual_video_row  = 0;
size_t actual_video_col  = 0;


void init_video();   // inizializza lo screen
void send_char_to_terminal(int, int, char, int);
uint16_t set_char_terminal(char, char);
void terminal_writechar(const unsigned char, int);
void print(const unsigned char*);


#define VGA_WIDTH 200
#define VGA_HEIGHT 100


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

size_t actual_color_terminal = VERDE;

#endif