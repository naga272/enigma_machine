#include "config.h"
#include "kernel.h"
#include "idt/idt.h"

#define ENIGMA_SET  // rende visibile struct main_core vidibile al modulo 
#include "enigma/enigma.h"


extern void init_video();
extern void print(unsigned const char*);


void kernel_main()
{
    init_video();
    
    idt_init();

    enable_interrupts();

    main_core = __init__(
        (char*) "EKMFLGDQVZNTOWYHXUSPAIBRCJ",   // rotore 1
        (char*) "AJDKSIRUXBLHWTMCQGZNPYFVOE",   // rotore 2
        (char*) "BDFHJLCPRTXVZNYEIWGAKMUSQO"    // rotore 3
    );
}