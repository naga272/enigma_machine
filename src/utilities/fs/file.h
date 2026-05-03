#ifndef FILE_H
#define FILE_H

#include "config.h"
#include "utilities/fs/pparser.h"


typedef u32 FILE_SEEK_MODE;


enum {
    SEEK_SET,
    SEEK_CUR,
    SEEK_END
};

typedef u32 FILE_MODE;

enum {
    FILE_MODE_READ,
    FILE_MODE_WRITE,
    FILE_MODE_APPEND,
    FILE_MODE_INVALID,
};

struct disk;
typedef void* (*FS_OPEN_FUNCTION)(struct disk* disk, struct path_part* path, FILE_MODE mode);
typedef i32 (*FS_RESOLVE_FUNCTION)(struct disk* disk);


struct filesystem {
    // il filesystem return 0 se il disco struct disk* disk e' per lui
    FS_RESOLVE_FUNCTION resolve;
    FS_OPEN_FUNCTION open;

    char name[20];
};


struct file_descriptor {
    i32 index;
    struct filesystem* filesystem;
    void* private;

    struct disk* disk;
};


void fs_init();
i32 fopen(const char* filename, const char* mode);
void fs_insert_filesystem(struct filesystem*);

struct filesystem* fs_resolve(struct disk* disk);

#endif