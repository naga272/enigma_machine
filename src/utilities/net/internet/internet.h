#ifndef INTERNET_H
#define INTERNET_H


#define IPV4 0x0800
#define ICMP 1
#define TCP 6
#define UDP 17


#define IPV4_FLAG_DF 0x4000 // Don't Fragment 
#define IPV4_FLAG_MF 0x2000 // More Fragments 
#define IPV4_FRAG_OFF_MASK 0x1FFF


typedef struct ipv4_header { 
    u8 ver_ihl;             // 4 bit version (4), 4 bit IHL (header length in 32-bit words, tipico 5) 
    u8 tos;                 // DSCP/ECN (mettilo 0 all’inizio)
    u16 total_length;       // header + payload (in network byte order) 
    u16 identification;     // per frammentazione
    u16 flags_fragoff;      // 3 bit flags + 13 bit fragment offset 
    u8 ttl;                 // time to live 
    u8 protocol;            // es. 1=ICMP, 6=TCP, 17=UDP
    u16 header_checksum;    // checksum su solo header
    u32 src;                // indirizzo sorgente 
    u32 dst;                // indirizzo destinazione 
} attribute((packed)) ipv4_header_t;

#endif