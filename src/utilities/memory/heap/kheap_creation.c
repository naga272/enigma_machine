#include "utilities/memory/heap/kheap_creation.h"
#include "utilities/memory/heap/heap_creation.h"


struct heap         kernel_heap;
struct heap_table   kernel_heap_table;


extern void print_hex(uchar*);
extern void panic(uchar*);


void kheap_init()
{
    i32 total_table_entries = OS_HEAP_SIZE_BYTES / BLOCK_SIZE_HEAP;

    kernel_heap_table.entry = (HEAP_BLOCK_TABLE_ENTRY*) (OS_HEAP_TABLE_ADDRESS);
    kernel_heap_table.total = total_table_entries;

    void* end = (void*) (BASE_PTR_HEAP + OS_HEAP_SIZE_BYTES);

    i32 res = heap_create(&kernel_heap, (void*)(BASE_PTR_HEAP), end, &kernel_heap_table);
    if (res < 0)
        panic((uchar*) "Failed to create heap\n");
}
