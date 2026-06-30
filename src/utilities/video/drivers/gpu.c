#include "utilities/video/drivers/gpu.h"
#include "utilities/video/drivers/virtio_gpu/virtio_gpu.h"
#include "utilities/video/kprintf.h"


MODULE_LICENSE("GPL-3.0");
MODULE_AUTHOR("naga272");
MODULE_DESCRIPTION("driver manager che si occupa di instradare ai driver corretti i dati ai gpuc");


extern pci_dev_list_t* gpus;
extern void print_hex(size_t);


#define IS_VIRTIO_GPU_CHIP(gpuc) (gpuc->vendor == 0x1AF4 && gpuc->device == 0x1050)


O3 ainline void init_gpus_driver(struct pci_device* gpuc)
{
    kprintf(
        "vendor: %p; device: %p; class_code: %p;",
        gpuc->vendor,
        gpuc->device,
        gpuc->class_code
    );

    if (IS_VIRTIO_GPU_CHIP(gpuc))
        init_virtio(gpuc);

    return;
}


O3 void init_gpu()
{
    print_hex(gpus->tot_num_device);
    for (size_t idx = 0; idx != gpus->tot_num_device; idx++)
        init_gpus_driver(&gpus->dev[idx]);

    return;
}
