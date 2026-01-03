#ifndef SYSCALL_H
#define SYSCALL_H

#include "utilities/idt/idt.h"


extern i32 do_int80h(struct regs_t *);
i32 do_int80h(struct regs_t *);

#endif
