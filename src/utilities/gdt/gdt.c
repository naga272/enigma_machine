#include "utilities/gdt/gdt.h"


extern void set_message_x_panic(uchar* msg);


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