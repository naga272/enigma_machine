#include "config.h"
#include "utilities/idt/body_int/syscalls/syscall.h"
#include "utilities/idt/idt.h"
#include "config.h"

#define READ 0
#define WRITE 1

#define REAL_TOTAL_INT_CREATED 4


i32 read(struct regs_t *r)
{

    return 0;
}


i32 write(struct regs_t *r)
{
    return 0;
}


i32 open(struct regs_t *r)
{
    return 0;
}


i32 close(struct regs_t *r)
{
    return 0;
}


i32 (*elenco_ptr_syscalls[OS_TOTAL_INTERRUPTS])(struct regs_t *) = {
    read,
    write,
    open,
    close
};


O3 i32 do_int80h(struct regs_t *r)
{
    if (r->eax > REAL_TOTAL_INT_CREATED - 1)
        return -ENOSYS;     // invalid no syscall

    return elenco_ptr_syscalls[r->eax](r);
}
