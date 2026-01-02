#ifndef PIT_H
#define PIT_H

#include "config.h"

extern void do_pit();
extern void init_hardware_pit();

#define PIT_FREQ 1193182
#define HZ 300
#define PIT_DIV (PIT_FREQ / HZ)

#endif