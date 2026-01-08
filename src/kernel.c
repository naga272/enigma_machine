#define OS_X_QEMU

#include "config.h"
#include "kernel.h"
#include "utilities/stdlib/stdlib.h"
#include "utilities/string/string.h"
#include "utilities/video/video.h"
#include "utilities/io/io.h"
#include "utilities/idt/idt.h"
#include "utilities/idt/body_int/slave/rtc_orologio.h"
#include "utilities/idt/body_int/master/input_keyboard.h"
#include "utilities/disk/disk.h"


extern void test_int80h(void);
struct user_table utente;


O3 static inline void init_shell()
{
    if (utente.magic == USER_MAGIC)
        return;

    terminal_initialize(BG_BIANCO_C_NERO);
    print((uchar*) start_msg);

    while (!setup_finish) {
        try_the_setup(&utente, tmp_char_container);
        tmp_char_container = 0;
        asm volatile("hlt");
    }

    // offset = 128 * 512 = 65536 byte
    /*
    utente.magic = USER_MAGIC;

    u8 sector[512];
    memset(sector, 0, 512);
    memcpy(sector, &utente, sizeof(struct user_table));
    disk_write_sector(USER_TABLE_LBA, 1, sector);
    */
    terminal_initialize(actual_color_terminal);
    print((uchar*) ">>>");
}


O3 static inline void render_time()
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


O3 static inline void trigger_BsOD()
{
    asm volatile (
        "xor %%edx, %%edx\n"
        "mov $1, %%eax\n"
        "div %%edx\n"
        :
        :
        : "eax", "edx"
    );
}


u8 flag_x_int80h = 0;
static inline void try_int80h()
{
    if (flag_x_int80h)
        return;

    test_int80h();
    flag_x_int80h++;
}


O3 static inline void main()
{
    gestisci_char_to_write(tmp_char_container);
    tmp_char_container = 0;

    render_time();

    /*
    === DIVISIONE PER ZERO TRIGGERA LA Blue Screen of the dead ===
    */
    // trigger_BsOD();

    /*
    === SYSCALL PER UTENTI ===
    */
    // try_int80h();
}


O3 void kernel_main()
{

    disable_interrupts();

    idt_init();

    /* NOT YET READY
    u8 sector[512];

    disk_search_and_init();

    // offset = 128 * 512 = 65536 byte
    memset(&utente, 0, sizeof(utente));
    memset(sector, 0, 511);

    disk_read_sector(USER_TABLE_LBA, 1, sector);
    memcpy(&utente, sector, sizeof(struct user_table));
    */

    init_shell();

    enable_interrupts();

    rtc_get_time(&t);

    asm volatile("sti");

    while (VIVO) {
        main();
        asm volatile("hlt");
    }
}
