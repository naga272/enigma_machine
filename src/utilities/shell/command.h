#ifndef COMMAND_H
#define COMMAND_H

#include "utilities/string/string.h"

extern u8 try_execute_comm(uchar*);
extern u8 power_off();
extern u8 reboot();
extern u8 cls();

u8 try_execute_comm(uchar*);
u8 power_off();
u8 reboot();
u8 cls();


#endif
