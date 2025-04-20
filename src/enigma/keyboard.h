
#ifndef KEYBOARD_H
#define KEYBOARD_H

#include "config.h"

#define CAPS_LOCK_SCANCODE  0x3A // caps lock key scancode

#define SHIFT_LEFT_PRESS    0x2A // scancode maiusc left key press 
#define SHIFT_RIGHT_PRESS   0x36 // scancode maiusc right key press

#define SHIFT_LEFT_RELEASE  0xAA // scancode maiusc left key release
#define SHIFT_RIGHT_RELEASE 0xB6 // scancode maiusc right key release


uchar keyboard_map_QZERTY[128] = {
    0,  27, '1', '2', '3', '4', '5', '6', '7', '8', '9', '0', '\'', 141, '\b', '\t', /* 0x00 - 0x0F */
    'q', 'w', 'e', 'r', 't', 'y', 'u', 'i', 'o', 'p', 138, '+', '\n', 0,             /* 0x10 - 0x1F */
    'a', 's', 'd', 'f', 'g', 'h', 'j', 'k', 'l', 149, 133, 151, 0, '\\',             /* 0x20 - 0x2F */
    'z', 'x', 'c', 'v', 'b', 'n', 'm', ',', '.', '-', 0, '*', 0, ' ', 0, 0, 0, 0, 0, /* 0x30 - 0x3F */
    0, 0, 0, 0, 0, 0, 0, '7', '8', '9', '-', '4', '5', '6', '+', '1',               /* 0x40 - 0x4F */
    '2', '3', '0', '.', 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,                         /* 0x50 - 0x5F */
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,                                 /* 0x60 - 0x6F */
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0                                  /* 0x70 - 0x7F */
};


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


#endif
