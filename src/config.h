#ifndef CONFIG_H
#define CONFIG_H

#include <stdint.h>
#include <stddef.h>
#include "errors_no.h"

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

#ifndef ENIGMAOS_SECTOR_SIZE
#define ENIGMAOS_SECTOR_SIZE 512
#endif

typedef uint32_t u32;
typedef int32_t i32;

typedef uint16_t u16;
typedef int16_t i16;

typedef uint8_t u8;
typedef int8_t i8;

typedef unsigned short ushort;
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

/* STANDARD COLOR */
#define NERO            0
#define BLU             1
#define VERDE           2
#define CIANO           3
#define ROSSO           4
#define VIOLA           5
#define MARRONE         6
#define GRIGIO          7
#define GRIGIO_SCURO    8
#define BLU_CHIARO      9
#define VERDE_CHIARO    10
#define CIANO_CHIARO    11
#define ROSSO_CHIARO    12
#define VIOLA_CHIARO    13
#define GIALLO          14
#define BIANCO          15

#define BG_GC_C_GC(BG, C)   ((BG << 4)       | C)
#define BG_BLU_C_WHITE      ((BLU << 4)      | BIANCO)
#define BG_BIANCO_C_NERO    ((BIANCO << 4)   | NERO)
#define BG_NERO_C_BIANCO    ((NERO << 4)     | BIANCO) 
#define BG_NERO_C_VERDE     ((NERO << 4)     | VERDE)

#ifndef FASE_SETUP
#define FASE_SETUP (not_setup_finish == 0)
#endif

#define CHAR_END_PHRASE(x)  (x == '\n')
#define CHAR_BACKSPACE(x)   (x == '\b')

#define SIZEOFARR(x) (sizeof(x) / sizeof(x[0]))

#endif