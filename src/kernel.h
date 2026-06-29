#ifndef KERNEL_H
#define KERNEL_H

#include "config.h"
#include "utilities/io/io.h"
#include "utilities/stdlib/stdlib.h"
#include "utilities/string/string.h"
#include "utilities/video/video.h"
#include "utilities/memory/heap/kheap_creation.h"
#include "utilities/memory/paging/paging.h"
#include "utilities/idt/idt.h"
#include "utilities/idt/body_int/slave/rtc_orologio.h"

#include "utilities/setup/setup.h"
#include "utilities/book/book.h"
#include "utilities/markov/markov.h"
#include "utilities/gdt/gdt.h"

#include "utilities/disk/disk.h"
#include "utilities/disk/streamer.h"
#include "utilities/fs/pparser.h"
#include "utilities/fs/file.h"

#include "utilities/shell/command.h"
#include "utilities/pci/pci.h"
#include "utilities/net/net.h"
#include "utilities/net/ethernet/arp/arp.h"

#include "utilities/video/kprintf.h"


extern void test_int80h(void);

extern volatile uchar tmp_char_container;
extern uchar* magic_num_sec_config;
extern u8 is_ended_setup;

static struct paging_4gb_chunk *kernel_directory = 0;
struct book* b;

extern pci_dev_list_t* nics;

void kernel_main();


#define CASE_CHAR_WRITTEN                       \
    gestisci_char_to_write(tmp_char_container); \
    tmp_char_container = 0

#endif