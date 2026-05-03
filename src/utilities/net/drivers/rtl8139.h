#ifndef RTL8139_H
#define RTL8139_H

#include "utilities/pci/pci.h"


struct rtl8139_device {
    struct pci_device dev;

    u32 io_base;

    u8 mac[6];

    u8* rx_buffer;
};


void init_rtl8139(struct pci_device*);
extern void init_rtl8139(struct pci_device*);

#endif
