#ifndef RTL8139_H
#define RTL8139_H

#include "utilities/pci/pci.h"


#define TSAD0 0x20
#define TSD0  0x10

#define RBSTART 0x30
#define CR      0x37
#define CAPR    0x38
#define RCR     0x44


/*
* struct incapsulata da pci_device
* pci_device->priv = (void*) struct rtl8139_device
da testare>:
static u8 rtl_tx_buffer[2048] __attribute__((aligned(16)));
static u8 rtl_rx_buffer[8192 + 16 + 1500] __attribute__((aligned(16)));
*/
typedef struct rtl8139_device {
    u32 io_base;
    u8 mac[6];
    u8* rx_buffer;
    u32 cur_rx;
    u8* tx_buffer;
} rtl8139_dev_t;


void init_rtl8139(struct pci_device*);
extern void init_rtl8139(struct pci_device*);

#endif
