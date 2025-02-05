#include "enigma/enigma.h"
#include "string/string.h"

#define ALLOCATE_MEMORY
#include "stdlib/stdlib.h"
#undef ALLOCATE_MEMORY


struct Enigma_core* __init__(char* rotore1, char* rotore2, char* rotore3) 
{
    core_enigma* start = (core_enigma*) calloc(sizeof(core_enigma));

    strcat((char*) start->rotore1, LENROTORE, rotore1);
    strcat((char*) start->rotore2, LENROTORE, rotore2);
    strcat((char*) start->rotore3, LENROTORE, rotore3);

    start->plugboard    = m_plugboard;
    start->riflettore   = m_riflettore;

    return start;
}


unsigned const char m_plugboard(unsigned const char c)
{
    /*
        FASE Plugboard:
        In questa fase, vengono convertiti 10 caratteri da una 'mappa' prestabilita.
        Quella che ho preso io è:

            'A' : 'Z', 'Z' : 'A',   # 'A' == 'Z' <--> 'Z' == 'A'
            'B' : 'Y', 'Y' : 'B',   # 'B' == 'Y' <--> 'Y' == 'B'
            'C' : 'X', 'X' : 'C',   # 'C' == 'X' <--> 'X' == 'C'
            'D' : 'W', 'W' : 'D',   # 'D' == 'W' <--> 'W' == 'D'
            'E' : 'V', 'V' : 'E',   # 'E' == 'V' <--> 'V' == 'E'
            'F' : 'U', 'U' : 'F',   # 'F' == 'U' <--> 'U' == 'F'
            'G' : 'T', 'T' : 'G',   # 'G' == 'T' <--> 'T' == 'G'
            'H' : 'S', 'S' : 'H',   # 'H' == 'S' <--> 'S' == 'H'
            'I' : 'R', 'R' : 'I',   # 'I' == 'R' <--> 'R' == 'i'
            'J' : 'Q', 'Q' : 'J'    # 'J' == 'Q' <--> 'Q' == 'J'

        Se nel testo da criptare, quindi compare un carattere di quelli mappati in questa tabella, verra' sostituito col suo equivalente

        testo input:
        CIAO
        testo output:
        XRZO

        perche':
        'C' == 'X'
        'I' == 'R'
        'A' == 'Z'
        La 'O' rimane invariata perche' non e' mappata nella tabella.
    */
    return (unsigned const char) c; 
}


unsigned const char m_riflettore(unsigned const char c)
{
    // stesso concetto della plugboaqrd

    return (unsigned const char) c;
}
