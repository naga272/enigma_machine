
/*
*   GESTIONE DEGLI INTERRUPT: 
*   Quando si verifica un interrupt, il processore cerca la corrispondente voce nella IDT e chiama la funzione di gestione specificata. 
*   Se viene premuto per esempio un tasto, viene triggerato l'interrupt 0x21, e il processore chiama int21h, 
*   che a sua volta chiama int21h_handler per gestire l'evento.
*/

/*
* funzioni di gestione degli interrupt (descritte in idt.asm):
*   - no_interrupt():   e' un handler generico per interrupt non gestiti
*   - int21h():         e' specifico per l'interrupt 0x21, che è tipicamente associato alla tastiera.
*/


#include "config.h"

#include "video/video.h"
#define ACQUISISCI_FLAGS
#include "idt/idt.h"
#include "io/io.h"
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


void no_interrupt_handler()
{
    /*
    *   Funzione che viene chiamata quando viene generato un interrupt non gestito. 
    *   Invia un segnale di "End of Interrupt" (EOI) al PIC (Programmable Interrupt Controller) 
    *   per indicare che l'interrupt è stato gestito.
    */
    outb(0x20, 0x20);
}

uchar bff_cmd_line[SIZE_COMMAND_SHELL];
size_t x = 0;

void int21h_handler()
{
    /*
    *   Funzione che gestisce l'interrupt 0x21 (tastiera). 
    *   Quando viene premuto un tasto, questa funzione stampa un messaggio e invia un EOI al PIC. 
    */
    
    // insb(0x60) legge il codice del tasto dalla porta 0x60 (in al, 0x60)
    // per poi convertirlo nel codice del tasto in un carattere
    // keyboard_map_<tipo tastiera> definita in enigma.h (sono definite solo QZERTY e QWERTY)

    uchar c = keyboard_map_QZERTY[insb(0x60)];

    if (flag_x_colour_shell != 0) {

        if (c != '\n')
            c -= 32;

        if (c >= 'A' && c <= 'Z') {
            terminal_writechar(c, actual_color_terminal);
            bff_cmd_line[x] = c;
            x++;
        }

        if (c == '\n') {
            print((uchar*) "\nparola criptata: ");

            for (size_t i = 0; bff_cmd_line[i] != 0; i++) {
                terminal_writechar(core_enigma(bff_cmd_line[i]), actual_color_terminal);
            }

            memset((void*) bff_cmd_line, 0, SIZE_COMMAND_SHELL);
            x = 0;
            print((uchar*) "\nparola da criptare: ");
        }
    } else {
        switch (c) {
            case '1':
                terminal_initialize(BG_BLU_C_WHITE);
                flag_x_colour_shell++;
                print((uchar*) "parola da criptare: ");
                break;
            
            case '2':
                terminal_initialize(BG_BIANCO_C_NERO);
                flag_x_colour_shell++;
                print((uchar*) "parola da criptare: ");
                break;

            case '3':
                terminal_initialize(BG_NERO_C_BIANCO);
                flag_x_colour_shell++;
                print((uchar*) "parola da criptare: ");
                break;

            default:
                print((uchar*) "error! devi premere un tasto tra l'1 e il 3\n");
                print((uchar*) "scegli colore: ");
                break;
        }
    }

    outb(0x20, 0x20);
}


void idt_set(int interrupt_no, void* address)
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


void idt_init()
{
    memset(idt_descriptors, 0, sizeof(idt_descriptors)); // azzero tutti i campi della tabella
    
    idtr_descriptor.limit   = sizeof(idt_descriptors) - 1;
    idtr_descriptor.base    = (u32) idt_descriptors;

    for (int i = 0; i < OS_TOTAL_INTERRUPTS; i++)
        idt_set(i, no_interrupt);

    idt_set(0x21, int21h);

    // Load the interrupt descriptor table
    idt_load(&idtr_descriptor);
}
