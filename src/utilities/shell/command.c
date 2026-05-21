#include "config.h"

#include "utilities/io/io.h"
#include "utilities/shell/command.h"
#include "utilities/string/string.h"
#include "utilities/video/video.h"
#include "utilities/video/kprintf.h"
#include "utilities/pci/pci.h"
#include "utilities/net/net.h"


#define OS_X_QEMU


#if defined(OS_X_QEMU) && defined(OS_X_XBOCHS) && defined(OS_X_X86)
    #error, "impossibile definire OS_X_QEMU, OS_X_XBOCHS, OS_X_X86 insieme"
#endif


extern pci_dev_list_t* nics;


uchar* vec_reboot_comm = (uchar*) "RELOAD";
uchar* vec_power_off_comm = (uchar*) "QUIT";
uchar* vec_cls_comm = (uchar*) "CLS";
uchar* vec_ifconfig_comm = (uchar*) "IFCONFIG";


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
        kprintf(
            "\n=== NIC NUMBER %i ===\nName: %s\nVendor: %s\nBar 0: %i\n",
            nics->tot_num_device,
            ((net_ops_t*) nic->priv_methods)->get_name_dev(nic),
            ((net_ops_t*) nic->priv_methods)->get_vendor_dev(nic),
            ((net_ops_t*) nic->priv_methods)->get_bar0_dev(nic)
        );
        ((net_ops_t*) nic->priv_methods)->print_mac(nic);
    }
    print((uchar*) "\n>>> ");
    return 1;
}


u8 try_execute_comm(uchar* comm_to_execute)
{
    if (strcmp(comm_to_execute, vec_cls_comm))
        return cls();

    if (strcmp(comm_to_execute, vec_reboot_comm))
        return reboot();

    if (strcmp(comm_to_execute, vec_power_off_comm))
        return power_off();

    if (strcmp(comm_to_execute, vec_ifconfig_comm))
        return ifconfig();

    return 0;
}
