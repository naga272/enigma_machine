#ifndef PIT_H
#define PIT_H

#include "config.h"

extern void do_pit();
extern void init_hardware_pit();

#define PIT_FREQ 1193182

// frequenza
#define HZ 20

// ogni 1 / 20 S = 0,05 = 50 ms
#define PIT_DIV (PIT_FREQ / HZ)

#endif