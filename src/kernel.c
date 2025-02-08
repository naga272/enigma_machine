#include "config.h"
#include "kernel.h"
#include "idt/idt.h"


extern void terminal_initialize();
extern void print(unsigned const char*);


void kernel_main()
{
    terminal_initialize();
    idt_init();
    enable_interrupts();
}