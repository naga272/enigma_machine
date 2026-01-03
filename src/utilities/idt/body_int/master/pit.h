#ifndef PIT_H
#define PIT_H

#include "config.h"

extern void do_pit();
extern void init_hardware_pit();

#define PIT_FREQ 1193182

// frequenza
#define HZ 30

// ogni 1 / 30 S = 0,0333... = 33,33 ms
#define PIT_DIV (PIT_FREQ / HZ)

#endif