#ifndef CONFIG_H
#define CONFIG_H

#ifndef KERNEL_CODE_SELECTOR
#define KERNEL_CODE_SELECTOR 0x08
#endif

#ifndef KERNEL_DATA_SELECTOR
#define KERNEL_DATA_SELECTOR 0x10
#endif

#ifndef OS_TOTAL_INTERRUPTS
#define OS_TOTAL_INTERRUPTS 512  // l'os ha 512 interrupts totali
#endif

#ifndef SIZE_COMMAND_SHELL
#define SIZE_COMMAND_SHELL 2048
#endif

#include <stdint.h>

typedef uint8_t u8;
typedef int8_t i8;

typedef uint16_t u16;
typedef int16_t i16;

typedef uint32_t u32;
typedef int32_t i32;

typedef unsigned char uchar;

#ifndef O3
#define O3 __attribute__((optimize("O3")))
#endif

#ifndef KERR
#define KERR "<0>"
#endif

#ifndef KWARN
#define KWARN "<1>"
#endif

#ifndef KINFO
#define KINFO "<2>"
#endif

#ifndef KDBG
#define KDBG "<3>"
#endif

#endif