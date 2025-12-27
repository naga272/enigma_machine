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
    pushad

    call int0h_handler

    popad
    sti
    iret


int1h:
    cli
    pushad

    call int1h_handler

    popad
    sti
    iret


int2h:
    cli
    pushad

    call int2h_handler

    popad
    sti
    iret


int3h:
    cli
    pushad

    call int3h_handler

    popad
    sti
    iret


int4h:
    cli
    pushad

    call int4h_handler

    popad
    sti
    iret


int5h:
    cli
    pushad

    call int5h_handler

    popad
    sti
    iret


int6h:
    cli
    pushad

    call int6h_handler

    popad
    sti
    iret


int7h:
    cli
    pushad

    call int7h_handler

    popad
    sti
    iret


int8h:
    cli
    pushad

    call int8h_handler

    popad
    sti
    iret


int9h:
    cli
    pushad

    call int9h_handler

    popad
    sti
    iret


intah:
    cli
    pushad

    call intah_handler

    popad
    sti
    iret


intbh:
    cli
    pushad

    call intbh_handler

    popad
    sti
    iret


intch:
    cli
    pushad

    call intch_handler

    popad
    sti
    iret


intdh:
    cli
    pushad

    call intdh_handler

    popad
    sti
    iret


inteh:
    cli
    pushad

    call inteh_handler

    popad
    sti
    iret


intfh:
    cli
    pushad

    call intfh_handler

    popad
    sti
    iret


int10h:
    cli
    pushad

    call int10h_handler

    popad
    sti
    iret


int11h:
    cli
    pushad

    call int11h_handler

    popad
    sti
    iret


int12h:
    cli
    pushad

    call int12h_handler

    popad
    sti
    iret


int13h:
    cli
    pushad

    call int13h_handler

    popad
    sti
    iret


int14h:
    cli
    pushad

    call int14h_handler

    popad
    sti
    iret


int15h:
    cli
    pushad

    call int15h_handler

    popad
    sti
    iret


int16h:
    cli
    pushad

    call int16h_handler

    popad
    sti
    iret


int17h:
    cli
    pushad

    call int17h_handler

    popad
    sti
    iret


int18h:
    cli
    pushad

    call int18h_handler

    popad
    sti
    iret


int19h:
    cli
    pushad

    call int19h_handler

    popad
    sti
    iret


int1ah:
    cli
    pushad

    call int1ah_handler

    popad
    sti
    iret


int1bh:
    cli
    pushad

    call int1bh_handler

    popad
    sti
    iret


int1ch:
    cli
    pushad

    call int1ch_handler

    popad
    sti
    iret


int1dh:
    cli
    pushad

    call int1dh_handler

    popad
    sti
    iret


int1eh:
    cli
    pushad

    call int1eh_handler

    popad
    sti
    iret


int1fh:
    cli
    pushad

    call int1fh_handler

    popad
    sti
    iret

%endif
