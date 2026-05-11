#include "utilities/task/task.h"
#include "utilities/memory/heap/malloc.h"
#include "utilities/stdlib/stdlib.h"
#include "errors_no.h"


/*
* gestione della creazione e distruzione delle task.
*
* Tiene memorizzata:
*   - la task attualmente in esecuzione
*   - la testa e la coda della lista delle task
*
* Consente di:
*   - ottenere la task corrente
*   - ottenere la task successiva per lo scheduler
*   - rimuovere una task dalla lista
*   - liberare memoria e page directory di una task
*   - inizializzare una nuova task con stack, registri e paging
*   - creare una nuova task e aggiungerla alla lista globale
*
* Ogni task ha un contesto di esecuzione indipendente:
* registri CPU, stack, instruction pointer e page directory.
*/


struct task* current_task = 0;
struct task* task_tail = 0;
struct task* task_head = 0;


O3 struct task* task_current()
{
    /* get current task */
    return current_task;
}


O3 struct task* get_next_task()
{
    if (!current_task->next)
        return task_head;
    
    return current_task->next;
}


O3 static inline ainline void task_list_remove(struct task* task)
{
    if (task->prev)
        task->prev->next = task->next;

    if (task == task_head)
        task_head = task->next;

    if (task == task_tail)
        task_tail = task->prev;

    if (task == current_task)
        current_task = get_next_task();
}


O3 int task_free(struct task* task) 
{
    task->page_directory->__del__(task->page_directory);
    task_list_remove(task);
    kfree(task);
    return 0;
}


O3 int task_init(struct task* task)
{
    memset(task, 0, sizeof(struct task));
    // remap di tutti i 4 gb del task
    task->page_directory = paging_new_4gb(
        PAGING_IS_PRESENT | PAGING_ACCESS_FROM_ALL
    );

    if (!task->page_directory)
        return -EIO;

    task->registers.ip = PROGRAM_VIRTUAL_ADDR;
    task->registers.ss = USER_DATA_SEGMENT;
    task->registers.esp = PROGRAM_VIRTUAL_ADDR_STACK_START;

    return 0;
}


O3 struct task* task_new()
{
    int res = 0;
    struct task* task = kcalloc(sizeof(struct task));
    
    if (!task)
        return (struct task*) -ENOMEM;

    res = task_init(task);

    if (res != EXIT_SUCCESS) {
        task_free(task);
        return (struct task*) -EIO;
    }

    if (task_head == 0) {
        task_head = task;
        task_tail = task;
    }

    task_tail->next = task;
    task_tail->prev = task_tail;
    task_tail = task;

    return task;
}
