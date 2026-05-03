#ifndef IO_H
#define IO_H

#include "config.h"

uchar insb(ushort port);
ushort insw(ushort port);
u32 insl(u16 port);

void outb(ushort port, uchar val);
void outw(ushort port, ushort val);
void outl(u16 port, u32 value);

#endif