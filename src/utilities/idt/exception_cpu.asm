%ifndef EXCEPTION_CPU_ASM
%define EXCEPTION_CPU_ASM

section .asm

global int0h
global int1h
global int2h
global int3h
global int4h
global int5h
global int6h
global int7h
global int8h
global int9h
global intah
global intbh
global intch
global intdh
global inteh
global intfh
global int10h
global int11h
global int12h
global int13h
global int14h
global int15h
global int16h
global int17h
global int18h
global int19h
global int1ah
global int1bh
global int1ch
global int1dh
global int1eh
global int1fh

extern int0h_handler
extern int1h_handler
extern int2h_handler
extern int3h_handler
extern int4h_handler
extern int5h_handler
extern int6h_handler
extern int7h_handler
extern int8h_handler
extern int9h_handler
extern intah_handler
extern intbh_handler
extern intch_handler
extern intdh_handler
extern inteh_handler
extern intfh_handler
extern int10h_handler
extern int11h_handler
extern int12h_handler
extern int13h_handler
extern int14h_handler
extern int15h_handler
extern int16h_handler
extern int17h_handler
extern int18h_handler
extern int19h_handler
extern int1ah_handler
extern int1bh_handler
extern int1ch_handler
extern int1dh_handler
extern int1eh_handler
extern int1fh_handler


int0h:
    cli

    GESTIONE_STACK_INT int0h_handler

    sti
    iret


int1h:
    cli

    GESTIONE_STACK_INT int1h_handler

    sti
    iret


int2h:
    cli

    GESTIONE_STACK_INT int2h_handler

    sti
    iret


int3h:
    cli
    
    GESTIONE_STACK_INT int3h_handler

    sti
    iret


int4h:
    cli
    
    GESTIONE_STACK_INT int4h_handler

    sti
    iret


int5h:
    cli

    GESTIONE_STACK_INT int5h_handler

    sti
    iret


int6h:
    cli

    GESTIONE_STACK_INT int6h_handler

    sti
    iret


int7h:
    cli

    GESTIONE_STACK_INT int7h_handler

    sti
    iret


int8h:
    cli

    GESTIONE_STACK_INT int8h_handler

    sti
    iret


int9h:
    cli
    
    GESTIONE_STACK_INT int9h_handler

    sti
    iret


intah:
    cli

    GESTIONE_STACK_INT intah_handler

    sti
    iret


intbh:
    cli

    GESTIONE_STACK_INT intbh_handler

    sti
    iret


intch:
    cli

    GESTIONE_STACK_INT intch_handler

    sti
    iret


intdh:
    cli

    GESTIONE_STACK_INT intdh_handler

    sti
    iret


inteh:
    cli

    GESTIONE_STACK_INT inteh_handler

    sti
    iret


intfh:
    cli

    GESTIONE_STACK_INT intfh_handler

    sti
    iret


int10h:
    cli

    GESTIONE_STACK_INT int10h_handler

    sti
    iret


int11h:
    cli

    GESTIONE_STACK_INT int11h_handler

    sti
    iret


int12h:
    cli

    GESTIONE_STACK_INT int12h_handler

    sti
    iret


int13h:
    cli

    GESTIONE_STACK_INT int13h_handler

    sti
    iret


int14h:
    cli

    GESTIONE_STACK_INT int14h_handler

    sti
    iret


int15h:
    cli

    GESTIONE_STACK_INT int15h_handler

    sti
    iret


int16h:
    cli

    GESTIONE_STACK_INT int16h_handler

    sti
    iret


int17h:
    cli

    GESTIONE_STACK_INT int17h_handler

    sti
    iret


int18h:
    cli

    GESTIONE_STACK_INT int18h_handler

    sti
    iret


int19h:
    cli

    GESTIONE_STACK_INT int19h_handler

    sti
    iret


int1ah:
    cli

    GESTIONE_STACK_INT int1ah_handler

    sti
    iret


int1bh:
    cli

    GESTIONE_STACK_INT int1bh_handler

    sti
    iret


int1ch:
    cli

    GESTIONE_STACK_INT int1ch_handler

    sti
    iret


int1dh:
    cli

    GESTIONE_STACK_INT int1dh_handler

    sti
    iret


int1eh:
    cli

    GESTIONE_STACK_INT int1eh_handler

    sti
    iret


int1fh:
    cli

    GESTIONE_STACK_INT int1fh_handler

    sti
    iret

%endif
