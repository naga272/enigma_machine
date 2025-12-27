
// definizione tastiera italiana standard QZERTY
#include "config.h"
#include "utilities/idt/body_int/master/input_keyboard.h"


O3 void try_the_answer(uchar c)
{
    /*
    *   Questo codice viene usato in fase di setup per determinare il colore dello sfondo del terminale
    *   e dei caratteri
    *   @c: contiene un numero sotto forma di char per decidere i colori
    * **/

    if (c < '1' || c > '4') {
        if (!lock) {
            print(
                (uchar*) " \nerror! devi premere un tasto tra l'1 e il 4\n"
                "scegli colore: "
            );
            lock = 1;
            return;
        }
    }

    switch (c) {
        case '1':
            terminal_initialize(BG_BLU_C_WHITE);
            flag_x_colour_shell++;
            print((uchar*) ">>> ");
            break;

        case '2':
            terminal_initialize(BG_BIANCO_C_NERO);
            flag_x_colour_shell++;
            print((uchar*) ">>> ");
            break;

        case '3':
            terminal_initialize(BG_NERO_C_BIANCO);
            flag_x_colour_shell++;
            print((uchar*) ">>> ");
            break;

        case '4':
            terminal_initialize(BG_NERO_C_VERDE);
            flag_x_colour_shell++;
            print((uchar*) ">>> ");
            break;

        default:
            break;
    }

    /*
    *   Well, per qualche ragione a me sconosciuta
    *   se metto qui sotto:
    *       flag_x_colour_shell++;
    *       print((uchar*) ">>> ");
    *   si bugga, quindi lo lascio nello switch (li funziona)
    */
}


O3 static inline void start_encryption()
{
    terminal_writechar('\n', actual_color_terminal);

    for (size_t i = 0; bff_cmd_line[i] != 0; i++)
        terminal_writechar(core_enigma(bff_cmd_line[i]), actual_color_terminal);

    memset((void*) bff_cmd_line, 0, idx_buffer);

    idx_buffer = 0;

    print((uchar*) "\n>>> ");
}


O3 static inline void do_backspace(uchar c)
{
    if (idx_buffer > 0) {
        idx_buffer--;
        bff_cmd_line[idx_buffer] = 0;
        terminal_writechar(c, actual_color_terminal);
    }
}


void gestisci_scancode_from_controller(u8 scancode)
{
    if (RELEASE_KEY(scancode))
        return;   // ignora il rilascio tasti

    // keyboard_map_<tipo tastiera> definita in enigma/keyboard.h (e' definito solo QZERTY)
    uchar c = keyboard_map_QZERTY[scancode];
    
    if (FASE_SETUP) {
        try_the_answer(c);
        // a quanto pare va in deadlock l'os finche non finisce l'interrupt.
        // Quindi in ogni caso deve passare da outb(0x20, 0x20)
        return;
    }

    if (CHAR_BACKSPACE(c)) {
        do_backspace(c);
        return;
    }

    if (CHAR_END_PHRASE(c)) {
        start_encryption();
        return;
    }

    c -= 32;
    if (c >= 'A' && c <= 'Z') {
        terminal_writechar(c, actual_color_terminal);
        bff_cmd_line[idx_buffer] = c;
        idx_buffer++;
    }
}
