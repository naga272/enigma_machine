#ifndef DISK_H
#define DISK_H

#include "config.h"

#define ENIGMAOS_DISK_TYPE_REAL 0

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


#define USER_TABLE_LBA 128
#define USER_MAGIC 0x55534552

// typedef u32 ENIGMAOS_DISK_TYPE;

;
struct disk{
    // rappresenta l'hard disk
    u32 type;
    i32 sector_size;
};

/*
struct superblock {
    // settore 0
    u32 magic;              // magic number
    u32 version;
    u32 first_data_lba;
};

*/

;
struct user_entry {
    char username[32];
    u8 password[32];
    char actual_color_terminal;
};


struct user_table {
    uint32_t magic;
    uint32_t count;
    struct user_entry user;
};


extern i32 disk_write_sector(i32 lba, i32 total, void* buf);
extern i32 disk_read_sector(i32 lba, i32 total, void* buf);
extern void disk_search_and_init();
// extern struct disk* disk_get(i32);
// extern i32 disk_read_block(struct disk*, i32, i32, void*);


#endif