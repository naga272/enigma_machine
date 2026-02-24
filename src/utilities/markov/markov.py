import sys


'''
Il mio sistema operativo riesce a prendere max i primi 127 caratteri
della tabella ascii.
'''
ASCII_TABLE_SIZE = 127


'''
transition:

e' una matrice bidimensionale che contiene ASCII_SIZE elementi.
Ogni elemento di transition e' una lista che contiene ASCII_SIZE elementi.
Inizialmente viene inizializzata in questo modo (vedi funzione setup()):

transition = [
    [0, 0, 0, ..., 0], -> riga 0
    [0, 0, 0, ..., 0], -> riga 1
    ...,
    [0, 0, 0, ..., 0], -> riga 126
]

- l'indice della riga equivale al carattere premuto attualmente
- l'indice della colonna e' il carattere successivo

l'idea e' questa.
Quando arriva un char, lo memorizzo nella var char_actual.
Quando arriva un secondo char, char_actual lo sposto in char_before
e il nuovo lo sposto in char_actual.

Quando sono valorizzati sia char_before e char_actual
li inserisco all'interno della matrice transition, avendo osservato il pattern:

dopo il char (esempio) 'a' e' stato premuto il char 'b', quindi:

transition[char_before][char_actual] += 1

nell'ascii table la 'a' equivale al numero 97 e 'b' equivale al nuemero 98,
quindi:

transition[ord(char_before)][ord(char_actual)] += 1
risultato:

transition[97][98] += 1

'''


transition = []

char_before = ''
char_actual = ''
next_char = ''


def init_transition():
    global transition, ASCII_TABLE_SIZE
    for i in range(ASCII_TABLE_SIZE):
        transition.append([0] * ASCII_TABLE_SIZE)


def prevedi():
    global transition, char_before, next_char

    if char_before == '':
        return

    row = transition[ord(char_actual)]
    max_count = 0
    best_idx = None

    for idx, val in enumerate(row):
        if val > max_count:
            max_count = val
            best_idx = idx

    if best_idx is not None:
        next_char = chr(best_idx)

    return next_char


def insert_in_queue(c: str):
    global transition, char_actual, char_before

    if char_actual == '':
        char_actual = c
    else:
        char_before = char_actual
        char_actual = c
        transition[ord(char_before)][ord(char_actual)] += 1


def main(argc: int, argv: list) -> int:
    global next_char
    init_transition()

    sequence = "hello"

    # ripetizione di 10 volte per accumulare
    for _ in range(10):
        for c in sequence:
            insert_in_queue(c)
            print(f"input: {c}, predicted next: {prevedi()}")
    return 0


if __name__ == "__main__":
    result = main(len(sys.argv), sys.argv)
    sys.exit(result)
