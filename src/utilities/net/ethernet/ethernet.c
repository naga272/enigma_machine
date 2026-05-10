
#include "utilities/string/string.h"
#include "utilities/conversion/conversion.h"
#include "utilities/net/ethernet/ethernet.h"
#include "utilities/net/net.h"


/*
* ==== modulo per il LIVELLO 2 TCP/IP (ETHERNET) ====
*
* ethernet_send()    (ethernet.c)
*    v
*  build_frame       (ethernet.c)
*    v
*  vsend_nic()       (net.c)
*    v
*  send_rtl8139()    (rtl8139.c)
*
*
* es:
*
*           ethernet_send()    -> layer 2
*                 |
*            vsend_nic()       -> layer 1
*            /    |    \
*           /     |     \
*   driver_1.c    |      driver_2.c
*                 |
*             driver_2.c
*/


/*
* struct ethernet_frame 
* [dst][src][ethertype][payload]
* @dst: Lo scopo e' di indicare chi e' il destinatario del frame:
* @src: chi invia il frame
* @ethertype: tipo payload (che protocollo viene usato nel payload).
*             NB: big endian (network byte order), usare htons();
* @payload: paccehtto ARP
*
* Es:
* [FF:FF:FF:FF:FF:FF][52:54:00:12:34:56][0x0806][...]
* Significa:
* 52:54:00:12:34:56 manda in broadcast qualcosa in LAN usando il protocollo ARP (0x0806)
*/


i32 ethernet_send(struct pci_device* nic, u8* dst, u16 ethertype, void* payload, u32 payload_len)
{
    u32 actual_payload_len = (payload_len < 46) ? 46 : payload_len;
    u32 frame_len = sizeof(struct ethernet_frame) + actual_payload_len;

    struct ethernet_frame* frame = kcalloc(frame_len);
    if (!frame) {
        print((uchar*) "kcalloc error frame in ethernet_send");
        return -1;
    }

    u8* mac_offset = ((net_ops_t*) nic->priv_methods)->get_mac_addr_dev(nic);
    
    memcpy(frame->dst, dst, 6);
    memcpy(frame->src, mac_offset, 6);

    frame->ethertype = htons_16b(ethertype);

    memcpy(frame->payload, payload, actual_payload_len);
    // memcpy(frame->payload, payload, payload_len);

    i32 response = vsend_nic(nic, frame, frame_len);

    kfree(frame);
    return response;
}


i32 ethernet_recv(struct pci_device* nic, void* out, u32 max_len)
{
    u8* frame = kmalloc(1600);

    i32 len = vrecv_nic(nic, frame, 1600);
    if (len <= 14)
        return -1;

    struct ethernet_frame* eth = (void*) frame;

    u16 type = eth->ethertype;
    if (type == htons_16b(PROTOCOL_ARP))
        print((uchar*) "protocollo ARP\n");

    u32 payload_len = len - 14;

    if (payload_len > max_len) return -1;

    memcpy(out, eth->payload, payload_len);

    kfree(frame);
    return payload_len;
}
