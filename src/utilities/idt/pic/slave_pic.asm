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
    pushad

    call int28h_handler

    popad
    sti
    iret


int29h:    
    cli
    pushad

    call int29h_handler

    popad
    sti
    iret


int2ah:    
    cli
    pushad

    call int2ah_handler

    popad
    sti
    iret


int2bh:    
    cli
    pushad

    call int2bh_handler

    popad
    sti
    iret


int2ch:    
    cli
    pushad

    call int2ch_handler

    popad
    sti
    iret


int2dh:    
    cli
    pushad

    call int2dh_handler

    popad
    sti
    iret


int2eh:    
    cli
    pushad

    call int2eh_handler

    popad
    sti
    iret


int2fh:    
    cli
    pushad

    call int2fh_handler

    popad
    sti
    iret


%endif
