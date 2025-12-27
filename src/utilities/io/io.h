#ifndef IO_H
#define IO_H

unsigned char insb(unsigned char port);
unsigned char insw(unsigned char port);

void outb(unsigned short port, unsigned char val);
void outw(unsigned short port, unsigned short val);

#endif