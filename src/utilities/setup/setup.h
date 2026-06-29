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

extern i32 kprintf(const char* fmt, ...);

extern volatile uchar tmp_char_container;
extern u8 is_ended_setup;

#endif