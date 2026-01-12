
#include "utilities/disk/disk.h"
#include "utilities/io/io.h"


i32 disk_read_sector(i32 lba, i32 total, void* buf)
{
    outb(0x1F6, (lba >> 24) | 0xE0);
    outb(0x1F2, total);
    outb(0x1F3, (uchar)(lba & 0xff));
    outb(0x1F4, (uchar)(lba >> 8));
    outb(0x1F5, (uchar)(lba >> 16));
    outb(0x1F7, 0x20);

    uchar* ptr = (uchar*) buf;
    for (i32 b = 0; b < total; b++) {
        // Wait for the buffer to be ready
        char c = insb(0x1F7);
        while (!(c & 0x08))
            c = insb(0x1F7);

        // Copy from hard disk to memory
        for (int i = 0; i < 256; i++) {
            *ptr = insw(0x1F0);
            ptr++;
        }

    }
    return 0;
}
