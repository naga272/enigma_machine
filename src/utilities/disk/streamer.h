#ifndef DISKSTREAMER_H
#define DISKSTREAMER_H

#include "utilities/disk/disk.h"

/*
*  struct disk_stream
*  @pos -> posizione corrente dello stream espressa in byte rispetto
*          all'inizio del disco o della partizione letta
*  @disk -> puntatore alla struttura disk associata al disco da cui
*           leggere i dati
*
*  Rappresenta uno stream di lettura su un disco. La struct mantiene
*  il riferimento al disco da utilizzare e la posizione corrente da
*  cui iniziare la prossima lettura, permettendo di leggere dati in
*  modo sequenziale senza dover specificare ogni volta il settore e
*  l'offset manualmente.
*/
struct disk_stream {
    i32 pos;
    struct disk* disk;
};

struct disk_stream* diskstreamer_new(i32 disk_id);
i32 diskstreamer_seek(struct disk_stream* stream, i32 pos);
i32 diskstreamer_read(struct disk_stream* stream, void* out, i32 total);
void diskstreamer_close(struct disk_stream* stream);


extern struct disk_stream* diskstreamer_new(i32 disk_id);
extern i32 diskstreamer_seek(struct disk_stream* stream, i32 pos);
extern i32 diskstreamer_read(struct disk_stream* stream, void* out, i32 total);
extern void diskstreamer_close(struct disk_stream* stream);

#endif