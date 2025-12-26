%ifndef EXCEPTION_CPU_ASM
%define EXCEPTION_CPU_ASM

section .asm

global int0h

extern int0h_handler

int0h:
    cli
    pushad

    call int0h_handler

    popad
    sti
    iret

%endif
