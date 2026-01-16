#include "utilities/shell/command.h"
#include "utilities/idt/idt.h"


i32 do_reboot(struct regs_t* r)
{
    reboot();
    return 0;
}
