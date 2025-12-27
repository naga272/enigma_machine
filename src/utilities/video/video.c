#include "config.h"

#include "utilities/stdlib/stdlib.h"
#define settings_video
#include "utilities/video/video.h"
#include "utilities/io/io.h"


void terminal_writechar(uchar c, char colour);
void terminal_initialize(u8 colore);


O3 u16 set_char_terminal(uchar c, char colour)
{
    /*
    *   abbiamo un unsigned int a 16 bit.
    *   colour va a occupare gli 8 bit piu' significativi,
    *   c invece va a occupare gli 8 bit meno significativi.
    *   in questo modo posso passare il colore + carattere a 0xb8000 con una sola chiamata
    */
    return (colour << 8) | c;
}


O3 void terminal_put_char(int x, int y, uchar c, char colour)
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


O3 static inline void vga_update_cursor()
{
    u16 pos = terminal_row * VGA_WIDTH + terminal_col;
    outb(0x3d4, 0x0f);
    outb(0x3d5, (u8) (pos & 0xff));

    outb(0x3d4, 0x0e);
    outb(0x3d5, (u8) ((pos >> 8) & 0xff));
}


O3 static inline void update_cursor_on_x_y_pos(u16 y, u16 x)
{
    u16 pos = y * VGA_WIDTH + x;
    outb(0x3d4, 0x0f);
    outb(0x3d5, (u8) (pos & 0xff));

    outb(0x3d4, 0x0e);
    outb(0x3d5, (u8) ((pos >> 8) & 0xff));
}


O3 static inline void write_new_line()
{
    terminal_row++;
    terminal_col = 0;
}


O3 static inline void write_tab(uchar c, char colour)
{
    for (u8 i = 0; i != NUM_SPACE_TAB; i++)
        terminal_put_char(terminal_col + i, terminal_row, ' ', colour);            

    terminal_col += NUM_SPACE_TAB;
}


O3 static inline void go_back(char colour)
{
    if (terminal_col == 0) {
        terminal_col = VGA_WIDTH;
        terminal_row--;
        return;
    }

    terminal_col--;
    terminal_writechar(' ', colour);
    terminal_col--;
}


O3 static inline void write_char(uchar c, char colour)
{
    terminal_put_char(terminal_col, terminal_row, c, colour);
    terminal_col++;

    if (terminal_col == VGA_WIDTH)
        write_new_line();
}


O3 void terminal_writechar(uchar c, char colour)
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
            write_char(c, colour);
            break;
    }

    if (terminal_row >= VGA_HEIGHT - 1) {
        terminal_initialize(actual_color_terminal);
        terminal_row = 0;
    }

    vga_update_cursor();
}


O3 void print(const uchar* string)
{
    /*
    * Stampa in output una stringa
    */
    for (size_t i = 0; string[i] != '\0'; i++)
        terminal_writechar(string[i], actual_color_terminal);
}


u8 log_level = 3;

#ifndef max_level_log
#define max_level_log 3
#endif

#ifndef max_level_log_char
#define max_level_log_char (char) max_level_log + 48
#endif

O3 void printk(const uchar* msg)
{
    if (!(msg[0] == '<' && msg[1] >= '0' && msg[1] <= '3' && msg[2] == '>')) {
        printk((uchar*) KWARN "errore formattazione printk!!\n");
        return;
    }

    u8 lvl_msg = ((u8) msg[1]) - 48;
    msg += 3; // salto "<n>"

    if (lvl_msg > log_level)
        return;

    char tmp_actual_color_terminal = actual_color_terminal; 

    switch (lvl_msg) {
        case 0:
            actual_color_terminal = ROSSO;
            break;
        case 1:
            actual_color_terminal = GIALLO;
            break;
        case 2:
            actual_color_terminal = BLU_CHIARO;
            break;    
        case 3:
            actual_color_terminal = BIANCO;
            break;
    }

    print(msg);
    actual_color_terminal = tmp_actual_color_terminal;
}


O3 void enable_cursor(u8 start_cursor, u8 end_cursor)
{
	outb(0x3d4, 0x0a);
	outb(0x3d5, (insw((char) 0x3d5) & 0xc0) | start_cursor);

	outb(0x3d4, 0x08);
	outb(0x3d5, (insw((char) 0x3d5) & 0xe0) | end_cursor);
}


O3 void disable_cursor()
{
	outb(0x3d5, 0x0A);
	outb(0x3d4, 0x20);
}


O3 void terminal_initialize(u8 colore)
{
    /*
    *   Funzione usata all'interno di kernel.c nella funzione kernel_main.
    *   setta lo screen col colore nero
    **/
    enable_cursor((u8) 0, (u8) 0);
    video_mem = (u16*) (0xb8000);
    actual_color_terminal = colore;

    for (u32 y = 0; y < VGA_HEIGHT; y++) 
        for (u32 x = 0; x < VGA_WIDTH; x++) 
            terminal_put_char(x, y, ' ', colore);

    terminal_row = 0;
    terminal_col = 0;
}


char* panic_face = "\n\
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


static inline void delay(volatile u32 count)
{
    /*
    * mi serve per rallentare lo switch di colore delle scritte in panic()
    * @count: indica il "timer"
    */
    while (count--)
        asm volatile("nop");
}


u8 panic_init = 0;
O3 void panic(const char* msg)
{
    /*
    * In un os normale, la panic foo deve avviarsi solo quando le cose stanno andando
    * davvero troppo male e che quindi si vuole costringere l'utente a eseguire un riavvio
    * o a spegnere e riaccendere dal tasto fisico.
    * In questo os viene triggerata solo se viene eseguita una divisione per 0.
    * Se succede, disabilita tutti gli interrupt e mostra
    * la schemrata BSoD
    * */

    if (!panic_init) {
        terminal_initialize(BG_BLU_C_WHITE);
        panic_init++;
    }

    terminal_col = 0;
    terminal_row = 0;

    print((const uchar*) msg);
    print((const uchar*) panic_face);
    disable_cursor();    
}
