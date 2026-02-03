
#ifndef KEYBOARD_H
#define KEYBOARD_H

#include "config.h"

#define CAPS_LOCK_SCANCODE  0x3A        // caps lock key scancode
#define RELEASE_KEY(x)      (x & 0x80)  // release key pressed

#define SHIFT_LEFT_PRESS    0x2A        // scancode maiusc left key press 
#define SHIFT_RIGHT_PRESS   0x36        // scancode maiusc right key press

#define SHIFT_LEFT_RELEASE  0xAA        // scancode maiusc left key release
#define SHIFT_RIGHT_RELEASE 0xB6        // scancode maiusc right key release

#define CTRL_LEFT_PRESS 0x1D
#define CTRL_LEFT_RELEASED 0x9D

#define CTRL_RIGHT_PRESS 0x1D
#define CTRL_RIGHT_RELEASED 0x9D

/*
E0 4B   Freccia sinistra
E0 4D   Freccia destra
E0 48   Freccia su
E0 50   Freccia giù
*/

#define FRECCIA_SU 0x48
#define FRECCIA_GIU 0x50
#define FRECCIA_SINISTRA 0x4B
#define FRECCIA_DESTRA 0x4D


/*
typedef struct KEYBOARD_FLAGS {
    u8 maiusc: 1;
    u8 capslock: 1;   
} KB_FLAGS;


KB_FLAGS test = { .maiusc = 0, .capslock = 0 };


static inline uchar convert_case(uchar c) 
{
    if (test.capslock ^ test.maiusc && c >= 'a' && c <= 'z')
        return c - 32;

    return c;
}
*/


typedef struct KEYBOARD_FLAGS {
    u8 maiusc: 1;
    u8 capslock: 1;   

    u8 shiftleft: 1;
    u8 shiftright: 1;

    u8 ctrlleft: 1;
    u8 ctrlright: 1;

    u8 change_page_shell_left: 1;
    u8 change_page_shell_right: 1;
} KB_FLAGS;


#endif
