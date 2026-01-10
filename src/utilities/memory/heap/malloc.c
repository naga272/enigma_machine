#include "utilities/memory/heap/heap_creation.h"
#include "utilities/memory/heap/malloc.h"
#include "errors_no.h"


extern struct heap kernel_heap;


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


O3 static inline i32 heap_get_start_block(struct heap* heap, u32 total_blocks_required)
{
    /* cerca @total_blocks_required consecutivi liberi restituendo l'offset del primo blocco */
    i32 offset_entry = -ENOMEM;
    u32 tmp_total_blocks_required = total_blocks_required;

    for (size_t idx = 0; idx <= heap->table->total; idx++) {
        if (tmp_total_blocks_required == 0)
            break;

        if (heap->table->entry[idx] != HEAP_BLOCK_TABLE_ENTRY_FREE) {
            tmp_total_blocks_required = total_blocks_required;
            offset_entry = -ENOMEM;     /* ripristina il valore */
            continue;
        }

        if (offset_entry == -ENOMEM)
            offset_entry = idx;

        tmp_total_blocks_required--;
    }
    /*
    *   Caso in cui offset == idx ma comunque non e' stato sufficiente
    *   per il num blocks richiesti
    * **/
    return (tmp_total_blocks_required == 0)? offset_entry : -ENOMEM;
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


O3 static inline void *heap_malloc_blocks(struct heap* heap, u32 total_blocks_required)
{
    void* address = 0;

    u32 start_block = heap_get_start_block(heap, total_blocks_required);

    if (start_block < 0)
        return address;
    
    address = (void*) heap_block_to_address(heap, start_block);
    heap_mark_blocks_taken(heap, start_block, total_blocks_required);

    return address;
}


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


O3 void* kmalloc(size_t size)
{
    return heap_alloc(&kernel_heap, size);
}


O3 void kfree(void *address)
{
    heap_free(&kernel_heap, address);
}
