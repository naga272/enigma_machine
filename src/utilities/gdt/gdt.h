#ifndef GDT_H
#define GDT_H


#include "config.h"


/*
* struct gdt
*  @segment         -> Contiene i bit 0-15 del segmento (parte high)
*  @base_first      -> Contiene i bit 0-15 del segmento (parte low)
*  @base            -> Contiene i bit 16-23 della base
*  @access          -> Byte che definisce tipo e privilegi del segmento:
*                      P DPL S TYPE
*                      P    = (bit 7) Present, il segmento e' presente in ram
*                      DPL  = (bit 6-5) privilegi, determina il ring
*                      S    = (bit 4) Descriptor type, e' code o data segment?
*                      TYPE = (bit 3-0) il segmento e' rwx?
*  @high_flags      -> Bit 0-3 = bit 16-19 del limit
*                      bit 4-7 = flag del segmento
*  @base_24_31_bits -> Contiene gli ultimi 8 bit della base
**/
struct gdt {
    u16 segment;
    u16 base_first;
    u8 base;
    u8 access;
    u8 high_flags;
    u8 base_24_31_bits;
};


/*
* Serve per non costruire manualmente una entry gdt usando la struct gdt.
* Basta compilare questi tre campi e passarla poi alla funzione
* gdt_structured_to_gdt
** */
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