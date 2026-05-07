#ifndef NET_H
#define NET_H

#include "utilities/video/video.h"
#include "utilities/pci/pci.h"
#include "utilities/io/io.h"


void init_scheda_rete();
extern void init_scheda_rete();


typedef struct net_ops {
    uchar* (*get_name_dev) (struct pci_device* nic);
    uchar* (*get_mac_addr_dev) (struct pci_device* nic);
    i32 (*send) (struct pci_device* nic, void* data, u32 len);
    i32 (*recv) (struct pci_device* nic, void* out_buffer, u32 max_len);
    void (*reset) (struct pci_device* nic);
    void (*power_on) (struct pci_device* nic);
    void (*init_rx_buffer) (struct pci_device* nic);
    void (*print_mac) (struct pci_device* nic);
} net_ops_t;


#define IS_RTL8139_CHIP(nic) (nic->vendor == 0x10EC && nic->device == 0x8139)

#endif