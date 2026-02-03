#ifndef SETUP_H
#define SETUP_H

#include "config.h"

void try_set_colour(uchar c);
void init_setup();
void do_login();
void do_config();

extern void try_set_colour(uchar c);
extern void init_setup();
extern void do_config();

#endif