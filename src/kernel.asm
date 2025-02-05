[BITS 32]

global _start
extern kernel_main

CODE_SEG equ 0x08
DATA_SEG equ 0x10

_start:
    mov ax, DATA_SEG
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax
    mov ss, ax
    mov ebp, 0x00200000
    mov esp, ebp

    ; Enable the A20 line
    in al, 0x92
    or al, 2
    out 0x92, al
    ; end Enable a20 line

    ; remap the master PIC
    mov al, 00010000b 
    out 0x20, al ; tell master PIC

    mov al, 0x20 ; 0x20 e' dove il master ISR dovrebbe cominciare
    out 0x21, al

    mov al, 00000001b
    out 0x21, al
    ; end remap master PIC

    call kernel_main
    jmp $


times 512-($ - $$) db 0