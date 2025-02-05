#include "video/video.h"
#include "stdlib/stdlib.h"


uint16_t set_char_terminal(char c, char colour)
{
    /*
    *   abbiamo un unsigned int a 16 bit.
    *   colour va a occupare gli 8 bit piu' significativi,
    *   c invece va a occupare gli 8 bit meno significativi.
    *   in questo modo posso passare il colore + carattere a 0xb8000 con una sola chiamata
    */
    return (colour << 8) | c;
}


void send_char_to_terminal(int x, int y, char c, int colour)
{
    /*
    *   Stampa un carattere c di colore colour alla colonna x della riga y del monitor
    * Argv:
    *   - x:        colonna schermo
    *   - y:        row schermo
    *   - c:        carattere da stampare
    *   - colour:   colore del carattere
    */
    video_mem_address[(y * VGA_WIDTH) + x] = set_char_terminal(c, colour); 
}



void terminal_writechar(const unsigned char c, int colour)
{
    switch (c) {
        case '\n':
            actual_video_col = 0;
            actual_video_row++;
            
            break;

        case '\t':
            actual_video_col += 8;
            break;

        case '\b':
            if (actual_video_col != 0)
                actual_video_col--;

            send_char_to_terminal(actual_video_col, actual_video_row, ' ', colour);
            break;

        default:
            send_char_to_terminal(actual_video_col, actual_video_row, c, colour);
            actual_video_col++;

            if (actual_video_col == VGA_WIDTH) {
                actual_video_col = 0;
                actual_video_row++;
            }
            break;
    }
}


void print(const unsigned char* string)
{
    /*
    * Stampa in output una stringa
    */
    for(size_t i = 0; string[i] != '\0'; i++)
        terminal_writechar(string[i], actual_color_terminal);
}


void init_video()
{
    /*
    *   Funzione usata all'interno di kernel.c nella funzione kernel_main.
    *   setta lo screen col colore nero
    **/
    video_mem_address = (uint16_t*) (0xb8000);

    // memset((void*) keyboard_buffer, 0, (size_t) OS_SIZE_SHELL_COMMAND); 
    // counter_buffer = 0;
    
    for (int y = 0; y < VGA_HEIGHT; y++) 
        for (int x = 0; x < VGA_WIDTH; x++) 
            send_char_to_terminal(x, y, ' ', NERO);
}