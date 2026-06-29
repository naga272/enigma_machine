#include "utilities/shell/command.h"
#include "utilities/idt/idt.h"


MODULE_LICENSE("GPL-3.0");
MODULE_AUTHOR("naga272");
MODULE_DESCRIPTION("spegnimento della macchina da lato user-land");


i32 do_reboot(struct regs_t* r)
{
    reboot();
    return 0;
}
