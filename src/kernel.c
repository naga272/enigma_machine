#define OS_X_QEMU
#define DISPLAY_START_MSG

#include "config.h"
#include "kernel.h"

#include "utilities/stdlib/stdlib.h"

#include "utilities/video/video.h"
#include "utilities/memory/heap/malloc.h"
#include "utilities/memory/heap/kheap_creation.h"
#include "utilities/memory/heap/kheap_creation.h"

#include "utilities/io/io.h"
#include "utilities/idt/idt.h"
#include "utilities/idt/body_int/slave/rtc_orologio.h"
#include "utilities/idt/body_int/master/input_keyboard.h"


extern void test_int80h(void);


O3 void init_shell()
{
    terminal_initialize(BG_BIANCO_C_NERO);

    print((uchar*) start_msg);

    while (FASE_SETUP) {
        try_the_setup(tmp_char_container);
        asm volatile("hlt");
    }
}


O3 static inline void trigger_BsOD()
{
    asm volatile (
        "xor %%edx, %%edx\n"
        "mov $1, %%eax\n"
        "div %%edx\n"
        :
        :
        : "eax", "edx"
    );
}


u8 flag_x_int80h = 0;
static inline void try_int80h()
{
    if (flag_x_int80h)
        return;

    test_int80h();
    flag_x_int80h++;
}


O3 static inline void main()
{
    gestisci_char_to_write(tmp_char_container);
    tmp_char_container = 0;

    render_time();

    /*
    === DIVISIONE PER ZERO TRIGGERA LA Blue Screen of the dead ===
    */
    // trigger_BsOD();

    /*
    === SYSCALL PER UTENTI ===
    */
    // try_int80h();
}


O3 void kernel_main()
{
    disable_interrupts();

    idt_init();

    kheap_init();

    enable_interrupts();

    init_shell();

    // update dats nella struct @t
    rtc_get_time(&t);

    asm volatile("sti");

    while (1) {
        main();
        asm volatile("hlt");
    }
}
