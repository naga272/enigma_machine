#include "utilities/net/ethernet/ethernet.h"
#include "utilities/net/ethernet/arp/arp.h"
#include "utilities/net/net.h"
#include "utilities/conversion/conversion.h"
#include "utilities/stdlib/stdlib.h"
#include "utilities/string/string.h"


/*
* ==== modulo per il LIVELLO 2 TCP/IP (ETHERNET) ====
* arp_send_request() (arp.c)
*    v
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
*                 |
*          arp_send_request()  -> layer 2
*                 |
*           ethernet_send()    -> layer 2
*                 |
*            vsend_nic()       -> layer 1
*            /    |    \
*           /     |     \
*   driver_1.c    |      driver_3.c
*                 |
*             driver_2.c
*/


#define PROTOCOL_ARP  0x0806


O3 i32 arp_send_request(struct pci_device* nic, u32 target_ip)
{
    struct arp_packet arp = {0};

    arp.htype = htons_16b(1);
    arp.ptype = htons_16b(0x0800);
    arp.hlen  = 6;
    arp.plen  = 4;
    arp.oper  = htons_16b(1);

    memcpy(
        arp.sha,
        ((net_ops_t*) nic->priv_methods)->get_mac_addr_dev(nic),
        6
    );

    arp.spa = htons_32b(0);

    memset(arp.tha, 0, 6);
    arp.tpa = htons_32b(target_ip);

    return ethernet_send(
        nic,
        (u8[]){0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF},
        PROTOCOL_ARP,
        &arp,
        sizeof(arp)
    );
}


O3 i32 arp_recv(struct pci_device* nic, u8* mac_out, u32 target_ip)
{
    u8 buffer[1600];

    i32 len = vrecv_nic(nic, buffer, sizeof(buffer));
    if (len <= 0)
        return -1;

    struct ethernet_frame* eth = (struct ethernet_frame*)buffer;

    if (eth->ethertype != 0x0806)
        return -1;

    struct arp_packet* arp = (struct arp_packet*)eth->payload;

    if (htons_16b(arp->oper) != 2)
        return -1;

    if (arp->spa != htons_32b(target_ip))
        return -1;

    memcpy(mac_out, arp->sha, 6);

    return 1;
}
