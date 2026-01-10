#ifndef PAGING_H
#define PAGING_H

#include "config.h"


#define PAGING_CACHE_DISABLED  0b00010000
#define PAGING_WRITE_THROUGH   0b00001000
#define PAGING_ACCESS_FROM_ALL 0b00000100
#define PAGING_IS_WRITEABLE    0b00000010
#define PAGING_IS_PRESENT      0b00000001


#define SIZE_PAGE_DIRECTORY 1024
#define SIZE_PAGE_TABLE 1024
#define PAGING_SIZE_BLOCKS_ENTRY 4096

struct paging_4gb_chunk {
    u32* directory_entry;
    u8 flags;
    u32* (*get_paging_directory) (struct paging_4gb_chunk*);
    void (*switch_directory) (struct paging_4gb_chunk*);
    void (*__del__) (struct paging_4gb_chunk*);
};

struct paging_4gb_chunk* paging_new_4gb(u8 flags);
extern void paging_load_directory(u32* directory);
extern void enable_paging();

#endif