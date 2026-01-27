#include "config.h"

#include "utilities/io/io.h"
#include "utilities/shell/command.h"
#include "utilities/string/string.h"
#include "utilities/video/video.h"


#define OS_X_QEMU


uchar* vec_reboot_comm = (uchar*) "RELOAD";
uchar* vec_power_off_comm = (uchar*) "QUIT";
uchar* vec_cls_comm = (uchar*) "CLS";


void reboot()
{
    /*
    *   Uso il controller della tastiera per forzare il riavvio hardware della cpu
    *   - 0x64 e' la porta per il controller della tastiera
    *   - 0xFE e' il comando Pulse Output Line. 
    *       Questo comando abbassa la linea RESET della cpu.
    *       La cpu ricevendo il segnale di reset ricomincia da zero,
    * ** */
    outb(0x64, 0xFE);
}


void power_off()
{
#ifdef OS_X_QEMU
    /* 
    *   uso una porta specifica che viene intercettata da qemu,
    *   che vedendo il valore 0x2000 capisce che deve spegnere la macchina
    */
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


void cls()
{
    terminal_initialize(actual_color_terminal);
}


u8 try_execute_comm(uchar* comm_to_execute)
{
    if (strcmp(comm_to_execute, vec_reboot_comm))
        reboot();

    else if (strcmp(comm_to_execute, vec_power_off_comm))
        power_off();

    else if (strcmp(comm_to_execute, vec_cls_comm))
        cls();

    return 0;
}
