
#define ENIGMA_SET  // rende possibile la dichiarazione di variabili 
#include "enigma/enigma.h"
#include "string/string.h"
#include "stdlib/stdlib.h"


const uchar m_plugboard(const uchar c)
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

    for (size_t i = 0; i < 20; i++) {
        if (c == plugboard[i][0]) {
            return plugboard[i][1]; 
        } else if (c == plugboard[i][1]) {
            return plugboard[i][0];
        }
    }
    // caso in cui il carattere non e' mappato, restituisco il carattere c normale
    return c; 
}


const uchar m_riflettore(const uchar c)
{
    // stesso concetto della plugboaqrd
    for (size_t i = 0; i < 26; i++) {

        if (c == riflettore[i][0]) 
            return riflettore[i][1]; 

        else if (c == riflettore[i][1])
            return riflettore[i][0];
    }

    return c;
}


uchar* gira_rotore(uchar *rotore) {
    // rotore mantiene l'indirizzo dell'inizio dell'array
    
    uchar *tmp_mem_rotore = rotore;
    char last = tmp_mem_rotore[LENROTORE - 1];
    
    for (size_t i = LENROTORE - 1; i > 0; i--) {
        tmp_mem_rotore[i] = tmp_mem_rotore[i - 1];
    }
    
    tmp_mem_rotore[0] = last;
    return rotore; 
}
