#ifndef ARP_H
#define ARP_H


struct arp_packet {
    u16 htype;   // Ethernet = 1
    u16 ptype;   // IPv4 = 0x0800
    u8  hlen;    // MAC = 6
    u8  plen;    // IPv4 = 4
    u16 oper;    // 1 = request, 2 = reply

    u8  sha[6];  // sender MAC
    u32 spa;     // sender IP

    u8  tha[6];  // target MAC (0 in request)
    u32 tpa;     // target IP
} __attribute__((packed));


typedef struct arp_cache_entry { 
    u32 ip; // host byte order 
    u8 mac[6];
    u32 last_seen_ticks;
    u8 valid; 
} arp_cache_entry_t;


i32 arp_send_request(struct pci_device* nic, u32 target_ip);
extern i32 arp_send_request(struct pci_device* nic, u32 target_ip);

i32 arp_recv(struct pci_device* nic, u8* mac_out, u32 target_ip);
extern i32 arp_recv(struct pci_device* nic, u8* mac_out, u32 target_ip);

u32 ip_to_u32(u8 a, u8 b, u8 c, u8 d);
extern u32 ip_to_u32(u8 a, u8 b, u8 c, u8 d);

#endif