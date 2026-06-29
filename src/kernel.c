#define OS_X_QEMU
// #define DISPLAY_START_MSG

#include "kernel.h"


MODULE_LICENSE("GPL-3.0");
MODULE_AUTHOR("naga272");
MODULE_DESCRIPTION("Entry point del kernel");


O3 void init_shell()
{
    uchar buf_config[512];

    disk_read_sector(SECTOR_CONFIG, 1, buf_config);

    uchar magic_num_disk[9];

    for (i8 i = 0; i < 9; i++)
        magic_num_disk[i] = buf_config[i];

    // non si sa mai
    magic_num_disk[8] = '\0';

    // combacia la firma? se si leggo i dati dal disco,
    // altrimenti eseguo il setup
    if (strcmp(magic_num_disk, magic_num_sec_config)) {
        do_config(buf_config);
        book_init();
        return;
    }

    init_setup(b);
    is_ended_setup++;
    book_init();
}


O3 ainline void trigger_BsOD()
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


O3 ainline void main()
{
    CASE_CHAR_WRITTEN;

    render_time();
    prevedi_markov();
}


O3 ainline void test_net()
{
    // i32 arp_send_request(struct pci_device* nic, u32 target_ip)
    arp_send_request(&nics->dev[0], ip_to_u32(10, 0, 2, 2));
    
    /*
    u8 mac_out[6] = {0};
    // i32 arp_recv(struct pci_device* nic, u32 target_ip)

    kprintf(
        "risposta da arp_recv() -> %i\n",
        arp_recv(
            &nics->dev[0],
            mac_out,
            ip_to_u32(10, 0, 2, 2)
        )
    );
    */
}


void kernel_main()
{
    disable_interrupts();
    
    // init gdt
    gdt_init();

    // inizializzazione heap
    kheap_init();

    // inizializzazione paging (identity mapped, virt=phi_addr)
    kernel_directory = paging_new_4gb(
        PAGING_IS_WRITEABLE | PAGING_IS_PRESENT | PAGING_ACCESS_FROM_ALL
    );

    kernel_directory->switch_directory(kernel_directory);

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

    /*
    === DIVISIONE PER ZERO TRIGGERA LA Blue Screen of the dead ===
    */
    // trigger_BsOD();

    // test_int80h();

    // inizializzazione shell
    init_shell();

    init_commands();

    test_net();

    while (1) {
        main();
        asm volatile("hlt");
    }
}
