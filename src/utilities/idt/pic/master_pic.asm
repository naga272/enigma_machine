%ifndef MASTER_PIC_ASM
%define MASTER_PIC_ASM

section .asm


global int20h
global int21h
global int22h
global int23h
global int24h
global int25h
global int26h
global int27h


extern int20h_handler
extern int21h_handler
extern int22h_handler
extern int23h_handler
extern int24h_handler
extern int25h_handler
extern int26h_handler
extern int27h_handler


int20h:    
    cli

    GESTIONE_STACK_INT int20h_handler

    sti
    iret


int21h:    
    cli

    GESTIONE_STACK_INT int21h_handler

    sti
    iret


int22h:    
    cli

    GESTIONE_STACK_INT int22h_handler

    sti
    iret


int23h:    
    cli

    GESTIONE_STACK_INT int23h_handler

    sti
    iret


int24h:    
    cli

    GESTIONE_STACK_INT int24h_handler

    sti
    iret


int25h:    
    cli

    GESTIONE_STACK_INT int25h_handler

    sti
    iret


int26h:    
    cli

    GESTIONE_STACK_INT int26h_handler

    sti
    iret


int27h:    
    cli

    GESTIONE_STACK_INT int27h_handler

    sti
    iret

%endif
