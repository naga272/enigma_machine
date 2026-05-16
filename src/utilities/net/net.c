#include "utilities/net/net.h"
#include "utilities/net/drivers/rtl8139.h"


/*
* ==== modulo per il LIVELLO 1 TCP/IP (FISICO) ====
* questo file ha il compito di instradare al driver corretto della scheda di rete
* i dati.
* Questo modulo quindi, consente di trattare nic diversi allo stesso modo.
* es:
*
*            vsend_nic()
*            /    |    \
*           /     |     \
*   driver_1.c    |      driver_2.c
*                 |
*             driver_2.c
*
* ogni driver ha il suo send() perche' i nic potrebbero funzionare in modi diversi
*/


/* Steps:
*
*   PCI Scan    (fatto: utilities/pci/pci.c)
*      v
*   pci_dev_list_t* nics    (fatto: utilities/pci/pci.c)
*      v
*     MAC   (fatto: utilities/net/drivers/<driver_dev>.c)
*      v
*     reset     (fatto: utilities/net/net.c)
*      v
*    RX buffer  (fatto: utilities/net/net.c)
*      v
*    Enable RX/TX   (fatto: utilities/net/net.c)
*      v
*   Ethernet frame send/receive (not yet ready)
*      v
*     ARP
*      v
*     IP
*      v
*    UDP/TCP
*      v
*     (:D)
*/


extern pci_dev_list_t* nics;
extern void print_hex(size_t);


O3 i32 vrecv_nic(struct pci_device* nic, void* data, u32 len)
{
    // virtual recv (binding al recv del driver specifico)

    // print_hex((size_t) ((net_ops_t*) nic->priv_methods)->recv);

    return ((net_ops_t*) nic->priv_methods)->recv(nic, data, len);
}


O3 i32 vsend_nic(struct pci_device* nic, void* data, u32 len) 
{
    // virtual send (binding al send del driver specifico)
    return ((net_ops_t*) nic->priv_methods)->send(nic, data, len);
}


O3 static inline ainline u32 pci_read32(u8 bus, u8 slot, u8 func, u8 offset)
{
    u32 address;

    address = (u32) (1 << 31)         |
        ((u32) bus  << 16)            |
        ((u32) slot << 11)            |
        ((u32) func << 8)             |
        ((u32) (offset & 0xFC));

    outl(CONFIG_ADDRESS, address);
    return insl(CONFIG_DATA);
}


O3 static inline void init_nic_driver(struct pci_device* nic)
{
    /*
    * Ogni nic ha il suo modo per funzionare,
    * quindi faccio una serie di if per "mapparli" con il loro driver.
    * @nic->priv: contiene informazioni del device nello specifico
    * @nic->priv_methods: ptr a tutti i metodi disponibile per quel device.
    *
    * Sono ptr a funzione che puntano direttamente alle funzioni di un driver.
    * Il "mapping" avviene in "init_<nome_device>" del driver
    **/
    if (IS_RTL8139_CHIP(nic)) {
        init_rtl8139(nic);
        goto out;
    }

    // else if () {
    //      ...
    //      goto out;
    // }
    // etc...

    return;
out:
    ((net_ops_t*) nic->priv_methods)->reset(nic);
    ((net_ops_t*) nic->priv_methods)->power_on(nic);
    ((net_ops_t*) nic->priv_methods)->print_mac(nic);
    ((net_ops_t*) nic->priv_methods)->init_rx_buffer(nic);
}


O3 void init_scheda_rete()
{
    // print_hex(nics->tot_num_device);

    for (size_t idx = 0; idx != nics->tot_num_device; idx++)
        init_nic_driver(&nics->dev[idx]);

    return;
}
