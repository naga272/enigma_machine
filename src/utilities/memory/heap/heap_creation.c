#include "utilities/memory/heap/heap_creation.h"
#include "utilities/stdlib/stdlib.h"


/* CREAZIONE HEAP PER PROGRAMMA GENERICO */

/*
*   heap gestito tramite algoritmo Slab allocator.
*   Consiste in suddividere la zona heap (0x1000000 a 0xC000000)
*   in blocchi da 4096 bytes.
*   Quando con una malloc / calloc vengono richiesti tipo 50 bytes,
*   Il kernel deve trovare il primo blocco libero dell'heap che soddisfa lo spazio
*   di 50 bytes, tracciare quel blocco come occupato.
*   Una chiamata a kmalloc o kcalloc viene detta anche data pool.
*   Quando non abbiamo piu' bisogno di quel blocco possiamo chiamare la funzione kfree(),
*   che si occupa di liberare un determinato blocco (in modo da essere usabile da altri programmi)
*   Questo modulo e' usabile per l'inizializzazione di qualunque processo
*/

static inline ainline i32 heap_validate_table(void* ptr, void* end, struct heap_table* table)
{
    i32 res = 0;

    size_t table_size = (size_t) (end - ptr);
    size_t total_blocks = table_size / BLOCK_SIZE_HEAP;

    if (table->total != total_blocks) {
        res = -EINVARG;
        goto out;
    }

out:
    return res;
}


O3 static inline ainline i32 heap_validate_alignment(void* ptr)
{
    /*
    *   Verifica allineamento del blocco.
    *   Se non è allineato rischio che escono fuori dei blocchi grandi != 4096,
    *   (nel kernel porta a comportamenti indefinitim, invece in userland seg. fault)  
    * * */
    return ((u32) ptr % BLOCK_SIZE_HEAP) == 0;
}


i32 heap_create(struct heap* heap, void* ptr, void* end, struct heap_table* table)
{
    i32 res = 0;

    if (!heap_validate_alignment(ptr) || !heap_validate_alignment(end)) {
        res = -EINVARG;
        goto out;
    }

    memset(heap, 0, sizeof(struct heap));
    heap->saddr = ptr;
    heap->table = table;

    res = heap_validate_table(ptr, end, table);
    if (res < 0)
        goto out;

    size_t table_size = sizeof(HEAP_BLOCK_TABLE_ENTRY) * table->total;
    memset(table->entry, HEAP_BLOCK_TABLE_ENTRY_FREE, table_size);

out:
    return res;
}
