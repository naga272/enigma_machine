#include "utilities/net/net.h"
#include "utilities/net/drivers/rtl8139.h"
#include "utilities/memory/heap/malloc.h"
#include "utilities/video/video.h"
#include "utilities/string/string.h"


extern void print_hex(size_t);

#define RX_RING 8192
#define ALIGNMENT 16 
#define MAXETHFRM 1500
#define RX_BUFFER RX_RING + ALIGNMENT + MAXETHFRM


#define RTL_BUFF_OFFS(nic)      ((u16) (nic->io_base + 0x30)) 
#define RCR_OFFS(nic)           ((u16) (nic->io_base + 0x44))
#define POWER_OFFS_RTL(nic)     ((u16) (nic->io_base + 0x37))  
#define RTL_RX_OK   (1 << 0)
#define RTL_RX_ERR  (1 << 1)

#define DEBUG
// #undef DEBUG


O3 static inline uchar* get_name_dev_rtl8139(struct pci_device* nic)
{
    return (uchar*) "rtl8139";
}


O3 static inline void insert_mac_addr_in_struct(rtl8139_dev_t* rtl)
{
    /*
    * Tramite l'indirizzo di BAR0 ricavato durante lo scan del PCI
    * si prende il mac address, coppia per coppia
    * */
    for (u8 i = 0; i < 6; i++)
        rtl->mac[i] = insb(rtl->io_base + i);
}


O3 static inline u8* get_mac_addr_dev(struct pci_device* nic)
{
    rtl8139_dev_t* rtl = (rtl8139_dev_t*) nic->priv;
    return rtl->mac;
}


O3 static inline void print_mac(struct pci_device* nic)
{
    rtl8139_dev_t* rtl = (rtl8139_dev_t*) nic->priv;

#ifdef DEBUG
    // qemu crea una scheda di rete col seguente MAC:
    // 52:54:00:12:34:56
    print_hex(rtl->mac[0]);
    print((uchar*) ":");
    
    print_hex(rtl->mac[1]);
    print((uchar*) ":");
    
    print_hex(rtl->mac[2]);
    print((uchar*) ":");

    print_hex(rtl->mac[3]);
    print((uchar*) ":");
    
    print_hex(rtl->mac[4]);
    print((uchar*) ":");
    
    print_hex(rtl->mac[5]);
    print((uchar*) "\n");
#endif
}


O3 static inline void reset_rtl8139(struct pci_device* nic)
{
    /*
    * A questo punto rtl potrebbe avere i registri ancora sporchi
    * causa operazioni fatte l'ultima volta all'accensione della macchina,
    * quindi mi occupo di pulire tutto il contenuto (evita bug).
    */
    rtl8139_dev_t* rtl = (rtl8139_dev_t*) nic->priv;

    outb(rtl->io_base + 0x37, 0x10);

    // il reset non e' istantaneo, aspetta che finisca
    while (insb(rtl->io_base + 0x37) & 0x10);
}


O3 static inline void check_isr(struct pci_device* nic)
{
    /* Interrupt Status Register
    * La RTL8139 aggiorna alcuni bit quando succedono eventi:
    * - pacchetto ricevuto
    * - trasmissione completata
    * - errore TX
    * - errore RX
    * - buffer overflow
    *
    * TX OK: 0x0004
    * RX OK: 0x0001
    * TX Error: 0x0008
    * NIC non sta processando: 0x0000
    */
    rtl8139_dev_t* rtl = (rtl8139_dev_t*) nic->priv;

    if (!rtl)
        return;

    u16 isr = insw(rtl->io_base + 0x3E);

    print((uchar*) "\nISR: ");
    print_hex((u32) isr);

    // clear interrupt flags
    outw(rtl->io_base + 0x3E, isr);
}


O3 static inline i32 send_rtl8139(struct pci_device* dev, void* data, u32 len)
{
    rtl8139_dev_t* rtl = dev->priv;

    if (!rtl || !data || len == 0 || len > 1514)
        return -1;

    print((uchar*) "\nbefore send isr: ");
    check_isr(dev);

    memcpy(rtl->tx_buffer, data, len);

    // TSAD0 = buffer address
    outl(rtl->io_base + TSAD0, (u32)rtl->tx_buffer);

    // TSD0 = length + start
    outl(rtl->io_base + TSD0, len);

    print((uchar*) "\nafter send isr: ");
    check_isr(dev);
    print((uchar*) "\n");
    
    return len;
}


O3 static inline i32 recv_rtl8139(struct pci_device* dev, void* out, u32 max_len)
{
    rtl8139_dev_t* rtl = dev->priv;

    u8* pkt = rtl->rx_buffer + rtl->cur_rx;

    u16 status = *(u16*) (pkt);
    u16 len    = *(u16*) (pkt + 2);

    if (!(status & RTL_RX_OK))
        return -1;

    if (status & (1 << 1)) // error bit
        set_message_x_panic((uchar*) "status error");

    print_hex(status);
    print_hex(len);

    memcpy(out, pkt + 4, len);

    rtl->cur_rx = (rtl->cur_rx + len + 4 + 3) & ~3;
    rtl->cur_rx %= RX_BUFFER;

    // aggiorna CAPR
    outw(rtl->io_base + CAPR, rtl->cur_rx - 4);

    return len;
}


O3 static inline void init_tx_buffer_rtl8139(struct pci_device* nic)
{
    rtl8139_dev_t* rtl = (rtl8139_dev_t*) nic->priv;

    rtl->tx_buffer = kmalloc(1500);
    if (!rtl->tx_buffer)
        set_message_x_panic((uchar*) "alloc error tx_buffer");
}


O3 static inline void init_rx_buffer_rtl8139(struct pci_device* nic)
{
    /* RX Buffer:
    * 8192 + RX ring
    * 16   + alignment
    * 1500 = max Ethernet frame
    * ----
    * 9708
    */
    rtl8139_dev_t* rtl = (rtl8139_dev_t*) nic->priv;

    rtl->rx_buffer = kmalloc(sizeof(char) * RX_BUFFER);
    if (!rtl->rx_buffer)
        set_message_x_panic((uchar*) "alloc error rtx->rx_buffer");

    // comunicazione con l'rtl8139 di dove si trova il buffer in rx in ram
    outl(RTL_BUFF_OFFS(rtl), (u32) rtl->rx_buffer);

    /* 0x44 = RCR (Receive Configuration Register)
    * RCR decide:
    * - pacchetti da accettare
    * - dimensione buffer (8, 16, 32, 64 kb)
    * - DMA Burst (quanti dati la NIC trasferisce per burst)
    * - wrapping (quando il buffer finisce, torna allo start)
    */
    outl(RCR_OFFS(rtl), 0x0000E70F);
}


O3 static inline void power_on(struct pci_device* nic)
{
    /* 
    * accensione della scheda di rete tramite CR (command register).
    * 0x04 +  RX Enable
    * 0x08 =  TX Enable
    * ------
    * 0x0C
    */
    rtl8139_dev_t* rtl = (rtl8139_dev_t*) nic->priv;
    outb(POWER_OFFS_RTL(rtl), 0x0C);
}


O3 void init_rtl8139(struct pci_device* device) 
{
    rtl8139_dev_t *rtl8139 = kcalloc(sizeof(rtl8139_dev_t));
    net_ops_t* ops_rtl8139 = (net_ops_t*) kcalloc(sizeof(net_ops_t));

    if (!rtl8139)
        set_message_x_panic((uchar*) "alloc error struct rtl8139_dev_t");

    if (!ops_rtl8139)
        set_message_x_panic((uchar*) "alloc error struct ops_rtl8139");

    device->priv = (void*) rtl8139;

    rtl8139->io_base = (u32) device->bar[0].addr;
    rtl8139->cur_rx = 0;

    insert_mac_addr_in_struct(rtl8139);

    ops_rtl8139->get_name_dev = get_name_dev_rtl8139;
    ops_rtl8139->get_mac_addr_dev = get_mac_addr_dev;
    ops_rtl8139->init_rx_buffer = init_rx_buffer_rtl8139;
    ops_rtl8139->init_tx_buffer = init_tx_buffer_rtl8139;
    ops_rtl8139->reset = reset_rtl8139;
    ops_rtl8139->power_on = power_on;
    ops_rtl8139->send = send_rtl8139;
    ops_rtl8139->recv = recv_rtl8139;
    ops_rtl8139->print_mac = print_mac;

    device->priv_methods = (void*) ops_rtl8139;
}
