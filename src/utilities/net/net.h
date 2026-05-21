#ifndef NET_H
#define NET_H

#include "utilities/video/video.h"
#include "utilities/pci/pci.h"
#include "utilities/io/io.h"


void init_scheda_rete();
extern void init_scheda_rete();

i32 vrecv_nic(struct pci_device* nic, void* data, u32 len);
i32 vsend_nic(struct pci_device* nic, void* data, u32 len);

extern i32 vsend_nic(struct pci_device* nic, void* data, u32 len);
extern i32 vrecv_nic(struct pci_device* nic, void* data, u32 len);

typedef struct net_ops {
    uchar* (*get_name_dev) (struct pci_device* nic);
    uchar* (*get_vendor_dev) (struct pci_device* nic);
    u8* (*get_mac_addr_dev) (struct pci_device* nic);
    i32 (*send) (struct pci_device* nic, void* data, u32 len);
    i32 (*recv) (struct pci_device* nic, void* out_buffer, u32 max_len);
    void (*reset) (struct pci_device* nic);
    void (*power_on) (struct pci_device* nic);
    void (*init_rx_buffer) (struct pci_device* nic);
    void (*init_tx_buffer) (struct pci_device* nic);
    void (*print_mac) (struct pci_device* nic);
    i32 (*get_bar0_dev) (struct pci_device* nic);
} net_ops_t;


#define IS_RTL8139_CHIP(nic) (nic->vendor == 0x10EC && nic->device == 0x8139)

#endif