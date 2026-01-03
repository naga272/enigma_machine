#ifndef IDT_H
#define IDT_H

#include <stdint.h>
#include <stddef.h>
#include "utilities/io/io.h"
#include "utilities/idt/interrupts_num.h"

/*
* L'interrupt descriptor table descrive come gli interrupt vengono chiamati in protected mode.
* Una istanza della struct @idt_desc == a una singola voce dell'idt
* 
* La struct @idt_desc DEVE AVERE IL SEGUENTE ORDINE:
* @offset_1:    la "parte bassa" dell'indirizzo della routine da eseguire
* @selector:    contiene la routine di gestione dell'interrupt. Per le routine non usate, il campo viene settato a 0
* @zero:        non usabile, da settare a 0
* @type_attr:   tipi e attributi dell'entry. definisce il tipo di gate(interrupt gate e trap gate) e i privilegi richiesti
* @offset_2:    la "parte alta" dell'indirizzo della routine da eseguire
*
*
* Invece la struct @idtr_desc rappresenta lo stato del registro idtr (interrupt descriptor table register)
* La struct @idtr_desc DEVE AVERE IL SEGUENTE ORDINE:
* @limit:   grandezza max della idt (sizeof(idt_desc[OS_TOTAL_INTERRUPTS]) - 1)
* @base:    indirizzo da dove parte la tabella idt_desc[OS_TOTAL_INTERRUPTS]
*
* Le struct non devono avere padding aggiunto dal compilatore, quindi uso __attribute__((packed))
*/

struct idt_desc
{
    uint16_t offset_1;  // Offset bits 0 - 15
    uint16_t selector;  // Selector thats in our GDT
    uint8_t zero;       // Does nothing, unused set to zero
    uint8_t type_attr;  // Descriptor type and attributes
    uint16_t offset_2;  // Offset bits 16-31
} __attribute__((packed));


struct idtr_desc
{
    uint16_t limit;     // Size of descriptor table -1
    uint32_t base;      // Base address of the start of the interrupt descriptor table
} __attribute__((packed));


void idt_init();
void enable_interrupts();
void disable_interrupts();

// usato per l'assegnamento di una funzione di default agli interrupt 
void no_interrupt();
void idt_load(struct idtr_desc* ptr); // (carica IN IDTR la idt)


#ifndef EOI_MASTER
#define EOI_MASTER outb(0x20, 0x20)
#endif

#ifndef EOI_SLAVE
#define EOI_SLAVE outb(0xA0, 0x20)
#endif


// from stdlib/stdlib.c - stdlib.h
extern void* memset(void *ptr, int c, size_t n);


typedef struct regs_t {
    u32 ds;
    u32 es;
    u32 fs;
    u32 gs;

    u32 edi;
    u32 esi;
    u32 ebp;
    u32 esp;
    u32 ebx;
    u32 edx;
    u32 ecx;
    u32 eax;

    u32 int_no;
    u32 err_code;

    u32 eip;
    u32 cs;
    u32 eflags;
} regs_t;

#endif
