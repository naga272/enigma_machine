section .asm


global test_int80h

buffer_test_int80h: db "Hello world", 0x00


test_int80h:
    pushad

    mov eax, 4 ; write syscall
    mov ebx, 1
    mov ecx, buffer_test_int80h
    mov edx, 12
    int 80h     ; syscall SYS_WRITE

    popad
    ret
