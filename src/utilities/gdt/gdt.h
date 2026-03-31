#ifndef GDT_H
#define GDT_H


#include "config.h"


struct gdt {
    u16 segment;
    u16 base_first;
    u8 base;
    u8 access;
    u8 high_flags;
    u8 base_24_31_bits;
};


struct gdt_structured {
    u32 base;
    u32 limit;
    u8 type;
};


void gdt_load(struct gdt* gdt, i32 size);
void gdt_structured_to_gdt(struct gdt* gdt, struct gdt_structured *gdt_structured, i32 total_entries);

extern void gdt_load(struct gdt* gdt, i32 size);
extern void gdt_structured_to_gdt(struct gdt* gdt, struct gdt_structured *gdt_structured, i32 total_entries);

#endif