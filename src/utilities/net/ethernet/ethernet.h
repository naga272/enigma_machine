#ifndef ETHERNET_H
#define ETHERNET_H

#include "utilities/net/net.h"
#include "config.h"


#define PROTOCOL_ARP  0x0806
#define PROTOCOL_IPV4 0x0800
#define PROTOCOL_IPV6 0x08DD


struct ethernet_frame {
    u8 dst[6];
    u8 src[6];
    u16 ethertype;
    u8 payload[];       // dimensione variabile
} __attribute__((packed));


i32 ethernet_send(struct pci_device* nic, u8* dst, u16 ethertype, void* payload, u32 payload_len);
extern i32 ethernet_send(struct pci_device* nic, u8* dst, u16 ethertype, void* payload, u32 payload_len);

i32 ethernet_recv(struct pci_device* nic, void* out, u32 max_len);
extern i32 ethernet_recv(struct pci_device* nic, void* out, u32 max_len);

#endif