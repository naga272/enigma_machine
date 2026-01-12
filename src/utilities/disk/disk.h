#ifndef DISK_H
#define DISK_H

#include "config.h"

extern i32 disk_read_sector(i32 lba, i32 total, void* buf);
i32 disk_read_sector(i32 lba, i32 total, void* buf);


#endif
