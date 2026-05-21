#define OS_X_QEMU
// #define DISPLAY_START_MSG

#include "config.h"
#include "kernel.h"


extern void test_int80h(void);

extern volatile uchar tmp_char_container;
extern uchar* magic_num_sec_128;
extern u8 is_ended_setup;

static struct paging_4gb_chunk *kernel_directory = 0;
struct book* b;

extern pci_dev_list_t* nics;


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
        book_init();
        return;
    }

    init_setup(b);
    is_ended_setup++;
    book_init();
}


O3 static inline void trigger_BsOD()
{
    // 1 / 0 = panic()
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
    prevedi_markov();
}


void kernel_main()
{
    disable_interrupts();

    // inizializzazione heap
    kheap_init();

    // inizializzazione paging (identity mapped, virt=phi_addr)
    kernel_directory = paging_new_4gb(
        PAGING_IS_WRITEABLE | PAGING_IS_PRESENT | PAGING_ACCESS_FROM_ALL
    );

    kernel_directory->switch_directory(kernel_directory);

    // inizializzazione + caricamento della gdt del kernel
    gdt_init();

    // inizializzazione idt + settings hardware components
    idt_init();

    // inizializzazione filesystem
    fs_init();

    // inizializzazione disk
    disk_search_and_init();

    // predizione del prossimo interrupt del PIC
    init_markov_model_idt();

    // initialize dats nella struct @t
    rtc_get_time(&t);

    // inizializzazione pci
    search_all_device_pci();
    
    // inizializzazione scheda di rete
    init_scheda_rete();
    
    // inizializzazione shell
    init_shell();

    // i32 arp_send_request(struct pci_device* nic, u32 target_ip)
    arp_send_request(
        &nics->dev[0],
        ip_to_u32(10, 0, 2, 2)
    );

    /*
    === DIVISIONE PER ZERO TRIGGERA LA Blue Screen of the dead ===
    */
    // trigger_BsOD();

    test_int80h();
    while (1) {
        main();
        asm volatile("hlt");
    }
}
