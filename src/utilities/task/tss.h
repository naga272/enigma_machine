#ifndef TSS_H
#define TSS_H


#include "config.h"


/*
* Il TSS e' una struttura usata dalla cpu per sapere quale stack kernel
* usare quando si passa da ring 3 a ring 0.
*
* Se un utente in ring 3 esegue una syscall o genera un interrupt,
* dallo stack user la cpu deve passare allo stack del kernel.
* Quindi prende ss0 e esp0 dal tss e cambia lo stack automaticamente**
* */

struct tss {
    u32 link;
    u32 esp0;   // kernel stack pointer
    u32 ss0;    // kernel stack segment
    u32 esp1;
    u32 esp2;
    u32 ss2;
    u32 sr3;
    u32 eip;
    u32 eflags;
    u32 eax;
    u32 ecx;
    u32 edx;
    u32 ebx;
    u32 esp;
    u32 ebp;
    u32 esi;
    u32 edi;
    u32 es;
    u32 cs;
    u32 ss;
    u32 ds;
    u32 fs;
    u32 gs;
    u32 ldtr;
    u32 iobp;
} __attribute__((packed));


void tss_load(i32 tss_segment);

extern void tss_load(i32 tss_segment);

#endif