#ifndef PIC_H
#define PIC_H

#include "utilities/io/io.h"
#include "utilities/memory/heap/malloc.h"
#include "utilities/video/video.h"


#define CONFIG_ADDRESS 0xCF8
#define CONFIG_DATA 0xCFC
#define PCI_NONE 0xFFFF
#define DEVICE_INESISTENTE(vendor) (vendor == PCI_NONE)


struct pci_bar {
    u64 addr;
    u8 type;   // 0 = MMIO, 1 = IO
    u8 is64;
};


/*
* al posto di scannerizzare tutto PCI ogni volta quando devo prendere
* un dispositivo, scansioni una volta sola e me lo metto da parte
*
* struct pci_device:
*  @bus -> quale bus del pci    // asse x
*  @slot -> idx device          // asse y
*  @func -> idx func device     // asse y
*
*  @vendor -> identificativo del produttore hardware
*  @device -> device id (modello specifico del dispositivo)
*  @class_code -> categoria generale hardware (nic)
*  @subclass -> sottocategoria specifica del dispositivo (ethernet controller, )
*  @priv -> ptr a struct con caratteristiche specifiche del device
*  @priv_method -> metodi usabili sul device
*/

struct pci_device {
    u16 bus;
    u8 slot;
    u8 func;
    
    u16 vendor;
    u16 device;

    void* priv;

    u8 class_code;
    u8 subclass;

    void* priv_methods;

    struct pci_bar bar[6];
};


struct virt_pci_dev {
    struct pci_device *dev;
    size_t tot_num_device;
};


/* pci controller device struct */
typedef struct virt_pci_dev pci_dev_list_t;


#ifdef INIT_PCI_STRUCT_LIST

// array di gpu device
pci_dev_list_t* gpus = NULL;

// array di network interface controller
pci_dev_list_t* nics = NULL;

// array di Mass storage controller
pci_dev_list_t* massStocs = NULL;

// array di bridge controller
pci_dev_list_t* brcs = NULL;

#endif


void search_all_device_pci();
extern void search_all_device_pci();
extern void set_message_x_panic(uchar* msg);
extern pci_dev_list_t* get_nics();

#endif