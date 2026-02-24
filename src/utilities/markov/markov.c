#include "config.h"
#include "utilities/memory/heap/malloc.h"
#include "utilities/markov/markov.h"


/*
*   Idea generale
*   transition del file markov.py
*
*   e' una matrice bidimensionale che contiene ASCII_SIZE elementi (127).
*   Ogni elemento di transition e' una lista che contiene ASCII_SIZE elementi.
*   Inizialmente viene inizializzata in questo modo (vedi funzione setup()):
*
*   transition = [
*       [0, 0, 0, ..., 0], -> riga 0
*       [0, 0, 0, ..., 0], -> riga 1
*       ...,
*       [0, 0, 0, ..., 0], -> riga 126
*   ]
*
*   - l'indice della riga equivale al carattere premuto attualmente
*   - l'indice della colonna e' il carattere successivo
*
*   l'idea e' questa.
*   Quando arriva un char, lo memorizzo nella var char_actual.
*   Quando arriva un secondo char, char_actual lo sposto in char_before
*   e il nuovo lo sposto in char_actual.
*
*   Quando sono valorizzati sia char_before e char_actual
*   li inserisco all'interno della matrice transition, avendo osservato il pattern:
*
*   dopo il char (esempio) 'a' e' stato premuto il char 'b', quindi:
*
*   transition[char_before][char_actual] += 1
*
*   nell'ascii table la 'a' equivale al numero 97 e 'b' equivale al nuemero 98,
*   quindi:
*
*   transition[ord(char_before)][ord(char_actual)] += 1
*   risultato:
*
*   transition[97][98] += 1
*
*   Questo esempio l'ho fatto su caratteri (vedi file di prova markov.py),
*   l'idea di usarlo in questo os e' di predire quale sara' il prossimo
*   interrupt che arrivera' dal PIC.
*
*   Gli interrupt totali che possono arrivare sono 7 per il master
*   (-1 causa IRQ#2 che fa da ponte con lo slave).
*   Gli altri dello slave devo ancora finire di settarli,
*   quindi per il momento ne considero solo 7.
*
*/

#ifndef ACTUAL_INTRT_CREATED
#define ACTUAL_INTRT_CREATED 7
#else
#error "macro ACTUAL_INTRT_CREATED definita altrove, attenzione"
#endif

static u32 max_val_u32 = 4294967295U;
static char** markov_entry;
uchar entry_before = (char) 0;
uchar entry_actual = (char) 0;


O3 static inline void panic_table_prediction_idt()
{
    /*
    *   L'idea e' questa:
    *   Se resetto tutta la tabella all'inizio comincera'
    *   a sparare a caso, quindi per tenere il piu consistente
    *   possibile la predizione, divido per 2 tutti i valori memorizzati
    *   cosi non parto proprio da 0 di nuovo ma ho comunque
    *   una base da predire
    * * */
    for (u8 y = 0; y < ACTUAL_INTRT_CREATED; y++)    
        for (u8 x = 0; x < ACTUAL_INTRT_CREATED; x++)
            markov_entry[y][x] /= 2;
}


O3 static inline void check_status_table(uchar before, uchar actual)
{
    /**
     * Uno dei possibili problemi e' che se raggiunge il valore max per un intero
     * unsigned a 32 bit torna a 0 e potrebbe far sbagliare tutte le predizioni
     * successive (uccidendo le prestazioni).
     * Di conseguenza preferisco resettare la tabella (o disabilitarla)
     * anziche' fargli sbagliare tutte
     * le predizioni successive sempre
     * *** */

    if (markov_entry[before][actual] < max_val_u32)
        return;
    
    panic_table_prediction_idt();
}


O3 u8 prevedi_markov()
{
    if (entry_before == (char) 0)
        return (char) 0;
    
    u32* row = (u32*)markov_entry[entry_actual];
    u32 max_count = 0;
    u8 best_idx = 0;

    for (u8 idx = 0; idx < ACTUAL_INTRT_CREATED; idx++) {
        if (row[idx] > max_count) {
            max_count = row[idx];
            best_idx = idx;
        }
    }

    // num interrupt PIC piu probabile
    return best_idx;
}


O3 void insert_markov_entry(uchar new_entry)
{
    // da 0x00 a 0x19 sono interrupt della cpu.
    // 0x19 esadecimale equivale a 25 decimale.
    // tolgo i primi 25 interrupt che sono usati dalla cpu,
    // sono eventi cosi' rari che non ha nemmeno senso considerarli
    new_entry -= 25;

    if (entry_actual == 0) {
        entry_actual = new_entry;
        return;
    }
    entry_before = entry_actual;
    entry_actual = new_entry;

    check_status_table(entry_before, entry_actual);

    markov_entry[entry_before][entry_actual]++;
}


O3 static inline void init_matrix()
{
    /*
    * matrice 7x7.
    * Ogni elemento della riga della matrice e' grande sizeof(u32) bytes
    */
    markov_entry = kcalloc(sizeof(void*) * ACTUAL_INTRT_CREATED);

    for (u8 idx = 0; idx < ACTUAL_INTRT_CREATED; idx++)
        markov_entry[idx] = kcalloc(sizeof(u32) * ACTUAL_INTRT_CREATED);
}


O3 void init_markov_model_idt()
{
    init_matrix();
}

