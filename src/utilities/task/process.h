#ifndef PROCESS_H
#define PROCESS_H


#include "config.h"
#include "utilities/task/task.h"


struct process {
    u16 pid;
    char filename[KERNEL_FS_MAX_PATH];

    struct task* task;

    // memory x malloc
    void* allocations[MAX_PROGRAM_ALLOCATION];

    // ptr fisico al processo in memoria
    void *ptr;

    // ptr stack memory
    void* stack;

    // size data puntati da @ptr
    u32 size;
};

#endif