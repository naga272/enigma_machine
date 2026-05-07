#ifndef RTL8139_H
#define RTL8139_H

#include "utilities/pci/pci.h"


/*
* struct incapsulata da pci_device
* pci_device->priv = (void*) struct rtl8139_device
*
*/
typedef struct rtl8139_device {
    u32 io_base;
    u8 mac[6];
    u8* rx_buffer;
    u32 cur_rx;
} rtl8139_dev_t;


void init_rtl8139(struct pci_device*);
extern void init_rtl8139(struct pci_device*);

#endif
