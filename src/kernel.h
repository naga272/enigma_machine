#ifndef KERNEL_H
#define KERNEL_H

void kernel_main();

uchar start_msg[] = "\
=============================================================\n\
|Welcome to my EnigmaOs!                                    |\n\
|author: naga272                                            |\n\
|Set a colour for your shell:                               |\n\
|  -digita 1 per un background blue and colore testo white  |\n\
|  -digita 2 per un background bianco and colore testo nero |\n\
|  -digita 3 per un background nero and colore testo bianco |\n\
|  -digita 4 per un background nero and colore testo verde  |\n\
=============================================================\n\
>>> inserisci qui il numero: ";


uchar giorni_settimana[8][4] = {
    /* A quanto pare l'rtc ha un suo modo di tenere la conta dei giorni:
        sunday = 1
        monday = 2
        tuesday = 3
        wednesday = 4
        etc ...
    */
    "",
    "SUN",
    "MON",
    "TUE",
    "WED",
    "THU",
    "FRI",
    "SAT",
};


// struct che contiene .sec, .min, .ore, .giorno, mese, anno
struct tempo_t t;

/*
formattazione orario in prima riga
"ddd:MM:yyyy hh:mm:ss"
*/
uchar time_formatted[19];

// usato in modo provvisorio per aggiornare il timer (finche non capisco il problema
// in IRQ#8)
u8 first_rendering = 1;
#endif