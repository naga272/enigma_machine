#define INIT_PCI_STRUCT_LIST
#include "utilities/pci/pci.h"


/* Premesse
*
* https://it.wikipedia.org/wiki/Peripheral_Component_Interconnect
*
* Concetto di PCI
* il PCI serve a collegare la CPU con le periferiche interne
* usando la scheda madre
*
* Registri
* I registri di configurazione per una qualsiasi scheda che usa il bus PCI
* per comunicare si suddividono in registri mappati in memoria e in registri del
* PCI Configuration Space.
* il PCI Configuration Space e' una memoria per informazioni aggiuntive:
*   - Vendor ID: salvato in un registro da 16 bit, assegnato dalla casa produttrice del chip
*   - Device ID: salvato in un registro da 16 bit, assegnato dalla casa produttrice del chip
*   - Subsystem Vendor ID: contraddistingue la casa produttrice della scheda e il
*                          Subsystem Device ID è assegnato da essa per identificare la scheda
*   - Command Register: settato bit a bit e provvede a controllare il funzionamento della scheda secondo lo standard PCI.
*   - Status Register: registro dove vengono salvate informazioni relative agli eventi legati al bus PCI
*/


/*
* https://wiki.osdev.org/PCI#The_PCI_Bus
*/


extern void print_hex(size_t);
extern void print(const uchar*);


O3 static inline ainline u32 pci_read32(u8 bus, u8 slot, u8 func, u8 offset)
{
    /*
    * mi viene da piangere )=
    *
    * Costruzione indirizzo PCI:
    * bit 31:
    *    1 = abilita PCI config access
    * bus << 16:
    *    scelta del bus PCI
    * slot << 11:
    *    quale device sul bus
    * func << 8:
    *    sotto-funzione del device (multi-function devices)
    * offset & 0xFC:
    *    registro interno del device (allineamento 4 byte)
    */
    u32 address;

    address = (u32) (1 << 31)         |
        ((u32) bus  << 16)            |
        ((u32) slot << 11)            |
        ((u32) func << 8)             |
        ((u32) (offset & 0xFC));

    /*
    - gate 0xCF8 (CONFIG_ADDRESS):
    Quale device PCI vuoi interrogare?

    - gate 0xCFC (CONFIG_DATA):
    risultato dell'interrogazione a CONFIG_ADDRESS
    */
    outl(CONFIG_ADDRESS, address);
    return insl(CONFIG_DATA);
}


O3 void pci_write32(u8 bus, u8 slot, u8 func, u8 offset, u32 value)
{
    u32 address =
        (1U << 31) |
        ((u32) bus << 16) |
        ((u32) slot << 11) |
        ((u32) func << 8) |
        (offset & 0xFC);

    outl(0xCF8, address);
    outl(0xCFC, value);
}


O3 void pci_enable_device(struct pci_device* dev)
{
    // Abilita il dispositivo sul BUS PCI.
    u32 reg = pci_read32(dev->bus, dev->slot, dev->func, 0x04);

    // CPU può usare in/out sui BAR I/O
    reg |= (1 << 0); // I/O Space

    // NIC può fare DMA sulla RAM
    reg |= (1 << 2); // Bus Master

    pci_write32(dev->bus, dev->slot, dev->func, 0x04, reg);
}


O3 static inline ainline void pci_read_bars(struct pci_device *dev, u16 bus, u8 slot, u8 func)
{
    /* pci_read_bars
    *  Scopo:
    *      Legge e interpreta i Base Address Registers (BAR0-BAR5) di un
    *      dispositivo PCI, salvando dentro struct pci_device dove il device
    *      espone i propri registri hardware.
    *  Concetto:
    *      Per poter interagire con un dispositivo, bisogna conoscere la posizione dei
    *      suoi registri.
    *      L'idea e' quindi di catturare l'offset base dei registri
    *      per inserirli poi all'interno di @dev->bar[x].
    *      Ogni device PCI può avere fino a 6 BAR:
    *          BAR0 ... BAR5
    *
    *      Ogni BAR può rappresentare:
    *      - una regione I/O
    *      - una regione MMIO
    *
    *      In pratica:
    *      - BAR I/O     -> usa in/out (port mapped I/O)
    *      - BAR MMIO    -> usa memoria mappata (Memory Mapped I/O)
    *
    *      Esempio RTL8139:
    *      BAR0 = 0xC000
    *
    *      Significa:
    *      i registri della scheda sono accessibili da:
    *          insb(0xC000 + offset)
    *          outb(0xC000 + offset)
    *       (insb() e outb() sono in utilities/io/io.asm)
    *
    *  @dev:
    *      ptr alla struct pci_device da riempire
    *
    *  @bus:
    *      bus PCI del dispositivo
    *
    *  @slot:
    *      slot del bus PCI
    *
    *  @func:
    *      Function slot del bus PCI
    */
    u8 i = 0;

    while (i < 6) {
        u32 bar_low = pci_read32(bus, slot, func, 0x10 + i * 4);

        if (bar_low == 0 || bar_low == 0xFFFFFFFF) {
            dev->bar[i].addr = 0;
            dev->bar[i].type = 0;
            dev->bar[i].is64 = 0;
            i++;
            continue;
        }

        if (bar_low & 0x1) {
            // I/O BAR
            dev->bar[i].addr = bar_low & ~0x3;
            dev->bar[i].type = 1;
            dev->bar[i].is64 = 0;
            i++;
            continue;
        }

        // memory BAR
        u8 type = (bar_low >> 1) & 0x3;

        if (type == 0x2) {
            // 64-bit BAR
            u32 bar_high = pci_read32(bus, slot, func, 0x10 + (i + 1) * 4);

            dev->bar[i].addr =
                ((u64)bar_high << 32) |
                (bar_low & ~0xF);

            dev->bar[i].type = 0;
            dev->bar[i].is64 = 1;

            dev->bar[i + 1].addr = 0;
            dev->bar[i + 1].is64 = 1;

            i += 2;
        } else {
            // 32-bit BAR
            dev->bar[i].addr = bar_low & ~0xF;
            dev->bar[i].type = 0;
            dev->bar[i].is64 = 0;
            i++;
        }
    }
}


O3 static inline ainline u16 pci_get_vendor(u8 bus, u8 slot, u8 func)
{
    /*
    *  lettura del Vendor ID (identificativo del produttore hardware)
    *  di un dispositivo PCI presente in uno specifico bus/slot.
    *
    *  Il Vendor ID occupa i bit 0-15 del registro PCI offset 0x00.
    *
    *  Offset 0x00 layout:
    *   Bits 31-16 -> Device ID
    *   Bits 15-0  -> Vendor ID
    *
    *   Esempio:
    *      - 0x813910EC
    *        Vendor = 0x10EC (Realtek)
    *        Device = 0x8139
    *
    *  @bus:
    *    numero del bus PCI (0-255)
    *
    *  @slot:
    *    numero dello slot/device sul bus (0-31)
    *
    *  Return:
    *     Vendor ID
    *
    *  se == 0xFFFF:
    *      nessun dispositivo presente nello slot
    *
    */
    return (u16) (pci_read32(bus, slot, func, 0x00) & 0xFFFF);
}


O3 static inline ainline u16 pci_get_device(u8 bus, u8 slot, u8 func)
{
    /*     
    *   lettura del Device ID (modello specifico del dispositivo)
    *   di una periferica PCI.
    *
    *   Il Device ID occupa i bit 16-31 del registro offset 0x00.
    *
    *   Offset 0x00 layout:
    *      Bits 31-16 -> Device ID
    *      Bits 15-0  -> Vendor ID
    *
    *   argv:
    *       @bus: numero bus PCI
    *       @slot: numero slot PCI
    *
    *   ret: Device ID a 16 bit
    *
    *   Uso:
    *      Vendor + Device identificano precisamente l’hardware
    *
    *   esempio:
    *      0x813910EC
    *      device = 0x8139
    *      10EC + 8139 identificano il dispositivo RTL8139
    */
    return (u16) ((pci_read32(bus, slot, func, 0x00) >> 16) & 0xFFFF);
}


O3 static inline ainline u8 pci_get_class(u8 bus, u8 slot, u8 func)
{
    /* 
    *  lettura del Class Code principale del dispositivo PCI
    *  (la categoria generale hardware)
    *
    *   Registro:
    *       Offset 0x08
    *
    *   layout:
    *       Bits 31-24 -> Class Code
    *       Bits 23-16 -> Subclass
    *       Bits 15-8  -> Prog IF
    *       Bits 7-0   -> Revision ID
    *
    *   argv:
    *   @bus: bus PCI
    *   @slot: slot PCI
    *
    *   ret: Class code a 8 bit
    *
    *   classi esempio:
    *      0x01 -> Mass Storage Controller
    *      0x02 -> Network Controller
    *      0x03 -> Display Controller
    *      0x06 -> Bridge Device
    */
    return (u8) ((pci_read32(bus, slot, func, 0x08) >> 24) & 0xFF);
}


O3 static inline ainline u8 pci_get_subclass(u8 bus, u8 slot, u8 func)
{
    /*
    * lettura della sottocategoria specifica del dispositivo PCI.
    * Serve a distinguere dispositivi della stessa classe, es:
    *
    *   registro:
    *       Offset 0x08
    *
    *   layout:
    *       Bits 31-24 -> Class
    *       Bits 23-16 -> Subclass
    *
    *   argv:
    *       @bus: bus PCI
    *       @slot: slot PCI
    *
    *   ret: subclass code
    *
    *   esempi di valore per il return:
    *       0x00 -> Unclassified
    *       0x01 -> Mass Storage Controller
    *       0x02 -> Network Controller => quello che serve a me >:D
    *       0x03 -> Display Controller
    *       0x06 -> Bridge Device
    *       0x0C -> Serial Bus Controller
    */
    return (u8) ((pci_read32(bus, slot, func, 0x08) >> 16) & 0xFF);
}


O3 static inline ainline pci_dev_list_t* dynamic_insert_in_struct(pci_dev_list_t* array, struct pci_device *dev)
{
    /*
    * Per evitare di scrivere questo codice per tutte le funzioni dei vari dispositivi,
    * ho deciso di astrarre.
    * */
    if (array == NULL) {
        array = kmalloc(sizeof(pci_dev_list_t));

        if (!array)
            kprintd((uchar*) "Error alloc in insert_in_network_controller (nic == null)");

        array->dev = kmalloc(sizeof(struct pci_device));
        array->tot_num_device = 0;
    } else {    
        array->dev = krealloc(
            array->dev,
            array->tot_num_device * sizeof(struct pci_device),
            (array->tot_num_device + 1) * sizeof(struct pci_device)
        );
    }

    if (!array->dev)
        kprintd((uchar*) "Error realloc in insert_in_network_controller (nic == null)");

    array->dev[array->tot_num_device] = *dev;
    array->tot_num_device++;
    return array;
}


O3 static inline ainline void pci_memorize_device(struct pci_device *dev)
{
    /*
    *  classi:
    *      0x01 (ID_MSC) -> Mass Storage Controller (dispositivo di archiviazione)
    *      0x02 (ID_NIC) -> Network Controller
    *      0x03 (ID_DC) -> Display Controller
    *      0x06 (ID_BD) -> Bridge Device
    */
    switch (dev->class_code) {
        case ID_ERR:
            break;  // dispositivo non riconosciuto
        case ID_MSC:
            massStocs = dynamic_insert_in_struct(massStocs, dev);
            break;
        case ID_NIC:
            nics = dynamic_insert_in_struct(nics, dev);
            break;
        case ID_DC:
            gpus = dynamic_insert_in_struct(gpus, dev);
            break;
        case ID_BD:
            brcs = dynamic_insert_in_struct(brcs, dev);
            break;    
        default:
            return;
    }
}


O3 void search_all_device_pci()
{
    for (u16 bus = 0; bus < 256; bus++) {
        for (u8 slot = 0; slot < 32; slot++) {
            for (u8 func = 0; func < 8; func++) {
                u16 vendor = pci_get_vendor(bus, slot, func);

                if (DEVICE_INESISTENTE(vendor))
                    continue;

                struct pci_device dev = { 0 };

                dev.bus         = bus;
                dev.slot        = slot;
                dev.vendor      = vendor;
                dev.func        = func;

                dev.device      = pci_get_device(bus, slot, func);
                dev.class_code  = pci_get_class(bus, slot, func);
                dev.subclass    = pci_get_subclass(bus, slot, func);

                pci_read_bars(&dev, bus, slot, func);
                pci_memorize_device(&dev);
                pci_enable_device(&dev);
            }
        }
    }
}
