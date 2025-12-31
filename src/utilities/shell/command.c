#include "config.h"

#include "utilities/shell/command.h"
#include "utilities/string/string.h"
#include "utilities/io/io.h"


#define OS_X_QEMU


void reboot()
{
    outb(0x64, 0xFE);
}


void power_off()
{
#ifdef OS_X_QEMU
    // :D    
    outw(0x604, 0x2000);
#endif

#ifdef OS_X_XBOCHS
    // :D
    outw(0xB004, 0x2000);
#endif

#ifdef OS_X_X86
    // >_<
#endif

}


uchar* vec_reboot_comm = (uchar*) "REBOOT";
uchar* vec_power_off_comm = (uchar*) "QUIT";


u8 try_execute_comm(uchar* comm_to_execute)
{
    if (strcmp(comm_to_execute, vec_reboot_comm))
        reboot();

    else if (strcmp(comm_to_execute, vec_power_off_comm))
        power_off();

    return 0;
}
