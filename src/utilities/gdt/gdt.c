#include "utilities/gdt/gdt.h"
#include "utilities/stdlib/stdlib.h"
#include "utilities/task/tss.h"


MODULE_LICENSE("GPL-3.0");
MODULE_AUTHOR("naga272");
MODULE_DESCRIPTION("ridefinizione della gdt per il kernel");


/* 
* La GDT del bootloader e' usa e getta. Bisogna crearne un'altra per il kernel
* che verra' usata per il resto dell'eseucizione.
*   Steps:
*       - bootloader crea una gdt temporanea
*       - bootloader inserisce quella gdt tramite lgdt
*       - viene caricato poi il kernel in ram e fatto il jmp
*       - il Kernel crea la sua gdt, sovrascrivendo quella del bootloader
**/

struct tss tss;
extern void set_message_x_panic(uchar* msg);


struct gdt gdt_real[ENIGMAOS_TOTAL_GDT_SEGMENTS];
struct gdt_structured gdt_structured[ENIGMAOS_TOTAL_GDT_SEGMENTS] = {
    {.base = 0x00, .limit = 0x00, .type = 0x00},                 // NULL Segment (richiesta obbligatoria dalla CPU)

    // tutto questo significa che il codice e i dati condividono tutto lo spazio di memoria (4gb)
    {.base = 0x00, .limit = 0xffffffff, .type = 0x9a},           // Kernel code segment
    {.base = 0x00, .limit = 0xffffffff, .type = 0x92},           // Kernel data segment

    // user ring
    {.base = 0x00, .limit = 0xffffffff, .type = 0xf8},           // user code segment
    {.base = 0x00, .limit = 0xffffffff, .type = 0xf2},           // user data segment

    // tss segment
    {.base = (u32) &tss, .limit = sizeof(tss), .type = 0xE9},    // tss segment
};


void encodeGdtEntry(u8* target, struct gdt_structured source)
{
    if ((source.limit > 65536) && ((source.limit & 0xFFF) != 0xFFF))
        set_message_x_panic((uchar*) "Error encodeGdtEntry!\n");

    target[6] = 0x40;
    if (source.limit > 65536) {
        source.limit = source.limit >> 12;
        target[6] = 0xC0;
    }

    // Encodes the limit
    target[0] = source.limit & 0xFF;
    target[1] = (source.limit >> 8) & 0xFF;
    target[6] |= (source.limit >> 16) & 0x0F;

    // Encode the base
    target[2] = source.base & 0xFF;
    target[3] = (source.base >> 8) & 0xFF;
    target[4] = (source.base >> 16) & 0xFF;
    target[7] = (source.base >> 24) & 0xFF;

    // Set the type
    target[5] = source.type;
}


void gdt_structured_to_gdt(struct gdt* gdt, struct gdt_structured* structured_gdt, i32 total_entires)
{
    for (i32 i = 0; i < total_entires; i++)
        encodeGdtEntry((u8*) &gdt[i], structured_gdt[i]);
}


void gdt_init()
{
    // init gdt
    memset(gdt_real, 0x00, sizeof(gdt_real));

    // conversione nella vera entry GDT da 8 byte richiesta dalla CPU
    gdt_structured_to_gdt(gdt_real, gdt_structured, ENIGMAOS_TOTAL_GDT_SEGMENTS);

    // caricamento nel registro per la gdt
    gdt_load(gdt_real, sizeof(gdt_real));

    // inizializzazione tss
    memset(&tss, 0x00, sizeof(tss));
    tss.esp = 0x600000;     // kernel stack
    tss.ss0 = KERNEL_DATA_SELECTOR;

    // load tss
    tss_load(0x28);
}