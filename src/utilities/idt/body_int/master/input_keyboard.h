#ifndef INPUT_KEYBOARD_H
#define INPUT_KEYBOARD_H

#include "utilities/stdlib/stdlib.h"


extern volatile u8 new_char_written;      // flag
extern volatile uchar tmp_char_container; // char scritto


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

#endif