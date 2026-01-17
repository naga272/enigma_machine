#define OS_X_QEMU
#define DISPLAY_START_MSG

#include "config.h"
#include "kernel.h"

#include "utilities/stdlib/stdlib.h"
#include "utilities/string/string.h"

#include "utilities/video/video.h"
#include "utilities/memory/heap/malloc.h"
#include "utilities/memory/heap/kheap_creation.h"
#include "utilities/memory/heap/kheap_creation.h"

#include "utilities/memory/paging/paging.h"

#include "utilities/io/io.h"
#include "utilities/idt/idt.h"
#include "utilities/idt/body_int/slave/rtc_orologio.h"
#include "utilities/idt/body_int/master/input_keyboard.h"
#include "utilities/disk/disk.h"


static struct paging_4gb_chunk *kernel_directory = 0;
extern void test_int80h(void);

uchar* magic_num_sec_128 = (uchar*) "EnigmaOs";
uchar *username = (uchar*) "Mario";
uchar *password = (uchar*) "Password123!";
uchar buf128[512];


O3 static inline void test_disk()
{
    /*
    * Test formattazione sector 128  
    *
    *  ____________________________________________________________
    * |                  SETTORE 128 (512 bytes)                   |
    * |------------------------------------------------------------|
    * | FIRMA |PADD| USERNAME | PADD | PASSWORD | PADD | CS | PADD |
    * |-------|----|----------|------|----------|------|----|------|
    * |   8   |  1 |    32    |  1   |    32    |   1  |  1 |  436 |
    *  ------------------------------------------------------------
    * 
    * **** */
    uchar buf[512];

    u16 offset = 0;

    // firma
    for (; magic_num_sec_128[offset] != '\0'; offset++)
        buf[offset] = magic_num_sec_128[offset];
    // padding
    buf[offset] = ' ';
    offset++;

    // username
    for (i8 idx = 0; username[idx] != '\0'; idx++, offset++)
        buf[offset] = username[idx];

    // padding
    buf[offset] = ' ';
    offset++;

    // password
    for (i8 i = 0; password[i] != '\0' ; i++, offset++)
        buf[offset] = password[i];

    // padding
    buf[offset] = ' ';

    // colori shell
    buf[offset + 1] = actual_color_terminal;

    disk_write_sector(128, 1, (void*) buf);
    disk_read_sector(128, 1, buf);

    print(buf);
}


O3 static inline void do_config()
{
    terminal_initialize((u8) buf128[9]);
    print((uchar*) ">>>");
}


O3 static inline void write_on_128_sector()
{
    uchar buf[512];

    u16 offset = 0;

    // firma
    for (; magic_num_sec_128[offset] != '\0'; offset++)
        buf[offset] = magic_num_sec_128[offset];
    
    // colori shell
    buf[offset + 1] = actual_color_terminal;

    disk_write_sector(128, 1, (void*) buf);
    // disk_read_sector(128, 1, buf);
}


O3 void init_shell()
{
    uchar magic_num_disk[9];

    for (int i = 0; i < 9; i++)
        magic_num_disk[i] = buf128[i];

    magic_num_disk[8] = '\0';  // non si sa mai

    if (strcmp(magic_num_disk, magic_num_sec_128)) {
        do_config();
        return;
    }

    terminal_initialize(BG_BIANCO_C_NERO);

    // print(magic_num_disk);

    print((uchar*) start_msg);

    while (FASE_SETUP) {
        try_the_setup(tmp_char_container);
        asm volatile("hlt");
    }

    write_on_128_sector();
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
    try_int80h();
}


O3 void kernel_main()
{
    disable_interrupts();

    // inizializzazione idt + settings hardware componenents
    idt_init();

    // inizializzazione paging
    kernel_directory = paging_new_4gb(
        PAGING_IS_WRITEABLE | PAGING_IS_PRESENT | PAGING_ACCESS_FROM_ALL
    );

    kernel_directory->switch_directory(kernel_directory);

    // inizializzazione heap
    kheap_init();

    enable_interrupts();

    disk_read_sector(128, 1, buf128);

    init_shell();

    // update dats nella struct @t
    rtc_get_time(&t);

    while (1) {
        main();
        asm volatile("hlt");
    }
}
