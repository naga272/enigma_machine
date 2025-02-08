#ifndef CONFIG_H
#define CONFIG_H

#define KERNEL_CODE_SELECTOR 0x08
#define KERNEL_DATA_SELECTOR 0x10

#ifndef OS_TOTAL_INTERRUPTS
    #define OS_TOTAL_INTERRUPTS 512  // l'os ha 512 interrupts totali
#endif


#include <stdint.h>

typedef uint8_t u8;
typedef int8_t i8;

typedef uint16_t u16;
typedef int16_t i16;

typedef uint32_t u32;
typedef int32_t i32;

typedef unsigned char uchar;
#endif