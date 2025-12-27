#include "config.h"

#define ENIGMA_SET  // rende possibile la dichiarazione di variabili di enigma/enigma.h
#include "utilities/enigma/enigma.h"
#include "utilities/stdlib/stdlib.h"


O3 static inline const uchar m_plugboard(const uchar c)
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

    for (size_t i = 0; i < LENPLUGBOARD; i++)
        if (c == plugboard[i][0])
            return plugboard[i][1];
 
        else if (c == plugboard[i][1])
            return plugboard[i][0];

    // caso in cui il carattere non e' mappato, restituisco il carattere c normale
    return c; 
}


O3 static inline const uchar m_riflettore(const uchar c)
{
    // stesso concetto della plugboaqrd
    for (size_t i = 0; i < 26; i++)
        if (c == riflettore[i][0]) 
            return riflettore[i][1];
 
        else if (c == riflettore[i][1])
            return riflettore[i][0];

    return c;
}


static inline uchar* gira_rotore(uchar *rotore)
{
    // @*rotore: mantiene l'indirizzo dell'inizio dell'array
    
    uchar *tmp_mem_rotore = rotore;
    char last = tmp_mem_rotore[LENROTORE - 1];
    
    for (size_t i = LENROTORE - 1; i > 0; i--)
        tmp_mem_rotore[i] = tmp_mem_rotore[i - 1];
    
    tmp_mem_rotore[0] = last;
    return rotore; 
}


O3 static inline uchar rotore_reverse(uchar *rotor, uchar c)
{
    for (u8 i = 0; i < 26; i++)
        if (rotor[i] == c)
            return 'A' + i;

    // metti caso che sono sfigato, non si sa mai
    return c; 
}


O3 static inline void update_stato_rotori()
{
    rotore1 = gira_rotore(rotore1);
    count_rotore1++;

    if (GIRO_COMPLETO(count_rotore1)) {
        // il primo rotore ha completato un giro,
        // quindi deve tornare a 1 e gira di 1
        // il secondo rotore
        count_rotore1 = 1;
        count_rotore2++;
        rotore2 = gira_rotore(rotore2);
    
        if (GIRO_COMPLETO(count_rotore2)) {
            // il secondo rotore ha completato un giro,
            // quindi deve tornare a 1 e gira di 1
            // il terzo rotore
            count_rotore2 = 1;
            rotore3 = gira_rotore(rotore3);
        }
    }
}


O3 uchar core_enigma(uchar container)
{
    container = m_plugboard(container);

    // INIZIO FASE ROTORI
    container = rotore1[(u8) container - (u8) 'A'];
    update_stato_rotori();

    // passaggio al secondo rotore
    container = rotore2[(u8) container - (u8) 'A'];

    // passaggio al terzo rotore
    container = rotore3[(u8) container - (u8) 'A'];

    // INIZIO FASE RIFLETTORE 
    container = m_riflettore(container);

    // INIZIO FASE ROTORI REVERSE   
    container = rotore_reverse(rotore3, container);
    container = rotore_reverse(rotore2, container);
    container = rotore_reverse(rotore1, container);

    // INIZIO FASE PLUGBOARD 
    container = m_plugboard(container);

    return container;
}
