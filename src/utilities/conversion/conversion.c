#include "config.h"
#include "utilities/conversion/conversion.h"


u16 switch_endian16(u16 nb)
{
    return (nb >> 8) | (nb << 8);
}


u32 switch_endian32(u32 nb)
{
    return ((nb >> 24) &0xff)       |
            ((nb << 8) &0xff0000)   |
            ((nb >> 8) &0xff00)     |
            ((nb << 24) &0xff000000);

}