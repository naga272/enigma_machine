#ifndef COMMAND_H
#define COMMAND_H

#include "utilities/string/string.h"

extern u8 try_execute_comm(uchar*);
extern void power_off();
extern void reboot();

u8 try_execute_comm(uchar*);
void power_off();
void reboot();


#endif
