%ifndef SYSCALLS_ASM
%define SYSCALLS_ASM

%define KERNEL_DS 0x10

section .asm


global int80h
extern int80h_handler


int80h:
    cli
    GESTIONE_STACK_INT int80h_handler
    sti
    iret

%endif
