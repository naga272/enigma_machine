#ifndef ENIGMA_H
#define ENIGMA_H


#include <stdint.h>

#define LENROTORE 25

typedef struct Enigma_core {
    unsigned const char 
        not_encript,
        plugboard_dict[10][2],   // matrice {chiave : valore}
        rotore1[LENROTORE],
        rotore2[LENROTORE],
        rotore3[LENROTORE],
        riflettore_dict[10][2];

    // metodi
    unsigned const char (*plugboard) (unsigned const char); 
    unsigned const char (*riflettore)(unsigned const char); 
} core_enigma;


struct Enigma_core* __init__();

unsigned const char m_plugboard(unsigned const char);
unsigned const char m_riflettore(unsigned const char);

#ifdef ENIGMA_SET
struct Enigma_core* main_core;
#undef ENIGMA_SET
#endif


const unsigned char plugboard[20][2] = {
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


#endif