#include "config.h"
#include "utilities/conversion/conversion.h"


O3 static inline ainline u16 switch_endian16(u16 nb)
{
    return (nb >> 8) | (nb << 8);
}


O3 static inline ainline u32 switch_endian32(u32 nb)
{
    return ((nb >> 24) & 0xff)       |
            ((nb << 8) & 0xff0000)   |
            ((nb >> 8) & 0xff00)     |
            ((nb << 24) & 0xff000000);
}


O3 u16 htons_16b(u16 host16)
{
    /* htons
    *  Host TO Network Short
    *
    *  Converte un valore a 16 bit dal formato host endian
    *  (x86 = little endian) al formato network endian
    *  (big endian).
    *
    *  Uso:
    *  Ethernet EtherType
    *  porte TCP/UDP
    *  campi IPv4 a 16 bit
    *
    *  Esempio:
    *  0x0806 (ARP)
    *  in RAM x86 = 06 08
    *  network    = 08 06
    *
    *  @host16 -> valore 16 bit in endian host
    *
    *  Return:
    *  valore convertito in network byte order
    */
    return switch_endian16(host16);
}


O3 u32 htons_32b(u32 host32)
{
    /* htons
    *  Host TO Network Short
    *
    *  Scopo:
    *  Converte un valore a 32 bit dal formato host endian
    *  (x86 = little endian) al formato network endian
    *  (big endian).
    *
    *  Esempio:
    *  0x0806
    *  in RAM x86 = 06 08
    *  network    = 08 06
    *
    *  @host32 -> valore 32 bit in endian host
    *
    *  Return:
    *  valore convertito in network byte order
    */
    return switch_endian32(host32);
}


u32 ip_to_u32(u8 a, u8 b, u8 c, u8 d)
{
    return ((u32) a << 24) |
           ((u32) b << 16) |
           ((u32) c << 8)  |
           ((u32) d);
}
