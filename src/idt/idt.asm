section .asm

%include "src/idt/exception_cpu.asm"
%include "src/idt/pic/master_pic.asm"
%include "src/idt/pic/slave_pic.asm"

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

