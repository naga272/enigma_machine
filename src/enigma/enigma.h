#ifndef ENIGMA_H
#define ENIGMA_H

#include <stddef.h>
#include "config.h"


#define LENROTORE 26
#define LENPLUGBOARD 20
#define LENRIFLETTORE 26

#ifdef ENIGMA_SET

const uchar plugboard[LENPLUGBOARD][2] = {
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
    "JEKMFLGDQVZNTOWYHXUSPAIBRC\0",   // rotore 1
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

uchar riflettore[LENRIFLETTORE][2] = {
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


uchar container; // contenitore carattere premuto da tastiera 


#undef ENIGMA_SET
#endif


#endif