#ifndef CONVERSION_H
#define CONVERSION_H

u32 htons_32b(u32);
u16 htons_16b(u16);
u32 ip_to_u32(u8 a, u8 b, u8 c, u8 d);


extern u16 htons_16b(u16);
extern u32 htons_32b(u32);
extern u32 ip_to_u32(u8 a, u8 b, u8 c, u8 d);

#endif