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
    pushad

    call int20h_handler

    popad
    sti
    iret


int21h:    
    cli
    pushad

    call int21h_handler

    popad
    sti
    iret


int22h:    
    cli
    pushad

    call int22h_handler

    popad
    sti
    iret


int23h:    
    cli
    pushad

    call int23h_handler

    popad
    sti
    iret


int24h:    
    cli
    pushad

    call int24h_handler

    popad
    sti
    iret


int25h:    
    cli
    pushad

    call int25h_handler

    popad
    sti
    iret


int26h:    
    cli
    pushad

    call int26h_handler

    popad
    sti
    iret


int27h:    
    cli
    pushad

    call int27h_handler

    popad
    sti
    iret

%endif
