#ifndef HEAP_H
#define HEAP_H

#include "config.h"
#include "errors_no.h"

// start heap memory
#define BASE_PTR_HEAP           ((void*) 0x1000000)
#define BLOCK_SIZE_HEAP         4096
#define OS_HEAP_SIZE_BYTES      104857600   // 100 MB

// costanti che rappresentano lo stato di un blocco di memoria nella tabella degli heap. 
// Un blocco puo' essere occupato o libero
#define HEAP_BLOCK_TABLE_ENTRY_TAKEN 0x01
#define HEAP_BLOCK_TABLE_ENTRY_FREE 0x00

// flag che utilizzo per capire se un blocco ha un blocco successivo oppure e' il primo
#define HEAP_BLOCK_HAS_NEXT  0b100000000
#define HEAP_BLOCK_IS_FIRST  0b010000000

#define OS_HEAP_TABLE_ADDRESS   0x07E00


// rappresenta una voce della tabella degli heap
typedef unsigned char HEAP_BLOCK_TABLE_ENTRY;


struct heap_table{
    /*
    * struct heap_table rappresenta la tabella degli heap.
    * Tiene traccia di come è messo ogni blocco di memoria nell'heap pool 
    * (quindi se il blocco e' libero o occupato, se fa parte di una sequenza, etc...).
    *   @entries:   ogni voce rappresenta un blocco di memoria nell'heap pool.
    *   @total:     numero totali di voci
    */
    HEAP_BLOCK_TABLE_ENTRY* entry;
    size_t total;
};


struct heap{
    struct heap_table* table;
    void *saddr;
};


extern i32 heap_create(struct heap* obj_heap, void *start_address, void *end_address, struct heap_table* table);
i32 heap_create(struct heap* obj_heap, void *start_address, void *end_address, struct heap_table* table);

#endif
