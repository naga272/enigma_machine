#include "utilities/disk/streamer.h"
#include "utilities/memory/heap/malloc.h"


struct disk_stream* diskstreamer_new(i32 disk_id)
{
    struct disk* disk = disk_get(disk_id);

    if (!disk_id)
        return 0;

    struct disk_stream* streamer = kcalloc(sizeof(struct disk_stream));
    streamer->pos = 0;
    streamer->disk = disk;
    return streamer;
}


i32 diskstreamer_seek(struct disk_stream* stream, i32 pos)
{
    stream->pos = pos;
    return 0;
}


i32 diskstreamer_read(struct disk_stream* stream, void* out, i32 total)
{
    i32 sector = stream->pos / ENIGMAOS_SECTOR_SIZE;
    i32 offset = stream->pos % ENIGMAOS_SECTOR_SIZE;

    char buf[ENIGMAOS_SECTOR_SIZE];
    i32 res = disk_read_block(stream->disk, sector, 1, buf);
    
    if (res < 0) 
        return res;
    
    i32 total_to_read = total > ENIGMAOS_SECTOR_SIZE ? ENIGMAOS_SECTOR_SIZE : total;

    for (i32 i = 0; i < total_to_read; i++) {
        *(char*) out++ = buf[offset + i];
    }

    stream->pos += total_to_read;

    if (total > ENIGMAOS_SECTOR_SIZE)
        res = diskstreamer_read(stream, out, total - ENIGMAOS_SECTOR_SIZE);

    return res;
}


void diskstream_close(struct disk_stream* stream)
{
    kfree(stream);
}
