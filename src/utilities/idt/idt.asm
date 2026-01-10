section .asm

; Note: GESTIONE_STACK_INT deve stare qui per evitare errori con l'assembler
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


%include "src/utilities/idt/syscalls.asm"
%include "src/utilities/idt/exception_cpu.asm"
%include "src/utilities/idt/pic/master_pic.asm"
%include "src/utilities/idt/pic/slave_pic.asm"


global idt_load
global no_interrupt


global enable_interrupts    ; abilita interrupt (istruzione sti)
global disable_interrupts   ; disabilita interrupt (istruzione cli)


; functions descitte in idt.c
extern no_interrupt_handler


enable_interrupts:
    sti
    ret


disable_interrupts:
    cli
    ret


idt_load: 
    ; carica il registro IDTR col valore passato come parametro
    push ebp
    mov ebp, esp

    mov ebx, [ebp + 8]
    lidt[ebx]

    pop ebp
    ret


no_interrupt: 
    cli
    pushad

    call no_interrupt_handler

    popad
    sti
    iret
