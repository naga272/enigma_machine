#include "config.h"

#include "utilities/io/io.h"
#include "utilities/video/kprintf.h"
#include "utilities/shell/command.h"
#include "utilities/pci/pci.h"
#include "utilities/net/net.h"
#include "utilities/patricia_tree/patricia_tree.h"
#include "utilities/idt/body_int/slave/rtc_orologio.h"


#define OS_X_QEMU


#if defined(OS_X_QEMU) && defined(OS_X_XBOCHS) && defined(OS_X_X86)
    #error, "impossibile definire OS_X_QEMU, OS_X_XBOCHS, OS_X_X86 insieme"
#endif


MODULE_LICENSE("GPL-3.0");
MODULE_AUTHOR("naga272");
MODULE_DESCRIPTION("gestione comandi per la shell");


extern pci_dev_list_t* nics;
extern struct tempo_t t;


uchar* vec_reload_time_comm = (uchar*) "RELOAD_TIME";
uchar* vec_reboot_comm      = (uchar*) "REBOOT";
uchar* vec_power_off_comm   = (uchar*) "QUIT";
uchar* vec_cls_comm         = (uchar*) "CLS";
uchar* vec_ifconfig_comm    = (uchar*) "IFCONFIG";



u8 reboot()
{
    /*
    *   Uso il controller della tastiera per forzare il riavvio hardware della cpu
    *   - 0x64 e' la porta per il controller della tastiera
    *   - 0xFE e' il comando Pulse Output Line. 
    *       Questo comando abbassa la linea RESET della cpu.
    *       La cpu ricevendo il segnale di reset ricomincia da zero,
    * ** */
    outb(0x64, 0xFE);
    return 1;
}


u8 power_off()
{
#ifdef OS_X_QEMU
    /* 
    *   uso una porta specifica che viene intercettata da qemu,
    *   che vedendo il valore 0x2000 capisce che deve spegnere la macchina
    */
    // :D
    outw(0x604, 0x2000);
#endif

#ifdef OS_X_XBOCHS
    // :D
    outw(0xB004, 0x2000);
#endif

#ifdef OS_X_X86
    // >_<
#endif
    return 1;
}


u8 cls()
{
    terminal_initialize(actual_color_terminal);
    print((uchar*) ">>> ");
    return 1;
}


u8 ifconfig()
{
    for (size_t idx = 0; idx != nics->tot_num_device; idx++) {
        struct pci_device* nic = &nics->dev[idx];
        
        // riduzione accessi in ram
        net_ops_t* priv_methods = (net_ops_t*) nic->priv_methods;

        kprintf(
            "\n=== NIC NUMBER %i ===\nName: %s\nVendor: %s\nBar 0: %i\n",
            nics->tot_num_device,
            priv_methods->get_name_dev(nic),
            priv_methods->get_vendor_dev(nic),
            priv_methods->get_bar0_dev(nic)
        );

        priv_methods->print_mac(nic);
    }

    print((uchar*) "\n>>> ");
    return 1;
}


u8 reload_time()
{
    kprintf("Hello, sono in reload_time\n");
    return 1;
}


O3 ainline void count_occurrence(size_t* num_occurence, char* string, size_t max_len_string, char pattern)
{
    for (size_t idx = 0; idx < max_len_string; idx++) {
        if (string[idx] == '\0') {
            (*num_occurence)++;
            return;
        }

        if (string[idx] == pattern)
            (*num_occurence)++;
    }
}


O3 ainline void parse_prompt(char* name_command, size_t* argc, char** argv, uchar* comm_to_exec)
{
    char* tmp_comm_to_exec = (char*) comm_to_exec;

    size_t tot_len_command = strlen(tmp_comm_to_exec);
    size_t len_command = strnlen_terminator(tmp_comm_to_exec, tot_len_command, ' ');

    name_command = kcalloc(len_command);
    if (!name_command) {
        kprintf("error data pool for name_command\n");
        argv = NULL;
        name_command = NULL;
    }

    memcpy(name_command, comm_to_exec, len_command);

    if (comm_to_exec[len_command - 1] == '\0') {
        argv = NULL;
        return;
    }

    // ora devo calcolare il numero di argomenti presenti per capire quanti ptr devo usare
    // sposto ptr al primo char dopo ' '
    comm_to_exec += len_command;
    size_t num_space = 1;

    count_occurrence(
        &num_space,
        (char*) comm_to_exec,
        tot_len_command - len_command,
        ' '
    );

    *argc = num_space;

    // numero ptr a stringhe
    argv = kcalloc(num_space);
    if (!argv)
        kprintf("error data pool for argv");
}


O3 ainline void free_argv(i32 argc, char** argv)
{
    for (size_t idx = 0; idx < argc; idx++)
        kfree(argv[idx]);
}


u8 try_execute_comm(uchar* comm_to_execute)
{
    // char* name_command;
    // i32 argc = 0;
    // char** argv;

    // parse_prompt(name_command, &argc, argv, comm_to_execute);
 
    command_func_t func;

    func = patricia_search(
        command_tree,
        (char*) comm_to_execute
    );

    if (func)
        return func();

    // kfree_argv(argc, argv);
    return 0;
}


void init_commands()
{
    command_tree = create_node("");

    patricia_insert(command_tree, "CLS", cls);

    patricia_insert(command_tree, "REBOOT", reboot);

    patricia_insert(command_tree, "QUIT", power_off);

    patricia_insert(command_tree, "IFCONFIG", ifconfig);

    patricia_insert(command_tree, "RELOAD_TIME", reload_time);
}
