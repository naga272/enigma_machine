#include "utilities/net/net.h"
#include "utilities/net/drivers/rtl8139.h"


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
    return ((net_ops_t*) nic->priv_methods)->recv(nic, data, len);
}


O3 i32 vsend_nic(struct pci_device* nic, void* data, u32 len) 
{
    // virtual send (binding al send del driver specifico)
    return ((net_ops_t*) nic->priv_methods)->send(nic, data, len);
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
    ((net_ops_t*) nic->priv_methods)->init_rx_buffer(nic);
    ((net_ops_t*) nic->priv_methods)->power_on(nic);
    ((net_ops_t*) nic->priv_methods)->print_mac(nic);
}


O3 void init_scheda_rete()
{
    // print_hex(nics->tot_num_device);

    for (size_t idx = 0; idx != nics->tot_num_device; idx++)
        init_nic_driver(&nics->dev[idx]);

    return;
}
