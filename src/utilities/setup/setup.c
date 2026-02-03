
#include "utilities/setup/setup.h"
#include "utilities/stdlib/stdlib.h"
#include "utilities/string/string.h"
#include "utilities/video/video.h"
#include "utilities/disk/disk.h"
#include "utilities/idt/idt.h"
#include "utilities/enigma/enigma.h"
#include "utilities/book/book.h"

extern uchar tmp_char_container;
extern u8 is_ended_setup;

/* lock serve ha bloccare il numero di messaggi per errore durante la fase di setup */
u8 lock = 0;

// usato per dire se la fase di setup e' finita (try_the_setup foo)
u8 flag_x_colour_shell = 0;
u8 flag_x_username = 0;
u8 flag_x_password = 0;

uchar username[32];
uchar password[32];
uchar username_insert[32];

i8 idx_char_vect = 0;


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

uchar* magic_num_sec_128 = (uchar*) "EnigmaOs";

uchar buf128[512];


O3 static inline void test_disk()
{
    /*
    * Test formattazione serttore 128
    *  ____________________________________________________________
    * |                  SETTORE 128 (512 bytes)                   |
    * |------------------------------------------------------------|
    * | FIRMA |PADD| USERNAME | PADD | PASSWORD | PADD | CS | PADD |
    * |-------|----|----------|------|----------|------|----|------|
    * |   8   |  1 |    32    |  1   |    32    |   1  |  1 |  436 |
    *  ------------------------------------------------------------
    * 
    * * */
    uchar buf[512];

    u16 offset = 0;

    // firma
    for (; magic_num_sec_128[offset] != '\0'; offset++)
        buf[offset] = magic_num_sec_128[offset];

    // padding
    buf[offset] = ' ';
    offset++;

    // username
    for (i8 idx = 0; username[idx] != '\0'; idx++, offset++)
        buf[offset] = username[idx];

    // padding
    buf[offset] = ' ';
    offset++;

    // password
    for (i8 i = 0; password[i] != '\0' ; i++, offset++)
        buf[offset] = password[i];

    // padding
    buf[offset] = ' ';

    // colori shell
    buf[offset + 1] = actual_color_terminal;

    disk_write_sector(128, 1, (void*) buf);
    disk_read_sector(128, 1, buf);

    print(buf);
}


O3 static inline void write_on_sector_128()
{
    /*
    *                Test formattazione settore 128
    *  ____________________________________________________________
    * |                  SETTORE 128 (512 bytes)                   |
    * |------------------------------------------------------------|
    * | FIRMA |PADD| USERNAME | PADD | PASSWORD | PADD | CS | PADD |
    * |-------|----|----------|------|----------|------|----|------|
    * |   8   |  1 |    32    |  1   |    32    |   1  |  1 |  436 |
    *  ------------------------------------------------------------
    * * */

    uchar buf[512];
    u16 offset = 0;

    // FIRMA
    for (; magic_num_sec_128[offset] != '\0'; offset++)
        buf[offset] = magic_num_sec_128[offset];

    // PADDING
    offset++;
    buf[offset] = 0;

    // USERNAME
    for (i8 idx = 0; idx < 32; offset++, idx++)
        buf[offset] = core_enigma(username[idx]);

    // PADDING
    offset++;
    buf[offset] = 0;

    // PASSWORD
    for (i8 idx = 0; idx < 32; offset++, idx++)
        buf[offset] = core_enigma(password[idx]);

    // PADDING
    offset++;
    buf[offset] = 0;

    // colori shell (CS offset)
    buf[73] = actual_color_terminal;

    disk_write_sector(128, 1, (void*) buf);
    // disk_read_sector(128, 1, buf);
}


O3 void try_set_colour(uchar c)
{
    /*
    *   Questo codice viene usato in fase di setup per determinare il colore dello sfondo del terminale
    *   e dei caratteri
    *   @c: contiene un numero sotto forma di char per decidere i colori
    * **/
    if (!c)
        return;

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
            break;

        case '2':
            terminal_initialize(BG_BIANCO_C_NERO);
            flag_x_colour_shell++;
            break;

        case '3':
            terminal_initialize(BG_NERO_C_BIANCO);
            flag_x_colour_shell++;
            break;

        case '4':
            terminal_initialize(BG_NERO_C_VERDE);
            flag_x_colour_shell++;
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


void try_username(uchar char_pressed)
{
    if (!char_pressed)
        return;

    if (char_pressed == '\b') {
        if (idx_char_vect == 0)
            return;

        gestisci_char_to_write(char_pressed);
        idx_char_vect--;
        username[idx_char_vect] = '\0';
        return;
    }

    if (char_pressed == '\n') {
        if (idx_char_vect == 0)
            return;

        // gestisci_char_to_write(char_pressed);
        flag_x_username++;
        return;
    }

    if (idx_char_vect > 31 && char_pressed)
        return;

    gestisci_char_to_write(char_pressed);
    username[idx_char_vect] = char_pressed;
    idx_char_vect++;
}


void try_password(uchar char_pressed)
{
    if (!char_pressed)
        return;

    if (char_pressed == '\b') {
        if (idx_char_vect == 0)
            return;

        gestisci_char_to_write(char_pressed);
        idx_char_vect--;
        password[idx_char_vect] = '\0';
        return;
    }

    if (char_pressed == '\n') {
        if (idx_char_vect == 0)
            return;

        // gestisci_char_to_write(char_pressed);
        flag_x_password++;
        return;
    }

    if (idx_char_vect > 31 && char_pressed)
        return;

    gestisci_char_to_write('*');
    password[idx_char_vect] = char_pressed;
    idx_char_vect++;
}


void init_setup(struct book* b)
{
    terminal_initialize(BG_BIANCO_C_NERO);

    print((uchar*) start_msg);

    while (!flag_x_colour_shell) {
        try_set_colour(tmp_char_container);
        tmp_char_container = 0;
        asm volatile("hlt");
    }

    idx_char_vect = 0;
    print((uchar*) "Inserisci username: ");

    while (!flag_x_username) {
        try_username(tmp_char_container);
        tmp_char_container = 0;
        asm volatile("hlt");
    }

    idx_char_vect = 0;
    print((uchar*) "\nInserisci password: ");

    while (!flag_x_password) {
        try_password(tmp_char_container);
        tmp_char_container = 0;
        asm volatile("hlt");
    }

    write_on_sector_128();

    print((uchar*) "\n>>>");
}


uchar username_written_by_user[32];
uchar password_written_by_user[32];


O3 static inline void cmp_credentials()
{
    i8 credential_valid = 1;

    for (u8 idx = 0; idx < 32; idx++) {
        username_insert[idx] = username_written_by_user[idx];
        username_written_by_user[idx] = core_enigma(username_written_by_user[idx]);
    }
        
    for (u8 idx = 0; idx < 32; idx++)
        password_written_by_user[idx] = core_enigma(password_written_by_user[idx]);

    if (strcmp(username, username_written_by_user) == 0)
        credential_valid = 0;

    if (strcmp(password, password_written_by_user) == 0)
        credential_valid = 0;

    if (credential_valid)
        return;

    /*
    anche se attiva la bsod l'utente e' in grado di scrivere,
    quindi disabilito tutti gli interrupts
    */

    set_message_x_panic((uchar*) "Error! credenziali non valide!");

    while (1) {}
}


O3 static inline i8 check_username(uchar char_pressed)
{
    if (!char_pressed)
        return 0;

    if (char_pressed == '\b') {
        if (idx_char_vect == 0)
            return 0;

        gestisci_char_to_write(char_pressed);
        idx_char_vect--;
        username_written_by_user[idx_char_vect] = '\0';
        return 0;
    }

    if (char_pressed == '\n') {
        if (idx_char_vect == 0)
            return 0;

        // gestisci_char_to_write(char_pressed);
        return 1;
    }

    if (idx_char_vect > 31 && char_pressed)
        return 0;

    gestisci_char_to_write(char_pressed);
    username_written_by_user[idx_char_vect] = char_pressed;
    idx_char_vect++;
    return 0;
}


O3 static inline i8 check_password(uchar char_pressed)
{
    if (!char_pressed)
        return 0;

    if (char_pressed == '\b') {
        if (idx_char_vect == 0)
            return 0;

        gestisci_char_to_write(char_pressed);
        idx_char_vect--;
        password_written_by_user[idx_char_vect] = '\0';
        return 0;
    }

    if (char_pressed == '\n') {
        if (idx_char_vect == 0)
            return 0;

        // gestisci_char_to_write(char_pressed);
        return 1;
    }

    if (idx_char_vect > 31 && char_pressed)
        return 0;

    gestisci_char_to_write('*');
    password_written_by_user[idx_char_vect] = char_pressed;
    idx_char_vect++;
    return 0;
}


void insert_username_phase()
{
    idx_char_vect = 0;

    print((uchar*) "Username: ");
    while (!check_username(tmp_char_container)) {
        tmp_char_container = 0;
        asm volatile("hlt");
    }

    tmp_char_container = 0;
    idx_char_vect = 0;
}


void insert_password_phase()
{
    print((uchar*) "\nPassword: ");

    while (!check_password(tmp_char_container)) {
        tmp_char_container = 0;
        asm volatile("hlt");
    }
}


O3 void do_login()
{
    insert_username_phase();

    insert_password_phase();

    cmp_credentials();

    print((uchar*) "\nWelcome ");
    print((uchar*) username_insert);
    print((uchar*) "!");
}


O3 void do_config(uchar *buf128)
{
    terminal_initialize((u8) buf128[73]);

    u8 offset = 9;

    for (u8 idx = 0; idx < 32; idx++, offset++)
        username[idx] = buf128[offset];

    offset++;

    for (u8 idx = 0; idx < 32; idx++, offset++)
        password[idx] = buf128[offset];

    do_login();

    is_ended_setup++;
    // print(buf128);
}
