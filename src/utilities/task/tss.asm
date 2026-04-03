section .asm

global tss_load


tss_load:
    push ebp
    mov ebp, esp

    ; ax contiene l'entry TSS della GDT
    mov ax, [ebp + 8]

    ; ltr = Load Task Register
    ; istruzione usata per caricare nel registro tr l'entry tss
    ltr ax

    pop ebp
    ret
