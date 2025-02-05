
#include "config.h"
#include "idt/idt.h"
#include "io/io.h"
#include "stdlib/stdlib.h"

/*
*   Interrupt Descriptor Table (IDT)
*   Quando eravamo in real mode, usavamo gli interrupt della interrupt vector table.
*   In protected mode si usa la interrupt descriptor table, che descrive come gli interrupt
*   vengono chiamati in protected mode (nb. gli int possono essere mappati ovunque in memoria)
*   Name        bit         Description
*   offset      46-63       The higher part of the offset to execute
*   P           47          This shoul be set to 0 for unused interrupts
*   DPL         45-46       The ring level the processor requires to call this int
*   S           44          should be set to zero for trap gates
*   Type        40-43       The type of gate 
*   zero        32-39       Unused bit
*   Selector    16-31       The selector this interrupt is bounded to IE the kernel code
*   Offset      0-15        The lower part of the offset to execute
*/


struct idt_desc idt_descriptors[OS_TOTAL_INTERRUPTS];   // ogni elemento rappresenta un'interrupt
struct idtr_desc idtr_descriptor;                       // rappresenta il registro idtr (interrupt descriptor table register)


// si trova in idt.asm (carica la idt)
extern void idt_load(struct idtr_desc* ptr);    

extern void print(const unsigned char*);

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
*   - idt_zero():       gestisce l'interrupt 0, divisione per 0
*/
extern void no_interrupt();
extern void int21h();


void idt_zero()
{
    print((unsigned const char *) "error!");
}


void no_interrupt_handler()
{
    /*
    *   Funzione che viene chiamata quando viene generato un interrupt non gestito. 
    *   Invia un segnale di "End of Interrupt" (EOI) al PIC (Programmable Interrupt Controller) 
    *   per indicare che l'interrupt è stato gestito.
    */
    outb(0x20, 0x20);
}

const unsigned char c;


void int21h_handler()
{
    /*
    *   Funzione che gestisce l'interrupt 0x21 (tastiera). 
    *   Quando viene premuto un tasto, questa funzione stampa un messaggio e invia un EOI al PIC. 
    */
    
    // insb(0x60) legge il codice del tasto dalla porta 0x60
    // per poi convrtirlo nel codice del tasto in un carattere
    // keyboard_map definita in utilities/keyboard/keyboard.c
    c = insb(0x60);

    outb(0x20, 0x20);
}


void idt_set(int interrupt_no, void* address)
{
    /*
    *   @interrupt_no:  Numero dell'interrupt
    *   @address:       Puntatore a funzione che viene triggerato dopo un'evento
    */
    struct idt_desc* desc = &idt_descriptors[interrupt_no]; // rappresenta un singolo interrupt
    desc->offset_1  = (uint32_t) address & 0x0000ffff;       
    desc->selector  = KERNEL_CODE_SELECTOR;
    desc->zero      = 0x00;
    desc->type_attr = 0xEE;
    desc->offset_2  = (uint32_t) address >> 16;
}


void idt_init()
{
    memset(idt_descriptors, 0, sizeof(idt_descriptors)); // azzero tutti i campi della tabella
    
    idtr_descriptor.limit   = sizeof(idt_descriptors) - 1;
    idtr_descriptor.base    = (uint32_t) idt_descriptors;

    for (int i = 0; i < OS_TOTAL_INTERRUPTS; i++)
        idt_set(i, no_interrupt);

    idt_set(0, idt_zero);
    idt_set(0x21, int21h);

    // Load the interrupt descriptor table
    idt_load(&idtr_descriptor);
}


