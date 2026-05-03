#include "utilities/memory/heap/heap_creation.h"
#include "utilities/memory/heap/malloc.h"
#include "utilities/stdlib/stdlib.h"
#include "errors_no.h"


extern struct heap kernel_heap;
extern void print_hex(size_t num);


O3 static inline u32 heap_address_to_block(struct heap *heap, void* ptr)
{
    /* Funzione per ottenere il blocco gestito dal void* ptr */
    return ((u32) ptr - (u32) heap->saddr) / BLOCK_SIZE_HEAP;
}


u32 heap_block_to_address(struct heap* heap, u32 block)
{
    /*
    *  converte un numero di blocco in un indirizzo di memoria
    **/
    return (u32) heap->saddr + (block * BLOCK_SIZE_HEAP);
}


O3 static inline u32 heap_align_value_to_upper(u32 val)
{
    /*
    *   Allinea una dimensione multipla di BLOCK_SIZE_HEAP
    *   Restituisce numero bytes arrotondati (per eccesso o difetto)
    * **/
    if ((val % BLOCK_SIZE_HEAP) == 0)
        return val;

    val = (val - (val % BLOCK_SIZE_HEAP));
    val += BLOCK_SIZE_HEAP;
    return val;
}


static inline i32 heap_get_entry_type(HEAP_BLOCK_TABLE_ENTRY entry)
{
    return entry & 0x0f;
}


O3 i32 heap_get_start_block(struct heap* heap, u32 total_blocks)
{
    struct heap_table* table = heap->table;
    i32 bc = 0;
    i32 bs = -1;

    for (size_t i = 0; i < table->total; i++) {
        if (heap_get_entry_type(table->entry[i]) != HEAP_BLOCK_TABLE_ENTRY_FREE) {
            bc = 0;
            bs = -1;
            continue;
        }

        // If this is the first block
        if (bs == -1)
            bs = i;

        bc++;

        if (bc == total_blocks)
            break;
    }

    if (bs == -1)
        return -ENOMEM;

    return bs;

}



O3 static inline void heap_mark_blocks_taken(struct heap* heap, u32 start_block, u32 total_blocks_required)
{
    u32 last_block = start_block + total_blocks_required;

    if (total_blocks_required > 1)
        heap->table->entry[start_block] |= HEAP_BLOCK_IS_FIRST;

    for (size_t idx = start_block; idx != last_block; idx++) {
        heap->table->entry[idx] |= HEAP_BLOCK_TABLE_ENTRY_TAKEN;

        if (idx != last_block - 1)
            heap->table->entry[idx] |= HEAP_BLOCK_HAS_NEXT;
    }
}


O3 static inline void* heap_malloc_blocks(struct heap* heap, u32 total_blocks_required)
{
    void* address = 0;

    i32 start_block = heap_get_start_block(heap, total_blocks_required);

    if (start_block < 0)
        return address;
    
    address = (void*) heap_block_to_address(heap, start_block);
    heap_mark_blocks_taken(heap, start_block, total_blocks_required);

    return address;
}

/*
static inline void* heap_alloc(struct heap* heap, size_t size)
{
     Ogni data pool e' organizzato in questo modo:
    *  | HEADER | BODY |
    *  Vengono allocati oltre ai bytes richiesti dall'utente (BODY)
    *  4 bytes per ricordare quanti bytes sono stati richiesti (mi serve per
    *   la realloc()). Questa parte e' HEADER.
    * prima di restituire il blocco allocato sposto il ptr di 4 bytes in avanti
    * cosi' l'utente non modifica l'HEADER:
    *   | HEADER | BODY |
    *            ^
    *           ptr offset
    
    size_t header_size = sizeof(size_t);

    size_t total_size = size + header_size;

    size_t aligned = heap_align_value_to_upper(total_size);

    size_t blocks = aligned / BLOCK_SIZE_HEAP;

    void* raw = heap_malloc_blocks(heap, blocks);

    if (!raw)
        return NULL;

    size_t* header = (size_t*) raw;
    *header = size;

    return (void*) ((u8*)raw + header_size);
}
*/


O3 static inline void* heap_alloc(struct heap* heap, size_t size)
{
    u32 arrotonda_num_bytes = heap_align_value_to_upper(size);
    u32 total_blocks_required = arrotonda_num_bytes / BLOCK_SIZE_HEAP;

    return heap_malloc_blocks(heap, total_blocks_required);
}


O3 static inline void heap_mark_blocks_free(struct heap *heap, u32 num_block)
{
    /* il problema non richiede solo di liberare il blocco,
    ma anche quelli concatenati a lui */

    for (u32 idx = num_block; idx < heap->table->total; idx++) {
        heap->table->entry[idx] = HEAP_BLOCK_TABLE_ENTRY_FREE;

        if (heap->table->entry[idx] != HEAP_BLOCK_HAS_NEXT)
            break;
    }
}


O3 static inline void heap_free(struct heap* heap, void *addrs)
{
    heap_mark_blocks_free(
        heap,
        heap_address_to_block(heap, addrs)
    );
}


O3 void* kcalloc(size_t size)
{
    void *ptr = heap_alloc(&kernel_heap, size);
    return memset(ptr, 0, size);
}


O3 void* kmalloc(size_t size)
{
    return heap_alloc(&kernel_heap, size);
}


O3 void* krealloc(void* old_ptr, size_t old_size, size_t new_size)
{
    // mi serve in pci.c
    if (old_ptr == 0 || old_ptr == NULL)
        return heap_alloc(&kernel_heap, new_size);

    // da completare (caso in cui richiesta una grandezza minore)
    if (old_size > new_size)
        return NULL;

    char* tmp_old_ptr = (char*) old_ptr;
    char* new_ptr = heap_alloc(&kernel_heap, new_size);

    for (u32 idx = 0; idx < old_size; idx++)
        new_ptr[idx] = tmp_old_ptr[idx];

    kfree(old_ptr);

    return (void*) new_ptr;
}


O3 void kfree(void *address)
{
    heap_free(&kernel_heap, address);
}