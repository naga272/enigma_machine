section .asm

global idt_load
global no_interrupt
global int0h
global int20h
global int21h
global int22h
global int23h
global int24h
global int25h
global int26h
global int27h
global int28h
global int29h
global int2ah
global int2bh
global int2ch
global int2dh
global int2eh
global int2fh
global enable_interrupts    ; abilita interrupt (istruzione sti)
global disable_interrupts   ; disabilita interrupt (istruzione cli)


; functions descitte in idt.c
extern no_interrupt_handler
extern int0h_handler
extern int20h_handler
extern int21h_handler
extern int22h_handler
extern int23h_handler
extern int24h_handler
extern int25h_handler
extern int26h_handler
extern int27h_handler
extern int28h_handler
extern int29h_handler
extern int2ah_handler
extern int2bh_handler
extern int2ch_handler
extern int2dh_handler
extern int2eh_handler
extern int2fh_handler


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


int0h:
    cli
    pushad

    call int0h_handler

    popad
    sti
    iret


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
