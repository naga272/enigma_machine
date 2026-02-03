#define OS_X_QEMU
#define DISPLAY_START_MSG

#include "config.h"
#include "kernel.h"

#include "utilities/stdlib/stdlib.h"
#include "utilities/string/string.h"

#include "utilities/video/video.h"
#include "utilities/memory/heap/malloc.h"
#include "utilities/memory/heap/kheap_creation.h"

#include "utilities/memory/paging/paging.h"

#include "utilities/io/io.h"
#include "utilities/idt/idt.h"
#include "utilities/idt/body_int/slave/rtc_orologio.h"
#include "utilities/disk/disk.h"
#include "utilities/setup/setup.h"
#include "utilities/book/book.h"

extern void test_int80h(void);

extern volatile uchar tmp_char_container;
extern uchar* magic_num_sec_128;

extern uchar username[32];
extern uchar password[32];

extern uchar username_insert[32];
extern u8 is_ended_setup;

static struct paging_4gb_chunk *kernel_directory = 0;
struct book* b;


O3 void init_shell()
{
    uchar buf128[512];

    disk_read_sector(128, 1, buf128);

    uchar magic_num_disk[9];

    for (i8 i = 0; i < 9; i++)
        magic_num_disk[i] = buf128[i];

    magic_num_disk[8] = '\0';  // non si sa mai

    // combacia la firma? se si leggo i dati dal disco,
    // altrimenti eseguo il setup
    if (strcmp(magic_num_disk, magic_num_sec_128)) {
        do_config(buf128);
        return;
    }

    b = init_book(16);

    init_setup(b);
    is_ended_setup++;
}


O3 static inline void trigger_BsOD()
{
    // 1 / 0
    asm volatile (
        "xor %%edx, %%edx\n"
        "mov $1, %%eax\n"
        "div %%edx\n"
        :
        :
        : "eax", "edx"
    );
}


static inline void try_int80h()
{
    test_int80h();
}


O3 static inline void main()
{
    gestisci_char_to_write(tmp_char_container);
    tmp_char_container = 0;

    render_time();
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

    init_shell();

    enable_interrupts();

    // update dats nella struct @t
    rtc_get_time(&t);

    /*
    === DIVISIONE PER ZERO TRIGGERA LA Blue Screen of the dead ===
    */
    // trigger_BsOD();

    /*
    === SYSCALL PER UTENTI ===
    */
    // try_int80h();
    while (1) {
        main();
        asm volatile("hlt");
    }
}
