#ifndef CONFIG_H
#define CONFIG_H

#define KERNEL_CODE_SELECTOR 0x08
#define KERNEL_DATA_SELECTOR 0x10

#ifndef OS_TOTAL_INTERRUPTS
    #define OS_TOTAL_INTERRUPTS 512  // l'os ha 512 interrupts totali
#endif


#endif