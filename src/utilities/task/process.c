#include "errors_no.h"
#include "utilities/stdlib.h"
#include "utilities/memory/heap/heap.h"
#include "utilities/task/process.h"
#include "utilities/task/task.h"


/*
* Gestisce la creazione e inizializzazione di un processo.
* Mantiene il puntatore al processo corrente e una coda globale
* di processi schedulabili.
*
* Permette di:
*   - inizializzare una struct process
*   - ottenere il processo corrente
*   - recuperare un processo dato il PID/slot
*   - caricare i dati binari di un processo
*   - creare un nuovo processo in uno slot libero
*
* process_load_for_slot() alloca la struttura del processo,
* verifica che lo slot sia disponibile, inizializza il processo
* e prepara il caricamento del binario e delle struct.
*
* NB: In coda nello schduler ci possono stare max 12 processi
*/


struct process* current_process = 0;
struct process* scheduler[MAX_PROCESS_X_QUEUE] = {0};


O3 ainline void process_init(struct process* process)
{
    memset(process, 0x00, sizeof(struct process));
}


O3 struct process* get_current_process()
{
    return current_process;
}


O3 i32 process_get(i32 pid)
{
    if (pid < 0 || pid >= MAX_PROCESS_X_QUEUE)
        return -EINVARG;

    return scheduler[pid];
}


O3 ainline i32 process_load_binary(const char* filename, struct process* process)
{
    i32 res = 0;
    return res;
}


O3 ainline i32 process_load_data(const char* filename, struct process* process)
{
    i32 res = 0;
    res = process_load_binary(filename, process);
    return res;
}


O3 i32 process_load_for_slot(const char* filename, struct process** process, i32 process_slot)
{
    // process_slot e' l'idx di MAX_PROCESS_X_QUEUE
    i32 res = 0;
    struct task* task = 0;
    struct process* __init__;
    void* program_stack_ptr = 0;

    // se lo slot e' gia' occupato, non posso prenderlo
    // error EISTKN = error impossible taken
    if (process_get(process_slot) != 0)
        return -EISTKN;
    
    __init__ = kcalloc(sizeof(struct process));

    if (!__init__)
        return -ENOMEM;
    
    process_init(__init__);
    res = process_load_data(filename, __init__);

    if (res < 0)
        return res;

    return res;
}
