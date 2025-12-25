
/*
*   GESTIONE DEGLI INTERRUPT: 
*   Quando si verifica un interrupt, il processore cerca la corrispondente voce nella IDT e chiama la funzione di gestione specificata. 
*   Se viene premuto per esempio un tasto, viene triggerato l'interrupt 0x21, e il processore chiama int21h, 
*   che a sua volta chiama int21h_handler per gestire l'evento.
*/

/*
* funzioni di gestione degli interrupt (descritte in idt.asm):
*   - no_interrupt():   e' un handler generico per interrupt non gestiti
*   - int0h():		e' specificato per l'interrupt 0, usato per la divisione per zero
*   - int21h():         e' specifico per l'interrupt 0x21, che è associato alla tastiera.
*/


#include "config.h"

#include "video/video.h"

#include "idt/idt.h"
#include "stdlib/stdlib.h"

#include "enigma/keyboard.h"    // definizione tastiera itialiana standard QZERTY
#include "enigma/enigma.h"


struct idt_desc idt_descriptors[OS_TOTAL_INTERRUPTS];   // ogni elemento rappresenta un'interrupt
struct idtr_desc idtr_descriptor;                       // rappresenta il registro idtr (interrupt descriptor table register)

// funzioni che si trovano in idt.asm 
extern uchar core_enigma(uchar container);
extern void* memset(void *ptr, int c, size_t n);
extern void idt_load(struct idtr_desc* ptr); // (carica la idt)
extern void no_interrupt(); // usato per l'assegnamento di una funzione di default agli interrupt
extern void int21h();       // interrupt per la tastiera
extern void int0h();       // interrupt per la tastiera


/*
*   Usati per memorizzare i caratteri da criptare
*/
uchar bff_cmd_line[SIZE_COMMAND_SHELL];
size_t idx_buffer = 0;


O3 void no_interrupt_handler()
{
    /*
    *   Funzione che viene chiamata quando viene generato un interrupt non gestito. 
    *   Invia un segnale di "End of Interrupt" (EOI) al PIC (Programmable Interrupt Controller) 
    *   per indicare che l'interrupt è stato gestito.
    */
    EOI;
}


u8 lock = 0;
u8 flag_x_colour_shell = 0;

#define FASE_SETUP (flag_x_colour_shell == 0)

O3 static inline void try_the_answer(uchar c)
{
    /*
    *   Questo codice viene usato in fase di setup per determinare il colore dello sfondo del terminale
    *   e dei caratteri**/
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
    print((uchar*) "\nparola criptata: ");

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


O3 void int0h_handler()
{
    /*
    * Questo interrupt viene triggherato quando viene eseguita una divisione
    * per zero.
    * Prima di eseguire la DIV la cpu esegue dei controlli per verificare la validità
    * del divisore. Se vede che e' 0 viene triggherata una eccezione, andando
    * a chiamare così la funzione puntata dal puntatore in IDT[0]
    * */
    disable_interrupts();
    disable_cursor();
    panic((uchar*) "Impossibile eseguire la divisione per zero\n");
    asm volatile ("hlt");
}


O3 void int21h_handler()
{
    /*
    *   Funzione che gestisce l'interrupt 0x21 (tastiera). 
    *   Quando viene premuto un tasto, questa funzione stampa un messaggio e invia un EOI al PIC.
    * 
    *   Descrizione step by step:
    *   - un tasto viene premuto
    *   - la tastiera in base al tasto premuto genera un scancode che identifica quel tasto
    *   - lo manda al controller della tastiera
    *   - Il controller mette lo scancode all'interno di un buffer e alza il IRQ1 (sono linee hardware su
    *       cui vanno segnali elettrici, basso == inattivo, alto == richiesta di interrupt).
    *   - Dopo che ha alzato il PIC che sta continuando a monitorare le linee da IRQ0 a IRQ7 vede IRQ1 attiva,
    *       alza un altra linea che va da PIC a CPU (linea chiamata INTR) che indica che c'è un interrupt
    *       da eseguire.
    *   - La cpu sapendo che c'è un interrupt da eseguire, se sta facendo qualcosa la termina il prima possibile e poi si mette
    *     ad alzare un altro filo chiamato INTA.
    *   - Il pic vedendo alzato INTA capisce che la cpu vuole sapere quale interrupt è stato eseguito, così il PIC
    *       passa il vettore e gli passa anche il numero dell'interrupt (in questo caso 0x21)
    *   - La cpu va a leggersi il numero dell'interrupt, che e' stato associato a una funzione.
    *       Nel caso dell'21h viene chiamata appunto la funzione int21_handler()
    */

    /* insb(0x60)
    * la cpu si va a leggere dal buffer del controller il char.
    * Se il buffer è stato svuotato completamente, il controller abbassa IRQ1.
    */
    u8 scancode = insb(0x60);

    if (RELEASE_KEY(scancode))
        goto out;   // ignora il rilascio tasti

    // keyboard_map_<tipo tastiera> definita in enigma/keyboard.h (e' definito solo QZERTY)
    uchar c = keyboard_map_QZERTY[scancode];
    
    if (FASE_SETUP) {
        try_the_answer(c);
        // a quanto pare va in deadlock l'os finche non finisce l'interrupt.
        // Quindi in ogni caso deve passare da outb(0x20, 0x20)
        goto out;
    }

    if (CHAR_BACKSPACE(c)) {
        do_backspace(c);
        goto out;
    }

    if (CHAR_END_PHRASE(c)) {
        start_encryption();
        goto out;
    }

    c -= 32;
    if (c >= 'A' && c <= 'Z') {
        terminal_writechar(c, actual_color_terminal);
        bff_cmd_line[idx_buffer] = c;
        idx_buffer++;
    }

out:
    EOI;
}


O3 void idt_set(int interrupt_no, void* address)
{
    /*
    *   @interrupt_no:  Numero dell'interrupt
    *   @address:       Puntatore a funzione che viene triggerato dopo un'evento
    */
    struct idt_desc* desc = &idt_descriptors[interrupt_no]; // rappresenta un singolo interrupt
    desc->offset_1  = (u32) address & 0x0000ffff;       
    desc->selector  = KERNEL_CODE_SELECTOR;
    desc->zero      = 0x00;
    desc->type_attr = 0xEE;
    desc->offset_2  = (u32) address >> 16;
}


O3 static inline void set_default_int()
{
    for (int i = 0; i < OS_TOTAL_INTERRUPTS; i++)
        idt_set(i, no_interrupt);
}


O3 void idt_init()
{
    // buffer che contiene la lista di caratteri da tradurre secondo la
    // crittografia di enigma
    memset((void*) bff_cmd_line, 0, SIZE_COMMAND_SHELL);

    memset(idt_descriptors, 0, sizeof(idt_descriptors)); // azzero tutti i campi della tabella

    idtr_descriptor.limit   = sizeof(idt_descriptors) - 1;
    idtr_descriptor.base    = (u32) idt_descriptors;

    set_default_int();

    idt_set(0x00, int0h);
    idt_set(0x21, int21h);

    // Load the interrupt descriptor table
    idt_load(&idtr_descriptor);
}
