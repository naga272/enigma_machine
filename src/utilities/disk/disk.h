#ifndef DISK_H
#define DISK_H

#include "config.h"

#define ATA_DATA        0x1F0
#define ATA_ERROR       0x1F1
#define ATA_SECCOUNT    0x1F2
#define ATA_LBA_LOW     0x1F3
#define ATA_LBA_MID     0x1F4
#define ATA_LBA_HIGH    0x1F5
#define ATA_DRIVE       0x1F6
#define ATA_STATUS      0x1F7
#define ATA_COMMAND     0x1F7

#define ATA_BSY 0x80
#define ATA_DRQ 0x08
#define ATA_ERR 0x01

#define READ_SECTOR  0x20
#define WRITE_SECTOR 0x30
#define ATA_FLUSH 0xE7

#define MAGIC_WORD_SECT_128 (uchar*) "EnigmaOs"
#define LEN_MAGIC_WORD_SECT_128 9

extern i32 disk_read_sector(i32 lba, i32 total, void* buf);
i32 disk_read_sector(i32 lba, i32 total, void* buf);


extern i32 disk_write_sector(i32 lba, i32 total, void* buf);
i32 disk_write_sector(i32 lba, i32 total, void* buf);


#endif
