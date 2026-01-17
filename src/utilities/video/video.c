
#include "config.h"

#include "utilities/stdlib/stdlib.h"
#include "utilities/io/io.h"

#define settings_video
#include "utilities/video/video.h"
#include "utilities/shell/command.h"
#include "utilities/idt/body_int/slave/rtc_orologio.h"


extern uchar core_enigma(uchar);


uchar buffer_line_cmd[SIZE_COMMAND_SHELL];
size_t idx_buff = 0;
u8 is_ended_setup = 0;


static inline void delay(volatile u32 count)
{
    /*
    * @count: indica il "timer"
    */
    while (count--)
        asm volatile("nop");
}


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


O3 void terminal_put_char(i32 x, i32 y, uchar c, char colour)
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


O3 void update_cursor_on_x_y_pos(u16 y, u16 x)
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


O3 static inline void do_backspace()
{
    if (idx_buff == 0 && is_ended_setup)
        return;

    if (is_ended_setup) {
        idx_buff--;
        buffer_line_cmd[idx_buff] = 0;
    }

    terminal_col--;
    terminal_writechar(' ', actual_color_terminal);
    terminal_col--;
    // print((uchar*) buffer_line_cmd);
    vga_update_cursor();
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
            do_backspace(colour);
            break;
        default:
            write_char(c, colour);
            break;
    }

    if (terminal_row >= VGA_HEIGHT - 1) {
        terminal_initialize(actual_color_terminal);
        terminal_row = 1;
        terminal_col = 1;
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

    terminal_row = 1;
    terminal_col = 0;

    memset(buffer_line_cmd, 0, SIZE_COMMAND_SHELL);
    idx_buff = 0;
}


void clean_bff_cmd_line()
{
    memset(buffer_line_cmd, 0, idx_buff);
    idx_buff = 0;
}


O3 static inline void start_encryption()
{
    terminal_writechar('\n', actual_color_terminal);

    for (size_t i = 0; buffer_line_cmd[i] != 0; i++)
        terminal_writechar(core_enigma(buffer_line_cmd[i]), actual_color_terminal);

    clean_bff_cmd_line();
    print((uchar*) "\n>>> ");
}


void gestisci_char_to_write(uchar tmp_char_container)
{
    if (!tmp_char_container || (tmp_char_container >= '0' && tmp_char_container <= '4'))
        return;

    if (CHAR_BACKSPACE(tmp_char_container)) {
        do_backspace();
        return;
    }

    if (CHAR_END_PHRASE(tmp_char_container)) {
        if (!try_execute_comm(buffer_line_cmd))
            if (is_ended_setup)
                start_encryption();

        return;
    }

    terminal_writechar(tmp_char_container, actual_color_terminal);

    if (is_ended_setup) {
        buffer_line_cmd[idx_buff] = tmp_char_container;
        idx_buff++;
    }
}


void print_hex(u32 val) {
    uchar hex[11]; // "0x" + 8 cifre + '\0'
    hex[0] = '0';
    hex[1] = 'x';
    
    for (int i = 0; i < 8; i++) {
        u8 nibble = (val >> (28 - i * 4)) & 0xF;
        if (nibble < 10)
            hex[2 + i] = '0' + nibble;
        else
            hex[2 + i] = 'A' + (nibble - 10);
    }
    hex[10] = '\0';
    print(hex);
}


O3 void panic(const uchar* msg, struct regs_t* status_reg)
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

    // show a message that explain what happened
    print(msg);

    // show panic face
    print(panic_face);

    // show status register
    print((uchar*) "eax=");
    print_hex(status_reg->eax);
    print((uchar*) "\t");

    print((uchar*) "ebx=");
    print_hex(status_reg->ebx);
    print((uchar*) "\t");

    print((uchar*) "ecx=");
    print_hex(status_reg->ecx);
    print((uchar*) "\t");

    print((uchar*) "edx=");
    print_hex(status_reg->edx);
    print((uchar*) "\n");

    print((uchar*) "edi=");
    print_hex(status_reg->edi);
    print((uchar*) "\t");

    print((uchar*) "esi=");
    print_hex(status_reg->esi);
    print((uchar*) "\t");

    print((uchar*) "ebp=");
    print_hex(status_reg->ebp);
    print((uchar*) "\t");

    print((uchar*) "esp=");
    print_hex(status_reg->esp);
    print((uchar*) "\n");

    print((uchar*) "eflags=");
    print_hex(status_reg->eflags);
    print((uchar*) "\t");

    print((uchar*) "eip=");
    print_hex(status_reg->eip);
    print((uchar*) "\t");

    print((uchar*) "cs=");
    print_hex(status_reg->cs);
    print((uchar*) "\t");
    
    print((uchar*) "intno=");
    print_hex(status_reg->int_no);

    disable_cursor();
}


u8 first_rendering = 1;
O3 void render_time()
{
    if (!t.rtc_dirty && !first_rendering)
        return;

    t.sec++;

    if (t.sec == 60) {
        t.min++;
        t.sec = 0;
    }

    if (t.min == 60) {
        t.min = 0;
        t.ore++;
    }

    if (t.ore == 24) {
        // per evitare troppi casini, tanto capita una sola volta in 24h
        rtc_get_time(&t);
    }

    u8 tmp_terminal_col = terminal_col;
    u8 tmp_terminal_row = terminal_row;

    terminal_col = VGA_WIDTH - SIZEOFARR(time_formatted);
    terminal_row = 0;

    time_formatted[0] = giorni_settimana[t.giorno_sett][0];
    time_formatted[1] = giorni_settimana[t.giorno_sett][1];
    time_formatted[2] = giorni_settimana[t.giorno_sett][2];
    time_formatted[3] = ' ';

    time_formatted[4] = '0' + (t.giorno_mese / 10);
    time_formatted[5] = '0' + (t.giorno_mese % 10);
    time_formatted[6] = '/';

    time_formatted[7] = '0' + (t.mese / 10);
    time_formatted[8] = '0' + (t.mese % 10);
    time_formatted[9] = '/';

    time_formatted[10] = '0' + (t.anno / 10);
    time_formatted[11] = '0' + (t.anno % 10);
    time_formatted[12] = ' ';

    time_formatted[13] = '0' + (t.ore / 10);
    time_formatted[14] = '0' + (t.ore % 10);
    time_formatted[15] = ':';
    
    time_formatted[16] = '0' + (t.min / 10);
    time_formatted[17] = '0' + (t.min % 10);
    time_formatted[18] = ':';
    
    time_formatted[19] = '0' + (t.sec / 10);
    time_formatted[20] = '0' + (t.sec % 10);
    time_formatted[21] = '\0';

    print((uchar*) time_formatted);

    terminal_row = tmp_terminal_row;
    terminal_col = tmp_terminal_col;

    // riporto il curose nella posizion e attuale
    update_cursor_on_x_y_pos(terminal_row, terminal_col);

    // resetto il flag
    set_rtc_dirty(&t, 0);
    first_rendering = 0;
}
