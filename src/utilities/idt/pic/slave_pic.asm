%ifndef SLAVE_PIC
%define SLAVE_PIC

section .asm

global int28h
global int29h
global int2ah
global int2bh
global int2ch
global int2dh
global int2eh
global int2fh


extern int28h_handler
extern int29h_handler
extern int2ah_handler
extern int2bh_handler
extern int2ch_handler
extern int2dh_handler
extern int2eh_handler
extern int2fh_handler


int28h:    
    cli

    GESTIONE_STACK_INT int28h_handler

    sti
    iret


int29h:    
    cli

    GESTIONE_STACK_INT int29h_handler

    popad
    sti
    iret


int2ah:    
    cli

    GESTIONE_STACK_INT int2ah_handler

    sti
    iret


int2bh:    
    cli

    GESTIONE_STACK_INT int2bh_handler

    sti
    iret


int2ch:    
    cli

    GESTIONE_STACK_INT int2ch_handler

    sti
    iret


int2dh:    
    cli

    GESTIONE_STACK_INT int2dh_handler

    sti
    iret


int2eh:    
    cli

    GESTIONE_STACK_INT int2eh_handler

    sti
    iret


int2fh:    
    cli

    GESTIONE_STACK_INT int20h_handler

    sti
    iret


%endif
