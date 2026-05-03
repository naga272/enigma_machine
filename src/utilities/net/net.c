#include "utilities/net/net.h"
#include "utilities/net/drivers/rtl8139.h"


extern pci_dev_list_t* nics;
extern void print_hex(size_t);


O3 static inline void init_nic_driver(struct pci_device* nic)
{
    /*
    * Ogni nic ha il suo modo per funzionare,
    * quindi faccio una serie di if per "mapparli" con il loro driver.
    **/
    if (IS_RTL8139_CHIP(nic))
        init_rtl8139(nic);

    // else if ()
    //      ...
    // etc...
}


O3 void init_scheda_rete()
{
    // print_hex(nics->tot_num_device);

    for (size_t idx = 0; idx != nics->tot_num_device; idx++)
        init_nic_driver(&nics->dev[idx]);

    return;
}
