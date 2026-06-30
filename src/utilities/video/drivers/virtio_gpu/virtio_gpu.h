#ifndef VIRTIO_GPU_H
#define VIRTIO_GPU_H

#include "config.h"
#include "utilities/pci/pci.h"


extern void init_virtio(struct pci_device*);
void init_virtio(struct pci_device*);


struct virtq_desc {
    u64 addr;
    u32 len;
    u16 flags;
    u16 next;
};


typedef struct virtio_gpu {

    u64 common_cfg;
    u64 notify_cfg;
    u64 isr_cfg;
    u64 device_cfg;

    struct virtq_desc *desc;

    u16 queue_size;

    void* framebuffer;

    u32 width;
    u32 height;


} virtio_gpu_t;


#endif
