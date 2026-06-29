ENTRY(_start)
OUTPUT_FORMAT(binary)

SECTIONS
{
    . = 1M;
    .text : ALIGN(4096)
    {
        *(.text)
    }
    .rodata : ALIGN(4096)
    {
        *(.rodata)
    }
    .data : ALIGN(4096)
    {
        *(.data)
    }
    .bss : ALIGN(4096)
    {
        *(COMMON)
        *(.bss)
    }
    .asm : ALIGN(4096)
    {
        *(.asm)
    }
    .modinfo : ALIGN(4096)
    {
        KEEP(*(.modinfo))
    }
    .drivers : ALIGN(4096)
    {
        KEEP(*(.drivers))
    }
    .initcall : ALIGN(4096)
    {
        KEEP(*(.initcall))
    }
    .syscalls : ALIGN(4096)
    {
        KEEP(*(.syscalls))
    }
}
