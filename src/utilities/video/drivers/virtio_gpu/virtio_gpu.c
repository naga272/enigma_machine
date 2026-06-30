#include "utilities/video/drivers/virtio_gpu/virtio_gpu.h"
#include "utilities/memory/heap/malloc.h"
#include "utilities/video/kprintf.h"
#include "utilities/string/string.h"


MODULE_LICENSE("GPL-3.0");
MODULE_AUTHOR("naga272");
MODULE_DESCRIPTION("driver per la gestione e configurazione dei dispositivi virtio");


extern pci_dev_list_t* gpus;

// lo uso per debug
extern void set_message_x_panic(uchar* msg);


void init_virtio(struct pci_device* gpu)
{
    kprintf(
        "bar 0: %p\nbar 1: %p\n",
        gpu->bar[0].addr,
        gpu->bar[1].addr
    );

    virtio_gpu_t* virtio = kcalloc(sizeof(virtio_gpu_t));

    if (!virtio)
        set_message_x_panic((uchar*) "Error, impossibile allocare memoria per la gpu");

    gpu->priv = (void*) virtio;
}
