#ifndef SYSCALL_H
#define SYSCALL_H

#include "utilities/idt/idt.h"


extern void do_int80h(struct regs_t *);
void do_int80h(struct regs_t *);

#endif
