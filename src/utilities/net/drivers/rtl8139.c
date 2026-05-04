#include "utilities/net/drivers/rtl8139.h"
#include "utilities/memory/heap/malloc.c"
#include "utilities/video/video.h"


/*
*   PCI Scan    (fatto: utilities/pci/pci.c)
*      v
*   pci_dev_list_t* nics    (fatto: utilities/pci/pci.c)
*      v
*     MAC   (fatto: utilities/net/drivers/rtl8139.c)
*      v
*     reset     (fatto: utilities/net/drivers/rtl8139.c)
*      v
*    RX buffer
*      v
*    Enable RX/TX
*      v
*   Ethernet frame send/receive
*      v
*     ARP
*      v
*     IP
*      v
*    UDP/TCP
*      v
*     (:D)
*/


extern void print_hex(size_t);

#define DEBUG
#undef DEBUG


O3 static inline void set_mac_address(struct rtl8139_device* rtl)
{
    /*
    * Tramite l'indirizzo di BAR0 ricavato durante lo scan del PCI
    * si prende il mac address, coppia per coppia
    * */

    for (u8 i = 0; i < 6; i++)
        rtl->mac[i] = insb(rtl->io_base + i);
}


O3 static inline void reset_rtl(struct rtl8139_device* rtl)
{
    /*
    * A questo punto rtl potrebbe avere i registri ancora sporchi
    * causa operazioni fatte l'ultima volta all'accensione della macchina,
    * quindi mi occupo di pulire tutto il contenuto (evita bug).
    */

    outb(rtl->io_base + 0x37, 0x10);

    // il reset non e' istantaneo, aspetta che finisca
    while (insb(rtl->io_base + 0x37) & 0x10);
}


O3 void init_rtl8139(struct pci_device* device) 
{
    struct rtl8139_device rtl;
    rtl.dev = *device;

    rtl.io_base = (u32) rtl.dev.bar[0].addr;

    set_mac_address(&rtl);

    reset_rtl(&rtl);
    
    
    /* RX Buffer:
    * 8192 + RX ring
    * 16   + alignment
    * 1500 = max Ethernet frame
    * ----
    * 9708
    */
    rtl.rx_buffer = kmalloc(sizeof(char) * 9708);

    outl((u16) (rtl.io_base + 0x30), (u32) rtl.rx_buffer);

    outl((u16) (rtl.io_base + 0x44), 0x0000E70F);

    outb((u16) (rtl.io_base + 0x37), 0x0C);


#ifdef DEBUG
    // qemu crea una scheda di rete col seguente MAC:
    // 52:54:00:12:34:56
    print_hex(rtl.mac[0]);
    print((uchar*) ":");
    
    print_hex(rtl.mac[1]);
    print((uchar*) ":");
    
    print_hex(rtl.mac[2]);
    print((uchar*) ":");

    print_hex(rtl.mac[3]);
    print((uchar*) ":");
    
    print_hex(rtl.mac[4]);
    print((uchar*) ":");
    
    print_hex(rtl.mac[5]);
    print((uchar*) "\n");
#endif

}
