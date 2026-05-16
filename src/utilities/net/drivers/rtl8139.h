#ifndef RTL8139_H
#define RTL8139_H

#include "utilities/pci/pci.h"


#define TSAD0 0x20
#define TSD0  0x10

#define RBSTART 0x30
#define CR      0x37
#define CAPR    0x38
#define RCR     0x44

#define RX_RING 8192
#define ALIGNMENT 16 
#define MAXETHFRM 1500
#define RX_BUFFER RX_RING + ALIGNMENT + MAXETHFRM

#define TX_BUFFER 2048


/*
* struct incapsulata da pci_device
* pci_device->priv = (void*) struct rtl8139_device
*/
typedef struct rtl8139_device {
    u32 io_base;
    u8 mac[6];
    u32 cur_rx;
    u8 tx_buffer[2048] __attribute__((aligned(16)));
    u8 rx_buffer[RX_BUFFER] __attribute__((aligned(16)));
} rtl8139_dev_t;


void init_rtl8139(struct pci_device*);
extern void init_rtl8139(struct pci_device*);

#endif
