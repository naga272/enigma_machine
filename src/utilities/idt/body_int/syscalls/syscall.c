#include "config.h"
#include "utilities/idt/body_int/syscalls/syscall.h"
#include "utilities/idt/idt.h"


#define READ 0
#define WRITE 1

#define REAL_TOTAL_INT_CREATED 1


void read(struct regs_t *r)
{

}


void write(struct regs_t *r)
{

}


void (*elenco_ptr_syscalls[512])(struct regs_t *) = {
    read,
    write,
};


O3 void do_int80h(struct regs_t *r)
{
    if (r->eax > REAL_TOTAL_INT_CREATED)
        return;     // invalid no syscall

    elenco_ptr_syscalls[r->eax](r);
}
