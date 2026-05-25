#ifndef CONFIG_H
#define CONFIG_H

#include <stdint.h>
#include <stddef.h>
#include "errors_no.h"

#define EXIT_SUCCESS 0x00

#define KERNEL_CODE_SELECTOR 0x08

#define KERNEL_DATA_SELECTOR 0x10

// idt
#define OS_TOTAL_INTERRUPTS 512  // l'os ha 512 interrupts totali

#define SIZE_COMMAND_SHELL 2048

typedef uint64_t u64;
typedef int64_t i64;

typedef uint32_t u32;
typedef int32_t i32;

typedef uint16_t u16;
typedef int16_t i16;

typedef uint8_t u8;
typedef int8_t i8;

typedef unsigned char uchar;
typedef unsigned short ushort;


#ifndef O3
#define O3 __attribute__((optimize("O3")))
#endif

#ifndef ainline
#define ainline __attribute__((always_inline))
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
#define FASE_SETUP (flag_x_colour_shell == 0)
#endif

#define CHAR_END_PHRASE(x)  (x == '\n')
#define CHAR_BACKSPACE(x)   (x == '\b')

#define SIZEOFARR(x) (sizeof(x) / sizeof(x[0]))


// filesystems

#define ENIGMAOS_SECTOR_SIZE 512

#define KERNEL_FS_MAX_PATH 108

#define ENIGMAOS_MAX_FILESYSTEMS 12

#define ENIGMAOS_MAX_FILE_DESCRIPTORS 512


// gestione processi e gdt

#define ENIGMAOS_TOTAL_GDT_SEGMENTS 6

#define PROGRAM_VIRTUAL_ADDR 0x400000

#define PROGRAM_USER_ADDR_STACK_SIZE 1024 * 16

#define PROGRAM_VIRTUAL_ADDR_STACK_START 0x3ff000

#define PROGRAM_VIRTUAL_STACK_ADDR_END PROGRAM_VIRTUAL_STACK_ADDR_START - PROGRAM_USER_ADDR_STACK_SIZE

#define USER_DATA_SEGMENT 0x400000

#define USER_CODE_SEGMENT 0x1b

#define MAX_PROGRAM_ALLOCATION 1024

#define MAX_PROCESS_X_QUEUE 12

#endif