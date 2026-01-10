#include "utilities/memory/heap/kheap_creation.h"
#include "utilities/memory/heap/heap_creation.h"


struct heap         kernel_heap;
struct heap_table   kernel_heap_table;


void kheap_init()
{
    /* inizializzo l'heap per il kernel*/
    kernel_heap_table.entry = (HEAP_BLOCK_TABLE_ENTRY*) OS_HEAP_TABLE_ADDRESS;
    kernel_heap_table.total = OS_HEAP_SIZE_BYTES / BLOCK_SIZE_HEAP;

    /* l'inizializzazione di kernel_heap viene fatta dentro heap_create foo*/
    heap_create(
        &kernel_heap,
        BASE_PTR_HEAP,
        BASE_PTR_HEAP + OS_HEAP_SIZE_BYTES,
        &kernel_heap_table
    );
}
