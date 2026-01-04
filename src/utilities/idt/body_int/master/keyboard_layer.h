
#ifndef KEYBOARD_H
#define KEYBOARD_H

#include "config.h"

#define CAPS_LOCK_SCANCODE  0x3A        // caps lock key scancode
#define RELEASE_KEY(x)      (x & 0x80)  // release key pressed
#define SHIFT_LEFT_PRESS    0x2A        // scancode maiusc left key press 
#define SHIFT_RIGHT_PRESS   0x36        // scancode maiusc right key press

#define SHIFT_LEFT_RELEASE  0xAA        // scancode maiusc left key release
#define SHIFT_RIGHT_RELEASE 0xB6        // scancode maiusc right key release


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

#endif
