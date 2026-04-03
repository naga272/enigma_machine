#define OS_X_QEMU
// #define DISPLAY_START_MSG

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
#include "utilities/fs/pparser.h"
#include "utilities/disk/disk.h"
#include "utilities/disk/streamer.h"
#include "utilities/setup/setup.h"
#include "utilities/book/book.h"
#include "utilities/markov/markov.h"
#include "utilities/gdt/gdt.h"
#include "utilities/task/tss.h"


extern void test_int80h(void);

extern volatile uchar tmp_char_container;
extern uchar* magic_num_sec_128;

extern uchar username[32];
extern uchar password[32];

extern uchar username_insert[32];
extern u8 is_ended_setup;

static struct paging_4gb_chunk *kernel_directory = 0;
struct book* b;

struct tss tss;
struct gdt gdt_real[ENIGMAOS_TOTAL_GDT_SEGMENTS];
struct gdt_structured gdt_structured[ENIGMAOS_TOTAL_GDT_SEGMENTS] = {
    {.base = 0x00, .limit = 0x00, .type = 0x00},                 // NULL Segment (richiesta obbligatoria dalla CPU)

    // tutto questo significa che il codice e i dati condividono tutto lo spazio di memoria (4gb)
    {.base = 0x00, .limit = 0xffffffff, .type = 0x9a},           // Kernel code segment
    {.base = 0x00, .limit = 0xffffffff, .type = 0x92},           // Kernel data segment

    // user ring
    {.base = 0x00, .limit = 0xffffffff, .type = 0xf8},           // user code segment
    {.base = 0x00, .limit = 0xffffffff, .type = 0xf2},           // user data segment

    // tss segment
    {.base = (u32) &tss, .limit = sizeof(tss), .type = 0xE9},    // tss segment
};


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


O3 static inline void main()
{
    gestisci_char_to_write(tmp_char_container);
    tmp_char_container = 0;

    render_time();
}


O3 void kernel_main()
{
    disable_interrupts();

    // init gdt
    memset(gdt_real, 0x00, sizeof(gdt_real));

    // conversione nella vera entry GDT da 8 byte richiesta dalla CPU
    gdt_structured_to_gdt(gdt_real, gdt_structured, ENIGMAOS_TOTAL_GDT_SEGMENTS);

    // caricamento nel registro per la gdt
    gdt_load(gdt_real, sizeof(gdt_real));

    // inizializzazione idt + settings hardware components
    idt_init();

    // inizializzazione heap
    kheap_init();

    // inizializzazione disk
    disk_search_and_init();

    /*
    struct disk_stream* stream = diskstreamer_new(0);
    diskstreamer_seek(stream, 0x201);
    uchar c = 0;
    diskstreamer_read(stream, &c, 1);
    */

    // inizializzazione tss
    memset(&tss, 0x00, sizeof(tss));
    tss.esp = 0x600000;     // kernel stack
    tss.ss0 = KERNEL_DATA_SELECTOR;

    // load tss
    tss_load(0x28);

    // inizializzazione paging
    kernel_directory = paging_new_4gb(
        PAGING_IS_WRITEABLE | PAGING_IS_PRESENT | PAGING_ACCESS_FROM_ALL
    );

    kernel_directory->switch_directory(kernel_directory);

    // predizione del prossimo interrupt del PIC
    init_markov_model_idt();

    init_shell();

    // initialize dats nella struct @t
    rtc_get_time(&t);

    enable_interrupts();

    /*
    === DIVISIONE PER ZERO TRIGGERA LA Blue Screen of the dead ===
    */
    // trigger_BsOD();

    /*
    === TEST SYSCALL PER UTENTI ===
    */
    // test_int80h();
    while (1) {
        main();
        asm volatile("hlt");
    }
}
