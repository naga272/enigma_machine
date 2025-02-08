#ifndef ENIGMA_H
#define ENIGMA_H

#include <stddef.h>
#include "config.h"


#define LENROTORE 26


#ifdef ENIGMA_SET
/*
*   La plugboard e' un componente opzionale nella reale macchina enigma, 
*   per questo ho deciso di metterla fuori dalla struct Enigma_core
*/
const uchar plugboard[20][2] = {
    {'A', 'Z'}, {'Z', 'A'},
    {'B', 'Y'}, {'Y', 'B'},
    {'C', 'X'}, {'X', 'C'},
    {'D', 'W'}, {'W', 'D'},
    {'E', 'V'}, {'V', 'E'},
    {'F', 'U'}, {'U', 'F'},
    {'G', 'T'}, {'T', 'G'},
    {'H', 'S'}, {'S', 'H'},
    {'I', 'R'}, {'R', 'I'},
    {'J', 'Q'}, {'Q', 'J'}
};


/*
    "ABCDEFGHIJKLMNOPQRSTUVWXYZ\0"    // alfabeto standard
    "EKMFLGDQVZNTOWYHXUSPAIBRCJ\0",   // rotore 1
    "AJDKSIRUXBLHWTMCQGZNPYFVOE\0",   // rotore 2
    "BDFHJLCPRTXVZNYEIWGAKMUSQO\0"    // rotore 3
*/
uchar alfabeto[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";

// questi contatori consentono di capire quando il riflettore num. 2 e num. 3 devono girare 
// (a ogni giro completo del primo, gira il secondo, etc..)

u8 
    count_rotore1 = 0, 
    count_rotore2 = 0;


uchar *rotore1 = (uchar*) "EKMFLGDQVZNTOWYHXUSPAIBRCJ";
uchar *rotore2 = (uchar*) "AJDKSIRUXBLHWTMCQGZNPYFVOE";
uchar *rotore3 = (uchar*) "BDFHJLCPRTXVZNYEIWGAKMUSQO";

uchar riflettore[26][2] = {
    {'A', 'Y'}, {'Y', 'A'},
    {'B', 'R'}, {'R', 'B'},
    {'C', 'U'}, {'U', 'C'},
    {'D', 'H'}, {'H', 'D'},
    {'E', 'Q'}, {'Q', 'E'},
    {'F', 'S'}, {'S', 'F'},
    {'G', 'L'}, {'L', 'G'},
    {'I', 'P'}, {'P', 'I'},
    {'J', 'X'}, {'X', 'J'},
    {'K', 'N'}, {'N', 'K'},
    {'M', 'O'}, {'O', 'M'},
    {'T', 'Z'}, {'Z', 'T'},
    {'V', 'W'}, {'W', 'V'},
};

// tastiera italiana standard
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


uchar container; // contenitore carattere premuto da tastiera 


#undef ENIGMA_SET
#endif


const uchar m_plugboard(const uchar);
const uchar m_riflettore(const uchar);
uchar* gira_rotore(uchar*);


#endif