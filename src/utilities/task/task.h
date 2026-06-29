#ifndef TASK_H
#define TASK_H

#include "config.h"
#include "utilities/memory/paging/paging.h"


struct registers {
    u32 edi;
    u32 esi;
    u32 ebp;
    u32 ebx;
    u32 edx;
    u32 ecx;
    u32 eax;

    u32 ip;
    u32 cs;
    u32 flags;
    u32 esp;
    u32 ss;
};


struct task {
    // page directory del signolo task
    struct paging_4gb_chunk* page_directory;

    // registers del singolo task
    struct registers registers;

    // next task da eseguire
    struct task* next;

    // precedente task da eseguire
    struct task* prev;
};


extern struct task* task_new();
extern i32 task_init(struct task* task);
extern i32 task_free(struct task* task);
extern struct task* get_next_task();

#endif