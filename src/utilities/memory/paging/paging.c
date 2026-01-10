#include "utilities/memory/paging/paging.h"
#include "utilities/memory/heap/malloc.h"


static u32* current_directory = 0;


O3 static inline void init_page_table(u32* page_table, u32 offset, u8 flags)
{
    /* inizializza ogni voce puntata dalla page table */
    for (u32 i = 0; i < SIZE_PAGE_TABLE; i++)
        page_table[i] = (offset + (i * PAGING_SIZE_BLOCKS_ENTRY)) | flags;
}


O3 static inline struct paging_4gb_chunk* init_page_directory(u8 flags)
{
    /* 
    *   inizializza la tabella per la directory page
    *   directory Page[1024] -> Page Table[1024] -> 4096 bytes  
    * ** */
    struct paging_4gb_chunk* chunk = kcalloc(sizeof(struct paging_4gb_chunk));

    u32* directory = kcalloc(sizeof(u32) * SIZE_PAGE_DIRECTORY);

    u32 offset = 0;

    for (u32 idx = 0; idx < SIZE_PAGE_DIRECTORY; idx++) {

        // creo una tabella per ogni entry di directory
        u32* page_table = kcalloc(sizeof(u32) * SIZE_PAGE_TABLE);

        // per ogni tabella creata devo assegnare 1024 blocchi
        init_page_table(page_table, offset, flags);

        offset += PAGING_SIZE_BLOCKS_ENTRY * SIZE_PAGE_TABLE;

        directory[idx] = (u32) page_table | flags | PAGING_IS_WRITEABLE;
    }

    chunk->directory_entry = directory;
    chunk->flags = flags;

    return chunk;
}


O3 u32* __get_paging_directory(struct paging_4gb_chunk* self)
{
    return self->directory_entry;
}


O3 void __switch_directory(struct paging_4gb_chunk* self)
{
    paging_load_directory(self->directory_entry);
    current_directory = self->directory_entry;
}


O3 void __del_paging_directory(struct paging_4gb_chunk* self)
{
    for (u32 idx = 0; idx < SIZE_PAGE_DIRECTORY; idx++)
        kfree((void*) (self->directory_entry[idx] | self->flags | PAGING_IS_WRITEABLE));

    kfree(self->directory_entry);
    kfree(self);
}


struct paging_4gb_chunk* paging_new_4gb(u8 flags)
{
    struct paging_4gb_chunk* chunk = init_page_directory(flags);
    chunk->get_paging_directory = __get_paging_directory;
    chunk->switch_directory = __switch_directory;
    chunk->__del__ = __del_paging_directory;
    return chunk; 
}
