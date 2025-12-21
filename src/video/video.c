#include "stdlib/stdlib.h"

#define settings_video
#include "video/video.h"
#include "io/io.h"


void terminal_writechar(uchar c, char colour);


uint16_t set_char_terminal(uchar c, char colour)
{
    /*
    *   abbiamo un unsigned int a 16 bit.
    *   colour va a occupare gli 8 bit piu' significativi,
    *   c invece va a occupare gli 8 bit meno significativi.
    *   in questo modo posso passare il colore + carattere a 0xb8000 con una sola chiamata
    */
    return (colour << 8) | c;
}


void terminal_put_char(int x, int y, uchar c, char colour)
{
    /*
    *   Stampa un carattere c di colore colour alla colonna x della riga y del monitor
    * Argv:
    *   - x:        colonna schermo
    *   - y:        row schermo
    *   - c:        carattere da stampare
    *   - colour:   colore del carattere
    */
    video_mem[(y * VGA_WIDTH) + x] = set_char_terminal(c, colour); 
}


static inline void write_new_line()
{
    if (terminal_row == VGA_HEIGHT)
        terminal_row = 0;
    else
        terminal_row++;

    terminal_col = 0;
}


static inline void write_tab(uchar c, char colour)
{
    for (u8 i = 0; i != NUM_SPACE_TAB; i++)
        terminal_put_char(terminal_col, terminal_row, ' ', colour);            

    terminal_col += NUM_SPACE_TAB;
}


static inline void write_normal_char(uchar c, char colour)
{
    terminal_put_char(terminal_col, terminal_row, c, colour);
    terminal_col++;

    if (terminal_col == VGA_WIDTH) {
        terminal_col = 0;
        terminal_row++;
    }
}


static inline void cursor_back()
{

}


static inline void erase_at_cursor(char colour)
{
    
}


static inline void vga_update_cursor()
{
    
}


static inline void go_back(char colour)
{
    cursor_back();
    erase_at_cursor(actual_color_terminal);
    vga_update_cursor();

    if (terminal_col == 0) {
        terminal_col = VGA_WIDTH;
        terminal_row--;
        return;
    }

    terminal_col--;
    terminal_writechar(' ', colour);
    terminal_col--;
}


void terminal_writechar(uchar c, char colour)
{
    /*
    *   A differenza di terminal_put_char non posso decidere in quale colonna / riga mettere un carattere
    */

    switch (c) {
        case '\n':
            write_new_line();
            break;
        case '\t':
            write_tab(c, colour);
            break;
        case '\b':
            go_back(colour);
            break;
        default:
            write_normal_char(c, colour);
            break;
    }
}


void print(const uchar* string)
{
    /*
    * Stampa in output una stringa
    */
    for (size_t i = 0; string[i] != '\0'; i++)
        terminal_writechar(string[i], actual_color_terminal);
}


void terminal_initialize(int colore)
{
    /*
    *   Funzione usata all'interno di kernel.c nella funzione kernel_main.
    *   setta lo screen col colore nero
    **/
    video_mem = (uint16_t*) (0xb8000);
    actual_color_terminal = colore;

    for (int y = 0; y < VGA_HEIGHT; y++) 
        for (int x = 0; x < VGA_WIDTH; x++) 
            terminal_put_char(x, y, ' ', colore);
    
    terminal_row = 0;
    terminal_col = 0;
}
