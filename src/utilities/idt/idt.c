
/*
*   GESTIONE DEGLI INTERRUPT: 
*   Quando si verifica un interrupt, il processore cerca la corrispondente voce nella IDT e chiama la funzione di gestione specificata. 
*   Se viene premuto per esempio un tasto, viene triggerato l'interrupt 0x21, e il processore chiama int21h, 
*   che a sua volta chiama int21h_handler per gestire l'evento.
*/

#include "config.h"

#include "utilities/video/video.h"
#include "utilities/stdlib/stdlib.h"

#include "utilities/idt/idt.h"
#include "utilities/idt/interrupts_num.h"


// usato in int20h_handler
u8 num_color = 0;

// usato per la gestione di eccezioni triggherate dalla cpu
u8 trigger_exception = 0;
struct idt_desc idt_descriptors[OS_TOTAL_INTERRUPTS];   // ogni elemento rappresenta un'interrupt
struct idtr_desc idtr_descriptor;                       // rappresenta il registro idtr (interrupt descriptor table register)


O3 void no_interrupt_handler()
{
    /*
    *   Funzione che viene chiamata quando viene generato un interrupt non gestito. 
    *   Invia un segnale di "End of Interrupt" (EOI) al PIC (Programmable Interrupt Controller) 
    *   per indicare che l'interrupt è stato gestito.
    */
   EOI_MASTER;
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
    if (!trigger_exception)
        trigger_exception++;
}


O3 void int1h_handler()
{
    /*
    * Interrupt usato per il debug
    * */
    if (!trigger_exception)
        trigger_exception++;
}


O3 void int2h_handler()
{
    /*
    * Interrupt usato per IMI
    * */
    if (!trigger_exception)
        trigger_exception++;
}


O3 void int3h_handler()
{
    /*
    * Interrupt usato per casi di overflow
    * */
    if (!trigger_exception)
        trigger_exception++;
}


O3 void int4h_handler()
{
    /*
    * Interrupt usato per Bound
    * */
    if (!trigger_exception)
        trigger_exception++;
}


O3 void int5h_handler()
{
    /*
    * Interrupt usato per Invalid opcode
    * */
    if (!trigger_exception)
        trigger_exception++;
}


O3 void int6h_handler()
{
    /*
    * Interrupt usato per Device not available
    * */
    if (!trigger_exception)
        trigger_exception++;
}


O3 void int7h_handler()
{
    /*
    * Interrupt usato per Double fault
    * */
    if (!trigger_exception)
        trigger_exception++;
}


O3 void int8h_handler()
{
    /*
    * Interrupt usato per coprocessor segment 
    * */
    if (!trigger_exception)
        trigger_exception++;
}


O3 void int9h_handler()
{
    /*
    * Questo interrupt viene triggherato quando viene eseguita una divisione
    * per zero.
    * Prima di eseguire la DIV la cpu esegue dei controlli per verificare la validità
    * del divisore. Se vede che e' 0 viene triggherata una eccezione, andando
    * a chiamare così la funzione puntata dal puntatore in IDT[0]
    * */
    if (!trigger_exception)
        trigger_exception++;
}


O3 void intah_handler()
{
    /*
    * Questo interrupt viene triggherato quando viene eseguita una divisione
    * per zero.
    * Prima di eseguire la DIV la cpu esegue dei controlli per verificare la validità
    * del divisore. Se vede che e' 0 viene triggherata una eccezione, andando
    * a chiamare così la funzione puntata dal puntatore in IDT[0]
    * */
    if (!trigger_exception)
        trigger_exception++;
}


O3 void intbh_handler()
{
    /*
    * Questo interrupt viene triggherato quando viene eseguita una divisione
    * per zero.
    * Prima di eseguire la DIV la cpu esegue dei controlli per verificare la validità
    * del divisore. Se vede che e' 0 viene triggherata una eccezione, andando
    * a chiamare così la funzione puntata dal puntatore in IDT[0]
    * */
    if (!trigger_exception)
        trigger_exception++;
}


O3 void intch_handler()
{
    /*
    * Questo interrupt viene triggherato quando viene eseguita una divisione
    * per zero.
    * Prima di eseguire la DIV la cpu esegue dei controlli per verificare la validità
    * del divisore. Se vede che e' 0 viene triggherata una eccezione, andando
    * a chiamare così la funzione puntata dal puntatore in IDT[0]
    * */
    if (!trigger_exception)
        trigger_exception++;
}


O3 void intdh_handler()
{
    /*
    * Questo interrupt viene triggherato quando viene eseguita una divisione
    * per zero.
    * Prima di eseguire la DIV la cpu esegue dei controlli per verificare la validità
    * del divisore. Se vede che e' 0 viene triggherata una eccezione, andando
    * a chiamare così la funzione puntata dal puntatore in IDT[0]
    * */
    if (!trigger_exception)
        trigger_exception++;
}

O3 void inteh_handler()
{
    /*
    * Questo interrupt viene triggherato quando viene eseguita una divisione
    * per zero.
    * Prima di eseguire la DIV la cpu esegue dei controlli per verificare la validità
    * del divisore. Se vede che e' 0 viene triggherata una eccezione, andando
    * a chiamare così la funzione puntata dal puntatore in IDT[0]
    * */
    if (!trigger_exception)
        trigger_exception++;
}


O3 void intfh_handler()
{
    /*
    * Questo interrupt viene triggherato quando viene eseguita una divisione
    * per zero.
    * Prima di eseguire la DIV la cpu esegue dei controlli per verificare la validità
    * del divisore. Se vede che e' 0 viene triggherata una eccezione, andando
    * a chiamare così la funzione puntata dal puntatore in IDT[0]
    * */
    if (!trigger_exception)
        trigger_exception++;
}


O3 void int10h_handler()
{
    /*
    * Questo interrupt viene triggherato quando viene eseguita una divisione
    * per zero.
    * Prima di eseguire la DIV la cpu esegue dei controlli per verificare la validità
    * del divisore. Se vede che e' 0 viene triggherata una eccezione, andando
    * a chiamare così la funzione puntata dal puntatore in IDT[0]
    * */
    if (!trigger_exception)
        trigger_exception++;
}


O3 void int11h_handler()
{
    /*
    * Questo interrupt viene triggherato quando viene eseguita una divisione
    * per zero.
    * Prima di eseguire la DIV la cpu esegue dei controlli per verificare la validità
    * del divisore. Se vede che e' 0 viene triggherata una eccezione, andando
    * a chiamare così la funzione puntata dal puntatore in IDT[0]
    * */
    if (!trigger_exception)
        trigger_exception++;
}


O3 void int12h_handler()
{
    /*
    * Questo interrupt viene triggherato quando viene eseguita una divisione
    * per zero.
    * Prima di eseguire la DIV la cpu esegue dei controlli per verificare la validità
    * del divisore. Se vede che e' 0 viene triggherata una eccezione, andando
    * a chiamare così la funzione puntata dal puntatore in IDT[0]
    * */
    if (!trigger_exception)
        trigger_exception++;
}


O3 void int13h_handler()
{
    /*
    * Questo interrupt viene triggherato quando viene eseguita una divisione
    * per zero.
    * Prima di eseguire la DIV la cpu esegue dei controlli per verificare la validità
    * del divisore. Se vede che e' 0 viene triggherata una eccezione, andando
    * a chiamare così la funzione puntata dal puntatore in IDT[0]
    * */
    if (!trigger_exception)
        trigger_exception++;
}


O3 void int14h_handler()
{
    /*
    * Questo interrupt viene triggherato quando viene eseguita una divisione
    * per zero.
    * Prima di eseguire la DIV la cpu esegue dei controlli per verificare la validità
    * del divisore. Se vede che e' 0 viene triggherata una eccezione, andando
    * a chiamare così la funzione puntata dal puntatore in IDT[0]
    * */
    if (!trigger_exception)
        trigger_exception++;
}


O3 void int15h_handler()
{
    /*
    * Questo interrupt viene triggherato quando viene eseguita una divisione
    * per zero.
    * Prima di eseguire la DIV la cpu esegue dei controlli per verificare la validità
    * del divisore. Se vede che e' 0 viene triggherata una eccezione, andando
    * a chiamare così la funzione puntata dal puntatore in IDT[0]
    * */
    if (!trigger_exception)
        trigger_exception++;
}


O3 void int16h_handler()
{
    /*
    * Questo interrupt viene triggherato quando viene eseguita una divisione
    * per zero.
    * Prima di eseguire la DIV la cpu esegue dei controlli per verificare la validità
    * del divisore. Se vede che e' 0 viene triggherata una eccezione, andando
    * a chiamare così la funzione puntata dal puntatore in IDT[0]
    * */
    if (!trigger_exception)
        trigger_exception++;
}


O3 void int17h_handler()
{
    /*
    * Questo interrupt viene triggherato quando viene eseguita una divisione
    * per zero.
    * Prima di eseguire la DIV la cpu esegue dei controlli per verificare la validità
    * del divisore. Se vede che e' 0 viene triggherata una eccezione, andando
    * a chiamare così la funzione puntata dal puntatore in IDT[0]
    * */
    if (!trigger_exception)
        trigger_exception++;
}


O3 void int18h_handler()
{
    /*
    * Questo interrupt viene triggherato quando viene eseguita una divisione
    * per zero.
    * Prima di eseguire la DIV la cpu esegue dei controlli per verificare la validità
    * del divisore. Se vede che e' 0 viene triggherata una eccezione, andando
    * a chiamare così la funzione puntata dal puntatore in IDT[0]
    * */
    if (!trigger_exception)
        trigger_exception++;
}


O3 void int19h_handler()
{
    /*
    * Questo interrupt viene triggherato quando viene eseguita una divisione
    * per zero.
    * Prima di eseguire la DIV la cpu esegue dei controlli per verificare la validità
    * del divisore. Se vede che e' 0 viene triggherata una eccezione, andando
    * a chiamare così la funzione puntata dal puntatore in IDT[0]
    * */
    if (!trigger_exception)
        trigger_exception++;
}


O3 void int1ah_handler()
{
    /*
    * Questo interrupt viene triggherato quando viene eseguita una divisione
    * per zero.
    * Prima di eseguire la DIV la cpu esegue dei controlli per verificare la validità
    * del divisore. Se vede che e' 0 viene triggherata una eccezione, andando
    * a chiamare così la funzione puntata dal puntatore in IDT[0]
    * */
    if (!trigger_exception)
        trigger_exception++;
}


O3 void int1bh_handler()
{
    /*
    * Questo interrupt viene triggherato quando viene eseguita una divisione
    * per zero.
    * Prima di eseguire la DIV la cpu esegue dei controlli per verificare la validità
    * del divisore. Se vede che e' 0 viene triggherata una eccezione, andando
    * a chiamare così la funzione puntata dal puntatore in IDT[0]
    * */
    if (!trigger_exception)
        trigger_exception++;
}


O3 void int1ch_handler()
{
    /*
    * Questo interrupt viene triggherato quando viene eseguita una divisione
    * per zero.
    * Prima di eseguire la DIV la cpu esegue dei controlli per verificare la validità
    * del divisore. Se vede che e' 0 viene triggherata una eccezione, andando
    * a chiamare così la funzione puntata dal puntatore in IDT[0]
    * */
    if (!trigger_exception)
        trigger_exception++;
}


O3 void int1dh_handler()
{
    /*
    * Questo interrupt viene triggherato quando viene eseguita una divisione
    * per zero.
    * Prima di eseguire la DIV la cpu esegue dei controlli per verificare la validità
    * del divisore. Se vede che e' 0 viene triggherata una eccezione, andando
    * a chiamare così la funzione puntata dal puntatore in IDT[0]
    * */
    if (!trigger_exception)
        trigger_exception++;
}


O3 void int1eh_handler()
{
    /*
    * Questo interrupt viene triggherato quando viene eseguita una divisione
    * per zero.
    * Prima di eseguire la DIV la cpu esegue dei controlli per verificare la validità
    * del divisore. Se vede che e' 0 viene triggherata una eccezione, andando
    * a chiamare così la funzione puntata dal puntatore in IDT[0]
    * */
    if (!trigger_exception)
        trigger_exception++;
}


O3 void int1fh_handler()
{
    /*
    * Questo interrupt viene triggherato quando viene eseguita una divisione
    * per zero.
    * Prima di eseguire la DIV la cpu esegue dei controlli per verificare la validità
    * del divisore. Se vede che e' 0 viene triggherata una eccezione, andando
    * a chiamare così la funzione puntata dal puntatore in IDT[0]
    * */
    if (!trigger_exception)
        trigger_exception++;
}


O3 void int20h_handler()
{
    if (!trigger_exception)
        goto out;

    if (num_color > 15)
        num_color = 1;

    switch (num_color) {
        // ho saltato un colore perche' il colore delle scritte sono uguali al colore del bg
        case 1:
            actual_color_terminal = BG_GC_C_GC(BLU, NERO);
            break;
        case 2:
            actual_color_terminal = BG_GC_C_GC(BLU, VERDE);
            break;
        case 3:
            actual_color_terminal = BG_GC_C_GC(BLU, CIANO);
            break;
        case 4:
            actual_color_terminal = BG_GC_C_GC(BLU, ROSSO);
            break;
        case 5:
            actual_color_terminal = BG_GC_C_GC(BLU, VIOLA);
            break;
        case 6:
            actual_color_terminal = BG_GC_C_GC(BLU, MARRONE);
            break;
        case 7:
            actual_color_terminal = BG_GC_C_GC(BLU, GRIGIO);
            break;
        case 8:
            actual_color_terminal = BG_GC_C_GC(BLU, GRIGIO_SCURO);
            break;
        case 9:
            actual_color_terminal = BG_GC_C_GC(BLU, BLU_CHIARO);
            break;
        case 10:
            actual_color_terminal = BG_GC_C_GC(BLU, VERDE_CHIARO);
            break;
        case 11:
            actual_color_terminal = BG_GC_C_GC(BLU, CIANO_CHIARO);
            break;
        case 12:
            actual_color_terminal = BG_GC_C_GC(BLU, ROSSO_CHIARO);
            break;
        case 13:
            actual_color_terminal = BG_GC_C_GC(BLU, VIOLA_CHIARO);
            break;
        case 14:
            actual_color_terminal = BG_GC_C_GC(BLU, GIALLO);
            break;
        case 15:
            actual_color_terminal = BG_GC_C_GC(BLU, BIANCO);
            break;
    }

    panic((uchar*) "Impossibile eseguire la divisione per zero\n");

    num_color++;
out:
    EOI_MASTER;
}


extern void gestisci_scancode_from_controller(u8);


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
    * la cpu si va a leggere dal buffer del controller della tastiera il char.
    * Se il buffer è stato svuotato completamente, il PIC abbassa IRQ#1.
    */
    u8 scancode = insb(0x60);

    gestisci_scancode_from_controller(scancode);

out:
    EOI_MASTER;
}


O3 void int22h_handler()
{
    EOI_MASTER;
}


O3 void int23h_handler()
{
    EOI_MASTER;
}


O3 void int24h_handler()
{
    EOI_MASTER;
}


O3 void int25h_handler()
{
    EOI_MASTER;
}


O3 void int26h_handler()
{
    EOI_MASTER;
}


O3 void int27h_handler()
{
    EOI_MASTER;
}


O3 void int28h_handler()
{
    /*
    * RTC orologio
    ****/
    EOI_SLAVE;
    EOI_MASTER;
}


O3 void int29h_handler()
{
    EOI_SLAVE;
    EOI_MASTER;
}


O3 void int2ah_handler()
{
    EOI_SLAVE;
    EOI_MASTER;
}


O3 void int2bh_handler()
{
    EOI_SLAVE;
    EOI_MASTER;
}


O3 void int2ch_handler()
{
    EOI_SLAVE;
    EOI_MASTER;
}


O3 void int2dh_handler()
{
    EOI_SLAVE;
    EOI_MASTER;
}


O3 void int2eh_handler()
{
    EOI_SLAVE;
    EOI_MASTER;
}


O3 void int2fh_handler()
{
    EOI_SLAVE;
    EOI_MASTER;
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


O3 static inline void set_timer_pit()
{
    #define oscilloscopio_frequenza 1193182
    #define hz 1193182 - 1

    u16 divisione = oscilloscopio_frequenza / hz;

    outb(0x43, 0x36);
    outb(0x40, divisione & 0xFF);   // low
    outb(0x40, divisione >> 8);     // high
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
    // memset((void*) bff_cmd_line, 0, SIZE_COMMAND_SHELL);

    memset(idt_descriptors, 0, sizeof(idt_descriptors)); // azzero tutti i campi della tabella

    idtr_descriptor.limit   = sizeof(idt_descriptors) - 1;
    idtr_descriptor.base    = (u32) idt_descriptors;

    set_default_int();

    /* ECCEZIONI DELLA CPU */
    idt_set(0x00, int0h);   // divisione per zero
    idt_set(0x01, int1h);   // debug
    idt_set(0x02, int2h);   // IMI
    idt_set(0x03, int3h);   // breackpoint
    idt_set(0x04, int4h);   // Overflow
    idt_set(0x05, int5h);   // Bound
    idt_set(0x06, int6h);   // Invalid opcode
    idt_set(0x07, int7h);   // Device not available
    idt_set(0x08, int8h);   // double fault
    idt_set(0x09, int9h);   // Coprocessor segment overrun
    idt_set(0x0a, intah);   // Invalid TSS
    idt_set(0x0b, intbh);   // Segment not present
    idt_set(0x0c, intch);   // Stack fault
    idt_set(0x0d, intdh);   // General Protection Fault
    idt_set(0x0e, inteh);   // Page fault
    idt_set(0x0f, intfh);   // disoccupato
    idt_set(0x10, int10h);   // x86 FPU error
    idt_set(0x11, int11h);   // Alignment check
    idt_set(0x12, int12h);   // Machine check
    idt_set(0x13, int13h);   // SIMD floating point
    idt_set(0x14, int14h);   // disoccupato
    idt_set(0x15, int15h);   // disoccupato
    idt_set(0x16, int16h);   // disoccupato
    idt_set(0x17, int17h);   // disoccupato
    idt_set(0x18, int18h);   // disoccupato
    idt_set(0x19, int19h);   // disoccupato
    idt_set(0x1a, int1ah);   // disoccupato
    idt_set(0x1b, int1bh);   // disoccupato
    idt_set(0x1c, int1ch);   // disoccupato
    idt_set(0x1d, int1dh);   // disoccupato
    idt_set(0x1e, int1eh);   // disoccupato
    idt_set(0x1f, int1fh);   // disoccupato

    /* IRQ MASTER */
    idt_set(0x20, int20h);  // PIT timer
    idt_set(0x21, int21h);  // tastiera
    idt_set(0x22, int22h);  // collegamento verso lo slave
    idt_set(0x23, int23h);  // COM2 / COM4
    idt_set(0x24, int24h);  // COM1 / COM3
    idt_set(0x25, int25h);  // LPT / audio
    idt_set(0x26, int26h);  // floppy
    idt_set(0x27, int27h);  // spurious

    /* IRQ SLAVE */
    idt_set(0x28, int28h);  // RTC (orologio)
    idt_set(0x29, int29h);  // redirect to irq2 del master
    idt_set(0x2A, int2ah);  // libero
    idt_set(0x2B, int2bh);  // libero
    idt_set(0x2C, int2ch);  // mouse
    idt_set(0x2D, int2dh);  // FPU
    idt_set(0x2E, int2eh);  // IDE Primary 
    idt_set(0x2F, int2fh);  // IDE Secondary
    
    // Load the interrupt descriptor table
    idt_load(&idtr_descriptor);

    set_timer_pit();
}
