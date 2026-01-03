%ifndef SYSCALLS_ASM
%define SYSCALLS_ASM

%define KERNEL_DS 0x10

section .asm


global int80h
extern int80h_handler


int80h:
    pusha
    push ds
    push es
    push fs
    push gs

    mov ax, KERNEL_DS
    mov ds, ax
    mov es, ax

    push esp              ; passa puntatore a regs_t
    call int80h_handler

    ; rimpiazzo eax salvato da pusha
    add esp, 4
    mov [esp + 28], eax
    pop gs
    pop fs
    pop es
    pop ds
    popa
    iret

%endif
