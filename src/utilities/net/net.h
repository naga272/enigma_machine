#ifndef NET_H
#define NET_H

#include "utilities/video/video.h"
#include "utilities/pci/pci.h"
#include "utilities/io/io.h"

void init_scheda_rete();
extern void init_scheda_rete();


#define IS_RTL8139_CHIP(nic) (nic->vendor == 0x10EC && nic->device == 0x8139)


#endif