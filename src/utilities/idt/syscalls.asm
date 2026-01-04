%ifndef SYSCALLS_ASM
%define SYSCALLS_ASM

%define KERNEL_DS 0x10

section .asm


global int80h
extern int80h_handler


%macro GESTIONE_STACK_INT 1
    push 0              ; num error code
    push 0              ; int_no = 0

    pushad              ; salva EAX..EDI
    push ds
    push es
    push fs
    push gs

    mov ax, 0x10
    mov ds, ax
    mov es, ax

    push esp            ; &regs_t
    call %1
    add esp, 4

    pop gs
    pop fs
    pop es
    pop ds
    popad
    add esp, 8          ; err_code + int_no
%endmacro


int80h:
    cli
    GESTIONE_STACK_INT int80h_handler
    iret

%endif
