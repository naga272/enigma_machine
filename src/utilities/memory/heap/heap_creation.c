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

O3 static inline i32 heap_validate_table(struct heap_table* table, void* start_address, void* end_address)
{
    /*
    * Verifico che lo spazio richiesto sia valido
    * **/
    size_t total_blocks = (size_t) (end_address - start_address);
    if (total_blocks != table->total) {
        return -EINVARG;
    }
    return 0;
}


O3 static inline i32 heap_validate_alignment(void* ptr)
{
    /*
    *   Verifica allineamento del blocco.
    *   Se non è allineato rischio che escono fuori dei blocchi grandi != 4096,
    *   (nel kernel porta a comportamenti indefinitim, invece in userland seg. fault)  
    * * */
    return ((u32) ptr % OS_HEAP_SIZE_BYTES) == 0;
}


O3 i32 heap_create(struct heap* obj_heap, void *start_address, void *end_address, struct heap_table* table)
{
    /* inizializza la zona dell'heap + inizializza le voci per ogni processo */

    if (!heap_validate_alignment(start_address) || !heap_validate_alignment(end_address))
        return -EINVARG;

    memset(obj_heap, 0, sizeof(struct heap));

    obj_heap->table = table;
    obj_heap->saddr = start_address;

    i32 res = heap_validate_table(table, start_address, end_address);

    if (res < 0)
        return res;

    // puslisco tutto il contenuto del blocco (i dati nel blocco dopo la free rimangono)
    size_t table_size = sizeof(HEAP_BLOCK_TABLE_ENTRY) * table->total;
    memset(table->entry, HEAP_BLOCK_TABLE_ENTRY_FREE, table_size);

    return 0;
}
